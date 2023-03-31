#include <iostream>
#include "simulator.h"
#include "simu_shard.h"


#define VIZ_SECTION_BEGIN(tag)	if(_ScriptVizEnabled)													\
										{	auto __section_scope = _ScriptVizJson.ScopeAppendingElement();		\
											_ScriptVizJson.Object( (( J(type) = tag )) );	\
											auto __section_body = _ScriptVizJson.ScopeAppendingKey("content");	

#define VIZ_QUERY_SECTION_BEGIN(tag, cmd)	if(_ScriptVizEnabled)													\
										{	auto __section_scope = _ScriptVizJson.ScopeAppendingElement();		\
											_ScriptVizJson.Object( (( J(type) = tag ),(J(command) = cmd)) );	\
											auto __section_body = _ScriptVizJson.ScopeAppendingKey("content");

#define VIZ_SECTION_END						_ScriptVizSectionNum++; }

static const constexpr char* PREDA_DATA_FOLDER = "/.preda/";

namespace oxd
{
void StandardOutWriter(LPCSTR log, int type, LPVOID cookie)
{
	std::string str(log);
	std::cout << log << std::endl << std::flush;
}

int SimulatorMain(const os::CommandLine& cmd)
{
	rt::String lockPath;
#ifdef _DEBUG
	os::EnableCrashDump("chsimu.dmp", true);
#endif
	if(cmd.HasOption("stdout"))
		os::_details::SetConsoleLogWriteFunction(StandardOutWriter, nullptr);
#if defined(PLATFORM_WIN)
	const char* homeDir = getenv("HOMEPATH");
#else
	const char* homeDir = getenv("HOME");
#endif
	rt::String predaHomePath = rt::SS(homeDir, strlen(homeDir)) + rt::String(PREDA_DATA_FOLDER);
	lockPath = predaHomePath + ".preda_lock";
	os::File lockfile(lockPath, "a+b", true);
	if(!lockfile.IsOpen())
	{
		_LOG("Unable to create lockfile: " << lockPath);
		return 1;
	}
	else if(!lockfile.Lock())
	{
		_LOG("Another chain simulator is runnig. Please wait until the other job is finished");
		return 1;
	}
	if(cmd.GetTextCount() == 0)
	{
		_LOG("chsimu input_file.(prd|sol|prdts) [-async] [-perftest] [-order:n] [-viz:output_filename] [-viz_templ:webui_template_path]");
		return 1;
	}

	if(cmd.HasOption("log"))
	{
		rt::String defaultLogPath = predaHomePath + "outputs.log";
		rt::String_Ref log = cmd.GetOption("log", defaultLogPath);
		os::SetLogFile(ALLOCA_C_STRING(log), false);
	}

	{	Simulator sim;
		uint32_t order = 2;
		if (cmd.HasOption("order"))
		{
			rt::String order_str = cmd.GetOption("order");
			if (!order_str.HasOnlyNumbers() || order_str.ToNumber(order) < 0)
			{
				_LOG("[PRD]: Invalid Shard Order input. It must be a positive integer greater than zero.")
				return 1;
			}
		}

		bool viz_to_console = !(cmd.HasOption("viz") && cmd.HasOption("viz_templ"));
		if(sim.Init(cmd.GetOptionAs<uint32_t>("order", 2), cmd.HasOption("async"), cmd.HasOption("WASM"), viz_to_console))
		{
			os::SetProcessPriority(os::PROCPRIO_HIGH);

			rt::String_Ref script = cmd.GetText(0);
			rt::Buffer<rt::String_Ref> fnArr;
			for (uint32_t i = 0; i < cmd.GetTextCount(); i++)
			{
				fnArr.push_back(cmd.GetText(i));
			}
			sim.Run(fnArr);
		}

		if(!viz_to_console)
		{
			sim.ExportVizHtml(cmd.GetOption("viz_templ"), cmd.GetOption("viz"));
		}
	}
	lockfile.Unlock();
	lockfile.Close();
	//os::_details::DumpTrackedMemoryAllocation();
	return 0;
}

Simulator::Simulator()
	:_ScriptRand(19)
	,_ScriptEnv(*this)
	,LineNum(0)
	,_VizToConsole(true)
{
	rt::Zero(_Engines);
}

void Simulator::CreateExecuteUnit(ExecuteUnit* out) const
{
	for(int i=0; i<sizeofArray(_Engines); i++)
	{
		_SafeRelease(out->pUnits[i]);

		auto& e = _Engines[i];
		if(e.pEngine)
		{
			out->pUnits[i] = e.pEngine->CreateExecuteUnit();
		}
	}
}

bool Simulator::CompleteShardExecution()
{
	if(os::AtomicIncrement(&_iShardsExecuted) == (int)_Shards.GetSize())
	{
		os::AtomicAdd(-(int32_t)_Shards.GetSize(), &_iShardsExecuted);
		return true;
	}

	return false;
}

bool Simulator::_InitEngine(rvm::EngineId eng, const char* dll_name, const char* repo, const char* engine_config)
{
	auto& ee = _Engines[(int)eng];
	ASSERT(ee.pEngine == nullptr);

	os::File::RemovePath(repo);

	ee.hModule = os::LoadDynamicLibrary(dll_name);
	if(ee.hModule)
	{
		auto factory = (rvm::GetEngineFunctionType)os::GetDynamicLibrarySymbol(ee.hModule, rvm::GetEngineFunctionName());
		if(factory)
		{
			os::File::CreateDirectories(repo, false);

			ee.pEngine = factory(engine_config);
			rvm::ConstString initErrorMsg = { nullptr, 0 };
			if(ee.pEngine && ee.pEngine->Initialize(ALLOCA_C_STRING(rt::String_Ref(dll_name).GetFilePath()), repo, this, &initErrorMsg))
			{
				_LOG_HIGHLIGHT("Execution Engine Initialized, <"<<ee.pEngine->GetName().Str()<<"> v"<<ee.pEngine->GetVersion().Str()<<", "<<ee.pEngine->GetVendorInfo().Str());
				_LOG("Repository: "<<repo<<", Module: "<<dll_name<<" ("<<rt::EnumStringify(eng)<<")\n");
				return true;
			}
			else
			{
				_LOG_ERROR("Failed to initialized PREDA engine, db path: " << repo);
				if(initErrorMsg.StrPtr)
					_LOG_WARNING("Failed to initialize: "<<initErrorMsg.Str());
			}
		}
		else
		{
			_LOG_WARNING("Unable to load engine export symbol")
		}
	}
	else
	{
		_LOG_WARNING("Unable to load engine module")
	}

	_LOG_WARNING("Failed to mount execution engine: "<<dll_name<<" ("<<rt::EnumStringify(eng)<<") with repository in "<<repo<<'\n');
	return false;
}


bool Simulator::Init(uint32_t shard_order, bool async_shard, bool defaultWASM, bool viz_to_console)
{
	_bChainStepping = true;
	_bShardAsync = async_shard;
	_iShardsExecuted = 0;
	_ScriptVizEnabled = os::CommandLine::Get().HasOption("viz");
	_VizToConsole = viz_to_console;
	_DefaultRTMode = defaultWASM ? "WASM" : "Native";
	rt::String repo_dir("./chsimu_repo");
#if defined(PLATFORM_WIN)
	char* homeDir = getenv("HOMEPATH");
#else
	char* homeDir = getenv("HOME");
#endif

	repo_dir = rt::SS(homeDir, strlen(homeDir)) + PREDA_DATA_FOLDER + "chsimu_repo";
	os::File::RemovePath(repo_dir);

	_LOG("Physical CPU core: "<<os::GetNumberOfPhysicalProcessors()<<", Logic CPU core: "<<os::GetNumberOfProcessors());

	int engine = 0;
	if(_InitEngine(rvm::EngineId::PREDA_NATIVE, "./preda_engine",	repo_dir + "/native", "-native")) engine++;
	if(_InitEngine(rvm::EngineId::PREDA_WASM,	"./preda_engine",	repo_dir + "/wasm",	"-wasm")) engine++;
	if(_InitEngine(rvm::EngineId::SOLIDITY_EVM,	"./preda_engine",	repo_dir + "/evm", "-evm")) engine++;
	
	if(engine)
	{
		_InitChain(shard_order);
		return true;
	}
	else
	{
		_LOG_ERROR("No execution engine available.");
	}

	Term();
	return false;
}

void Simulator::Term()
{
	if(_pGlobalShard)
	{
		for(auto p : _Shards)p->Term();
		_pGlobalShard->Term();

		for(auto p : _Shards)_SafeDel(p);
		_SafeDel(_pGlobalShard);
	}

	_TxnPool.clear();

	for(auto& e : _Engines)
	{
		if(e.pEngine)
		{
			_SafeRelease(e.pEngine);
			os::UnloadDynamicLibrary(e.hModule);
			e.hModule = INVALID_HANDLE_VALUE;
		}
	}
}

rvm::EngineId Simulator::ResolveRTEngine(rt::String in, rt::String& filename)
{
	rt::String_Ref segs[2];
	auto co = in.Split(segs, 2, ':');
	filename = segs[0];
	rt::String runtimeMode = co > 1 ? segs[1] : _DefaultRTMode;
	if (filename.GetExtName() == rt::SS(".prd") && runtimeMode == "Native")
	{
		return rvm::EngineId::PREDA_NATIVE;
	}
	else if (filename.GetExtName() == rt::SS(".prd") && runtimeMode ==  "WASM")
	{
		return rvm::EngineId::PREDA_WASM;
	}
	else if (filename.GetExtName() == rt::SS(".sol-json") && co == 1)
	{
		return rvm::EngineId::SOLIDITY_EVM;
	}
	return rvm::EngineId::Unassigned;
}

bool Simulator::Compile(rvm::EngineId e, rt::Buffer<rt::String>& sources, rt::Buffer<rt::String_Ref>& code_fns)
{
	auto* engine = GetEngine(e);
	if(!engine)
	{
		_LOG_WARNING("Engine "<<rt::EnumStringify(e)<<" is not available");
		return false;
	}

	_pGlobalShard->DeployBegin(nullptr);

	BuildContracts	build(GetEngine(e), e);
	build.Init(DAPP_NAME, DAPP_ID, e);
	for (int i = 0; i < sources.GetSize(); i++)
	{
		build.AddSource(sources[i], code_fns[i]);
	}
	bool ret = build.Compile(*_pGlobalShard);
	_pGlobalShard->DeployEnd(false);
	if (!ret)
	{
		return false;
	}

	rt::Json json;
	json.Array();
	build.GetContractsInfo(json, *_pGlobalShard);
	_LOG(rt::JsonBeautified(json));

	return ret;
}

bool Simulator::_ComposeSolJson(rt::JsonObject inJson, rt::Json& out, rt::String fn)
{
	bool exist;
	rt::String_Ref entryFile = inJson.GetValue("entryFile", exist);
	if (!exist)
	{
		_LOG_WARNING("[PRD]: failed to find entry file: " << fn);
		return false;
	}

	rt::String_Ref entryContract = inJson.GetValue("entryContract", exist);
	if (!exist)
	{
		_LOG_WARNING("[PRD]: failed to find entry contract: " << fn);
		return false;
	}

	out.Object() << (
		J(entryFile) = entryFile,
		J(entryContract) = entryContract
		);

	rt::JsonObject sources = inJson.GetValue("sources", exist);
	if (!exist)
	{
		_LOG_WARNING("[PRD]: failed to find sources: " << fn);
		return false;
	}

	{
		auto scope = out.ScopeAppendingKey("sources");
		out.Object();
		rt::JsonKeyValuePair kv;
		while (sources.GetNextKeyValuePair(kv))
		{
			rt::String absPath;
			os::File::ResolveRelativePath(_ScriptPath + kv.GetValue(), absPath);
			rt::String solContent;
			if (!os::File::LoadText(absPath, solContent))
			{
				_LOG_WARNING("[PRD]: failed to load source code: " << absPath);
				return false;
			}
			out << (
				rt::_JTag(kv.GetKey()) = (
					J(content) = rt::JsonEscapeString(solContent)
					)
				);
		}
	}
	return true;
}

bool Simulator::Build(ExecuteUnit& exec_units, const rt::String_Ref& file_list, bool within_script)
{
	rt::String_Ref fns[256];
	uint32_t co = file_list.Split<true>(fns, sizeofArray(fns),", \t");
	if(co == 0)return false;

	BuildContracts preda_native	(GetEngine(rvm::EngineId::PREDA_NATIVE), rvm::EngineId::PREDA_NATIVE);
	BuildContracts preda_wasm	(GetEngine(rvm::EngineId::PREDA_WASM), rvm::EngineId::PREDA_WASM);
	BuildContracts solidity		(GetEngine(rvm::EngineId::SOLIDITY_EVM), rvm::EngineId::SOLIDITY_EVM);
	preda_native.Init(DAPP_NAME, DAPP_ID, rvm::EngineId::PREDA_NATIVE);
	preda_wasm.Init(DAPP_NAME, DAPP_ID, rvm::EngineId::PREDA_WASM);
	solidity.Init(DAPP_NAME, DAPP_ID, rvm::EngineId::SOLIDITY_EVM);

	rt::BufferEx<rt::String> codes;
	rt::BufferEx<rt::String> filenames;
	SimuTxn* txn = nullptr;

	for(uint32_t i=0; i<co; i++)
	{
		rt::String cur_fn;
		rvm::EngineId eid = ResolveRTEngine(fns[i], cur_fn);
		if(within_script)
		{
			os::File::ResolveRelativePath(_ScriptPath + cur_fn, filenames.push_back());
		}
		else
			filenames.push_back() = cur_fn;

		if(!os::File::LoadText(filenames[i], codes.push_back()))
		{
			_LOG_WARNING("[PRD]:  Line " << GetLineNum() << ":failed to load source code: "<<filenames[i]);
			return false;
		}

		BuildContracts* target = nullptr;
		if (eid == rvm::EngineId::SOLIDITY_EVM)
		{
			target = &solidity;

			rt::JsonObject codes_json = codes[i];

			rt::Json new_code;
			if (!_ComposeSolJson(codes_json, new_code, cur_fn))
			{
				return false;
			}

			codes[i] = new_code.GetInternalString();

			// evm needs a transaction
			txn = SimuTxn::Create(0U);
			txn->Type = rvm::InvokeContextType::Normal;
			txn->Contract = rvm::_details::CONTRACT_SET_SCOPE((rvm::ContractId)233, rvm::Scope::Global);
			txn->Op = rvm::OpCode(0);
			txn->BuildNum = 0;
			txn->Timestamp = os::Timestamp::Get();
			txn->Flag = TXN_BROADCAST;
			txn->OriginateHeight = 0;
			txn->OriginateShardIndex = 0;
			txn->OriginateShardOrder = 0;
			txn->Target = ADDRESS;
		}
		else if(eid == rvm::EngineId::PREDA_NATIVE)
		{
				target = &preda_native;
		}
		else if(eid == rvm::EngineId::PREDA_WASM)
		{
				target = &preda_wasm;
		}
		else
		{
			_LOG_WARNING("[PRD]: unsupported target for source code: "<<filenames[i]);
			return false;
		}

		ASSERT(target);
		target->AddSource(codes[i], filenames[i]);
	}

	_pGlobalShard->DeployBegin(txn);

	auto compile = [this](BuildContracts& b){
		if(b.GetSourceCount() == 0)return true;
		return b.Compile(*_pGlobalShard) && b.Link() && _pGlobalShard->AllocateContractIds(b);
	}; 

	auto deploy = [this](BuildContracts& b, rvm::ExecuteUnit* exec){
		if(b.GetSourceCount() == 0)return true;
		return b.Deploy(exec, _pGlobalShard, -1) && _pGlobalShard->FinalizeDeployment(b, b.GetContractDeploymentIds(), b.GetInterfaceDeploymentIds());
	};

	bool ret =	compile(solidity) && compile(preda_wasm) && compile(preda_native);

	VIZ_SECTION_BEGIN("Deploy");
	_ScriptVizJson.Array();
	int succ_count = 0;
	if(solidity.IsCompiled()){ solidity.GetContractsInfo(_ScriptVizJson, *_pGlobalShard); succ_count++; }
	if (preda_wasm.IsCompiled()) { preda_wasm.GetContractsInfo(_ScriptVizJson, *_pGlobalShard); succ_count++; }
	if (preda_native.IsCompiled()) { preda_native.GetContractsInfo(_ScriptVizJson, *_pGlobalShard); succ_count++; }
	VIZ_SECTION_END;
	ret = ret && deploy(solidity, exec_units.Get(rvm::EngineId::SOLIDITY_EVM)) &&
				 deploy(preda_wasm, exec_units.Get(rvm::EngineId::PREDA_WASM)) &&
				 deploy(preda_native, exec_units.Get(rvm::EngineId::PREDA_NATIVE));

	_pGlobalShard->DeployEnd(ret);
	return ret;
}

void Simulator::Run(rt::Buffer<rt::String_Ref>& input_files)
{
	rt::String ext;
	rt::Buffer<rt::String> codes;
	rt::String_Ref cur_fn;
	rvm::EngineId e = _DefaultRTMode == "WASM" ? rvm::EngineId::PREDA_WASM : rvm::EngineId::PREDA_NATIVE;
	for (int i = 0; i < input_files.GetSize(); i++)
	{
		_ScriptPath = rt::String_Ref(input_files[i]).GetFilePath() + '/';
		ext = rt::String_Ref(input_files[i]).GetExtName().TrimLeft(1);
		ext.MakeLower();
		cur_fn = input_files[i];
		if (ext != "prdts" && ext != "prd" && ext != "sol-json")
		{
			_LOG_WARNING("[PRD]: Invalid file format");
			return;
		}
		else if (ext == "prdts")
		{
			if (input_files.GetSize() > 1)
			{
				_LOG_WARNING("[PRD]: Only one prdts file can be processed at a time");
				return;
			}
			else
			{
				break;
			}
		}
		if (!os::File::LoadText(cur_fn.Begin(), codes.push_back()))
		{
			_LOG_WARNING("Contract source file: " << input_files[i] << " cannot be loaded");
			return;
		}
	}

	if (ext != "prdts")
	{
		if (ext == "sol-json")
		{
			if (input_files.GetSize() > 1)
			{
				_LOG_WARNING("[PRD]: Only one sol-json file can be processed at a time");
				return;
			}
			else
			{
				rt::JsonObject codes_json = codes[0];
				rt::Json new_code;
				if (!_ComposeSolJson(codes_json, new_code, cur_fn))
				{
					return;
				}
				codes[0] = new_code.GetInternalString();
				e = rvm::EngineId::SOLIDITY_EVM;
			}
		}
		WaitUntilIdle();
		if (Compile(e, codes, input_files))
			_LOG("[PRD]: Compile succeeded\n");
		return;
	}

	rt::String script, str;
	if(os::File::LoadText(cur_fn.Begin(), script))
	{
		{	auto& cmd = os::CommandLine::Get();
			for(UINT i=0; i<cmd.GetOptionCount(); i++)
			{
				str = rt::SS("$~") + cmd.GetOptionName(i) + '$';
				script.Replace(str, cmd.GetOptionValue(i));
			}

			for(UINT i=0; i<cmd.GetOptionCount(); i++)
			{
				str = rt::SS("~") + cmd.GetOptionName(i);
				script.Replace(str, cmd.GetOptionValue(i));
			}
		}

		_ScriptVizSectionNum = 0;
		_ScriptVizJson.Array();

		VIZ_SECTION_BEGIN("Run");
		_ScriptVizJson.Object(
			(J(script) = rt::String(cur_fn).EscapeCharacters("/"),
			(J(ShardOrder) = _ShardOrder))
		);
		VIZ_SECTION_END;

		_ScriptStopWatch.Restart();
		_ScriptStopWatch.SetOutputMillisecond();

		_ScriptAborted = false;
		rt::String_Ref line, cmd;
		rt::String connected;
		while(!_ScriptAborted && script.GetNextLine(line, false))
		{
			LineNum++;
			cmd = line.TrimRightSpace();
			if (!cmd.GetLength())
			{
				continue;
			}
			SSIZE_T var_begin = cmd.FindString(rt::String("$~"));
			SSIZE_T var_end = var_begin == -1 ? -1 : cmd.FindCharacter("$", var_begin + 1);
			if(var_begin != -1 && cmd.FindString("//") < 0)
			{
				_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Argument \"" << cmd.SubStr(var_begin, var_end - var_begin + 1) << "\" is undefined");
				break;
			}
			
			if(cmd.Last() == '\\')
			{
				connected += cmd.TrimRight(1);
				continue;
			}
			else
			{
				if(!connected.IsEmpty())
				{
					connected += cmd;
					cmd = connected;
				}
			}

			auto pos = cmd.FindString("//");
			if(pos >= 0)
			{
				cmd = cmd.SubStrHead(pos).TrimSpace();
				if(cmd.IsEmpty())
				{
					connected.Empty();
					continue;
				}
			}
			else
				cmd = cmd.TrimSpace();

			if(cmd == rt::SS("exit"))break;
			if(cmd == rt::SS("halt"))os::Sleep();

			ExecuteCommand(cmd);
			connected.Empty();
		}
	}
	else
	{
		_LOG_ERROR("Failed to load PREDA test script: "<< cur_fn);
	}
}

int32_t	Simulator::JsonifyCoreType(rvm::NativeTypeId tid, const rvm::ConstData* serialized, rvm::StringStream* json_out) const
{
	switch(tid)
	{
	case rvm::NativeTypeId::Address:
		if(serialized->DataSize == sizeof(rvm::ConstAddress))
		{
			rt::tos::Base32CrockfordLowercaseOnStack<> str(serialized->DataPtr, sizeof(rvm::ConstAddress));

			char q = '"';
			json_out->Append(&q, 1);
			json_out->Append(str.Begin(), (uint32_t)str.GetLength());
			json_out->Append(&q, 1);

			return (int)str.GetLength() + 2;
		}
		break;
	}

	ASSERT(0);
	return 0;
}

bool Simulator::JsonParseCoreType(rvm::NativeTypeId tid, const rvm::ConstString* json, rvm::DataBuffer* serialized_out) const
{
	uint8_t* data_out = nullptr;

	switch(tid)
	{
	case rvm::NativeTypeId::Address:
		{
			rt::String_Ref v = json->Str();
			v = v.TrimQuotes();
			if(	(data_out = serialized_out->SetSize(sizeof(rvm::ConstAddress))) &&
				os::Base32CrockfordDecode(data_out, sizeof(rvm::Address), v.Begin(), v.GetLength())
			)
				return true;
		}
		break;
	}

	ASSERT(0);
	serialized_out->SetSize(0);
	return false;
}

rvm::Scope Simulator::PrepareTxn(rvm::ContractId cid, rvm::OpCode opcode, rvm::BuildNum& buildnum_inout) const
{
	if(buildnum_inout == 0 || buildnum_inout == rvm::BuildNumLatest)
	{
		buildnum_inout = _pGlobalShard->_GetContractEffectiveBuild(cid);
		if(buildnum_inout == 0)return rvm::Scope::Neutral;
	}

	ContractVersionedId cvid = { cid, buildnum_inout };
	auto* c = _pGlobalShard->_ContractInfo.get(cvid);
	if(c)
		return c->ScopeOfOpcode[(int)opcode];
	else
	{
		buildnum_inout = 0;
		return rvm::Scope::Neutral;
	}
}

bool Simulator::ExecuteCommand(const rt::String_Ref& cmd_in)
{
	CmdParse cmd(cmd_in, GetLineNum());
	if(!cmd.Identifier.IsEmpty()){
		if(_TxnPool.has(cmd.Identifier))
		{
			_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Identifier \"" << cmd.Identifier << "\" already defined");
			return false;
		}
		else
		{
			rt::BufferEx<SimuTxn*> empty_buf;
			empty_buf.SetSize(0);
			_TxnPool[cmd.Identifier] = empty_buf;
		}
	}
	if(cmd.L1.IsEmpty() || cmd.Repeat == 0)return false;

	if(cmd.L1 == "allocate")return _ExecAllocate(cmd);
	if(cmd.L1 == "state")return _ExecState(cmd);
	if(cmd.L1 == "chain")return _ExecChain(cmd);
	if (cmd.L1 == "log")return _ExecLog(cmd);
#ifdef _VIZ
	if(cmd.L1 == "viz")
	{
		return _ExecVisualize(cmd, cmd_in);
	}
#endif
	if(cmd.L1 == "random" && cmd.L2 == "reseed")
	{
		int seed;
		if (!cmd.Args.IsEmpty()){
			int succeed = cmd.Args.ToNumber<int>(seed);
			if (succeed < 0)
			{
				_LOG("[PRD] Line " << LineNum << ": Invalid seed");
				return false;
			}
			new (&_ScriptRand) rt::Randomizer(seed);
		}
		else{
			new (&_ScriptRand) rt::Randomizer((uint32_t)os::Timestamp::Get());
		}
		return true;
	}

	if(cmd.L1 == "stopwatch")
	{
		if(cmd.L2 == "restart")
		{
			_LOG("Stopwatch restarted");
			_ScriptStopWatch.Restart();
			_ScriptStopWatch.SetOutputMillisecond();

			_ScriptStopWatchPendingTxnCount = _PendingTxnCount;
			_ScriptStopWatchExecutedTxnCount = _ExecutedTxnCount;

			return true;
		}
		if(cmd.L2 == "report")
		{
			uint64_t lapsed = rt::max<long long>(1LL, _ScriptStopWatch.TimeLapse());

			_LOG_HIGHLIGHT("Stopwatch: "<<lapsed<<" msec\n"
						   "Order: "<<_ShardOrder<<", "
						   "TPS:"<<(_ScriptStopWatchPendingTxnCount - _PendingTxnCount)*1000/lapsed<<", "
						   "uTPS:"<<(_ExecutedTxnCount - _ScriptStopWatchExecutedTxnCount)*1000/lapsed
			);

			return true;
		}
	}

	return _ExecIssueTxn(cmd);
}
#ifdef _VIZ
bool Simulator::_ExecVisualize(const CmdParse& cmd, const rt::String_Ref& cmd_in)
{
	bool result = false;
	rt::Json json;
	if (cmd.L2 == "block")
	{
		result = _ExecBlocksLog(cmd, json);
	}
	else if (cmd.L2 == "addr")
	{
		result = _ExecAddrStateLog(cmd, json);
	}
	else if (cmd.L2 == "shard")
	{
		result = _ExecShardStateLog(cmd, json);
	}
	else if (cmd.L2 == "txn")
	{
		result = _ExecTxnLog(cmd, json);
	}
	else if (cmd.L2 == "trace")
	{
		result = _ExecTraceLog(cmd, json);
	}
	else if (cmd.L2 == "section")
	{
		if (!cmd.Args.IsEmpty())
		{
			VIZ_SECTION_BEGIN("Section");
			_ScriptVizJson.String(cmd.Args);
			VIZ_SECTION_END
		}
		else
		{
			_LOG("[PRD] Line " << GetLineNum() << ": Empty viz.section input")
		}
	}
	else if (cmd.L2 == "profiling")
	{
		_ExecProfileLog(json);
		result = true;
	}

	if (result)
	{
		rt::String cap_cmd = cmd.L2;
		cap_cmd.First() -= 'a' - 'A';
		VIZ_QUERY_SECTION_BEGIN(cap_cmd, cmd_in);
		_ScriptVizJson.Object(json);
		VIZ_SECTION_END
	}
	return result;
}

void Simulator::_ExecProfileLog(rt::Json& json)
{
	uint64_t lapsed = rt::max<long long>(1LL, _ScriptStopWatch.TimeLapse());
	json.Array();
	{
		auto s = json.ScopeAppendingElement();
		GetGlobalShard()->JsonifyProfile(json);
		ULONGLONG global_pending_txn_count = _ShardPendingTxn.Last();
		json << (((J(TxnCount) = global_pending_txn_count),
			(J(TPS) = global_pending_txn_count * 1000 / lapsed)));
	}
	for (uint32_t sh = 0; sh < _Shards.GetSize(); sh++)
	{
		auto s1 = json.ScopeAppendingElement();
		_Shards[sh]->JsonifyProfile(json);
		ULONGLONG shard_pending_txn = _ShardPendingTxn[sh];
		json << ((J(TxnCount) = shard_pending_txn,
			J(TPS) = shard_pending_txn * 1000 / lapsed));
	}
}

bool Simulator::_ProcessIdentifierRequest(const CmdParse& cmd, rt::String& id_name, int& index, bool isTrace)
{
	if(cmd.Args.IsEmpty())
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Empty Identifier")
		return false;
	}
	SSIZE_T lbracket_pos = cmd.Args.FindCharacter('[');
	bool lbracket_exist = lbracket_pos != -1;
	bool index_provided = false;
	if (!lbracket_exist) {
		lbracket_pos = cmd.Args.GetLength();
	}
	id_name = cmd.Args.SubStr(0, lbracket_pos);
	if (!_TxnPool.has(id_name) || !_TxnPool.get(id_name).GetSize())
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Identitifer does not exist")
			return false;
	}

	if(lbracket_exist && cmd.Args.Last() != ']')
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Invalid representation of array")
		return false;
	}
	else if(lbracket_exist && !cmd.Args.EndsWith("[]"))
	{
		rt::String index_str = cmd.Args.SubStr(lbracket_pos + 1, cmd.Args.GetLength() - lbracket_pos - 2);
		index = index_str.ToNumber<int>();
		index_provided = true;
		if(index < 0 || !index_str.HasOnlyNumbers())
		{
			_LOG_WARNING("[PRD] Line " << GetLineNum() << ": negative array index/contains non-number")
			return false;
		}
	}

	if (isTrace && !index_provided && _TxnPool.get(id_name).GetSize() > 1)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Array index is not provided")
		return false;
	}
	else if(index >= 0 && index >= _TxnPool.get(id_name).GetSize())
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Index out of range")
		return false;
	}
	return true;
}

bool Simulator::_ExecTraceLog(const CmdParse& cmd, rt::Json& json)
{
	int index = 0;
	rt::String no_bracket;
	if(!_ProcessIdentifierRequest(cmd, no_bracket, index, true))
	{
		return false;
	}
	json.Array();
	SimuTxn* origin_txn = _TxnPool.get(no_bracket)[index];
	rt::BufferEx<std::pair<SimuTxn*,int>> queue;
	queue.push_back({origin_txn, -1});
	int id = 1;
	rt::Buffer<SimuShard*> all_shard = _Shards;
	all_shard.push_back(_pGlobalShard);
	while(queue.GetSize() > 0)
	{
		auto s = json.ScopeAppendingElement();
		std::pair<SimuTxn*,int> current_pair = 	*queue.Begin();
		queue.pop_front();
		json.Object((J(tx_id) = id));
		{
			auto s = json.ScopeAppendingKey("tx_info");
			json.Object();

			if(current_pair.first->Type == rvm::InvokeContextType::RelayInbound)
			{
				User a;
				a.Addr = current_pair.first->Target;
				a.ShardDword = rvm::_details::ADDRESS_SHARD_DWORD(a.Addr);
				current_pair.first->Target_index = (uint64_t)_Users.Find(a);
			}

			current_pair.first->Jsonify(GetEngine(current_pair.first->GetEngineId()), *_pGlobalShard, json, nullptr);
		}
		json << ((J(father)=current_pair.second));
		for(SimuShard* sh:all_shard)
		{
			const rt::BufferEx<SimuTxn*> relays = sh->GetTxnTrace(current_pair.first);
			if(relays.GetSize() > 0)
			{
				for(SimuTxn* st:relays)
				{
					queue.push_back({st, id});
				}
			}
		}
		id++;
	}
	return true;
}
rvm::InvokeResult* Simulator::_GetTxnResult(const SimuTxn* txn)
{
	if (txn->ShardIndex == 65535)
	{
		return _pGlobalShard->GetConfirmTxn(txn);
	}
	else if(txn->ShardIndex >= _Shards.GetSize())
	{
		return nullptr;
	}
	return _Shards[txn->ShardIndex]->GetConfirmTxn(txn);
}

bool Simulator::_ExecTxnLog(const CmdParse& cmd, rt::Json& json)
{
	int index = -1;
	rt::String no_bracket;
	if(!_ProcessIdentifierRequest(cmd, no_bracket, index, false))
	{
		return false;
	}
	json.Array();
	if(index >= 0)
	{
		auto s = json.ScopeAppendingElement();
		json.Object();
		SimuTxn* txn = _TxnPool.get(no_bracket)[index];
		txn->Jsonify(GetEngine(txn->GetEngineId()), *_pGlobalShard, json, _GetTxnResult(txn));
	}
	else
	{
		rt::BufferEx<SimuTxn*> vec = _TxnPool.get(no_bracket);
		for(auto txn_ptr: vec)
		{
			auto s = json.ScopeAppendingElement();
			json.Object();
			txn_ptr->Jsonify(GetEngine(txn_ptr->GetEngineId()), *_pGlobalShard, json, _GetTxnResult(txn_ptr));
		}
	}
	return true;
}

bool Simulator::_ExecBlocksLog(const CmdParse& cmd, rt::Json& json)
{
	if (cmd.Args.IsEmpty())
	{
		_LOG("[PRD] Line " << GetLineNum() << ": Missing block target");
		return false;
	}
	int starting_sh_pos = 0;
	int ending_sh_pos = (int)_Shards.GetSize();
	rt::String_Ref segs[2];
	if (cmd.Args[0] != '#')
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Block target should be denoted with '#'");
		return false;
	}
	int co = cmd.Args.TrimLeft(1).Split(segs, 2, ':');
	int blk_height = segs[1].IsEmpty() ? -1 : segs[1].ToNumber<int>();
	json.Array();
	if(segs[0] == "g" || segs[0] == "global")
	{
		if(!_pGlobalShard->JsonifyBlocks(json, blk_height))
		{
			json.Empty();
			return false;
		}
	}
	else
	{
		if(cmd.Args != "#all")
		{
			if (!segs[0].HasOnlyNumbers() || (co > 1 && !segs[1].HasOnlyNumbers()))
			{
				_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Invalid block target");
				return false;
			}
			starting_sh_pos = segs[0].ToNumber<int>();
			blk_height = segs[1].IsEmpty() ? -1 : segs[1].ToNumber<int>();
			ending_sh_pos = starting_sh_pos + 1;
			if(starting_sh_pos < 0 || starting_sh_pos >= _Shards.GetSize())
			{
				_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Block index is out of range");
				return false;
			}
		}
		for (; starting_sh_pos < ending_sh_pos; starting_sh_pos++)
		{
			if(!_Shards[starting_sh_pos]->JsonifyBlocks(json, blk_height))
			{
				json.Empty();
				return false;
			}
		}
	}
	return true;
}

bool Simulator::_ExecAddrStateLog(const CmdParse& cmd, rt::Json& json)
{
	rt::String_Ref segs[2];
	auto co = cmd.Args.Split(segs, 2, ' ');
	rt::String contract = co > 1 ? rt::String_Ref(segs[1].Begin(), cmd.Args.End()) : rt::String();
	rt::String target = segs[0];
	if(!_ProcessTargetRequest(target, GetLineNum(), false))
	{
		return false;
	}
	if(co > 1 && !_pGlobalShard->_Contracts.has(contract))
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Contract does not exist")
		return false;
	}
	rvm::ContractId contractid = (co > 1) ? _pGlobalShard->_Contracts.get(contract) : rvm::ContractId(0);
	json.Array();
	uint32_t s = target.ToNumber<int>();
	if (target == "random")
	{
		s = GetScriptRandomAddressIndex();
	}

	if (target == "all")
	{
		for (int sh = 0; sh < _Shards.GetSize(); sh++)
		{
			_Shards[sh]->JsonifyAllAddressStates(json, GetUsers(), contractid);
		}
	}
	else if(s >= 0 && s<_Users.GetSize())
	{
		rvm::Address addr = _Users[s].Addr;
		GetShard(GetShardIndex(addr))->JsonifyAddressState(json, addr, GetUsers(), contractid);
	}
	return true;
}

bool Simulator::_ProcessTargetRequest(rt::String& target, uint32_t LineNum, bool shardReq)
{
	rt::String trimmed = target.TrimLeft(1);
	if(target.GetLength() == 0)
	{
		_LOG_WARNING("[PRD] Line " << LineNum << ": Missing target index");
		return false;
	}
	else if(shardReq && target[0] != '#')
	{
		_LOG_WARNING("[PRD] Line " << LineNum << ": Shard target should be denoted with '#'");
		return false;
	}
	else if(!shardReq && target[0] != '@')
	{
		_LOG_WARNING("[PRD] Line " << LineNum << ": Address target should be denoted with '@'");
		return false;
	}
	else if(trimmed == "all")
	{
		target = trimmed;
		return true;
	}
	else if(shardReq && (trimmed == "g" || trimmed == "global"))
	{
		target = trimmed;
		return true;
	}
	else if (!shardReq && trimmed == "random")
	{
		target = trimmed;
		return true;
	}

	if (!trimmed.HasOnlyNumbers())
	{
		_LOG_WARNING("[PRD] Line " << LineNum << ": Target index must only contain digits");
		return false;
	}
	int target_num;
	int succeed = trimmed.ToNumber<int>(target_num);
	if (succeed < 0)
	{
		_LOG("[PRD] Line " << LineNum << ": Invalid target index")
		return false;
	}
	if (shardReq && target_num >= _Shards.GetSize())
	{
		_LOG("[PRD] Line " << LineNum << ": Shard index is out of range")
		return false;
	}
	else if (!shardReq && target_num >= _Users.GetSize())
	{
		_LOG("[PRD] Line " << LineNum << ": Address index is out of range")
		return false;
	}
	else if (target_num < 0)
	{
		_LOG("[PRD] Line " << LineNum << ": Target index must be positive");
		return false;
	}
	else
	{
		target = trimmed;
		return true;
	}
}

bool Simulator::_ExecShardStateLog(const CmdParse& cmd, rt::Json& json)
{
	bool succeed = false;
	rt::String_Ref segs[2];
	auto co = cmd.Args.Split(segs, 2, ' ');
	rt::String contract = co > 1 ? rt::String_Ref(segs[1].Begin(), cmd.Args.End()) : rt::String();
	rt::String target = segs[0];
	if(!_ProcessTargetRequest(target, GetLineNum(), true))
	{
		return false;
	}
	if(co > 1 && !_pGlobalShard->_Contracts.has(contract))
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Contract does not exist")
		return false;
	}
	rvm::ContractId contractid = (co > 1) ? _pGlobalShard->_Contracts.get(contract) : rvm::ContractId(0);
	json.Array();
	if (target == "all")
	{
		for (int sh = 0; sh < _Shards.GetSize(); sh++)
		{
			succeed = _Shards[sh]->JsonifyShardState(json, contractid);
		}
	}
	else if (target == "g" || target == "global")
	{
		succeed = _pGlobalShard->JsonifyShardState(json, contractid);
	}
	else
	{
		int s = target.ToNumber<int>();
		succeed = _Shards[s]->JsonifyShardState(json, contractid);
	}

	if(!succeed)
	{
		json.Empty();
		return false;
	}
	return true;
}
#endif
bool Simulator::_ExecLog(const CmdParse& cmd)
{
	if(cmd.L2 == "highlight"){ _LOG_HIGHLIGHT(rt::String("[HIGHLIGHT] ") + cmd.Args); }
	else if(cmd.L2 == "warning"){ _LOG_WARNING(rt::String("[WARNING] ") + cmd.Args); }
	else if(cmd.L2 == "error"){ _LOG_ERROR(rt::String("[ERROR] ") + cmd.Args); }
	else { _LOG(cmd.Args); }

	return true;
}

bool Simulator::_ExecChain(const CmdParse& cmd)
{
	if(cmd.L2 == "await")
	{
		//os::Sleep();
		WaitUntilIdle();
		return true;
	}
	else if(cmd.L2 == "step")
	{
		if (_Users.GetSize() == 0)
		{
			_LOG("[PRD]: No address has been allocated. Use \"allocate.address\" to create address");
			return false;
		}
		_bChainStepping = true;
		_bChainPaused = false;

		if(_bShardAsync)
		{
			for(auto p : _Shards)
				p->Step();
		}
		else
			_pGlobalShard->Step();

		return true;
	}
	else if(cmd.L2 == "run")
	{
		if (_Users.GetSize() == 0)
		{
			_LOG("[PRD]: No address has been allocated. Use \"allocate.address\" to create address");
			return false;
		}
		_bChainStepping = false;
		_bChainPaused = false;
#ifdef _VIZ
		for (int i = 0; i < _Shards.GetSize(); i++)
		{
			_ShardPendingTxn[i] = _Shards[i]->GetPendingTxnCount();
		}
		_ShardPendingTxn.push_back(GetGlobalShard()->GetPendingTxnCount());
#endif
		if(_bShardAsync)
		{
			for(auto p : _Shards)
				p->Step();
		}
		else
			_pGlobalShard->Step();
#ifdef _VIZ
		_ConvertQueueToTxnPool();
#endif
		WaitUntilIdle();
		_bChainPaused = true;

		return true;
	}
	else if(cmd.L2 == "stop")
	{
		_bChainPaused = true;
		return true;
	}
	else if(cmd.L2 == "info")
	{
		_pGlobalShard->LogInfo();
		for(auto p : _Shards)
			p->LogInfo();
		_LOG("Total Txn:"<<_PendingTxnCount<<'/'<<_ExecutedTxnCount);
	}
	else if(cmd.L2 == "gaslimit")
	{
		int succeed = cmd.Args.ToNumber<uint64_t>(_ScriptGasLimit);
		if (!cmd.Args.HasOnlyNumbers() || _ScriptGasLimit == 0 || succeed < 0)
		{
			_LOG("[PPD] Line " << GetLineNum() << ": Illeage gaslimit input");
			_ScriptGasLimit = 10000;
			return false;
		}
		return true;
	}
	else if(cmd.L2 == "deploy")
	{
		if (cmd.Args.IsEmpty())
		{
			_LOG_WARNING("[PPD] Line " << GetLineNum() << ": Empty Deploy Target")
		}
		WaitUntilIdle();
		if(!Build(_pGlobalShard->GetExecuteUnits(), cmd.Args, true))
			_ScriptAborted = true;

		return true;
	}

	return false;
}

rt::String_Ref Simulator::_LookupFunctionName(const rvm::Contract* c, rvm::OpCode op)
{
	uint32_t co = c->GetFunctionCount();
	for(uint32_t i=0; i<co; i++)
		if(c->GetFunctionOpCode(i) == op)
			return c->GetFunctionName(i).Str();

	return nullptr;
}

void Simulator::DebugPrint(rvm::DebugMessageType type, const rvm::ConstString* text, const rvm::ExecutionState* ctx, const rvm::Contract* contract)
{
	ASSERT(text);

	thread_local rt::String log;
	log = rt::SS("[PRD]");

	if(contract && ctx)
	{
		log += ": ";
		char ss[rvm::_details::ADDRESS_ABBREVIATION_LEN+1];

		if(ctx->GetInvokeType() == rvm::InvokeContextType::RelayInbound)
		{
			rvm::_details::ADDRESS_TO_ABBREVIATION(*ctx->GetInitiator(), ss);
			log += '[';
			log += rt::SS(ss) + "] #" + ShardIndexString(ctx->GetOriginatedShardIndex()) + "-h" + ctx->GetOriginatedBlockHeight() + " => ";
		}

		rvm::ContractScopeId cid = ctx->GetContractId();
		auto scope = rvm::_details::CONTRACT_SCOPE(cid);

		log += '#';
		log += ShardIndexString(ctx->GetShardIndex());

		if(scope == rvm::Scope::Address)
		{
			auto target = ctx->GetScopeTarget();
			ASSERT(target.Size == sizeof(rvm::Address));
			rvm::_details::ADDRESS_TO_ABBREVIATION(*(rvm::Address*)target.Data, ss);
			log += '[';
			log += rt::SS(ss) + "]-h" + ctx->GetBlockHeight();
		}

		log += rt::SS(": ") + contract->GetName().Str() + '.' + _LookupFunctionName(contract, ctx->GetOpCode());
	}

	static const rt::SS sep(": ");

	switch(type)
	{
	case rvm::DebugMessageType::Verbose:		_LOG_VERBOSE(log<<sep<<text->Str()); break;
	case rvm::DebugMessageType::Informational:	_LOG(log<<sep<<text->Str()); break;
	case rvm::DebugMessageType::Highlight:		_LOG_HIGHLIGHT(log<<sep<<text->Str()); break;
	case rvm::DebugMessageType::Warning:		_LOG_WARNING(log<<sep<<text->Str()); break;
	case rvm::DebugMessageType::Error:			_LOG_ERROR(log<<sep<<text->Str()); break;
	default: ASSERT(0);
	}
}

Simulator::CmdParse::CmdParse(const rt::String_Ref& cmd, uint32_t LineNum)
{
	int64_t identifier_pos = cmd.FindCharacter('=');
	if(identifier_pos != -1)
	{
		Identifier = cmd.SubStr(0, identifier_pos - 1);
		Identifier = Identifier.TrimSpace();
		if(Identifier.EndsWith("[]"))
		{
			Identifier_isArray = true;
			Identifier.RemoveCharacters("[]");
		}
		else
		{
			Identifier_isArray = false;
		}
	}
	if(Identifier.FindCharacter(" @#$%^&*()=+") != -1)
	{
		_LOG_WARNING("[PRD] Line " << LineNum << ": Identifier contains illegal symbol");
		return;
	}
	rt::String_Ref cmd_no_assign = identifier_pos == -1 ? cmd : cmd.SubStr(identifier_pos + 1).TrimSpace();
	rt::String_Ref str = cmd_no_assign.TrimAfter(" \n\r\t");

	Args = rt::String_Ref(str.End(), cmd.End()).TrimSpace();

	auto pos = str.FindCharacterReverse('*');
	if(pos < 0)
	{
		Repeat = 1;
	}
	else
	{
		rt::String repeatStr = str.SubStr(pos + 1);
		if (repeatStr.GetLength() == 0 || !repeatStr.HasOnlyNumbers())
		{
			Repeat = 0;
			_LOG("[PRD] Line " << LineNum << ": Invalid Repeat input")
		}
		else
		{
			Repeat = repeatStr.ToNumber<int>();
		}
		str = str.SubStrHead(pos);
	}

	rt::String_Ref segs[2];
	auto co = str.Split(segs, 2, '.');
	if(co == 1)
	{
		L1 = str;
		L2.Empty();
	}
	else
	{
		L1 = segs[0];
		L2 = rt::String_Ref(segs[1].Begin(), str.End());
	}

	if(L1.IsEmpty())
		Repeat = 0;
}

bool Simulator::_ExecAllocate(const CmdParse& cmd)
{
	if(cmd.L2 == "address")
	{
		int add = 0;
		int succeed = cmd.Args.ToNumber<int>(add);
		if (!cmd.Args.HasOnlyNumbers() || add <= 0 || succeed < 0)
		{
			_LOG("[PRD] Line " << GetLineNum() << ": Illegal input for number of addresses to be allcoated");
			add = 10;
			//return false;
		}

		uint32_t add_per = (add + (uint32_t)_Shards.GetSize() - 1)/(uint32_t)_Shards.GetSize();
		add = add_per*(uint32_t)_Shards.GetSize();

		uint32_t old = (uint32_t)_Users.GetSize();
		_Users.ExpandSize(old + add);

		uint32_t* count = (uint32_t*)alloca(sizeof(uint32_t)*_Shards.GetSize());
		rt::Zero(count, sizeof(uint32_t)*_Shards.GetSize());

		for(uint32_t i=old; i<_Users.GetSize();)
		{
			auto& a = _Users[i];
			_ScriptRand.Randomize(a.Addr);
			rvm::_details::ADDRESS_SET_SECSUITE(a.Addr, rvm::SecSuite::Ed25519);
			a.ShardDword = rvm::_details::ADDRESS_SHARD_DWORD(a.Addr);

			auto& co = count[a.ShardDword&_ShardBitmask];
			if(co < add_per)
			{
				i++;
				co++;
			}
		}

		_LOG(add<<" addresses added and evenly distributed in shards");
		_UserIndexRandMax = 0xffffffffU/(uint32_t)_Shards.GetSize()*(uint32_t)_Shards.GetSize();
		return true;
	}

	return false;
}

void Simulator::_InitChain(UINT shard_order)
{
	ASSERT(_Shards.GetSize() == 0);
	ASSERT(_pGlobalShard == nullptr);

	_ShardOrder = shard_order;
	_ScriptGasLimit = 10000;
	_bChainPaused = true;

	_PendingTxnCount = 0;
	_ExecutedTxnCount = 0;
	_ChainIdle.Set();

	uint32_t shard_count = 1<<_ShardOrder;
	_ShardBitmask = rvm::_details::ADDRESS_SHARD_BITMASK(_ShardOrder);

	uint64_t time_base = os::Timestamp::Get();
	_pGlobalShard = _New(SimuGlobalShard(this, time_base, _ShardOrder));

	_Shards.SetSize(shard_count);
	_ShardPendingTxn.SetSize(shard_count);
	for(uint32_t i=0; i<shard_count; i++)
		_Shards[i] = _New(SimuShard(this, time_base, _ShardOrder, i, _pGlobalShard));

	_pGlobalShard->Init();
	for(auto p : _Shards)
		p->Init();

	_LOG("[BC]: Chain initialized with "<<shard_count<<" shard(s), in "<<(_bShardAsync?"async":"sync")<<"-sharding mode");
}

void Simulator::WaitUntilIdle()
{
	_ChainIdle.WaitSignal();
}

Simulator::TargetParse::TargetParse(const rt::String_Ref& arg_part, rvm::Scope scope, uint32_t LineNum)
{
	ArgsJson = arg_part.TrimSpace();
	if(scope == rvm::Scope::Global)
	{
		if(ArgsJson.StartsWith("#global"))
			ArgsJson = ArgsJson.TrimLeft(7).TrimSpace();
	}
	else
	{
		Target = ArgsJson.TrimAfter(" \t").TrimSpace();
		
		if(Target[0] == '#' ||Target[0] == '@')
		{
			ArgsJson = rt::String_Ref(Target.End(), ArgsJson.End()).TrimSpace();
			if(ArgsJson.IsEmpty())
			{
				_LOG_WARNING("[BC] Line " << LineNum << ": missing argments json");
				Target.Empty();
			}
		}
		else
		{
			_LOG_WARNING("[BC] Line " << LineNum << ": '"<<Target<<"' is not a legal target");
			Target.Empty();
			ArgsJson.Empty();
		}
	}
}
#ifdef _VIZ
void Simulator::_ConvertQueueToTxnPool()
{
	rt::BufferEx<SimuTxn*> current_buf;
	rt::String current_id;
	if(_IdTxnQueue.GetSize() > 0)
	{
		std::pair<rt::String, SimuTxn*> p;
		_IdTxnQueue.Pop(p);
		current_buf.push_back(p.second);
		current_id = p.first;
	}
	else
	{
		return;
	}
	while(_IdTxnQueue.GetSize())
	{
		std::pair<rt::String, SimuTxn*> p;
		_IdTxnQueue.Pop(p);
		if(p.first != current_id)
		{
			_TxnPool[current_id] = current_buf;
			current_id = p.first;
			current_buf = _TxnPool.get(p.first);
		}
		current_buf.push_back(p.second);
	}
	_TxnPool[current_id] = current_buf;
}
#endif

rvm::ConstData Simulator::_ComposeState(oxd::SimuShard* s, rvm::BuildNum build, rvm::ContractScopeId csid, InputParametrized& input, const rt::String& in_state, rvm::Address* addr)
{
	rvm::ConstStateData stateData{nullptr, 0 , 0};
	if (rvm::_details::CONTRACT_SCOPE(csid) == rvm::Scope::Address)
	{
		SimuAddressContract k{ *addr, csid };
		const SimuState* state = s->GetAddressState(k);
		if (state)
		{
			stateData = { state->Data, state->DataSize, build };
		}
	}
	else
	{
		stateData = s->GetState(csid);
	}
	const rvm::ConstData data{ stateData.DataPtr, stateData.DataSize };
	rt::String out;
	oxd::StreamByString stateStr(out);
	
	rvm::RvmEngine* pEngine = GetEngine(rvm::_details::CONTRACT_ENGINE(csid));
	if (!pEngine)
		return { nullptr, 0 };
	pEngine->StateJsonify(build, csid, &data, &stateStr, _pGlobalShard);
	//in means input from user, might be incomplete state
	rt::JsonObject injson(in_state);
	//out means on chain state, is complete
	rt::JsonObject outjson(out);
	rt::JsonKeyValuePair p;
	//it is inconvenient to modify the original state json, therefore I'm constructing a new state
	rt::String newStateJson("{");
	while (outjson.GetNextKeyValuePair(p))
	{
		rt::String key = p.GetKey();
		bool exist = false;
		rt::String newStateVal = injson.GetValueRaw(key, exist);
		//GetValueRaw does not work properly if '$...$' is present
		int64_t start_pos = in_state.FindString(key);
		if (!exist && start_pos >= 0) //GetValueRaw can not find the value but the key exists
		{
			start_pos += key.GetLength() + 1;
			int64_t end_pos = in_state[start_pos] == '$' ? in_state.FindCharacter(",}]", in_state.FindCharacter('$', start_pos + 1)) : in_state.FindCharacter(',', start_pos + 1);
			newStateVal = in_state.SubStr(start_pos, end_pos - start_pos);
			exist = true;
		}
		//example: input is {weight:$random(1, 20)$}, GetValueRaw will obtain substring from "$r" to the first ',' which results in "$random(1"
		//need to handle special cases when value is wrapped in non standard json symbol and contains comma in between value
		if (exist && newStateVal[0] == '$' && newStateVal.Last() != '$')
		{
			start_pos = in_state.FindString(key) + key.GetLength() + 1;
			int64_t end_pos = in_state.FindCharacter("$", start_pos + 1);
			newStateVal = in_state.SubStr(start_pos, end_pos - start_pos + 1);
		}
		rt::String val = exist ? newStateVal : p.GetValueRaw();
		newStateJson += "\"" + key + "\":" + val + ",";
	}
	newStateJson = newStateJson.TrimRight(1) + "}";
	input.Parse(newStateJson);
	return input.ComposeState(build, csid);
}

bool Simulator::_ExecState(const CmdParse& cmd)
{
	if(cmd.L2 == "set")
	{
		rt::String_Ref op[2];
		if(cmd.Args.Split(op, 2, ". \t") != 2)return false;

		rvm::Scope scope;
		if(op[0] == "address"){ scope = rvm::Scope::Address; }
		else if(op[0] == "shard"){ scope = rvm::Scope::Shard; }
		else if(op[0] == "global"){ scope = rvm::Scope::Global; }
		else
		{
			_LOG("[BC] Line " << GetLineNum() << ": '"<<op[0]<<" is not a legal state identifier, which should be `addess/shard/global.[ContractName]`");
			return false;
		}

		rvm::ContractId cid = _pGlobalShard->_Contracts.get(op[1], (rvm::ContractId)0);
		if(cid == (rvm::ContractId)0)
		{
			_LOG("[BC] Line " << GetLineNum() << ": Contract '"<<op[1]<<"' is not found");
			return false;
		}

		TargetParse args(rt::String_Ref(op[1].End(), cmd.Args.End()), scope, GetLineNum());
		if(args.IsError())return false;
		thread_local InputParametrized input(*this);
		if(!input.Parse(args.ArgsJson))
			return false;

		auto build = _pGlobalShard->_GetContractEffectiveBuild(cid);
		rvm::ContractScopeId csid = rvm::_details::CONTRACT_SET_SCOPE(cid, scope);
		switch(scope)
		{
			case rvm::Scope::Global:
			{
				rvm::ConstData buf = _ComposeState(_pGlobalShard, build, csid, input, args.ArgsJson);
				_pGlobalShard->SetState(cid, scope, SimuState::Create(buf.DataSize, build, buf.DataPtr));
				return true;
			}
			case rvm::Scope::Shard:
			{
				rt::String target = args.Target;
				if(!_ProcessTargetRequest(target, GetLineNum(), true))
				{
					return false;
				}
				if(target == "all")
				{
					for(auto s: _Shards)
					{
						rvm::ConstData buf = _ComposeState(s, build, csid, input, args.ArgsJson);
						if (!buf.DataPtr)
						{
							_LOG("[BC] Line " << GetLineNum() << ": Failed to Set State");
							return false;
						}
						s->SetState(cid, scope, SimuState::Create(buf.DataSize, build, buf.DataPtr));
					}
				}
				else
				{
					uint32_t s = target.ToNumber<int>();
					if(s>=0 && s<_Shards.GetSize())
					{
						rvm::ConstData buf = _ComposeState(_Shards[s], build, csid, input, args.ArgsJson);
						if (!buf.DataPtr)
						{
							_LOG("[BC] Line " << GetLineNum() << ": Failed to Set State");
							return false;
						}
						_Shards[s]->SetState(cid, scope, SimuState::Create(buf.DataSize, build, buf.DataPtr));
					}
					else
					{
						_LOG_WARNING("[BC] Line " << GetLineNum() << ": shard index "<<s<<" is out of range, should be [0, "<<_Shards.GetSize()-1<<']');
						return false;
					}
				}

				return true;
			}
			case rvm::Scope::Address:
			{
				rt::String target = args.Target;
				if(!_ProcessTargetRequest(target, GetLineNum(), false))
				{
					return false;
				}
				if(target == "all")
				{
					for (auto& a : _Users)
					{
						rvm::ConstData buf = _ComposeState(_Shards[a.ShardDword & _ShardBitmask], build, csid, input, args.ArgsJson, &a.Addr);
						if (!buf.DataPtr)
						{
							_LOG("[BC] Line " << GetLineNum() << ": Failed to Set State");
							return false;
						}
						_Shards[a.ShardDword & _ShardBitmask]->SetState(cid, scope, a.Addr, SimuState::Create(buf.DataSize, build, buf.DataPtr));
					}
				}
				else if(target == "random")
				{
					for(int i=0; i<cmd.Repeat; i++)
					{
						thread_local uint32_t last = 0;
						last = (_ScriptRand.GetNext() + last)%_Users.GetSize();

						auto& a = _Users[last];
						rvm::ConstData buf = _ComposeState(_Shards[a.ShardDword & _ShardBitmask], build, csid, input, args.ArgsJson, &a.Addr);
						if (!buf.DataPtr)
						{
							_LOG("[BC] Line " << GetLineNum() << ": Failed to Set State");
							return false;
						}
						_Shards[a.ShardDword&_ShardBitmask]->SetState(cid, scope, a.Addr, SimuState::Create(buf.DataSize, build, buf.DataPtr));
					}
				}
				else
				{
					uint32_t s = target.ToNumber<int>();
					if(s>=0 && s<_Users.GetSize())
					{
						auto& a = _Users[s];
						rvm::ConstData buf = _ComposeState(_Shards[a.ShardDword & _ShardBitmask], build, csid, input, args.ArgsJson, &a.Addr);
						if (!buf.DataPtr)
						{
							_LOG("[BC] Line " << GetLineNum() << ": Failed to Set State");
							return false;
						}
						_Shards[a.ShardDword&_ShardBitmask]->SetState(cid, scope, a.Addr, SimuState::Create(buf.DataSize, build, buf.DataPtr));
					}
					else
					{
						_LOG_WARNING("[BC] Line " << GetLineNum() << ": address index "<<s<<" is out of range, should be [0, "<<_Users.GetSize()-1<<']');
						return false;
					}
				}
				return true;
			}
		}
	}

	return false;
}

uint32_t Simulator::GetScriptRandomAddressIndex() const
{
	for(;;)
	{
		uint32_t r = _ScriptRand.GetNext();
		if(r < _UserIndexRandMax)
		{
			return r%_Users.GetSize();
		}
	}
}

bool Simulator::_ExecIssueTxn(const CmdParse& cmd)
{
	ContractFunction fi;
	rvm::BuildNum build_num = rvm::BuildNumLatest;
	rvm::Scope scope;

	{	EnterCSBlock(_CS);
		fi = rt::_CastToConst(_pGlobalShard->_ContractFunctions).get(rt::String_Ref(cmd.L1.Begin(), cmd.L2.End()), ContractFunction());
		if(fi.Contract == (rvm::ContractId)0)
		{
			_LOG_WARNING("[BC] Line " << GetLineNum() << ": contract function '"<<rt::String_Ref(cmd.L1.Begin(), cmd.L2.End())<<"' is not found");
			return false;
		}

		scope = PrepareTxn(fi.Contract, fi.Op, build_num);
		ASSERT(scope != rvm::Scope::Neutral);
	}

	TargetParse target(cmd.Args, scope, GetLineNum());
	if(target.IsError())return false;
	if(target.Target.GetLength() > 0 && target.Target[0] == '@' && scope == rvm::Scope::Shard)
	{
		_LOG_WARNING("[BC] Line " << GetLineNum() << ": Target of a shard function should begin '#'");
		return false;
	}
	else if(target.Target.GetLength() > 0 && target.Target[0] == '#' && scope == rvm::Scope::Address)
	{
		_LOG_WARNING("[BC] Line " << GetLineNum() << ": Target of a address function should begin '@'");
		return false;
	}
	thread_local InputParametrized input(*this);
	if(!input.Parse(target.ArgsJson))
		return false;

	auto* txn = input.ComposeTxn(build_num, rvm::_details::CONTRACT_SET_SCOPE(fi.Contract, scope), fi.Op);
	if(!txn)
	{
		return false;
	}

	bool identifier_exist = !cmd.Identifier.IsEmpty();
	switch(scope)
	{
	case rvm::Scope::Global:
	{
		if(input.IsLoopIndexInvolved())
		{
			if(identifier_exist && !cmd.Identifier_isArray)
			{
				_LOG_WARNING("[BC] Line " << GetLineNum() << ": Identifier type of multiple txns must be array");
				return false;
			}
			auto* param = &input; // input in this thread should be used in all loop threads
			auto loop = [this,&cmd,txn,fi,scope,build_num,param,identifier_exist](int i) {
				if(i >= _Users.GetSize())return false;
				for (int repeat = 0; repeat < cmd.Repeat; repeat++)
				{
					SimuTxn* t = param->IsParameterized() ? param->ComposeTxn(build_num, rvm::_details::CONTRACT_SET_SCOPE(fi.Contract, scope), fi.Op, i) : txn->Clone();
					if(!t)
					{
						return false;
					}
					_pGlobalShard->PushTxn(t);
#ifdef _VIZ
					if(identifier_exist) _IdTxnQueue.Push({ cmd.Identifier, t });
#endif
				}
				return true;
			};

			os::ParallelLoop(loop);
			_SafeRelease(txn);
		}
		else
		{
			for (int repeat = 0; repeat < cmd.Repeat; repeat++)
			{
				SimuTxn* duplicates = input.IsParameterized() ? input.ComposeTxn(build_num, rvm::_details::CONTRACT_SET_SCOPE(fi.Contract, scope), fi.Op, repeat) : txn->Clone();
				_pGlobalShard->PushTxn(duplicates);
#ifdef _VIZ
				if(identifier_exist) _IdTxnQueue.Push({ cmd.Identifier, duplicates });
#endif
			}
		}
		break;
	}
	case rvm::Scope::Shard:
	{
		rt::String sh_target = target.Target;
		if(!_ProcessTargetRequest(sh_target, GetLineNum(), true))
		{
			return false;
		}
		if(sh_target == "all")
		{
			if(identifier_exist && !cmd.Identifier_isArray)
			{
				_LOG_WARNING("[BC] Line " << GetLineNum() << ": Identifier type of multiple txns must be array");
				return false;
			}
			for (uint32_t i = 0; i < _Shards.GetSize(); i++) {
				for (int repeat = 0; repeat < cmd.Repeat; repeat++)
				{
					SimuTxn* t = input.IsParameterized() ? input.ComposeTxn(build_num, rvm::_details::CONTRACT_SET_SCOPE(fi.Contract, scope), fi.Op, i) : txn->Clone();
					if(!t)
					{
						return false;
					}
					_Shards[i]->PushTxn(t);
#ifdef _VIZ
					if(identifier_exist) _IdTxnQueue.Push({ cmd.Identifier, t });
#endif
				}
			}
		}
		else
		{
			uint32_t s = sh_target.ToNumber<int>();
			if(s>=0 && s<_Shards.GetSize())
			{
				for (int repeat = 0; repeat < cmd.Repeat; repeat++)
				{
					SimuTxn* duplicates = input.IsParameterized() ? input.ComposeTxn(build_num, rvm::_details::CONTRACT_SET_SCOPE(fi.Contract, scope), fi.Op, repeat) : txn->Clone();;
					_Shards[s]->PushTxn(duplicates);
#ifdef _VIZ
					if(identifier_exist) _IdTxnQueue.Push({ cmd.Identifier, duplicates });
#endif
				}
			}
			else
			{
				_LOG_WARNING("[BC] Line " << GetLineNum() << ": shard index "<<s<<" is out of range, should be [0, "<<_Shards.GetSize()-1<<']');
				return false;
			}
		}
		break;
	}
	case rvm::Scope::Address:
	{
		rt::String addr_target = target.Target;
		if(!_ProcessTargetRequest(addr_target, GetLineNum(), false))
		{
			return false;
		}
		if(addr_target == "random")
		{
			auto* param = &input; // input in this thread should be used in all loop threads
			auto loop = [this,&cmd,txn,fi,scope,build_num,param,identifier_exist](int i) {
				if(i >= cmd.Repeat)return false;

				uint32_t last;
				last = GetScriptRandomAddressIndex();

				auto& a = _Users[last];

				SimuTxn* t = param->IsParameterized()?param->ComposeTxn(build_num, rvm::_details::CONTRACT_SET_SCOPE(fi.Contract, scope), fi.Op, i):txn->Clone();
				if(!t)
				{
					return false;
				}
				t->Target = a.Addr;
				t->Target_index = last;
				_Shards[a.ShardDword&_ShardBitmask]->PushTxn(t);
#ifdef _VIZ
				if(identifier_exist) _IdTxnQueue.Push({cmd.Identifier, t});
#endif
				return true;
			};

			os::ParallelLoop(loop);
			_SafeRelease(txn);
		}
		else if(addr_target == "all")
		{
			if(identifier_exist && !cmd.Identifier_isArray)
			{
				_LOG_WARNING("[BC] Line " << GetLineNum() << ": Identifier type of multiple txns must be array");
				return false;
			}
			auto* param = &input; // input in this thread should be used in all loop threads
			auto loop = [this,&cmd,txn,fi,scope,build_num,param,identifier_exist](int i) {
				if(i >= _Users.GetSize())return false;
				for (int repeat = 0; repeat < cmd.Repeat; repeat++)
				{
					SimuTxn* t = param->IsParameterized() ? param->ComposeTxn(build_num, rvm::_details::CONTRACT_SET_SCOPE(fi.Contract, scope), fi.Op, i) : txn->Clone();
					if (!t)
					{
						return false;
					}
					auto& a = _Users[i];
					t->Target = a.Addr;
					t->Target_index = i;
					_Shards[a.ShardDword & _ShardBitmask]->PushTxn(t);
#ifdef _VIZ
					if (identifier_exist) _IdTxnQueue.Push({ cmd.Identifier, t });
#endif
				}
				return true;
			};

			os::ParallelLoop(loop);
			_SafeRelease(txn);
		}
		else
		{
			uint32_t s = addr_target.ToNumber<int>();
			if(s>=0 && s<_Users.GetSize())
			{
				auto& a = _Users[s];
				txn->Target = a.Addr;
				txn->Target_index = s;

				auto* param = &input; // input in this thread should be used in all loop threads
				auto loop = [this,&cmd,txn,&a,fi,scope,build_num,param,identifier_exist, s](int i) {
					if(i >= cmd.Repeat)return false;

					SimuTxn* t = param->IsParameterized()?param->ComposeTxn(build_num, rvm::_details::CONTRACT_SET_SCOPE(fi.Contract, scope), fi.Op, i):txn->Clone();
					if(!t)
					{
						return false;
					}
					t->Target = a.Addr;
					t->Target_index = s;
					_Shards[a.ShardDword&_ShardBitmask]->PushTxn(t);
#ifdef _VIZ
					if(identifier_exist) _IdTxnQueue.Push({cmd.Identifier, t});
#endif
					return true;
				};

				os::ParallelLoop(loop);
				_SafeRelease(txn);
			}
		}

		break;
	}
	}
	return true;
}

bool Simulator::ExportVizHtml(const rt::String_Ref& templ, const rt::String_Ref& output) const
{
	rt::String html;
	if(!os::File::LoadText(ALLOCA_C_STRING(templ), html))
	{
		_LOG_WARNING("[BC]: Template visualization webpage can not be loaded: "<<templ);
		return false;
	}

	auto pos = html.FindString("</HEAD>");
	if(pos == -1)pos = html.FindString("</head>");
	if(pos == -1)
	{
		_LOG_WARNING("[BC]: No <HEAD> tag found in template visualization webpage: "<<templ);
	}

	rt::String out;

	out = html.SubStr(0, pos);
	out += "\n<script type=\"text/javascript\">\nvar PREDA_VIZ_LOG = \n";
#if defined(PLATFORM_DEBUG_BUILD)
	out += rt::JsonBeautified(_ScriptVizJson);
#else
	out += _ScriptVizJson;
#endif
	out += ";\n</script>\n\n";

	out += html.SubStr(pos);

	if(!os::File::SaveText(ALLOCA_C_STRING(output), out))
	{
		_LOG_WARNING("[BC]: Failed to save visualization webpage: "<<out);
		return false;
	}

	return true;
}

} // namespace oxd
