#include "../../SFC/core/ext/botan/botan.h"
#include <iostream>
#include "simulator.h"
#include "simu_shard.h"
#include "core_contracts.h"
#include "../native/types/abi_def_impl.h"

#define VIZ_SECTION_BEGIN(tag)	if(_ScriptVizEnabled)													\
										{	auto __section_scope = _ScriptVizJson.ScopeAppendingElement();		\
											_ScriptVizJson.Object( (( J(type) = tag )) );	\
											auto __section_body = _ScriptVizJson.ScopeAppendingKey("content");	

#define VIZ_QUERY_SECTION_BEGIN(tag, cmd)	if(_ScriptVizEnabled)													\
										{	auto __section_scope = _ScriptVizJson.ScopeAppendingElement();		\
											_ScriptVizJson.Object( (( J(type) = tag ),(J(command) = cmd)) );	\
											auto __section_body = _ScriptVizJson.ScopeAppendingKey("content");

#define VIZ_SECTION_END						_ScriptVizSectionNum++; }
#if defined(PLATFORM_WIN)
static const constexpr char* PREDA_DATA_FOLDER = "\\AppData\\Roaming\\.preda\\";
#elif defined(PLATFORM_MAC)
static const constexpr char* PREDA_DATA_FOLDER = "/Library/Application Support/.preda/";
#elif defined(PLATFORM_LINUX)	
static const constexpr char* PREDA_DATA_FOLDER = "/.preda/";
#endif
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
#pragma warning(disable: 4996)
	const char* homeDir;
	if((homeDir = getenv("USERPROFILE")) == nullptr && ((homeDir = getenv("HOMEPATH")) == nullptr))
	{
		_LOG("[PRD]: USERPROFILE/HOMEPATH is not found");
		return 1;
	}
#else
	const char* homeDir = getenv("HOME");
#endif
	rt::String predaHomePath = rt::SS(homeDir, strlen(homeDir)) + rt::String(PREDA_DATA_FOLDER);
	if(!os::File::CreateDirectories(predaHomePath))
	{
		_LOG("[PRD]: Unable to create Preda Home Directory: " << lockPath);
		return 1;
	}
	lockPath = predaHomePath + ".preda_lock";
	os::File lockfile(lockPath, "a+b", true);
	if(!lockfile.IsOpen())
	{
		_LOG("[PRD]: Unable to create lockfile: " << lockPath);
		return 1;
	}
	else if(!lockfile.Lock())
	{
		_LOG("[PRD]: Another chain simulator is runnig. Please wait until the other job is finished");
		return 1;
	}
	if(cmd.GetTextCount() == 0)
	{
		_LOG("[PRD]: chsimu input_file.(prd|sol|prdts) [-async] [-perftest] [-order:n] [-viz:output_filename] [-viz_templ:webui_template_path]");
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
		if(cmd.HasOption("order"))
		{
			rt::String order_str = cmd.GetOption("order");
			if(!order_str.HasOnlyNumbers() || order_str.ToNumber(order) < 0)
			{
				_LOG("[PRD]: Invalid Shard Order input. It must be a positive integer greater than zero.")
				return 1;
			}
		}

		if(sim.Init(cmd))
		{
			os::SetProcessPriority(os::PROCPRIO_HIGH);

			rt::String_Ref script = cmd.GetText(0);
			rt::Buffer<rt::String_Ref> fnArr;
			for(uint32_t i = 0; i < cmd.GetTextCount(); i++)
			{
				fnArr.push_back(cmd.GetText(i));
			}
			sim.Run(fnArr);
		}

		if(!sim.IsVizToConsole())
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

void Simulator::CreateExecuteUnit(ExecutionUnit* out) const
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
	_Engines[(int)rvm::EngineId::Core] = { INVALID_HANDLE_VALUE, &CoreEngine::Get() };

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
				if (!_CompileOnly)
				{
					_LOGC_HIGHLIGHT("Execution Engine Initialized, <" << ee.pEngine->GetName().Str() << "> v" << ee.pEngine->GetVersion().Str() << ", " << ee.pEngine->GetVendorInfo().Str());
					_LOGC("Repository: " << repo << ", Module: " << dll_name << " (" << rt::EnumStringify(eng) << ")\n");
				}
				return true;
			}
			else
			{
				_LOGC_WARNING("Failed to initialized PREDA engine, db path: " << repo);
				if(initErrorMsg.StrPtr)
					_LOGC_WARNING("Failed to initialize: "<<initErrorMsg.Str());
			}
		}
		else
		{
			_LOGC_WARNING("Unable to load engine export symbol")
		}
	}
	else
	{
		_LOGC_WARNING("Unable to load engine module")
	}

	_LOGC_WARNING("Failed to mount execution engine: "<<dll_name<<" ("<<rt::EnumStringify(eng)<<") with repository in "<<repo<<'\n');
	return false;
}

bool Simulator::Init(const os::CommandLine& cmd)
{
	uint32_t shard_order = cmd.GetOptionAs<uint32_t>("order", 2);
	_bChainStepping = true;
	_bShardAsync = cmd.HasOption("async");
	_iShardsExecuted = 0;
	_ScriptVizEnabled = cmd.HasOption("viz");
	_VizToConsole = !(cmd.HasOption("viz") && cmd.HasOption("viz_templ"));
	_DefaultRTMode = cmd.HasOption("WASM") ? "WASM" : "Native";
	rt::String fn = cmd.GetText(0);
	_CompileOnly = fn.GetExtName() == rt::SS(".prd");
	rt::String repo_dir("./chsimu_repo");
#if defined(PLATFORM_WIN)
	char* homeDir = getenv("HOMEPATH");
#else
	char* homeDir = getenv("HOME");
#endif
	auto _ProcessConfigJson = []()
	{
			rt::String jsonStr;
			//if config.json does not exist, load WASM engine
			if (!os::File::LoadText("config.json", jsonStr))
			{
				return true;
			}
			rt::JsonObject jsonObj(jsonStr);
			return jsonObj.GetValueAs<bool>("wasm");
	};
	repo_dir = rt::SS(homeDir, strlen(homeDir)) + PREDA_DATA_FOLDER + "chsimu_repo";
	os::File::RemovePath(repo_dir);
	if(!_CompileOnly) _LOG("Physical CPU core: "<<os::GetNumberOfPhysicalProcessors()<<", Logic CPU core: "<<os::GetNumberOfProcessors());

	int engine = 0;
	if(_InitEngine(rvm::EngineId::PREDA_NATIVE, "./preda_engine",	repo_dir + "/native", "-native")) engine++;
	if(_ProcessConfigJson() && _InitEngine(rvm::EngineId::PREDA_WASM,	"./preda_engine",	repo_dir + "/wasm",	"-wasm")) engine++;
	//if(_InitEngine(rvm::EngineId::SOLIDITY_EVM,	"./preda_engine",	repo_dir + "/evm", "-evm")) engine++;
	
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
			if(e.hModule != INVALID_HANDLE_VALUE)
			{
				os::UnloadDynamicLibrary(e.hModule);
				e.hModule = INVALID_HANDLE_VALUE;
			}
		}
	}
}

rvm::EngineId Simulator::_ResolveRTEngine(rt::String in, rt::String& filename)
{
	rt::String_Ref segs[2];
	auto co = in.Split(segs, 2, ':');
	filename = segs[0];
	rt::String runtimeMode = co > 1 ? segs[1] : _DefaultRTMode;
	if(filename.GetExtName() == rt::SS(".prd") && runtimeMode == "Native")
	{
		return rvm::EngineId::PREDA_NATIVE;
	}
	else if(filename.GetExtName() == rt::SS(".prd") && runtimeMode ==  "WASM")
	{
		return rvm::EngineId::PREDA_WASM;
	}
	else if(filename.GetExtName() == rt::SS(".sol-json") && co == 1)
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
		_LOG_WARNING("[PRD]: Engine "<<rt::EnumStringify(e)<<" is not available");
		return false;
	}

	_pGlobalShard->DeployBegin();

	BuildContracts	build(GetEngine(e), e);
	build.Init(DAPP_NAME, DAPP_ID, e);
	for(int i = 0; i < sources.GetSize(); i++)
	{
		build.AddContractCode(sources[i], nullptr, code_fns[i]);
	}
	bool ret = build.Compile(false);
	_pGlobalShard->DeployEnd(false);
	if(!ret)
	{
		return false;
	}

	rt::Json json;
	build.GetContractsInfo(json);
	_LOG(rt::JsonBeautified(json));

	return ret;
}

bool Simulator::_ComposeSolJson(rt::JsonObject inJson, rt::Json& out, rt::String fn)
{
	bool exist;
	rt::String_Ref entryFile = inJson.GetValue("entryFile", exist);
	if(!exist)
	{
		_LOG_WARNING("[PRD]: Failed to find entry file: " << fn);
		return false;
	}

	rt::String_Ref entryContract = inJson.GetValue("entryContract", exist);
	if(!exist)
	{
		_LOG_WARNING("[PRD]: Failed to find entry contract: " << fn);
		return false;
	}

	out.Object() << (
		J(entryFile) = entryFile,
		J(entryContract) = entryContract
		);

	rt::JsonObject sources = inJson.GetValue("sources", exist);
	if(!exist)
	{
		_LOG_WARNING("[PRD]: Failed to find sources: " << fn);
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
			if(!os::File::LoadText(absPath, solContent))
			{
				_LOG_WARNING("[PRD]: Failed to load source code: " << absPath);
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

bool Simulator::Deploy(ExecutionUnit& exec_units, const rt::String_Ref* fns, const rt::String_Ref* ctor_args, uint32_t co, bool within_script, rvm::InvokeResult &ctor_invoke_result)
{
	if(co == 0)return false;

	BuildContracts preda_native	(GetEngine(rvm::EngineId::PREDA_NATIVE), rvm::EngineId::PREDA_NATIVE);
	BuildContracts preda_wasm	(GetEngine(rvm::EngineId::PREDA_WASM), rvm::EngineId::PREDA_WASM);
	BuildContracts solidity		(GetEngine(rvm::EngineId::SOLIDITY_EVM), rvm::EngineId::SOLIDITY_EVM);
	preda_native.Init(DAPP_NAME, DAPP_ID, rvm::EngineId::PREDA_NATIVE);
	preda_wasm.Init(DAPP_NAME, DAPP_ID, rvm::EngineId::PREDA_WASM);
	solidity.Init(DAPP_NAME, DAPP_ID, rvm::EngineId::SOLIDITY_EVM);

	rt::BufferEx<rt::String> codes;
	rt::BufferEx<rt::String> filenames;

	for(uint32_t i=0; i<co; i++)
	{
		rt::String cur_fn;
		rvm::EngineId eid = _ResolveRTEngine(fns[i], cur_fn);
		if(within_script)
		{
			os::File::ResolveRelativePath(_ScriptPath + cur_fn, filenames.push_back());
		}
		else
			filenames.push_back() = cur_fn;

		if(!os::File::LoadText(filenames[i], codes.push_back()))
		{
			_LOG_WARNING("[PRD]:  Line " << GetLineNum() << ": Failed to load source code: "<<filenames[i]);
			return false;
		}

		BuildContracts* target = nullptr;
		if(eid == rvm::EngineId::SOLIDITY_EVM)
		{
			target = &solidity;

			rt::JsonObject codes_json = codes[i];

			rt::Json new_code;
			if(!_ComposeSolJson(codes_json, new_code, cur_fn))
			{
				return false;
			}

			codes[i] = new_code.GetInternalString();
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
			_LOG_WARNING("[PRD]: Unsupported target for source code: "<<filenames[i]);
			return false;
		}

		ASSERT(target);
		if(!ctor_args[i].IsEmpty())
			target->AddContractCode(codes[i], ctor_args[i], filenames[i]);
		else
			target->AddContractCode(codes[i], nullptr, filenames[i]);
	}

	_pGlobalShard->DeployBegin();

	auto compile = [this](BuildContracts& b){
		if(b.GetSourceCount() == 0)return true;
		return b.Compile() && b.Link() && _pGlobalShard->AllocateContractIds(b);
	};

	auto deploy = [this, &ctor_invoke_result](BuildContracts& b, rvm::ExecutionUnit* exec){
		if(b.GetSourceCount() == 0)return true;
		return b.Deploy(exec, _pGlobalShard) && _pGlobalShard->CommitDeployment(b) && (ctor_invoke_result = b.InvokeConstructor(exec, _pGlobalShard, -1)).Code == rvm::InvokeErrorCode::Success;
	};

	bool ret =	compile(solidity) && compile(preda_wasm) && compile(preda_native);

	VIZ_SECTION_BEGIN("Deploy");
	{
		_ScriptVizJson.Object();
		auto section = _ScriptVizJson.ScopeAppendingKey("info");
		_ScriptVizJson.Array();
		int succ_count = 0;
		if(solidity.IsCompiled())
		{
			auto section2 = _ScriptVizJson.ScopeMergingArray();
			solidity.GetContractsInfo(_ScriptVizJson); succ_count++;
		}
		if(preda_wasm.IsCompiled())
		{
			auto section2 = _ScriptVizJson.ScopeMergingArray();
			preda_wasm.GetContractsInfo(_ScriptVizJson); succ_count++;
		}
		if(preda_native.IsCompiled())
		{
			auto section2 = _ScriptVizJson.ScopeMergingArray();
			preda_native.GetContractsInfo(_ScriptVizJson); succ_count++;
		}
	}
	auto section2 = _ScriptVizJson.ScopeAppendingKey("sources");
	_ScriptVizJson.Array();
	auto addFileName = [this](BuildContracts& b, rt::Json& append) {
		for (auto iter = b._ContractToFilename.begin(); iter != b._ContractToFilename.end(); iter++)
		{
			auto s = append.ScopeAppendingElement();
			append.Object((J(contract) = iter->first, J(source) = iter->second));
		}
	};
	addFileName(solidity, _ScriptVizJson);
	addFileName(preda_wasm, _ScriptVizJson);
	addFileName(preda_native, _ScriptVizJson);

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
	for(int i = 0; i < input_files.GetSize(); i++)
	{
		_ScriptPath = rt::String_Ref(input_files[i]).GetFilePath() + '/';
		ext = rt::String_Ref(input_files[i]).GetExtName().TrimLeft(1);
		ext.MakeLower();
		cur_fn = input_files[i];
		if(ext != "prdts" && ext != "prd" && ext != "sol-json")
		{
			_LOG_WARNING("[PRD]: Invalid file format");
			return;
		}
		else if(ext == "prdts")
		{
			if(input_files.GetSize() > 1)
			{
				_LOG_WARNING("[PRD]: Only one prdts file can be processed at a time");
				return;
			}
			else
			{
				break;
			}
		}
		if(!os::File::LoadText(cur_fn.Begin(), codes.push_back()))
		{
			_LOG_WARNING("[PRD]: Contract source file: " << input_files[i] << " cannot be loaded");
			return;
		}
	}

	if(ext != "prdts")
	{
		if(ext == "sol-json")
		{
			if(input_files.GetSize() > 1)
			{
				_LOG_WARNING("[PRD]: Only one sol-json file can be processed at a time");
				return;
			}
			else
			{
				rt::JsonObject codes_json = codes[0];
				rt::Json new_code;
				if(!_ComposeSolJson(codes_json, new_code, cur_fn))
				{
					return;
				}
				codes[0] = new_code.GetInternalString();
				e = rvm::EngineId::SOLIDITY_EVM;
			}
		}
		WaitUntilIdle();
		if(Compile(e, codes, input_files))
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
			if(!cmd.GetLength())
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
			// String("//") can exist in a string type parameter
			if (pos >= 0 && !(cmd.FindCharacter('{') < pos && pos < cmd.FindCharacterReverse('}')))
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
		_LOG_ERROR("[PRD]: Failed to load PREDA test script: "<< cur_fn);
	}
}

rvm::Scope Simulator::PrepareTxn(rvm::ContractId cid, rvm::OpCode opcode, rvm::BuildNum& buildnum_inout) const
{
	if(buildnum_inout == 0 || buildnum_inout == rvm::BuildNumLatest)
	{
		buildnum_inout = _pGlobalShard->_GetContractEffectiveBuild(cid);
		if(buildnum_inout == 0)return rvm::ScopeInvalid;
	}

	rvm::ContractVersionId cvid = rvm::CONTRACT_SET_BUILD(cid, buildnum_inout);
	auto it = _pGlobalShard->_ContractInfo.find(cvid);
	if(it != _pGlobalShard->_ContractInfo.end())
		return it->second->ScopeOfOpcode[(int)opcode];
	else
	{
		buildnum_inout = 0;
		return rvm::ScopeInvalid;
	}
}

bool Simulator::ExecuteCommand(const rt::String_Ref& cmd_in)
{
	CmdParse cmd(cmd_in, GetLineNum());
	if(!cmd.Identifier.IsEmpty()){
		if (cmd.L1 == "csv")
		{
			return _ExecGenerateBatchTxn(cmd);
		}
		else if(!_TxnPool.has(cmd.Identifier))
		{
			rt::BufferEx<SimuTxn*> empty_buf;
			empty_buf.SetSize(0);
			_TxnPool[cmd.Identifier] = empty_buf;
		}
		else
		{
			_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Identifier \"" << cmd.Identifier << "\" already defined");
			return false;
		}
	}
	if(cmd.L1.IsEmpty() || cmd.Repeat == 0)return false;

	if(cmd.L1 == "allocate")return _ExecAllocate(cmd);
	if(cmd.L1 == "state")return _ExecState(cmd);
	if(cmd.L1 == "chain")return _ExecChain(cmd);
	if(cmd.L1 == "log")return _ExecLog(cmd);
	if(cmd.L1 == "viz")
	{
		return _ExecVisualize(cmd, cmd_in);
	}
	if(cmd.L1 == "random" && cmd.L2 == "reseed")
	{
		int seed;
		if(!cmd.Args.IsEmpty()){
			int succeed = cmd.Args.ToNumber<int>(seed);
			if(succeed < 0)
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
			_LOG("[PRD]: Stopwatch restarted");
			_ScriptStopWatch.Restart();
			_ScriptStopWatch.SetOutputMillisecond();

			_ScriptStopWatchPendingTxnCount = _PendingTxnCount;
			_ScriptStopWatchExecutedTxnCount = _ExecutedTxnCount;

			return true;
		}
		if(cmd.L2 == "report")
		{
			uint64_t lapsed = rt::max<long long>(1LL, _ScriptStopWatch.TimeLapse());

			_LOG_HIGHLIGHT("[PRD]: Stopwatch: "<<lapsed<<" msec\n"
						   "[PRD]: Order: "<<_ShardOrder<<", "
						   "TPS:"<<(_ScriptStopWatchPendingTxnCount - _PendingTxnCount)*1000/lapsed<<", "
						   "uTPS:"<<(_ExecutedTxnCount - _ScriptStopWatchExecutedTxnCount)*1000/lapsed
			);

			return true;
		}
	}

	return _ExecIssueTxn(cmd);
}
uint32_t Simulator::_AddNewUser(rt::String_Ref addrStr, rvm::Address& addr)
{
	auto iter = _NewUserIndex.find(addrStr);
	((oxd::SecureAddress*)&addr)->FromString(addrStr);
	if (iter == _NewUserIndex.end())
	{
		User newUser;
		newUser.Addr = addr;
		newUser.ShardDword = rvm::ADDRESS_SHARD_DWORD(addr);
		uint32_t index = (uint32_t)_Users.GetSize();
		_Users.push_back(newUser);
		_NewUserIndex[addrStr] = index;
		return index;
	}
	else
	{
		return iter->second;
	}
}
SimuTxn* Simulator::_ComposeTxnFromStr(const CmdParse& cmd, rvm::ContractInvokeId& cvid, ContractFunction& fi, TargetParse& target, InputParametrized& input)
{
	rvm::BuildNum build_num = rvm::BuildNumLatest;
	rvm::Scope scope;

	{	EnterCSBlock(_CS);
	if (!_GetContractFunction(cmd, fi))
	{
		return nullptr;
	}

	scope = PrepareTxn(fi.Contract, fi.Op, build_num);
	ASSERT(scope != rvm::ScopeInvalid);
	}
	cvid = rvm::CONTRACT_SET_SCOPE_BUILD(fi.Contract, scope, build_num);

	target = TargetParse(cmd.Args, scope, GetLineNum());
	if (target.IsError())return nullptr;
	if (target.Target.GetLength() > 0 && target.Target[0] == '@' && scope == rvm::Scope::Shard)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Target of a shard function should begin '#'");
		return nullptr;
	}
	else if (target.Target.GetLength() > 0 && target.Target[0] == '#' && scope == rvm::Scope::Address)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Target of a address function should begin '@'");
		return nullptr;
	}
	rt::String argStr = target.ArgsJson;
	if (rvm::CONTRACT_ENGINE(fi.Contract) == rvm::EngineId::SOLIDITY_EVM && !_ParseSolidityFunc(cmd.L2, argStr))
	{
		_LOG_WARNING("[BC] Line " << GetLineNum() << ": Invalid argument json");
		return nullptr;
	}
	if (!input.Parse(target.ArgsJson))
		return nullptr;

	return input.ComposeTxn(cvid, fi.Op);
}
bool Simulator::_ExecGenerateBatchTxn(const CmdParse& cmd)
{
	//csv.from("file_path")
	if (cmd.L2.SubStr(0, 4) == "from")
	{
		rt::String_Ref filePath = cmd.L2.SubStr(6);
		filePath[filePath.GetLength() - 2] = '\0';
		filePath.SetLength(filePath.GetLength() - 2);
		os::FileReadLine csvfile;
		rt::String absoluteFilePath;
		os::File::ResolveRelativePath(_ScriptPath + filePath, absoluteFilePath);
		if (absoluteFilePath.GetExtName() != ".csv")
		{
			_LOG("[PRD] Line " << GetLineNum() << ": Only CSV files allowed");
			return false;
		}
		else if (!csvfile.Open(absoluteFilePath.GetString()))
		{
			_LOG("[PRD] Line " << GetLineNum() << ": Unable to open CSV file, file path: " << filePath);
			return false;
		}

		rt::String_Ref line;
		csvfile.GetNextLine(line);
		if (!line.GetLength())
		{
			_LOG("[PRD] Line " << GetLineNum() << ": Unable to open CSV file");
			return false;
		}
		rt::String_Ref fields;
		int32_t contractPos = -1;
		int32_t funcPos = -1;
		int32_t senderAddrPos = -1;
		int32_t parametersPos = -1;
		rt::String_Ref seg[64];
		uint32_t co = line.Split(seg, 64, ",");
		if (co < 4)
		{
			_LOG("[PRD] Line " << GetLineNum() << ": Invalid input file format. At least 4 fields (contract_name, contract_function, sender, parameters) are required");
			return false;
		}
		for (int i = 0; i < (int32_t)co; i++)
		{
			rt::String_Ref field = seg[i];
			if (field == "contract_name") contractPos = i;
			else if (field == "contract_function") funcPos = i;
			else if (field == "sender") senderAddrPos = i;
			else if (field == "parameters") parametersPos = i;
		}
		if (contractPos == -1 || funcPos == -1 || senderAddrPos == -1 || parametersPos == -1)
		{
			_LOG("[PRD] Line " << GetLineNum() << ": Invalid input file format. At least 4 fields (contract_name, contract_function, sender, parameters) are required");
			return false;
		}
		std::vector<rt::String_Ref> txnSeg(co);
		auto iter = _batchImportTxns.find(cmd.Identifier);
		rt::BufferEx<SimuTxn*> txnList;
		if (iter != _batchImportTxns.end())
		{
			txnList = iter->second;
		}
		while (csvfile.GetNextLine(line))
		{
			uint32_t lineElementCo = line.Split(&txnSeg[0], co, ",");
			if (lineElementCo < co)
			{
				_LOG("[PRD] Line " << GetLineNum() << ": Invalid data format: " << line);
				continue;
			}
			//using Split on json object produce incorrect result
			SSIZE_T openBracketPos = line.FindCharacter('{');
			SSIZE_T closeBracketPos = line.FindCharacterReverse('}');
			if (openBracketPos < 0 || closeBracketPos < 0)
			{
				_LOG("Invalid CSV input: " << line);
				continue;
			}
			rt::String_Ref tmp = line.SubStr(openBracketPos, closeBracketPos - openBracketPos + 1);
			//json in CSV contains two quotation marks for example:{""amount"":1}, codes below replace two quotation marks with one
			std::string str(tmp.Begin(), tmp.GetLength());
			auto strIter = str.begin() + 1;
			bool isP = false;
			while (strIter != str.end())
			{
				char p = '"';
				if (*strIter == p)
				{
					if (isP)
					{
						str.erase(strIter);
						isP = false;
					}
					else
					{
						isP = true;
					}
				}
				else
				{
					isP = false;
				}
				strIter++;
			}
			rt::String_Ref param =  rt::String_Ref(str.c_str());
			rvm::Address addr;
			uint32_t index = 0;
			rt::String commandStr(txnSeg[contractPos]);
			rt::String_Ref targetStr = txnSeg[senderAddrPos];
			//global function: empty, shard function: #shard_index, address function: user_index or address
			bool isAddrTxn = false;
			if (targetStr.GetLength() > 0)
			{
				if (targetStr[0] == '#' && targetStr.TrimLeft(1).HasOnlyNumbers())
				{
					commandStr += rt::SS(".") + txnSeg[funcPos] + rt::SS(" ") + targetStr + rt::SS(" ") + rt::String_Ref(str.c_str());
				}
				else
				{
					isAddrTxn = true;
					index = targetStr.HasOnlyNumbers() ? targetStr.ToNumber<uint32_t>() : _AddNewUser(targetStr, addr);
					commandStr += rt::SS(".") + txnSeg[funcPos] + rt::SS(" @") + index + rt::SS(" ") + rt::String_Ref(str.c_str());
				}
			}
			else
			{
				commandStr += rt::SS(".") + txnSeg[funcPos] + rt::SS(" ") + rt::String_Ref(str.c_str());
			}
			CmdParse cmd(commandStr, GetLineNum());
			ContractFunction fi;
			TargetParse target;
			thread_local InputParametrized input(*this);
			rvm::ContractInvokeId cvid;
			SimuTxn* txn = _ComposeTxnFromStr(cmd, cvid, fi, target, input);
			if (!txn)
			{
				_LOG("Invalid CSV input: " << line);
				continue;
			}
			if (isAddrTxn)
			{
				txn->TargetIndex = index;
				txn->Target = ScopeTarget(addr);
			}
			else
			{
				txn->ShardIndex = targetStr.TrimLeft(1).ToNumber<uint16_t>();
			}
			txnList.push_back(txn);
		}
		_batchImportTxns[cmd.Identifier] = txnList;
	}
	return true;
}

bool Simulator::_ExecVisualize(const CmdParse& cmd, const rt::String_Ref& cmd_in)
{
	bool result = false;
	rt::Json json;
	if(cmd.L2 == "block")
	{

		result = _ExecBlocksLog(cmd, json);
	}
	else if(cmd.L2 == "addr")
	{
		result = _ExecAddrStateLog(cmd, json);
	}
	else if(cmd.L2 == "shard")
	{
		result = _ExecShardStateLog(cmd, json);
	}
	else if(cmd.L2 == "txn")
	{
		result = _ExecTxnLog(cmd, json);
	}
	else if(cmd.L2 == "trace")
	{
		result = _ExecTraceLog(cmd, json);
	}
	else if(cmd.L2 == "section")
	{
		if(!cmd.Args.IsEmpty())
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
	else if(cmd.L2 == "profiling")
	{
		_ExecProfileLog(json);
		result = true;
	}
	else if(cmd.L2 == "all_uint_scope")
	{
		result = _ExecAllKeyedScopeLog(cmd, json);
	}
	else if(cmd.L2.SubStr(0, 4) == "uint")
	{
		result = _ExecKeyedScopeLog(cmd, json);
	}
	if(result)
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
	for(uint32_t sh = 0; sh < _Shards.GetSize(); sh++)
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
	if(!lbracket_exist) {
		lbracket_pos = cmd.Args.GetLength();
	}
	id_name = cmd.Args.SubStr(0, lbracket_pos);
	if(!_TxnPool.has(id_name) || !_TxnPool.get(id_name).GetSize())
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
			_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Negative array index/contains non-number")
			return false;
		}
	}

	if(isTrace && !index_provided && _TxnPool.get(id_name).GetSize() > 1)
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
			if(current_pair.first->Type == rvm::InvokeContextType::RelayInbound && current_pair.first->GetScope() == rvm::Scope::Address)
			{
				User a;
				a.Addr = current_pair.first->Target.addr;
				a.ShardDword = rvm::ADDRESS_SHARD_DWORD(a.Addr);
				current_pair.first->TargetIndex = (int64_t)_Users.Find(a);
			}
			current_pair.first->Jsonify(GetEngine(current_pair.first->GetEngineId()), json);
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
bool Simulator::_ExecAllKeyedScopeLog(const CmdParse& cmd, rt::Json& json)
{
	rt::String contract = DAPP_NAME + rt::SS(".") + cmd.Args;
	if(!_pGlobalShard->_Contracts.has(contract))
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Contract does not exist")
			return false;
	}
	rvm::ContractVersionId cvid = _pGlobalShard->_Contracts.get(contract);
	json.Array();
	rvm::ContractScopeId csid = rvm::ContractScopeIdInvalid;
	rt::BufferEx<SimuAddressContract> key_buf;
	rvm::ScopeKeySized keysize[5] = { rvm::ScopeKeySized::UInt32, rvm::ScopeKeySized::UInt64, rvm::ScopeKeySized::UInt128, rvm::ScopeKeySized::UInt256, rvm::ScopeKeySized::UInt512 };
	uint32_t index = 0;
	for (uint32_t scopeLen = 32; scopeLen <= 512; scopeLen *= 2)
	{
		ScopeTarget tar;
		tar.target_size = (uint8_t)(scopeLen / sizeof(uint64_t));
		csid = rvm::CONTRACT_SET_SCOPE(rvm::CONTRACT_UNSET_BUILD(cvid), rvm::SCOPE_MAKE(rvm::ScopeType::Contract, keysize[index++], 0));
		key_buf.push_back({ tar , csid });
	}
	for (uint32_t sh = 0; sh < _Shards.GetSize(); sh++)
	{
		for (uint32_t i = 0; i < key_buf.GetSize(); i++)
		{
			_Shards[sh]->JsonifyScopeState(json, key_buf[i], true);
		}
	}
	return true;
}
bool Simulator::_ExecKeyedScopeLog(const CmdParse& cmd, rt::Json& json)
{
	rt::String_Ref segs[2];
	auto co = cmd.Args.Split(segs, 2, ' ');
	if(co < 2)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Invalid viz.keyscope format");
		return false;
	}
	rt::String contract = DAPP_NAME + rt::SS(".") + rt::String_Ref(segs[1].Begin(), cmd.Args.End());
	rt::String scopeTarget = segs[0];
	if(scopeTarget != "all" && !scopeTarget.HasOnlyNumbers())
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Invalid scope target");
		return false;
	}
	uint32_t scopeLen = cmd.L2.SubStr(4).ToNumber<uint32_t>();
	if(!_pGlobalShard->_Contracts.has(contract))
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Contract does not exist")
		return false;
	}
	rvm::ContractVersionId cvid = _pGlobalShard->_Contracts.get(contract);
	json.Array();
	rvm::ContractScopeId csid = rvm::ContractScopeIdInvalid;
	std::vector<uint8_t> buf(sizeof(rvm::UInt512));
	ScopeTarget tar;
	//res > 0 means constant out of range
	uint32_t res = 0;
	uint32_t uint32_buf = 0;
	if(scopeTarget != "all")
	{
		switch (scopeLen)
		{
		case 32:
			res = scopeTarget.ToNumber<uint32_t>(uint32_buf) == -1 ? 1 : 0;
			tar = ScopeTarget(uint32_buf);
			csid = rvm::CONTRACT_SET_SCOPE(rvm::CONTRACT_UNSET_BUILD(cvid), rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySized::UInt32, 0));
			break;
		case 64:
			res = (uint32_t)((ttmath::UInt<TTMATH_BITS(64)>*) & buf[0])->FromString(scopeTarget);
			tar = ScopeTarget(*(rvm::UInt64*)&buf[0]);
			csid = rvm::CONTRACT_SET_SCOPE(rvm::CONTRACT_UNSET_BUILD(cvid), rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySized::UInt64, 0));
			break;
		case 128:
			res = (uint32_t)((ttmath::UInt<TTMATH_BITS(128)>*) & buf[0])->FromString(scopeTarget);
			tar = ScopeTarget(*(rvm::UInt128*)&buf[0]);
			csid = rvm::CONTRACT_SET_SCOPE(rvm::CONTRACT_UNSET_BUILD(cvid), rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySized::UInt128, 0));
			break;
		case 256:
			res = (uint32_t)((ttmath::UInt<TTMATH_BITS(256)>*) & buf[0])->FromString(scopeTarget);
			tar = ScopeTarget(*(rvm::UInt256*)&buf[0]);
			csid = rvm::CONTRACT_SET_SCOPE(rvm::CONTRACT_UNSET_BUILD(cvid), rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySized::UInt256, 0));
			break;
		case 512:
			res = (uint32_t)((ttmath::UInt<TTMATH_BITS(512)>*) & buf[0])->FromString(scopeTarget);
			tar = ScopeTarget(*(rvm::UInt512*)&buf[0]);
			csid = rvm::CONTRACT_SET_SCOPE(rvm::CONTRACT_UNSET_BUILD(cvid), rvm::SCOPE_MAKE(rvm::ScopeType::Contract, rvm::ScopeKeySized::UInt512, 0));
			break;
		default:
			return false;
		}
	}
	else
	{
		tar.target_size = (uint8_t)(scopeLen / sizeof(uint64_t));
		csid = rvm::CONTRACT_SET_SCOPE(rvm::CONTRACT_UNSET_BUILD(cvid), rvm::ScopeInvalid);
	}

	if(res > 0)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Scope target is out of range");
		return false;
	}
	SimuAddressContract key{ tar, csid };
	if(scopeTarget == "all")
	{
		for (uint32_t sh = 0; sh < _Shards.GetSize(); sh++)
		{
			_Shards[sh]->JsonifyScopeState(json, key, true);
		}
	}
	else
	{
		uint32_t shardIndex = GetShardIndex(tar);
		if(!_Shards[shardIndex]->JsonifyScopeState(json, key, false))
		{
			_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Scope target does not exist");
			return false;
		}
	}
	return true;
}
bool Simulator::_ConfirmedTxnJsonify(const SimuTxn* txn, rt::Json& append) const
{
	if (txn->ShardIndex == rvm::GlobalShard)
	{
		return _pGlobalShard->ConfirmedTxnJsonify(txn, append);
	}
	else if (txn->ShardIndex >= _Shards.GetSize())
	{
		return false;
	}
	return _Shards[txn->ShardIndex]->ConfirmedTxnJsonify(txn, append);
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
		SimuTxn* txn = _TxnPool.get(no_bracket)[index];
		if (!_ConfirmedTxnJsonify(txn, json)) txn->Jsonify(GetEngine(txn->GetEngineId()), json);
	}
	else
	{
		rt::BufferEx<SimuTxn*> vec = _TxnPool.get(no_bracket);
		for(auto txn_ptr: vec)
		{
			if (!_ConfirmedTxnJsonify(txn_ptr, json)) txn_ptr->Jsonify(GetEngine(txn_ptr->GetEngineId()), json);
		}
	}
	return true;
}

bool Simulator::_ExecBlocksLog(const CmdParse& cmd, rt::Json& json)
{
	if(cmd.Args.IsEmpty())
	{
		_LOG("[PRD] Line " << GetLineNum() << ": Missing block target");
		return false;
	}
	int starting_sh_pos = 0;
	int ending_sh_pos = (int)_Shards.GetSize();
	rt::String_Ref segs[2];
	if(cmd.Args[0] != '#')
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
			if(!segs[0].HasOnlyNumbers() || (co > 1 && !segs[1].HasOnlyNumbers()))
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
		for(; starting_sh_pos < ending_sh_pos; starting_sh_pos++)
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
int32_t Simulator::_GetIndexFromAddrStr(const rt::String& target)
{
	int32_t s;
	rvm::Address addr;
	((oxd::SecureAddress*)&addr)->FromString(target);
	if (((oxd::SecureAddress*)&addr)->IsValid())
	{
		s = _AddNewUser(target, addr);
	}
	else if (target == "random")
	{
		s = GetScriptRandomAddressIndex();
	}
	else if (target.ToNumber<int32_t>(s) < 0)
	{
		return -1;
	}
	return s;
}

bool Simulator::_ExecAddrStateLog(const CmdParse& cmd, rt::Json& json)
{
	rt::String_Ref segs[2];
	auto co = cmd.Args.Split(segs, 2, ' ');
	rt::String contract = co > 1 ? rt::String_Ref(segs[1].Begin(), cmd.Args.End()) : rt::String();
	if(contract.FindCharacter('.') == -1)
		contract = DAPP_NAME + '.' + contract;
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
	rvm::ContractVersionId cvid = (co > 1) ? _pGlobalShard->_Contracts.get(contract) : rvm::ContractVersionIdInvalid;
	json.Array();

	int32_t s = _GetIndexFromAddrStr(target);

	rvm::ContractId cid = rvm::CONTRACT_UNSET_BUILD(cvid);
	if(target == "all")
	{
		for(int sh = 0; sh < _Shards.GetSize(); sh++)
		{
			_Shards[sh]->JsonifyAllAddressStates(json, GetUsers(), cid);
		}
	}
	else if(s >= 0 && s<_Users.GetSize())
	{
		rvm::Address addr = _Users[s].Addr;
		GetShard(GetShardIndex(addr))->JsonifyAddressState(json, &addr, GetUsers(), cid);
	}
	else
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Invalid viz.addr target");
		return false;
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
	else if(!shardReq && trimmed == "random")
	{
		target = trimmed;
		return true;
	}

	rvm::Address addr;
	((oxd::SecureAddress*)&addr)->FromString(trimmed);
	if (((oxd::SecureAddress*)&addr)->IsValid())
	{
		target = trimmed;
		return true;
	}
	if(!trimmed.HasOnlyNumbers())
	{
		_LOG_WARNING("[PRD] Line " << LineNum << ": Target index must only contain digits");
		return false;
	}
	int target_num;
	int succeed = trimmed.ToNumber<int>(target_num);
	if(succeed < 0)
	{
		_LOG("[PRD] Line " << LineNum << ": Invalid target index")
		return false;
	}
	if(shardReq && target_num >= _Shards.GetSize())
	{
		_LOG("[PRD] Line " << LineNum << ": Shard index is out of range")
		return false;
	}
	else if(!shardReq && target_num >= _Users.GetSize())
	{
		_LOG("[PRD] Line " << LineNum << ": Address index is out of range")
		return false;
	}
	else if(target_num < 0)
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
	rt::String contract = co > 1 ? DAPP_NAME + rt::SS(".") + rt::String_Ref(segs[1].Begin(), cmd.Args.End()) : rt::String();
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

	rvm::ContractVersionId cvid = (co > 1) ? _pGlobalShard->_Contracts.get(contract) : rvm::ContractVersionIdInvalid;
	rvm::ContractId cid = rvm::CONTRACT_UNSET_BUILD(cvid);
	json.Array();
	if(target == "all")
	{
		for(int sh = 0; sh < _Shards.GetSize(); sh++)
		{
			succeed = _Shards[sh]->JsonifyShardState(json, cid);
		}
	}
	else if(target == "g" || target == "global")
	{
		succeed = _pGlobalShard->JsonifyShardState(json, cid);
	}
	else
	{
		int s = target.ToNumber<int>();
		succeed = _Shards[s]->JsonifyShardState(json, cid);
	}

	if(!succeed)
	{
		json.Empty();
		return false;
	}
	return true;
}
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
		if(_Users.GetSize() == 0)
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
		{
			_ChainIdle.Reset();
			_pGlobalShard->Step();
			WaitUntilIdle();
		}

		return true;
	}
	else if(cmd.L2 == "run")
	{
		return _Step();
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
		_LOG("[PRD]: Total Txn:"<<_PendingTxnCount<<'/'<<_ExecutedTxnCount);
	}
	else if (cmd.L2 == "gaslimit" || cmd.L2 == "gaslimit.global")
	{
			return _SetGasLimit(cmd.Args, cmd.L2 == "gaslimit"? _ScriptGasLimit: _ScriptGlobalGasLimit);
	}
	else if(cmd.L2 == "deploy")
	{
		_RunDeployAsTxn(cmd);
		return true;
	}
	else if (cmd.L2 == "batch_insert_txn")
	{
		return _BatchInsertTxn(cmd.Args);
	}
	return false;
}
bool Simulator::_SetGasLimit(const rt::String_Ref& args, uint64_t& gaslimit)
{
	int succeed = args.ToNumber<uint64_t>(gaslimit);
	if (gaslimit == 0 || succeed < 0)
	{
		_LOG("[PPD] Line " << GetLineNum() << ": Illeage gaslimit input");
		gaslimit = 10000;
		return false;
	}
	return true;
}
bool Simulator::_BatchInsertTxn(const rt::String_Ref& csvData)
{
	auto iter = _batchImportTxns.find(csvData);
	if (iter == _batchImportTxns.end())
	{
		_LOG("[PPD] Line " << GetLineNum() << ": CSV data does not exist");
		return true;
	}
	rt::BufferEx<SimuTxn*>& buf = iter->second;
	for (uint32_t i = 0; i < buf.GetSize(); i++)
	{
		rvm::Scope scope = buf[i]->GetScope();
		switch (scope)
		{
			case rvm::Scope::Shard:
			{
				_Shards[buf[i]->ShardIndex]->PushNormalTxn(buf[i]);
			}
			break;
			case rvm::Scope::Global:
			{
				GetGlobalShard()->PushNormalTxn(buf[i]);
			}
			break;
			default:
			{
				_Shards[ADDRESS_SHARD_DWORD(buf[i]->Target.addr) & _ShardBitmask]->PushNormalTxn(buf[i]);
			}
		}
	}
	return true;
}
bool Simulator::_Step()
{
	if(_Users.GetSize() == 0)
	{
		_LOG("[PRD]: No address has been allocated. Use \"allocate.address\" to create address");
		return false;
	}
	_bChainStepping = false;
	_bChainPaused = false;
	for (int i = 0; i < _Shards.GetSize(); i++)
	{
		_ShardPendingTxn[i] = _Shards[i]->GetPendingTxnCount();
	}
	_ShardPendingTxn.push_back(GetGlobalShard()->GetPendingTxnCount());
	if(_bShardAsync)
	{
		for (auto p : _Shards)
			p->Step();
	}
	else
		_pGlobalShard->Step();
	_ConvertQueueToTxnPool();
	WaitUntilIdle();
	_bChainPaused = true;
	return true;
}

void Simulator::_RunDeployAsTxn(const CmdParse& cmd)
{
	SimuTxn* deployTxn;
	TargetParse target(cmd.Args, rvm::Scope::Address, GetLineNum());
	int32_t userIndex = _GetIndexFromAddrStr(target.Target.TrimLeft(1));
	deployTxn = SimuTxn::Create((uint32_t)cmd.Args.GetLength(), 0);
	if (userIndex >= 0 && userIndex < _Users.GetSize() && target.Target[0] == '@')
	{
		deployTxn->Target = ScopeTarget(_Users[userIndex].Addr);
	}
	else
	{
		_LOG("[PRD] Line " << GetLineNum() << ": Invalid deploy initiator");
		return;
	}
	deployTxn->Type = rvm::InvokeContextType::System;
	deployTxn->Timestamp = os::Timestamp::Get();
	deployTxn->Flag = (SimuTxnFlag)0;
	ASSERT(deployTxn->TokensSerializedSize == 0);
	memcpy(deployTxn->SerializedData, target.ArgsJson.Begin(), target.ArgsJson.GetLength());
	deployTxn->ArgsSerializedSize = (uint32_t)target.ArgsJson.GetLength();

	sec::Hash<sec::HASH_SHA256>().Calculate(((char*)deployTxn) + sizeof(rvm::HashValue), deployTxn->GetSize() - sizeof(rvm::HashValue), &deployTxn->Hash);

	GetGlobalShard()->PushNormalTxn(deployTxn);
	_Step();
}

rvm::InvokeResult Simulator::DeployFromStatement(const rt::String_Ref& deployStatement)
{
	rvm::InvokeResult ret{ 0, 0, rvm::InvokeErrorCode::Success, 0, nullptr };
	if(deployStatement.IsEmpty())
	{
		_LOG("[PPD] Line " << GetLineNum() << ": No deploy target");
		return ret;
	}

	// parsing filename1 filename2  .... 
	// parsing filename1={ json_argument } filename2  .... 
	static const size_t file_count_max = 256;
	rt::String_Ref fns[file_count_max], args[file_count_max];
	uint32_t co = 0;

	const char* p = deployStatement.Begin();
	const char* end = deployStatement.End();
	rt::CharacterSet sep = " ="; // possible characters as separator between filenames
	while (p < end && co < file_count_max)
	{
		rt::String_Ref remain(p, end), filename;
		auto seg_end = remain.FindCharacter(sep);
		bool has_argument = false;
		if(seg_end == 0)
		{
			p++;
			continue;
		}
		if(seg_end < 0)
			seg_end = remain.GetLength();
		else
			has_argument = remain[seg_end] == '=';
		fns[co] = filename = rt::String_Ref(p, seg_end).TrimSpace();
		auto& arg = args[co];
		co++;
		if(has_argument && !filename.IsEmpty())
		{
			remain = rt::String_Ref(&remain[seg_end + 1], end).TrimLeftSpace();
			if(!remain.IsEmpty() && remain[0] == '{')
			{
				arg = rt::JsonObject::GetFirstObject(remain);
				if(!arg.IsEmpty())
				{
					p = arg.End();
					SSIZE_T beginPos = arg.FindCharacter('$');
					SSIZE_T endPos = beginPos == -1 ? -1 : arg.FindCharacter("$", beginPos + 1);
					if (beginPos != -1 && arg.SubStr(beginPos + 2, endPos - beginPos - 2).HasOnlyNumbers())
					{
						InputParametrized input(*this);
						input.Parse(arg);
						rt::String newArg;
						input.Evaluate(newArg);
						SSIZE_T len = newArg.GetLength();
						char* addrStr = (char*)_Malloc8AL(char, len + 1);
						memset(addrStr, '\0', len + 1);
						memcpy(addrStr, newArg.Begin(), len);
						args[co - 1] = rt::String_Ref(addrStr, len);
					}
					while (p < end && !sep.Has(*p))
						p++;
					if(*p != '=')
					{
						p++;
						continue;
					}
				}
			}
		}
		else
		{
			p += seg_end + 1;
			continue;
		}
		_LOG_WARNING("[PPD] Line " << GetLineNum() << ": Deploy arguemnt of `" << filename << "` are ill-formatted");
		return ret;
	}

	if(!co)
	{
		_LOG("[PPD] Line " << GetLineNum() << ": No deploy target");
		return ret;
	}

	if(!Deploy(_pGlobalShard->GetExecuteUnits(), fns, args, co, true, ret))
		_ScriptAborted = true;

	return ret;
}

rt::String_Ref Simulator::_LookupFunctionName(const rvm::Contract* c, rvm::OpCode op)
{
	uint32_t co = c->GetFunctionCount();
	for(uint32_t i=0; i<co; i++)
		if(c->GetFunctionOpCode(i) == op)
			return c->GetFunctionName(i).Str();

	return nullptr;
}

void Simulator::DebugPrint(rvm::DebugMessageType type, const rvm::ConstString* text, const rvm::ExecutionState* ctx, const rvm::Contract* contract, int32_t line)
{
	rvm::BlockchainRuntime_DebugPrint(type, text, ctx, contract, line);
}

Simulator::CmdParse::CmdParse(const rt::String_Ref& cmd, uint32_t LineNum)
{
	int64_t identifier_pos = cmd.FindCharacter('='); // `=` shouldn't parse the entire line, it could be some text containing `=` after the actual command verb
	bool IDexist = identifier_pos != -1 && identifier_pos < cmd.FindCharacter('.');
	if(IDexist)
	{
		Identifier = cmd.SubStr(0, identifier_pos - 1);
		Identifier = Identifier.TrimSpace();
		if(Identifier.FindCharacter(" @#$%^&*()=+.") != -1)
		{
			_LOG_WARNING("[PRD] Line " << LineNum << ": Transaction identifier contains illegal symbol");
			return;
		}

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

	rt::String_Ref cmd_no_assign = !IDexist ? cmd : cmd.SubStr(identifier_pos + 1).TrimSpace();
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
		if(repeatStr.GetLength() == 0 || !repeatStr.HasOnlyNumbers())
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
		if(!cmd.Args.HasOnlyNumbers() || add <= 0 || succeed < 0)
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
			rvm::ADDRESS_SET_SECSUITE(a.Addr, rvm::SecSuite::Ed25519);
			a.ShardDword = rvm::ADDRESS_SHARD_DWORD(a.Addr);

			auto& co = count[a.ShardDword&_ShardBitmask];
			if(co < add_per)
			{
				i++;
				co++;
			}
		}

		_LOG("[PRD]: " << add << " addresses added and evenly distributed in shards");
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
	_ScriptGasLimit = _ScriptGlobalGasLimit = 100000000;
	_bChainPaused = true;

	_PendingTxnCount = 0;
	_ExecutedTxnCount = 0;
	_ChainIdle.Set();

	uint32_t shard_count = 1<<_ShardOrder;
	_ShardBitmask = rvm::ADDRESS_SHARD_BITMASK(_ShardOrder);

	uint64_t time_base = os::Timestamp::Get();
	_pGlobalShard = _New(SimuGlobalShard(this, time_base, _ShardOrder));

	_Shards.SetSize(shard_count);
	_ShardPendingTxn.SetSize(shard_count);
	for(uint32_t i=0; i<shard_count; i++)
		_Shards[i] = _New(SimuShard(this, time_base, _ShardOrder, i, _pGlobalShard));

	_pGlobalShard->Init();
	for(auto p : _Shards)
		p->Init();

	if(!_CompileOnly) _LOG("[PRD]: Chain initialized with "<<shard_count<<" shard(s), in "<<(_bShardAsync?"async":"sync")<<"-sharding mode");
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
				_LOG_WARNING("[PRD] Line " << LineNum << ": Missing argments json");
				Target.Empty();
			}
		}
		else
		{
			_LOG_WARNING("[PRD] Line " << LineNum << ": '"<<Target<<"' is not a legal target");
			Target.Empty();
			ArgsJson.Empty();
		}
	}
}
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

bool Simulator::_ModifyState(rvm::ContractInvokeId ciid, InputParametrized& input, const rt::String_Ref& in_state, bool replace, SimuShard* s, const rvm::ScopeKey& sk)
{
	if(input.Parse(in_state))
	{
		rvm::Scope scope = rvm::CONTRACT_SCOPE(ciid); 
		rvm::StringStreamImpl state_json;
		if(!replace)
		{	// get existing state
			rvm::ConstStateData stateData{ nullptr, 0 , 0}; 
			switch (scope) 
			{ 
			case rvm::Scope::Global: 
				stateData = _pGlobalShard->GetState(-ciid);
				break;
			case rvm::Scope::Shard:
				ASSERT(s);
				stateData = s->GetState(-ciid); 
				break;
			default:
				ASSERT(s);
				SimuAddressContract k{ ScopeTarget(sk), -ciid };
				const SimuState* state = s->GetAddressState(k);
				if (state)
				{
					stateData.DataPtr = state->Data;
					stateData.DataSize = state->DataSize;
				}
				break;
			}

			const rvm::ConstData data { stateData.DataPtr, stateData.DataSize }; 
			rvm::RvmEngine* pEngine = GetEngine(rvm::CONTRACT_ENGINE(ciid)); 
			if(!pEngine)return false;
 
			if (!pEngine->StateJsonify(ciid, &data, &state_json))
				return false;
		}

		auto build = rvm::CONTRACT_BUILD(ciid);
		rvm::ConstData buf;
		if (!input.ComposeState(buf, ciid, 0, state_json.GetString().Str()))
			return false;

		switch(scope)
		{ 
		case rvm::Scope::Global: 
			_pGlobalShard->SetState(-ciid, SimuState::Create(buf.DataSize, build, buf.DataPtr));
			break;
		case rvm::Scope::Shard:
			ASSERT(s);
			s->SetState(-ciid, SimuState::Create(buf.DataSize, build, buf.DataPtr));
			break;
		case rvm::Scope::Address:
			ASSERT(s);
			ASSERT(sk.Size == sizeof(rvm::Address));
			s->SetState(-ciid, *(rvm::Address*)sk.Data, SimuState::Create(buf.DataSize, build, buf.DataPtr));
			break;
		default:
			ASSERT(0);
		}

		return true;
	}

	return false;
}

bool Simulator::_ParseInvokeIdentifier(const rt::String_Ref& str, int line_num, InvokeIdentifier& out) const
{
	uint32_t co = str.Split(&out.DApp, 3, '.');

	if(co == 1)
	{
		out.Scope = "global";
		out.Contract = out.DApp;
		out.DApp = DAPP_NAME;
	}
	else if(co == 2)
	{
		out.Scope = out.Contract;
		out.Contract = out.DApp;
		out.DApp = DAPP_NAME;
	}

	rvm::Scope scope;
	if(out.Scope == "address"){ scope = rvm::Scope::Address; }
	else if(out.Scope == "shard"){ scope = rvm::Scope::Shard; }
	else if(out.Scope == "global"){ scope = rvm::Scope::Global; }
	else
	{
		_LOG("[PRD] Line " << line_num << ": '"<<out.Scope<<" is not a legal scope identifier, which should be `addess/shard/global`");
		return false;
	}

	rvm::ContractVersionId cvid = _pGlobalShard->_Contracts.get(out.DApp + '.' + out.Contract, rvm::ContractVersionIdInvalid);
	bool isUnnameContract = out.Contract.HasOnlyNumbers();
	rt::String contractName;
	if ((isUnnameContract && !_ResolveUnnameContract(out.Contract, rt::String_Ref(), contractName, cvid)) || cvid == rvm::ContractVersionIdInvalid)
	{
		_LOG("[PRD] Line " << line_num << ": Contract '"<<out.DApp<<'.'<<out.Contract<<"' is not found");
		return false;
	}

	out.CIID = cvid + scope;
	return true;
}
bool Simulator::_ResolveUnnameContract(const rt::String_Ref unnameContract, rt::String_Ref contractFunc, rt::String& contractName, rvm::ContractVersionId& originalCvid) const
{
	rvm::ContractVersionId cvid = (rvm::ContractVersionId)unnameContract.ToNumber<uint64_t>();
	oxd::ContractsDatabase::ContractInfo* info = _pGlobalShard->_ContractInfo.get(cvid);
	if (info)
	{
		for (auto& it : _pGlobalShard->_ContractInfo)
		{
			if (rt::IsEqual(it.second->Deployment.Module, info->Deployment.Module))
			{
				//make sure originalCvid is named
				bool isNamed = false;
				for (auto& named_it : _pGlobalShard->_Contracts)
				{
					if (named_it.second == it.first)
					{
						isNamed = true;
						contractName = named_it.first + rt::SS(".") + contractFunc;
					}
				}
				originalCvid = cvid;
				if (isNamed)
				{
					return true;
				}
			}
		}
		if (originalCvid == rvm::ContractVersionIdInvalid)
		{
			return false;
		}
	}
	return false;
}
bool Simulator::_ExecState(const CmdParse& cmd)
{
	thread_local InputParametrized input(*this);

	if(cmd.L2 == "set" || cmd.L2 == "update")
	{
		bool replace = cmd.L2 == "set";

		rt::String_Ref contract = cmd.Args.TrimAfter(" \t\r\n");

		InvokeIdentifier iid;
		if(!_ParseInvokeIdentifier(contract, GetLineNum(), iid))
			return false;

		rvm::Scope scope = rvm::CONTRACT_SCOPE(iid.CIID);

		TargetParse args(rt::String_Ref(contract.End(), cmd.Args.End()), scope, GetLineNum());
		if(args.IsError())return false;
		
		bool ret;
		switch(scope)
		{
			case rvm::Scope::Global:
				ret = _ModifyState(iid.CIID, input, args.ArgsJson, replace);
				break;
			case rvm::Scope::Shard:
			{
				rt::String target = args.Target;
				if(!_ProcessTargetRequest(target, GetLineNum(), true))
					return false;

				if(target == "all")
				{
					for(auto s: _Shards)
					{
						if(!_ModifyState(iid.CIID, input, args.ArgsJson, replace, s))
						{
							_LOG("[PRD] Line " << GetLineNum() << ": Failed to modify State in shard #"<<s->GetShardIndex());
							return false;
						}
					}
				}
				else
				{
					uint32_t s = target.ToNumber<int>();
					if(s>=0 && s<_Shards.GetSize())
					{
						if(!_ModifyState(iid.CIID, input, args.ArgsJson, replace, _Shards[s]))
						{
							_LOG("[PRD] Line " << GetLineNum() << ": Failed to modify State in shard #"<<_Shards[s]->GetShardIndex());
							return false;
						}
					}
					else
					{
						_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Shard index "<<s<<" is out of range, should be [0, "<<_Shards.GetSize()-1<<']');
						return false;
					}
				}

				return true;
			}
			case rvm::Scope::Address:
			{
				rt::String target = args.Target;
				if(!_ProcessTargetRequest(target, GetLineNum(), false))
					return false;

				if(target == "all")
				{
					for(auto& a : _Users)
					{
						if(!_ModifyState(iid.CIID, input, args.ArgsJson, replace, _Shards[a.ShardDword & _ShardBitmask], ScopeKeyPOD(a.Addr)))
						{
							_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Failed to modify state of address "<<b32a(a.Addr));
							return false;
						}
					}

					return true;
				}
				else if(target == "random")
				{
					for(int i=0; i<cmd.Repeat; i++)
					{
						thread_local uint32_t last = 0;
						last = (_ScriptRand.GetNext() + last)%_Users.GetSize();

						auto& a = _Users[last];
						if(!_ModifyState(iid.CIID, input, args.ArgsJson, replace, _Shards[a.ShardDword & _ShardBitmask], ScopeKeyPOD(a.Addr)))
						{
							_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Failed to modify state "<<b32a(a.Addr));
							return false;
						}
					}

					return true;
				}
				else
				{
					uint32_t s = target.ToNumber<int>();
					if(s>=0 && s<_Users.GetSize())
					{
						auto& a = _Users[s];
						ret = _ModifyState(iid.CIID, input, args.ArgsJson, replace, _Shards[a.ShardDword & _ShardBitmask], ScopeKeyPOD(a.Addr));
					}
					else
					{
						_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Address index "<<s<<" is out of range, should be [0, "<<_Users.GetSize()-1<<']');
						return false;
					}
				}
			}
		}

		if(ret)return true;
		_LOG("[PRD] Line " << GetLineNum() << ": Failed to modify State");
	}
	else if(cmd.L2 == "token")
	{
		rt::String_Ref segs[10];
		uint32_t co = cmd.Args.Split<true>(segs, sizeofArray(segs), " \t\r\n");
		if(segs[0] == "mint" && segs[2] == "by")
		{
			InvokeIdentifier iid;
			if(!_ParseInvokeIdentifier(segs[3], GetLineNum(), iid))
				return false;

			rvm::TokenId token = rvm::TokenIdFromSymbol(segs[1]);
			if(token == rvm::TokenIdInvalid)
			{
				_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Token symbol `"<<segs[1]<<"` is ill-formatted");
				return false;
			}

			// add supplier
			{
				CoreContractState<CORE_TOKEN_SUPPLIERS> state = _pGlobalShard->GetState(-CORE_TOKEN_SUPPLIERS);
				auto m = state.DeriveMutable();
				m.Set(rvm::UInt128{ (uint64_t)token, (uint64_t)-~iid.CIID }, rvm::TokenMinterFlag::Allowed);
				_pGlobalShard->SetState(-CORE_TOKEN_SUPPLIERS, state.CreateState(m, rvm::CONTRACT_BUILD(iid.CIID)));
			}

			// assign token default
			{
				CoreContractState<CORE_CONTRACT_DEFAULT> state = _pGlobalShard->GetState(-CORE_CONTRACT_DEFAULT);
				if(state.IsEmpty() || !state->Has(-~iid.CIID))
				{
					auto m = state.DeriveMutable();
					m.Set(-~iid.CIID, token);
					_pGlobalShard->SetState(-CORE_CONTRACT_DEFAULT, state.CreateState(m, rvm::CONTRACT_BUILD(iid.CIID)));
				}
			}

			return true;
		}
	}
	else if (cmd.L2 == "load" || cmd.L2 == "save")
	{
		rt::String_Ref segs[2];
		int co = cmd.Args.Split(segs, 2, ' ');
		rt::String_Ref targetSegs[2];
		segs[0].Split(targetSegs, 2, '.');
		if (cmd.L2 == "load")
		{
			return _ReadStateFromFile(segs[1], targetSegs);
		}
		else
		{
			rvm::ContractVersionId cvid = targetSegs[1] != rt::SS("all") ? _pGlobalShard->_Contracts.get(DAPP_NAME + rt::SS(".") + targetSegs[1]) : rvm::ContractVersionIdInvalid;
			_SaveStateToFile(segs[1], targetSegs[0], cvid);
			return true;
		}
	}
	return false;
}

uint32_t Simulator::GetScriptRandomAddressIndex() const
{
	EnterCSBlock(_RandScriptCS);
	for(;;)
	{
		uint32_t r = _ScriptRand.GetNext();
		if(r < _UserIndexRandMax)
		{
			return r%_Users.GetSize();
		}
	}
}

bool Simulator::_ParseSolidityFunc(const rt::String& functionName, rt::String& argument)
{
	rt::Json args;
	args.Object();
	args.MergeObject(argument);
	if(!args.GetLength())
	{
		return false;
	}
	args.AppendKeyWithString("SolFunctionName", functionName);
	argument = args.GetInternalString();
	return true;
}

bool Simulator::_GetContractFunction(const CmdParse& cmd, ContractFunction& fi) const
{
	bool isUnnameContract = cmd.L1.HasOnlyNumbers();
	rvm::ContractVersionId cvid = rvm::ContractVersionIdInvalid;
	rt::String contractName(cmd.L1.Begin(), cmd.L2.End());
	contractName = rt::SS(DAPP_NAME) + rt::SS(".") + contractName;
	if (isUnnameContract && !_ResolveUnnameContract(cmd.L1, cmd.L2, contractName, cvid))
	{
		return false;
	}
	rt::BufferEx<ContractFunction> buf = rt::_CastToConst(_pGlobalShard->_ContractFunctions).get(contractName, rt::BufferEx<ContractFunction>());
	if(buf.GetSize() == 0)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Contract function '" << rt::String_Ref(cmd.L1.Begin(), cmd.L2.End()) << "' is not found");
		return false;
	}
	else if(rvm::CONTRACT_ENGINE(buf[0].Contract) == rvm::EngineId::SOLIDITY_EVM)
	{
		fi = buf[0];
		return true;
	}
	UINT maxVarMatched = 0;
	bool matched = false;
	UINT minSignatureLength = 1024;
	for(int i = 0; i < buf.GetSize(); i++)
	{
		UINT numVarMatched = 0;
		rt::JsonObject args_json(cmd.Args);
		rt::String funcSignature = buf[i].FunctionSignature;
		if(funcSignature.GetLength() == 0 && args_json.IsEmptyObject()) //empty json won't enter the while loop below
		{
			fi = buf[i];
			maxVarMatched++;
			break;
		}
		rt::BufferEx<rt::String_Ref> args_sets;
		args_sets.ExpandSize(1024);
		uint32_t signatureLen = funcSignature.Split(&args_sets[0], 1024, " ");
		rt::JsonKeyValuePair p;
		while (args_json.GetNextKeyValuePair(p))
		{
			rt::String_Ref varName = p.GetKey();
			if(varName.FindCharacter("$)") != -1)
			{
				int64_t nextKeyPos = cmd.Args.FindCharacter(',', varName.Begin() - cmd.Args.Begin());
				int64_t nextColonPos = cmd.Args.FindCharacter(':', nextKeyPos);
				if(nextKeyPos == -1)
				{
					continue;
				}
				nextKeyPos++;
				varName = cmd.Args.SubStr(nextKeyPos, nextColonPos - nextKeyPos).TrimSpace();
			}
			if(args_sets.Find(varName) != -1)
			{
				numVarMatched++;
			}
			else
			{
				matched = false;
				break;
			}
			matched = true;
		}
		if(matched && numVarMatched >= maxVarMatched && signatureLen < minSignatureLength )
		{
			fi = buf[i];
			maxVarMatched = numVarMatched;
			minSignatureLength = signatureLen;
		}
	}
	if(maxVarMatched == 0)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Invalid function argument/s");
		return false;
	}
	if (isUnnameContract)
	{
		fi.Contract = rvm::CONTRACT_UNSET_BUILD(cvid);
	}
	return true;
}
bool Simulator::_ExecIssueTxn(const CmdParse& cmd)
{
	ContractFunction fi;
	TargetParse target;
	thread_local InputParametrized input(*this);
	rvm::ContractInvokeId cvid;
	auto* txn = _ComposeTxnFromStr(cmd, cvid, fi, target, input);
	if (!txn)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Unable to compose transaction");
		return false;
	}
	bool identifier_exist = !cmd.Identifier.IsEmpty();
	switch(txn->GetScope())
	{
	case rvm::Scope::Global:
	{
		if(input.IsLoopIndexInvolved())
		{
			if(identifier_exist && !cmd.Identifier_isArray)
			{
				_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Identifier type of multiple txns must be array");
				return false;
			}
			auto* param = &input; // input in this thread should be used in all loop threads
			auto loop = [this,&cmd,txn,cvid,fi,param,identifier_exist](int i) {
				if(i >= _Users.GetSize())return false;
				for(int repeat = 0; repeat < cmd.Repeat; repeat++)
				{
					SimuTxn* t = param->IsParameterized() ? param->ComposeTxn(cvid, fi.Op, i) : txn->Clone();
					if(!t)
					{
						return false;
					}
					_pGlobalShard->PushNormalTxn(t);
					if(identifier_exist) _IdTxnQueue.Push({ cmd.Identifier, t });
				}
				return true;
			};

			os::ParallelLoop(loop);
			_SafeRelease(txn);
		}
		else
		{
			for(int repeat = 0; repeat < cmd.Repeat; repeat++)
			{
				SimuTxn* duplicates = input.IsParameterized() ? input.ComposeTxn(cvid, fi.Op, repeat) : txn->Clone();
				_pGlobalShard->PushNormalTxn(duplicates);
				if(identifier_exist) _IdTxnQueue.Push({ cmd.Identifier, duplicates });
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
				_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Identifier type of multiple txns must be array");
				return false;
			}
			for(uint32_t i = 0; i < _Shards.GetSize(); i++) {
				for(int repeat = 0; repeat < cmd.Repeat; repeat++)
				{
					SimuTxn* t = input.IsParameterized() ? input.ComposeTxn(cvid, fi.Op, i) : txn->Clone();
					if(!t)
					{
						return false;
					}
					_Shards[i]->PushNormalTxn(t);
					if(identifier_exist) _IdTxnQueue.Push({ cmd.Identifier, t });
				}
			}
		}
		else
		{
			uint32_t s = sh_target.ToNumber<int>();
			if(s>=0 && s<_Shards.GetSize())
			{
				for(int repeat = 0; repeat < cmd.Repeat; repeat++)
				{
					SimuTxn* duplicates = input.IsParameterized() ? input.ComposeTxn(cvid, fi.Op, repeat) : txn->Clone();;
					_Shards[s]->PushNormalTxn(duplicates);
					if(identifier_exist) _IdTxnQueue.Push({ cmd.Identifier, duplicates });
				}
			}
			else
			{
				_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Shard index "<<s<<" is out of range, should be [0, "<<_Shards.GetSize()-1<<']');
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
			auto loop = [this,&cmd,txn,fi,cvid,param,identifier_exist](int i) {
				if(i >= cmd.Repeat)return false;

				uint32_t last;
				last = GetScriptRandomAddressIndex();

				auto& a = _Users[last];

				SimuTxn* t = param->IsParameterized()?param->ComposeTxn(cvid, fi.Op, i):txn->Clone();
				if(!t)
				{
					return false;
				}
				t->Target = ScopeTarget(a.Addr);
				t->TargetIndex = last;
				_Shards[a.ShardDword&_ShardBitmask]->PushNormalTxn(t);
				if(identifier_exist) _IdTxnQueue.Push({cmd.Identifier, t});
				return true;
			};

			os::ParallelLoop(loop);
			_SafeRelease(txn);
		}
		else if(addr_target == "all")
		{
			if(identifier_exist && !cmd.Identifier_isArray)
			{
				_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Identifier type of multiple txns must be array");
				return false;
			}
			auto* param = &input; // input in this thread should be used in all loop threads
			auto loop = [this,&cmd,txn,fi,cvid,param,identifier_exist](int i) {
				if(i >= _Users.GetSize())return false;
				for(int repeat = 0; repeat < cmd.Repeat; repeat++)
				{
					SimuTxn* t = param->IsParameterized() ? param->ComposeTxn(cvid, fi.Op, i) : txn->Clone();
					if(!t)
					{
						return false;
					}
					auto& a = _Users[i];
					t->Target = ScopeTarget(a.Addr);
					t->TargetIndex = i;
					_Shards[a.ShardDword & _ShardBitmask]->PushNormalTxn(t);
					if(identifier_exist) _IdTxnQueue.Push({ cmd.Identifier, t });
				}
				return true;
			};

			os::ParallelLoop(loop);
			_SafeRelease(txn);
		}
		else
		{
			int32_t s = _GetIndexFromAddrStr(addr_target);
			if(s>=0 && s<_Users.GetSize())
			{
				auto& a = _Users[s];
				txn->Target = ScopeTarget(a.Addr);
				txn->TargetIndex = s;

				auto* param = &input; // input in this thread should be used in all loop threads
				auto loop = [this,&cmd,txn,&a,fi,cvid,param,identifier_exist, s](int i) {
					if(i >= cmd.Repeat)return false;

					SimuTxn* t = param->IsParameterized()?param->ComposeTxn(cvid, fi.Op, i):txn->Clone();
					if(!t)
					{
						return false;
					}
					t->Target = ScopeTarget(a.Addr);
					t->TargetIndex = s;
					_Shards[a.ShardDword&_ShardBitmask]->PushNormalTxn(t);
					if(identifier_exist) _IdTxnQueue.Push({cmd.Identifier, t});
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
		_LOG_WARNING("[PRD]: Template visualization webpage can not be loaded: "<<templ);
		return false;
	}

	auto pos = html.FindString("</HEAD>");
	if(pos == -1)pos = html.FindString("</head>");
	if(pos == -1)
	{
		_LOG_WARNING("[PRD]: No <HEAD> tag found in template visualization webpage: "<<templ);
	}

	rt::String out;

	out = html.SubStr(0, pos);
	out += "\n<script type=\"text/javascript\">\nvar PREDA_VIZ_LOG = `\n";
#if defined(PLATFORM_DEBUG_BUILD)
	out += rt::JsonBeautified(_ScriptVizJson);
#else
	out += _ScriptVizJson;
#endif
	out += "`;\n</script>\n\n";

	out += html.SubStr(pos);

	if(!os::File::SaveText(ALLOCA_C_STRING(output), out))
	{
		_LOG_WARNING("[PRD]: Failed to save visualization webpage: "<<out);
		return false;
	}

	return true;
}
void Simulator::_SaveStateToFile(const rt::String_Ref& filename, const rt::String& scope, rvm::ContractVersionId cvid)
{
	os::File stateFile;
	rt::String absoluteFilePath;
	os::File::ResolveRelativePath(_ScriptPath + filename, absoluteFilePath);
	stateFile.Open(absoluteFilePath.Begin(), os::File::Normal_Write, true);
	rt::Json json;
	json.Array();
	if (scope == "address")
	{
		for (uint32_t i = 0; i < _Shards.GetSize(); i++)
		{
			_Shards[i]->JsonifyAddressStateWithoutGrouping(json, rvm::CONTRACT_UNSET_BUILD(cvid));
		}
		_LOG("[PRD]: Address states Written to: " << filename)
	}
	else
	{
		for (uint32_t i = 0; i < _Shards.GetSize(); i++)
		{
			_Shards[i]->JsonifyShardState(json, rvm::CONTRACT_UNSET_BUILD(cvid));
		}
		_pGlobalShard->JsonifyShardState(json, rvm::CONTRACT_UNSET_BUILD(cvid));
		_LOG("[PRD]: Shard states Written to: " << filename)
	}
	stateFile.Write(json.GetInternalString());
	stateFile.Close();
}
bool Simulator::_GenerateSetStateCmd(const rt::String_Ref& line, const rt::String_Ref& scope, const rt::String_Ref& target_contract)
{
	rt::JsonObject obj(line);
	rt::JsonArray stateArr(obj.GetValueRaw("States"));
	rt::String_Ref stateStr;	
	rt::String cmdStr;
	bool exist = false;
	rt::String_Ref target;
	while (stateArr.GetNextObject(stateStr))
	{
		rt::JsonObject stateObj(stateStr);
		bool CIDexist = false;
		rt::String_Ref CVIDStr = stateObj.GetValue("CVID");
		if (target_contract != rt::SS("all") && target_contract != stateObj.GetValue("Contract"))
		{
			return false;
		}
		if (scope == "address")
		{
			rvm::Address addr;
			target = obj.GetValue("Address", exist);
			if (!exist)
			{
				_LOG("[PRD] Line " << GetLineNum() << ": Invalid address state");
				return false;
			}
			uint32_t index = _AddNewUser(target, addr);
			cmdStr = "state.update ";
			cmdStr += CVIDStr + ".address" + rt::SS(" @") + index + rt::SS(" ") + stateObj.GetValue("State");

		}
		else
		{
			cmdStr = "state.update ";
			target = obj.GetValue("ShardIndex", exist);
			if(!exist)
			{
				_LOG("[PRD] Line " << GetLineNum() << ": Invalid shard state");
				return false;
			}
			bool IsGlobal = target == "#g";
			cmdStr += CVIDStr + rt::SS(".") + (IsGlobal ? rt::SS("global") : scope) + rt::SS(" ") + (IsGlobal ? rt::SS("#global") : obj.GetValue("ShardIndex"))  + rt::SS(" ") + stateObj.GetValue("State");
		}
		CmdParse cmd(cmdStr, GetLineNum());
		_ExecState(cmd);
	}
	return true;
}
bool Simulator::_ReadStateFromFile(const rt::String_Ref& filename, const rt::String_Ref* TargetSeg)
{
	rt::String_Ref scope = TargetSeg[0];
	rt::String_Ref target_contract = TargetSeg[1];
	os::File statefile;
	rt::String absoluteFilePath;
	os::File::ResolveRelativePath(_ScriptPath + filename, absoluteFilePath);
	if (!statefile.Open(absoluteFilePath.GetString()))
	{
		_LOG("[PRD] Line" << GetLineNum() << ": Unable to open state file, file path: " << filename);
		return false;
	}
	rt::String text;
	os::File::LoadText(absoluteFilePath, text);
	rt::JsonArray allStateArr(text);
	if (allStateArr.IsEmpty())
	{
		_LOG("[PRD] Line" << GetLineNum() << ": Unable to parse state file, file path: " << filename);
		return false;
	}
	rt::String_Ref line;
	uint64_t count = 0;
	rt::String cmdStr;
	while (allStateArr.GetNextObject(line))
	{
		if(!_GenerateSetStateCmd(line, scope, target_contract)) return false;
	}
	return true;
}
} // namespace oxd
