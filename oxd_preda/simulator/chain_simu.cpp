#include "chain_simu.h"
#include "simu_script.h"
#include "simu_shard.h"
#include "core_contracts.h"
#include "../native/types/abi_def_impl.h"
#include "../../SFC/core/ext/botan/botan.h"

namespace oxd
{
bool ChainSimulator::Init(const os::CommandLine& cmd)
{
	m_attribute.shardOrder = cmd.GetOptionAs<uint32_t>("order", 2);
	m_attribute.isShardAsync = cmd.HasOption("async");
	m_attribute.defaultEngineMode = (cmd.HasOption("WASM") || cmd.HasOption("wasm"))? rvm::EngineId::PREDA_WASM: rvm::EngineId::PREDA_NATIVE;

	m_runtimeInfo.shardsExecutedTxnCount = 0;
	m_runtimeInfo.isChainPaused = true;
	if(cmd.HasOption("viz") && cmd.HasOption("viz_templ"))
	{
		m_vizInfo.isVizEnabled = true;
		m_vizInfo.vizTmplFile = cmd.GetOption("viz_templ");
		m_vizInfo.vizOutputFile = cmd.GetOption("viz");
	}

#if defined(PLATFORM_WIN)
	char* homeDir = getenv("HOMEPATH");
#else
	char* homeDir = getenv("HOME");
#endif
	rt::String repo_dir(rt::SS(homeDir, strlen(homeDir)) + PREDA_DATA_FOLDER + "chsimu_repo");
	os::File::RemovePath(repo_dir);

	bool isWasmReady = _InitEngine(rvm::EngineId::PREDA_WASM, "./preda_engine", repo_dir + "/wasm", "-wasm");
	bool isNativeReady = _InitEngine(rvm::EngineId::PREDA_NATIVE, "./preda_engine", repo_dir + "/native", "-native");
	bool isEvmReady = _InitEngine(rvm::EngineId::SOLIDITY_EVM, "./preda_engine", repo_dir + "/evm", "-evm");

	if(!isWasmReady && ! isNativeReady && !isEvmReady)
	{
		_LOG_ERROR("No execution engine available.");
		return false;
	}

	_InitChain();
	return true;
}
bool ChainSimulator::Compile(const std::vector<std::pair<rt::String, rt::String>>& prdFiles)
{
	auto* engine = GetEngine(m_attribute.defaultEngineMode);
	if(!engine)
	{
		_LOG_WARNING("[PRD]: Engine "<< rt::EnumStringify(m_attribute.defaultEngineMode) <<" is not available");
		return false;
	}	

	m_pGlobalShard->DeployBegin();
	BuildContracts	build(engine, m_attribute.defaultEngineMode);
	build.Init(m_attribute.DAPP_NAME, m_attribute.DAPP_ID, m_attribute.defaultEngineMode);
	for(auto& prdFile : prdFiles)
		build.AddContractCode(prdFile.second, nullptr, prdFile.first);

	bool ret = build.Compile(false);
	m_pGlobalShard->DeployEnd(false);

	if(!ret)
		return false;

	rt::Json json;
	build.GetContractsInfo(json);
	_LOG(rt::JsonBeautified(json));

	return ret;
}

bool ChainSimulator::CompileSol(rt::String_Ref fileContent, rt::String_Ref filePath)
{
	auto* engine = GetEngine(rvm::EngineId::SOLIDITY_EVM);
	if(!engine)
	{
		_LOG_WARNING("[PRD]: Engine "<< rt::EnumStringify(m_attribute.defaultEngineMode) <<" is not available");
		return false;
	}

	m_pGlobalShard->DeployBegin();
	BuildContracts	build(engine, m_attribute.defaultEngineMode);
	build.Init(m_attribute.DAPP_NAME, m_attribute.DAPP_ID, m_attribute.defaultEngineMode);
	build.AddContractCode(fileContent, nullptr, filePath);
	bool ret = build.Compile(false);
	m_pGlobalShard->DeployEnd(false);

	if(!ret)
		return false;

	rt::Json json;
	build.GetContractsInfo(json);
	_LOG(rt::JsonBeautified(json));

	return ret;
}

void ChainSimulator::Deploy(SimuTxn* txn)
{
	m_pGlobalShard->PushNormalTxn(txn);
	Run();
}

bool ChainSimulator::SetState(rvm::ContractInvokeId ciid, SimuState* pState, uint32_t shardId, const rvm::Address* targetAddr)
{
	ASSERT(pState);
	// TODO: check state
	switch(rvm::CONTRACT_SCOPE(ciid))
	{ 
	case rvm::Scope::Global: 
		m_pGlobalShard->SetState(-ciid, pState); 
		break;
	case rvm::Scope::Shard:
		if(shardId > GetShardCount())
			return false;
		m_shards[shardId]->SetState(-ciid, pState);
		break;
	case rvm::Scope::Address:
		ASSERT(targetAddr);
		m_shards[GetShardIndex(*targetAddr)]->SetState(-ciid, *targetAddr, pState);
		break;
	default:
		ASSERT(0);
	}
	return true;
}

void ChainSimulator::IssueTxn(SimuTxn* txn)
{
	if(!txn) return;
	SimuShard* pShard = GetShard(txn->ShardIndex);
	ASSERT(pShard);
	pShard->PushNormalTxn(txn);
}

void ChainSimulator::Run(bool step)
{
	if(EnableViz())
	{
		for (int i = 0; i < m_shards.GetSize(); i++)
		{
			m_vizInfo.shardPendingTxnCount[i] = m_shards[i]->GetPendingTxnCount();
		}
		m_vizInfo.shardPendingTxnCount.push_back(GetGlobalShard()->GetPendingTxnCount());
	}

	m_runtimeInfo.isChainStepping = step;
	m_runtimeInfo.isChainPaused = false;
	m_chainIdle.Reset();
	if(m_attribute.isShardAsync)
	{
		for (auto p : m_shards)
			p->Step();
	}
	else
		m_pGlobalShard->Step();

	WaitUntilIdle();
	m_runtimeInfo.isChainPaused = true;
}

void ChainSimulator::Stop()
{
	m_runtimeInfo.isChainPaused = true;
}

void ChainSimulator::Await()
{
	WaitUntilIdle();
}

void ChainSimulator::Term()
{
	if(m_pGlobalShard)
	{
		for(auto p : m_shards)p->Term();
		m_pGlobalShard->Term();

		for(auto p : m_shards)_SafeDel(p);
		_SafeDel(m_pGlobalShard);
	}

	for(auto& e : m_engines)
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

void ChainSimulator::Info()
{
	m_pGlobalShard->LogInfo();
	for(auto p : m_shards)
		p->LogInfo();
	_LOG("[PRD]: Total Txn:" << m_runtimeInfo.pendingTxnCount << '/' << m_runtimeInfo.executedTxnCount);
}

void ChainSimulator::ExportViz()
{
	if (!EnableViz())
		return;
	rt::String html;
	if(!os::File::LoadText(ALLOCA_C_STRING(m_vizInfo.vizTmplFile), html))
	{
		_LOG_WARNING("[PRD]: Template visualization webpage can not be loaded: "<< m_vizInfo.vizTmplFile);
	}

	auto pos = html.FindString("</HEAD>");
	if(pos == -1)pos = html.FindString("</head>");
	if(pos == -1)
	{
		_LOG_WARNING("[PRD]: No <HEAD> tag found in template visualization webpage: "<< m_vizInfo.vizTmplFile);
	}

	rt::String out;
	out = html.SubStr(0, pos);
	out += "\n<script type=\"text/javascript\">\nvar PREDA_VIZ_LOG = `\n";
#if defined(PLATFORM_DEBUG_BUILD)
	out += rt::JsonBeautified(m_vizInfo.vizJson);
#else
	out += m_vizInfo.vizJson;
#endif
	out += "`;\n</script>\n\n";

	out += html.SubStr(pos);

	if(!os::File::SaveText(ALLOCA_C_STRING(m_vizInfo.vizOutputFile), out))
	{
		_LOG_WARNING("[PRD]: Failed to save visualization webpage: "<< out);
	}
}

bool ChainSimulator::VizBlock(uint32_t shardId, int64_t blockHeight, rt::Json& json)
{
	SimuShard* pShard = shardId == rvm::GlobalShard ? m_pGlobalShard : (shardId < m_shards.GetSize()) ? m_shards[shardId] : nullptr;
	if(!pShard || !pShard->JsonifyBlocks(json, blockHeight))
	{
		json.Empty();
		return false;
	}
	return true;
}

bool ChainSimulator::VizAddr(const std::string& contractName, const rvm::Address& userAddr, uint32_t userId, rt::Json& json)
{
	rvm::ContractVersionId cvid;
	if(rt::String_Ref(contractName).HasOnlyNumbers()){
		cvid = (rvm::ContractVersionId)rt::String_Ref(contractName).ToNumber<uint64_t>();
	}
	else{
		rt::String contractFullName = rt::SS(m_attribute.DAPP_NAME) + rt::SS(".") + contractName;
		rvm::ConstString contract = {contractFullName.Begin(), (uint32_t)contractFullName.GetLength()};
		cvid = GetContractByName(&contract);
	}
	rvm::ContractId cid = rvm::CONTRACT_UNSET_BUILD(cvid);
	if(!m_shards[GetShardIndex(userAddr)]->JsonifyAddressState(json, &userAddr, userId, cid))
		return false;
	return true;
}

bool ChainSimulator::VizShard(const std::string& contractName, uint32_t shardId, rt::Json& json)
{
	rvm::ContractVersionId cvid;
	if(rt::String_Ref(contractName).HasOnlyNumbers()){
		cvid = (rvm::ContractVersionId)rt::String_Ref(contractName).ToNumber<uint64_t>();
	}
	else{
		rt::String contractFullName = rt::SS(m_attribute.DAPP_NAME) + rt::SS(".") + contractName;
		rvm::ConstString contract = {contractFullName.Begin(), (uint32_t)contractFullName.GetLength()};
		cvid = GetContractByName(&contract);
	}
	rvm::ContractId cid = rvm::CONTRACT_UNSET_BUILD(cvid);
	SimuShard* pShard = shardId == rvm::GlobalShard ? m_pGlobalShard : (shardId < m_shards.GetSize()) ? m_shards[shardId] : nullptr;
	if(!pShard || !pShard->JsonifyShardState(json, cid))
	{
		json.Empty();
		return false;
	}
	return true;
}

bool ChainSimulator::VizTxn(SimuTxn* txn, rt::Json& json)
{
	SimuShard* pShard = txn->ShardIndex == rvm::GlobalShard ? m_pGlobalShard : (txn->ShardIndex < m_shards.GetSize()) ? m_shards[txn->ShardIndex] : nullptr;
	if(!pShard || !pShard->ConfirmedTxnJsonify(txn, json))
		txn->Jsonify(GetEngine(txn->GetEngineId()), json);
	return true;
}

bool ChainSimulator::VizTrace(SimuTxn* originTxn, rt::Json& json)
{
	rt::BufferEx<std::pair<SimuTxn*,int>> queue;
	queue.push_back({originTxn, -1});
	int id = 1;
	rt::Buffer<SimuShard*> all_shard = m_shards;
	all_shard.push_back(m_pGlobalShard);
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
				current_pair.first->TargetIndex = (int64_t)m_pScriptListener->GetUserId(a.Addr);
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

bool ChainSimulator::VizProfiling(rt::Json& json)
{
	uint64_t lapsed = rt::max<long long>(1LL, m_pScriptListener->GetTimeLapsed());
	{
		auto s = json.ScopeAppendingElement();
		GetGlobalShard()->JsonifyProfile(json);
		ULONGLONG global_pending_txn_count = m_vizInfo.shardPendingTxnCount.Last();
		json << (((J(TxnCount) = global_pending_txn_count),
			(J(TPS) = global_pending_txn_count * 1000 / lapsed)));
	}
	for(uint32_t sh = 0; sh < m_shards.GetSize(); sh++)
	{
		auto s1 = json.ScopeAppendingElement();
		m_shards[sh]->JsonifyProfile(json);
		ULONGLONG shard_pending_txn = m_vizInfo.shardPendingTxnCount[sh];
		json << ((J(TxnCount) = shard_pending_txn,
			J(TPS) = shard_pending_txn * 1000 / lapsed));
	}
	return true;
}

bool ChainSimulator::VizUintScope(const std::string& contractName, uint32_t scopeLen, std::string scopeTarget, rt::Json& json)
{
	rt::String contractFullName = rt::SS(m_attribute.DAPP_NAME) + rt::SS(".") + contractName;
	rvm::ConstString contract = {contractFullName.Begin(), (uint32_t)contractFullName.GetLength()};
	rvm::ContractVersionId cvid = GetContractByName(&contract);
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
			res = std::stoi(scopeTarget);
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
		for (uint32_t sh = 0; sh < m_shards.GetSize(); sh++)
		{
			m_shards[sh]->JsonifyScopeState(json, key, true);
		}
	}
	else
	{
		uint32_t shardIndex = GetShardIndex(tar);
		if(!m_shards[shardIndex]->JsonifyScopeState(json, key, false))
		{
			_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Scope target does not exist");
			return false;
		}
	}
	return true;
}

void ChainSimulator::AddSuplliedToken(rvm::ContractInvokeId ciid, rvm::TokenId tokenId)
{
	// add supplier
	{
		CoreContractState<CORE_TOKEN_SUPPLIERS> state = m_pGlobalShard->GetState(-CORE_TOKEN_SUPPLIERS);
		auto m = state.DeriveMutable();
		m.Set(rvm::UInt128{ (uint64_t)tokenId, (uint64_t)-~ciid }, rvm::TokenMinterFlag::Allowed);
		m_pGlobalShard->SetState(-CORE_TOKEN_SUPPLIERS, state.CreateState(m, rvm::CONTRACT_BUILD(ciid)));
	}

	// assign token default
	{
		CoreContractState<CORE_CONTRACT_DEFAULT> state = m_pGlobalShard->GetState(-CORE_CONTRACT_DEFAULT);
		if (state.IsEmpty() || !state->Has(-~ciid))
		{
			auto m = state.DeriveMutable();
			m.Set(-~ciid, tokenId);
			m_pGlobalShard->SetState(-CORE_CONTRACT_DEFAULT, state.CreateState(m, rvm::CONTRACT_BUILD(ciid)));
		}
	}
}

void ChainSimulator::GetStateJson(rvm::Scope scope, rvm::ContractVersionId cvid, rt::Json& out)
{
	switch(scope){
		case rvm::Scope::Address:
		for(auto pShard : m_shards){
			pShard->JsonifyAddressStateWithoutGrouping(out, rvm::CONTRACT_UNSET_BUILD(cvid));
		}
		break;
		case rvm::Scope::Shard:
		for(auto pShard : m_shards){
			pShard->JsonifyShardState(out, rvm::CONTRACT_UNSET_BUILD(cvid));
		}
		m_pGlobalShard->JsonifyShardState(out, rvm::CONTRACT_UNSET_BUILD(cvid));
		break;
		default:
		break;
	}
}

void ChainSimulator::_InitChain()
{
	ASSERT(m_shards.GetSize() == 0);
	ASSERT(m_pGlobalShard == nullptr);

	m_attribute.shardBitmask = rvm::ADDRESS_SHARD_BITMASK(GetShardOrder());
	m_runtimeInfo.gasLimit = m_runtimeInfo.globalGasLimit = defaultBlockGasLimit;
	m_runtimeInfo.isChainPaused = true;
	m_runtimeInfo.pendingTxnCount = 0;
	m_runtimeInfo.executedTxnCount = 0;
	m_chainIdle.Set();

	uint64_t time_base = os::Timestamp::Get();
	m_pGlobalShard = _New(SimuGlobalShard(this, time_base, GetShardOrder()));
	uint32_t shard_count = GetShardCount();
	m_shards.SetSize(GetShardCount());
	for(uint32_t i = 0; i < shard_count; i++){
		m_shards[i] = _New(SimuShard(this, time_base, GetShardOrder(), i, m_pGlobalShard));
	}

	m_pGlobalShard->Init();
	for(auto p : m_shards)
		p->Init();

	if(EnableViz())
		m_vizInfo.shardPendingTxnCount.SetSize(shard_count);

	_LOG("[PRD]: Chain initialized with " << shard_count << " shard(s), in " << (m_attribute.isShardAsync? "async" : "sync") << "-sharding mode");
	SimuTxn::DefaultGas = 10000000;
}

bool ChainSimulator::_InitEngine(rvm::EngineId eng, const char* dll_name, const char* repo, const char* engine_config)
{
	m_engines[(int)rvm::EngineId::Core] = { INVALID_HANDLE_VALUE, &oxd::CoreEngine::Get() };

	auto& ee = m_engines[(int)eng];
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
				_LOGC_HIGHLIGHT("Execution Engine Initialized, <" << ee.pEngine->GetName().Str() << "> v" << ee.pEngine->GetVersion().Str() << ", " << ee.pEngine->GetVendorInfo().Str());
				_LOGC("Repository: " << repo << ", Module: " << dll_name << " (" << rt::EnumStringify(eng) << ")\n");
				return true;
			}
			else
			{
				_LOGC_WARNING("Failed to initialized PREDA engine, db path: " << repo);
				if(initErrorMsg.StrPtr)
					_LOGC_WARNING("Failed to initialize: "<< initErrorMsg.Str());
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

	_LOGC_WARNING("Failed to mount execution engine: "<< dll_name << " ("<< rt::EnumStringify(eng) << ") with repository in " << repo << '\n');
	return false;
}

rvm::InvokeResult ChainSimulator::DeployFromStatement(rvm::ConstData deployArgs)
{

	uint32_t count = *(uint32_t*)(deployArgs.DataPtr);
	std::vector<rt::String_Ref> fileNames(count);
	std::vector<rt::String_Ref> args(count);
	const uint8_t* dataIt = deployArgs.DataPtr + sizeof(uint32_t);
	for(uint32_t i = 0; i < count; ++i)
	{
		uint32_t filePathLength = *(uint32_t*)(dataIt);
		dataIt += sizeof(uint32_t);
		fileNames[i] = rt::String_Ref((char*)dataIt, filePathLength);
		dataIt += filePathLength;

		uint32_t jsonParamsLength = *(uint32_t*)(dataIt);
		dataIt += sizeof(uint32_t);
		if(jsonParamsLength){
			args[i] = rt::String_Ref((char*)dataIt, jsonParamsLength);
			dataIt += jsonParamsLength;
		}
	}
	rvm::InvokeResult ret;
	_Deploy(m_pGlobalShard->GetExecuteUnits(), fileNames.data(), args.data(), count, ret);
	return ret;
}

bool ChainSimulator::CompleteShardExecution()
{
	if(os::AtomicIncrement(&m_runtimeInfo.shardsExecutedTxnCount) == (int)m_shards.GetSize())
	{
		os::AtomicAdd(-(int32_t)m_shards.GetSize(), &m_runtimeInfo.shardsExecutedTxnCount);
		return true;
	}

	return false;	
}

void ChainSimulator::CreateExecuteUnit(ExecutionUnit* out) const
{
	for(int i=0; i < sizeofArray(m_engines); i++)
	{
		_SafeRelease(out->pUnits[i]);

		auto& e = m_engines[i];
		if(e.pEngine)
		{
			out->pUnits[i] = e.pEngine->CreateExecuteUnit();
		}
	}
}

bool ChainSimulator::_Deploy(ExecutionUnit& exec_units, const rt::String_Ref* fileNames, const rt::String_Ref* args, uint32_t count, rvm::InvokeResult &out)
{
	if(count == 0)return false;

	BuildContracts preda_native	(GetEngine(rvm::EngineId::PREDA_NATIVE), rvm::EngineId::PREDA_NATIVE);
	BuildContracts preda_wasm	(GetEngine(rvm::EngineId::PREDA_WASM), rvm::EngineId::PREDA_WASM);
	BuildContracts solidity		(GetEngine(rvm::EngineId::SOLIDITY_EVM), rvm::EngineId::SOLIDITY_EVM);
	preda_native.Init(m_attribute.DAPP_NAME, m_attribute.DAPP_ID, rvm::EngineId::PREDA_NATIVE);
	preda_wasm.Init(m_attribute.DAPP_NAME, m_attribute.DAPP_ID, rvm::EngineId::PREDA_WASM);
	solidity.Init(m_attribute.DAPP_NAME, m_attribute.DAPP_ID, rvm::EngineId::SOLIDITY_EVM);

	rt::BufferEx<rt::String> codes;
	rt::BufferEx<rt::String> filePaths;

	for(uint32_t i = 0; i < count; i++)
	{
		rt::String cur_fn;
		rvm::EngineId eid = _ResolveRTEngine(fileNames[i], cur_fn);
		os::File::ResolveRelativePath(GetScriptDirPath() + cur_fn, filePaths.push_back());

		if(!os::File::LoadText(filePaths[i].Begin(), codes.push_back()))
		{
			_LOG_WARNING("[PRD]:  Line " << GetLineNum() << ": Failed to load source code: "<< filePaths[i]);
			return false;
		}

		BuildContracts* target = nullptr;
		switch(eid)
		{
		case rvm::EngineId::SOLIDITY_EVM:
		{
			target = &solidity;
			break;
		}
		case rvm::EngineId::PREDA_NATIVE:
			target = &preda_native;
			break;
		case rvm::EngineId::PREDA_WASM:
			target = &preda_wasm;
			break;
		default:
			_LOG_WARNING("[PRD]: Unsupported target for source code: "<< filePaths[i]);
			return false;
		}

		ASSERT(target);
		if(!args[i].IsEmpty())
			target->AddContractCode(codes[i], args[i], filePaths[i]);
		else
			target->AddContractCode(codes[i], nullptr, filePaths[i]);
	}

	m_pGlobalShard->DeployBegin();

	auto compile = [this](BuildContracts& b){
		if(b.GetSourceCount() == 0)return true;
		return b.Compile() && b.Link() && m_pGlobalShard->AllocateContractIds(b);
	};

	auto deploy = [this, &out](BuildContracts& b, rvm::ExecutionUnit* exec){
		if(b.GetSourceCount() == 0)return true;
		return b.Deploy(exec, m_pGlobalShard) && m_pGlobalShard->CommitDeployment(b) && (out = b.InvokeConstructor(exec, m_pGlobalShard, -1)).Code == rvm::InvokeErrorCode::Success;
	};

	bool ret =	compile(solidity) && compile(preda_wasm) && compile(preda_native);

	if(EnableViz())
	{
		VIZ_SECTION_BEGIN(m_vizInfo.vizJson, "Deploy");
		{
			m_vizInfo.vizJson.Object();
			auto section = m_vizInfo.vizJson.ScopeAppendingKey("info");
			m_vizInfo.vizJson.Array();
			int succ_count = 0;
			if(solidity.IsCompiled())
			{
				auto section2 = m_vizInfo.vizJson.ScopeMergingArray();
				solidity.GetContractsInfo(m_vizInfo.vizJson); succ_count++;
			}
			if(preda_wasm.IsCompiled())
			{
				auto section2 = m_vizInfo.vizJson.ScopeMergingArray();
				preda_wasm.GetContractsInfo(m_vizInfo.vizJson); succ_count++;
			}
			if(preda_native.IsCompiled())
			{
				auto section2 = m_vizInfo.vizJson.ScopeMergingArray();
				preda_native.GetContractsInfo(m_vizInfo.vizJson); succ_count++;
			}
		}
		auto section2 = m_vizInfo.vizJson.ScopeAppendingKey("sources");
		m_vizInfo.vizJson.Array();
		auto addFileName = [this](BuildContracts& b, rt::Json& append) {
			for (auto iter = b._ContractToFilename.begin(); iter != b._ContractToFilename.end(); iter++)
			{
				auto s = append.ScopeAppendingElement();
				append.Object((J(contract) = iter->first, J(source) = iter->second));
			}
		};
		addFileName(solidity, m_vizInfo.vizJson);
		addFileName(preda_wasm, m_vizInfo.vizJson);
		addFileName(preda_native, m_vizInfo.vizJson);

		VIZ_SECTION_END;
	}


	ret = ret && deploy(solidity, exec_units.Get(rvm::EngineId::SOLIDITY_EVM)) &&
				 deploy(preda_wasm, exec_units.Get(rvm::EngineId::PREDA_WASM)) &&
				 deploy(preda_native, exec_units.Get(rvm::EngineId::PREDA_NATIVE));

	m_pGlobalShard->DeployEnd(ret);
	return ret;
}

rvm::EngineId ChainSimulator::_ResolveRTEngine(rt::String in, rt::String& filename)
{
	rt::String_Ref segs[2];
	auto count = in.Split(segs, 2, ':');
	rvm::EngineId engineMode = m_attribute.defaultEngineMode;
	if(count > 1)
		engineMode = segs[1] == "NATIVE" ?  rvm::EngineId::PREDA_NATIVE : (segs[1] == "WASM" ? rvm::EngineId::PREDA_WASM : rvm::EngineId::Unassigned);
	filename = segs[0];
	if(filename.GetExtName() == rt::SS(".prd") && rvm::EngineId::PREDA_NATIVE == engineMode)
	{
		return rvm::EngineId::PREDA_NATIVE;
	}
	else if(filename.GetExtName() == rt::SS(".prd") && rvm::EngineId::PREDA_WASM == engineMode)
	{
		return rvm::EngineId::PREDA_WASM;
	}
	else if(filename.GetExtName() == rt::SS(".xtl") && count == 1)
	{
		return rvm::EngineId::SOLIDITY_EVM;
	}
	return rvm::EngineId::Unassigned;
}

bool ChainSimulator::_ComposeSolJson(rt::JsonObject inJson, rt::Json& out, rt::String fn)
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
			os::File::ResolveRelativePath(GetScriptDirPath() + kv.GetValue(), absPath);
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

bool ChainSimulator::GetContractFunction(rt::String_Ref contractName, rt::String_Ref functionName, rt::String_Ref jsonParameters, ContractFunction& outCf, rvm::ContractInvokeId& outCiid)
{
	// resolve cvid
	rt::String functionFullName = rt::SS(m_attribute.DAPP_NAME) + rt::SS(".") + contractName + rt::SS(".") + functionName;
	rvm::ContractVersionId cvid = rvm::ContractVersionIdInvalid;
	if(!_ResolveUnamedContract(contractName, functionName, functionFullName, cvid)) 
		return false;
	if (contractName.HasOnlyNumbers())
		outCf.Contract = rvm::CONTRACT_UNSET_BUILD(cvid);

	// search for the matched function from overloaded functions
	rt::BufferEx<ContractFunction> buf = rt::_CastToConst(GetGlobalShard()->_ContractFunctions).get(functionFullName, rt::BufferEx<ContractFunction>());
	if(buf.GetSize() == 0)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Contract function '" << contractName + rt::SS(".") + functionName << "' is not found");
		return false;
	}
	if(rvm::CONTRACT_ENGINE(buf[0].Contract) == rvm::EngineId::SOLIDITY_EVM)
		outCf = buf[0];
	else if(!_ResolveOverloadedFunctions(jsonParameters, buf, outCf))
		return false;

	// resolve ciid
	if (cvid == rvm::ContractVersionIdInvalid) {
		rvm::BuildNum build_num = GetGlobalShard()->_GetContractEffectiveBuild(outCf.Contract);
		if (0 == build_num)
			return false;
		cvid = rvm::CONTRACT_SET_BUILD(outCf.Contract, build_num);
	}

	rvm::Scope scope;
		auto it = GetGlobalShard()->_ContractInfo.find(cvid);
	if(it != GetGlobalShard()->_ContractInfo.end())
		scope = it->second->ScopeOfOpcode[(int)outCf.Op];
	else
		return false;
	outCiid = rvm::CONTRACT_SET_SCOPE(cvid, scope);
	return true;
}

int ChainSimulator::ComposeTxn(rvm::ContractInvokeId ciid, rvm::OpCode op, rt::String_Ref jsonParameters, rt::String_Ref tokensSuppliedStr, SimuTxn*& out)
{
	rt::BufferEx<uint8_t> tokensSupplied;
	if(tokensSuppliedStr.GetLength() && !_ResolveTokensSupplied(tokensSuppliedStr, tokensSupplied))
		return 2;

	thread_local rvm::DataBufferImpl data;
	data.Empty();
	rvm::ConstString s = { jsonParameters.Begin(), (uint32_t)jsonParameters.GetLength() };
	JsonLogError jsonErr;
	if(GetEngine(rvm::CONTRACT_ENGINE(ciid))->ArgumentsJsonParse(ciid, op, &s, &data, &jsonErr))
	{
		auto* txn = SimuTxn::Create(data.GetSize(), (uint32_t)tokensSupplied.GetSize());
		txn->Type = rvm::InvokeContextType::Normal;
		txn->Contract = ciid;
		txn->Op = op;
		txn->Timestamp = os::Timestamp::Get();
		txn->Flag = (SimuTxnFlag)0;
		txn->OriginateHeight = 0;
		txn->OriginateShardIndex = 0;
		txn->OriginateShardOrder = 0;
		txn->Height = 0;
		txn->ShardIndex = 0;
		txn->ShardOrder = 0;

		if(txn->TokensSerializedSize)
		{
			ASSERT(txn->TokensSerializedSize == tokensSupplied.GetSize());
			memcpy(txn->SerializedData, tokensSupplied.Begin(), tokensSupplied.GetSize());
		}

		if(txn->ArgsSerializedSize)
		{
			ASSERT(txn->ArgsSerializedSize == data.GetSize());
			memcpy(txn->SerializedData + txn->TokensSerializedSize, data.GetData(), data.GetSize());
		}
		sec::Hash<sec::HASH_SHA256>().Calculate(((char*)txn) + sizeof(rvm::HashValue), txn->GetSize() - sizeof(rvm::HashValue), &txn->Hash);
		out = txn;
		return 0;
	}
	else
	{
		_LOG("[PRD] Line " << GetLineNum() << ": Invalid function argument/s")
		return 3;
	}
}

int ChainSimulator::ComposeState(rvm::ContractInvokeId ciid, rt::String_Ref jsonParameters, SimuState*& out, uint32_t shardId, const rvm::ScopeKey& sk, bool isSettingWholeState)
{
	rvm::StringStreamImpl state_json;
	// if updating state, get existing state first
	if(!isSettingWholeState && !_ResolveExistingState(ciid, shardId, sk, state_json))
		return 2;
	auto build = rvm::CONTRACT_BUILD(ciid);
	rvm::ConstData buf;
	if(!_ComposeStateData(ciid, jsonParameters, state_json, buf))
		return 3;
#ifndef __APPLE__
	out = SimuState::Create(buf.DataSize, build, shardId, buf.DataPtr);
#else
	out = SimuState::Create(buf.DataSize, build, buf.DataPtr);
#endif
	return 0;
}

bool ChainSimulator::_ResolveOverloadedFunctions(rt::String_Ref jsonParameters, rt::BufferEx<ContractFunction>& funcs, ContractFunction& out)
{
	UINT maxVarMatched = 0;
	bool matched = false;
	UINT minSignatureLength = 1024;
	for(int i = 0; i < funcs.GetSize(); i++)
	{
		UINT numVarMatched = 0;
		rt::JsonObject args_json(jsonParameters);
		rt::String funcSignature = funcs[i].FunctionSignature;
		if(funcSignature.GetLength() == 0 && args_json.IsEmptyObject()) //empty json won't enter the while loop below
		{
			out = funcs[i];
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
				int64_t nextKeyPos = jsonParameters.FindCharacter(',', varName.Begin() - jsonParameters.Begin());
				int64_t nextColonPos = jsonParameters.FindCharacter(':', nextKeyPos);
				if(nextKeyPos == -1)
				{
					continue;
				}
				nextKeyPos++;
				varName = jsonParameters.SubStr(nextKeyPos, nextColonPos - nextKeyPos).TrimSpace();
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
			out = funcs[i];
			maxVarMatched = numVarMatched;
			minSignatureLength = signatureLen;
		}
	}
	if(maxVarMatched == 0)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Invalid function argument/s");
		return false;
	}
	return true;
}

bool ChainSimulator::_ResolveUnamedContract(rt::String_Ref contractName, rt::String_Ref functionName, rt::String& outFunctionFullName, rvm::ContractVersionId& outCvid)
{
	if(!contractName.HasOnlyNumbers()) 
		return true;
	rvm::ContractVersionId cvid = (rvm::ContractVersionId)contractName.ToNumber<uint64_t>();
	oxd::ContractsDatabase::ContractInfo* info = GetGlobalShard()->_ContractInfo.get(cvid);
	if (info)
	{
		for (auto& it : GetGlobalShard()->_ContractInfo)
		{
			if (rt::IsEqual(it.second->Deployment.Module, info->Deployment.Module))
			{
				//make sure originalCvid is named
				bool isNamed = false;
				for (auto& named_it : GetGlobalShard()->_Contracts)
				{
					if (named_it.second == it.first)
					{
						isNamed = true;
						outFunctionFullName = named_it.first + rt::SS(".") + functionName;
					}
				}
				outCvid = cvid;
				if (isNamed)
				{
					return true;
				}
			}
		}
		if (outCvid == rvm::ContractVersionIdInvalid)
		{
			rt::String errContract = contractName.HasOnlyNumbers() ? rt::SS(m_attribute.DAPP_NAME) + '.' + contractName : contractName;
			_LOG("[PRD] Line " << GetLineNum() << ": Contract '" << errContract << "' is not found");
			return false;
		}
	}
	rt::String errContract = contractName.HasOnlyNumbers() ? rt::SS(m_attribute.DAPP_NAME) + '.' + contractName : contractName;
	_LOG("[PRD] Line " << GetLineNum() << ": Contract '" << errContract << "' is not found");
	return false;
}

bool ChainSimulator::ResolveCiid(rt::String_Ref dappContractName, rvm::Scope scope, rvm::ContractInvokeId& out)
{
	rvm::ContractVersionId cvid = dappContractName.HasOnlyNumbers() ? (rvm::ContractVersionId)dappContractName.ToNumber<uint64_t>()
																: GetGlobalShard()->_Contracts.get(dappContractName, rvm::ContractVersionIdInvalid);
	if(cvid == rvm::ContractVersionIdInvalid) {
		rt::String errContract = dappContractName.HasOnlyNumbers() ? rt::SS(m_attribute.DAPP_NAME) + '.' + dappContractName : dappContractName;
		_LOG("[PRD] Line " << GetLineNum() << ": Contract '" << errContract << "' is not found");
		return false;
	}
	out = cvid + scope;
	return true;
}

bool ChainSimulator::_ResolveTokensSupplied(rt::String_Ref tokensSuppliedStr, rt::BufferEx<uint8_t>& out)
{
	static const rt::CharacterSet sep(",;+");
	static const rt::CharacterSet_Digits dig;

	rt::String_Ref segs[65];
	int pos = (int)tokensSuppliedStr.FindCharacter('(', 0);
	int end = (int)tokensSuppliedStr.FindCharacter(')', pos);
	if (pos < 0 || end < 0) return false;
	uint32_t count = rt::String_Ref(&tokensSuppliedStr[pos+1], &tokensSuppliedStr[end]).TrimSpace().Split<true>(segs, sizeofArray(segs), sep);

	if(count == sizeofArray(segs))return false;

	rvm::ArrayMutable<rvm::Coins> assets;
	assets.SetCount(count);

	rvm::CoinsMutable c;
	for(uint32_t i = 0; i < count; i++)
	{
		segs[i] = segs[i].TrimSpace();

		auto p = segs[i].FindCharacterReverse(dig);
		if(p < 0)return false;

		p++;
		if(!c.GetModifiableAmount().FromString(segs[i].SubStrHead(p)))
			return false;

		rt::String_Ref token_name = segs[i].SubStr(p).TrimSpace();
		token_name.MakeUpper();
		c.SetId(rvm::TokenIdFromSymbol(token_name));

		auto* coin = rvm::RvmImmutableTypeCompose(c);
		assets.Set(i, coin, rvm::RVMPTR_TAKE);
	}

	typedef rvm::Array<rvm::Coins> TOKENS;
	out.ChangeSize(TOKENS::GetEmbeddedSize(assets));
	if(!out.GetSize())return false;

	VERIFY(((TOKENS*)out.Begin())->Embed(assets) == out.GetSize());
	return true;
}

bool ChainSimulator::_ResolveExistingState(rvm::ContractInvokeId ciid, uint32_t shardId, const rvm::ScopeKey& sk, rvm::StringStreamImpl& out)
{
	rvm::ConstStateData stateData{ nullptr, 0 , 0}; 
	SimuShard* s = GetShard(shardId);
	ASSERT(s);
	switch (rvm::CONTRACT_SCOPE(ciid)) 
	{ 
	case rvm::Scope::Global: 
	case rvm::Scope::Shard:
		stateData = s->GetState(-ciid); 
		break;
	default:
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
	if(!pEngine) return false;

	return pEngine->StateJsonify(ciid, &data, &out);
}

bool ChainSimulator::_ComposeStateData(rvm::ContractInvokeId ciid, rt::String_Ref jsonParameters, const rt::String_Ref& existing_state, rvm::ConstData &out_buf)
{
	rt::String derived;
	rvm::ConstString s = { jsonParameters.Begin(), (uint32_t)jsonParameters.GetLength() };

	if(!existing_state.IsEmpty())
	{
		rt::JsonObject(existing_state).Derive(jsonParameters, derived);
		s = { derived.Begin(), (uint32_t)derived.GetLength() };
	}

	thread_local rvm::DataBufferImpl data;
	data.Empty();
	JsonLogError jsonErr;
	if (!GetEngine(rvm::CONTRACT_ENGINE(ciid))->StateJsonParse(ciid, &s, &data, &jsonErr))
		return false;
	
	out_buf = { data.GetData(), data.GetSize() };
	return true;
}

}