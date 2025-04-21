#include "../../SFC/core/ext/botan/botan.h"
#include "../../SFC/core/os/multi_thread.h"
#include "simu_script.h"
#include "chain_simu.h"
#include <array>

namespace oxd
{

int SimulatorMain(const os::CommandLine& cmd)
{
#ifdef _DEBUG
	os::EnableCrashDump("chsimu.dmp", true);
#endif

	if(cmd.HasOption("stdout")){
		auto StandardOutWriter = [](LPCSTR log, int type, LPVOID cookie){
			std::string str(log);
			std::cout << log << std::endl << std::flush;
		};
		os::_details::SetConsoleLogWriteFunction(StandardOutWriter, nullptr);
	}
	if(cmd.GetTextCount() == 0)
	{
		_LOG("[PRD]: chsimu input_file.(prd|sol|prdts) [-async] [-perftest] [-order:n] [-viz:output_filename] [-viz_templ:webui_template_path]");
		return 1;
	}

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
		_LOG("[PRD]: Unable to create Preda Home Directory: " << predaHomePath);
		return 1;
	}
	rt::String lockPath = predaHomePath + ".preda_lock";
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

	if(cmd.HasOption("log"))
	{
		rt::String defaultLogPath = predaHomePath + "outputs.log";
		rt::String_Ref log = cmd.GetOption("log", defaultLogPath);
		os::SetLogFile(ALLOCA_C_STRING(log), false);
	}

	{
		ChainSimulator chsimu;
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
		if(chsimu.Init(cmd))
		{
			os::SetProcessPriority(os::PROCPRIO_HIGH);
			std::vector<std::pair<rt::String, rt::String>> prdFiles;			// <filePath, fileContent>
			std::vector<std::pair<rt::String, rt::String>> prdtsFiles;
			std::vector<std::pair<rt::String, rt::String>> solFiles;

			// classify files
			for(uint32_t i = 0; i < cmd.GetTextCount(); i++){
				rt::String fileContent;
				if(!os::File::LoadText(cmd.GetText(i), fileContent)){
					_LOG_WARNING("[PRD]: Contract source file: " << cmd.GetText(i) << " cannot be loaded");
					continue;
				}
				std::string filePath(cmd.GetText(i));
				auto fileExtensionSplit = filePath.find_last_of('.');
				std::string extName = filePath.substr(fileExtensionSplit + 1);
				if("prd" == extName){
					prdFiles.push_back(std::make_pair(rt::String(filePath.c_str()), fileContent));
				}
				else if("prdts" == extName){
					// replace command values
					rt::String str;
					for (UINT i = 0; i < cmd.GetOptionCount(); i++)
					{
						str = rt::SS("$~") + cmd.GetOptionName(i) + '$';
						fileContent.Replace(str, cmd.GetOptionValue(i));
						str = rt::SS("~") + cmd.GetOptionName(i);
						fileContent.Replace(str, cmd.GetOptionValue(i));
					}
					prdtsFiles.push_back(std::make_pair(rt::String(filePath.c_str()), fileContent));
				}
				else if("sol-json" == extName){
					// TODO: handle solidity issues
					rt::JsonObject  codes_json = fileContent;
					rt::Json new_code;
					bool exist;
					rt::String_Ref entryFile = codes_json.GetValue("entryFile", exist);
					if (!exist)
					{
						_LOG_WARNING("[PRD]: Failed to find entry file: " << filePath);
						continue;
					}

					rt::String_Ref entryContract = codes_json.GetValue("entryContract", exist);
					if (!exist)
					{
						_LOG_WARNING("[PRD]: Failed to find entry contract: " << filePath);
						continue;
					}

					new_code.Object() << (
						J(entryFile) = entryFile,
						J(entryContract) = entryContract
						);

					rt::JsonObject sources = codes_json.GetValue("sources", exist);
					if (!exist)
					{
						_LOG_WARNING("[PRD]: Failed to find sources: " << filePath);
						continue;
					}

					{
						auto scope = new_code.ScopeAppendingKey("sources");
						new_code.Object();
						rt::JsonKeyValuePair kv;
						while (sources.GetNextKeyValuePair(kv))
						{
							rt::String absPath;
							os::File::ResolveRelativePath(rt::String_Ref(filePath).GetFilePath() + '/' + kv.GetValue(), absPath);
							rt::String solContent;
							if (!os::File::LoadText(absPath, solContent))
							{
								_LOG_WARNING("[PRD]: Failed to load source code: " << absPath);
								continue;
							}
							new_code << (
								rt::_JTag(kv.GetKey()) = (
									J(content) = rt::JsonEscapeString(solContent)
									)
								);
						}
					}
					solFiles.push_back(std::make_pair(rt::String(filePath.c_str()), new_code.GetInternalString()));
				}
			}

			// handle .prd files
			if(!prdFiles.empty() && chsimu.Compile(prdFiles))
				_LOG("[PRD]: Compile succeeded\n");

			// handle .prdts files
			for(auto& prdtsFile : prdtsFiles){
				// check undefined values
				rt::String_Ref line;
				uint32_t lineNum = 0;
				bool isPrdtsContentCorrect = true;
				while (prdtsFile.second.GetNextLine(line, false)) {
					++lineNum;
					rt::String_Ref cmd = line.TrimRightSpace();
					SSIZE_T var_begin = cmd.FindString(rt::String("$~"));
					SSIZE_T var_end = var_begin == -1 ? -1 : cmd.FindCharacter("$", var_begin + 1);
					if (var_begin != -1 && cmd.FindString("//") < 0)
					{
						_LOG_WARNING("[PRD] Line " << lineNum << ": Argument \"" << cmd.SubStr(var_begin, var_end - var_begin + 1) << "\" is undefined");
						isPrdtsContentCorrect = false;
					}
				}
				if (!isPrdtsContentCorrect)
					continue;

				rt::Json& json = chsimu.GetVizJson();
				json.Array();
				std::string filePath(prdtsFile.first);

				VIZ_SECTION_BEGIN(json, "Run");
				json.Object(
					(J(script) = rt::String(filePath.c_str()).EscapeCharacters("/"),
					(J(ShardOrder) = chsimu.GetShardOrder()))
				);
				VIZ_SECTION_END;
				auto fileExtensionSplit = filePath.find_last_of('.');
				std::string extName = filePath.substr(fileExtensionSplit + 1);
				PredaScriptRunner runner;
				runner.SetScriptDirPath(rt::String_Ref(filePath).GetFilePath() + '/');
				if(0 == runner.Run(chsimu, prdtsFile.second.Begin())){
					_LOG("[PRD]: Run script successfully\n");
				}
			}

			// handle .sol-json files
			for (auto& solFile : solFiles) 
				chsimu.CompileSol(solFile.second, solFile.first);
		}
		chsimu.ExportViz();
	}

	lockfile.Unlock();
	lockfile.Close();
	return 0;
}

int PredaScriptRunner::Run(ChainSimulator& _chsimu, const std::string& fileContent)
{
	PredaScriptRealListener listener(_chsimu);
	ScriptParseTreeBuilder builder(fileContent);
	antlr4::tree::ParseTreeWalker walker;
	_chsimu.SetScriptRunner(this);
	_chsimu.SetScriptListener(&listener);

	auto pScritps = builder.scripts();
	if (!pScritps)
		return 1;
	walker.walk(&listener, pScritps);

	_chsimu.SetScriptRunner(nullptr);
	_chsimu.SetScriptListener(nullptr);
	return 0;
}
PredaScriptRealListener::PredaScriptRealListener(ChainSimulator& _chsimu) :m_chsimu(_chsimu)
{
	m_stopWatch.Restart();
	m_stopWatch.SetOutputMillisecond();
}

void PredaScriptRealListener::enterScript(PredaScriptParser::ScriptContext * ctx)
{
	m_currentLineNum = (uint32_t)ctx->getStart()->getLine();
}

void PredaScriptRealListener::enterAwaitChain(PredaScriptParser::AwaitChainContext* /*ctx*/) 
{ 
	m_chsimu.Await();
}

void PredaScriptRealListener::enterStepChain(PredaScriptParser::StepChainContext* /*ctx*/) 
{ 
	m_chsimu.Run(true);
}

void PredaScriptRealListener::enterRunChain(PredaScriptParser::RunChainContext* /*ctx*/) 
{ 
	if (m_users.empty())
	{
		_LOG("[PRD]: No address has been allocated. Use \"allocate.address\" to create address");
		return;
	}
	m_chsimu.Run();
}

void PredaScriptRealListener::enterStopChain(PredaScriptParser::StopChainContext* /*ctx*/) 
{ 
	m_chsimu.Stop();
}

void PredaScriptRealListener::enterGetChainInfo(PredaScriptParser::GetChainInfoContext* /*ctx*/) 
{ 
	m_chsimu.Info();
}

void PredaScriptRealListener::enterIssueTxn(PredaScriptParser::IssueTxnContext * ctx)
{
	std::vector<oxd::SimuTxn*> txns;
	if(!ResolveIssueTxn(ctx, txns))
		return;

	for(auto txn : txns)
		m_chsimu.IssueTxn(txn);

	if(ctx->txnReturnInfo()){
		for(auto txn : txns){
			m_txnRecords[ctx->txnReturnInfo()->identifier()->getText()].push_back(txn);
		}
	}
}

void PredaScriptRealListener::enterDeployContractOnChain(PredaScriptParser::DeployContractOnChainContext * ctx)
{

	std::vector<uint32_t> userIds;
	std::vector<uint8_t> args;
	if (ctx->shardScope() || !ResolveUserIdFromAddressScope(ctx->addressScope(), userIds) || userIds.size() != 1 || !ResolveDeployArgsData(ctx->contractProperties(), args)) {
		_LOG("[PRD] Line " << GetLineNum() << ": Invalid deploy initiator.");
		return;
	}
	SimuTxn* deployTxn = SimuTxn::Create((uint32_t)args.size(), 0);
	deployTxn->Target = ScopeTarget(m_users[userIds[0]]);
	deployTxn->Type = rvm::InvokeContextType::System;
	deployTxn->Timestamp = os::Timestamp::Get();
	deployTxn->Flag = (SimuTxnFlag)0;
	ASSERT(deployTxn->TokensSerializedSize == 0);
	std::copy(args.begin(), args.end(), deployTxn->SerializedData);
	deployTxn->ArgsSerializedSize = (uint32_t)args.size();
	sec::Hash<sec::HASH_SHA256>().Calculate(((char*)deployTxn) + sizeof(rvm::HashValue), deployTxn->GetSize() - sizeof(rvm::HashValue), &deployTxn->Hash);

	m_chsimu.Deploy(deployTxn);
}

void PredaScriptRealListener::enterBatchInsertTxnOnChain(PredaScriptParser::BatchInsertTxnOnChainContext * ctx)
{
	if(m_batchTxns.find(ctx->varName()->getText()) == m_batchTxns.end())
		return;
	for(auto txn : m_batchTxns[ctx->varName()->getText()])
		m_chsimu.IssueTxn(txn);
}

void PredaScriptRealListener::enterVariableAssign(PredaScriptParser::VariableAssignContext * ctx)
{
	std::string varName = ctx->varName()->getText();
	if(m_scriptVariables.find(varName) != m_scriptVariables.end())
		return;
	scriptVariable var;
	if(ctx->varValue()->stringLiteral())
	{
		var.mType = scriptVariable::STRING;
		std::string value = ctx->varValue()->stringLiteral()->getText();
		var.data.resize(value.length() - 2);
		std::copy(value.begin() + 1, value.end() - 1, var.data.begin());
	}
	else if(ctx->varValue()->numberLiteral())
	{
		var.mType = scriptVariable::INT32;
		int32_t value = std::stoi(ctx->varValue()->numberLiteral()->getText());
		var.data.resize(sizeof(value));
		std::copy(&value, &value + 1, var.data.begin());
	}
	m_scriptVariables[varName] = var;
}

void PredaScriptRealListener::enterDataReadFromFile(PredaScriptParser::DataReadFromFileContext * ctx)
{
	std::string filePath(ctx->csvfilePath()->getText());
	rt::String absoluteFilePath;
	os::File::ResolveRelativePath(m_chsimu.GetScriptDirPath() + filePath, absoluteFilePath);
	os::FileReadLine csvfile;
	if (!csvfile.Open(absoluteFilePath.GetString()))
	{
		_LOG("[PRD] Line " << GetLineNum() << ": Unable to open CSV file, file path: " << filePath);
		return;
	}

	rt::String_Ref line;
	uint32_t lineNum = 0;
	csvfile.GetNextLine(line);
	++lineNum;

	rt::String_Ref fields;
	int32_t contractPos = -1;
	int32_t funcPos = -1;
	int32_t targetPos = -1;
	int32_t parametersPos = -1;
	constexpr uint32_t maxColumns = 64;
	rt::String_Ref seg[maxColumns];
	uint32_t count = line.Split(seg, maxColumns, ",");

	for (uint32_t i = 0; i < count; ++i)
	{
		if (seg[i] == "contract_name") contractPos = i;
		else if (seg[i] == "contract_function") funcPos = i;
		else if (seg[i] == "sender") targetPos = i;
		else if (seg[i] == "parameters") parametersPos = i;
	}
	if (!line.GetLength() || count < 4 || contractPos == -1 || funcPos == -1 || targetPos == -1 || parametersPos == -1)
	{
		_LOG("[CSV] Line " << lineNum << ": Invalid input file format. At least 4 fields (contract_name, contract_function, sender, parameters) are required");
		return;
	}
	std::vector<rt::String_Ref> txnSeg(count);
	std::vector<rt::String_Ref> lines;
	std::vector<oxd::SimuTxn*> txns;
	while (csvfile.GetNextLine(line))
	{
		++lineNum;
		uint32_t lineElementCo = line.Split(&txnSeg[0], count, ",");
		if (lineElementCo < count)
		{
			_LOG("[CSV] Line " << lineNum << ": Invalid data format, missing elements");
			continue;
		}
		SSIZE_T openBracketPos = line.FindCharacter('{');
		SSIZE_T closeBracketPos = line.FindCharacterReverse('}');
		if (openBracketPos < 0 || closeBracketPos < 0)
		{
			_LOG("[CSV] Line " << lineNum << "Invalid CSV input: " << line);
			continue;
		}
		rt::String_Ref twoQuotJson = line.SubStr(openBracketPos, closeBracketPos - openBracketPos + 1);
		//json in CSV contains two quotation marks for example:{""amount"":1}, codes below replace two quotation marks with one
		std::string jsonParam;
		bool quoteFlag = false;
		for (size_t i = 0; i < twoQuotJson.GetLength(); ++i)
		{
			if ('"' != twoQuotJson[i]) {
				quoteFlag = false;
				jsonParam.push_back(twoQuotJson[i]);
			}
			else if (!quoteFlag) {
				quoteFlag = true;
				jsonParam.push_back(twoQuotJson[i]);
			}
		}

		rt::String contractName(txnSeg[contractPos]);
		rt::String functionName(txnSeg[funcPos]);
		rt::String target(txnSeg[targetPos]);
		if (target.GetLength() && target[0] != '#')
			target = rt::SS("@") + target;
		rt::String issueTxnCommand = contractName + "." + functionName + target + jsonParam;

		ScriptParseTreeBuilder builder(issueTxnCommand.GetString());
		PredaScriptParser::IssueTxnContext* ctx = dynamic_cast<PredaScriptParser::IssueTxnContext*>(builder.issueTxn());
		if (!ctx) {
			_LOG("[CSV] Line " << lineNum << ": Invalid fromat. ");
			return;
		}
		std::vector<oxd::SimuTxn*> tmpTxns;
		if (!ResolveIssueTxn(ctx, tmpTxns))
			return;
		for(auto txn : tmpTxns)
			txns.emplace_back(txn);
	}
	m_batchTxns[ctx->varName()->getText()] = std::move(txns);
}

void PredaScriptRealListener::enterSetGasLimit(PredaScriptParser::SetGasLimitContext * ctx)
{
	uint32_t gas_limit = std::stoi(ctx->numberLiteral()->getText());
	if(ctx->GLOBAL())
		m_chsimu.SetScriptGlobalGasLimit(gas_limit);
	else
		m_chsimu.SetScriptGasLimit(gas_limit);
}

void PredaScriptRealListener::enterSetContractState(PredaScriptParser::SetContractStateContext * ctx)
{
	rvm::Scope scope = ctx->stateScope()->ADDRESS() ? rvm::Scope::Address : (ctx->stateScope()->SHARD() ? rvm::Scope::Shard : rvm::Scope::Global);
	if (isScopeTargetCorresponded(scope, ctx->scope()))
		ResolveModifyState(ctx->contractId(), ctx->scope(), ctx->jsonParameters(), true);
}

void PredaScriptRealListener::enterUpdateState(PredaScriptParser::UpdateStateContext * ctx)
{
	rvm::Scope scope = ctx->stateScope()->ADDRESS() ? rvm::Scope::Address : (ctx->stateScope()->SHARD() ? rvm::Scope::Shard : rvm::Scope::Global);
	if (isScopeTargetCorresponded(scope, ctx->scope()))
		ResolveModifyState(ctx->contractId(), ctx->scope(), ctx->jsonParameters(), false);
}

void PredaScriptRealListener::enterTokenState(PredaScriptParser::TokenStateContext * ctx)
{

}

void PredaScriptRealListener::enterMintToken(PredaScriptParser::MintTokenContext* ctx)
{
	if ("mint" != ctx->identifier()->getText())
		return;
	rvm::ContractInvokeId ciid;
	std::string dappContractName = ctx->contractId()->cvid() ? ctx->contractId()->cvid()->getText() : 
															   (ctx->contractId()->contractName()->dappName? ctx->contractId()->contractName()->getText() : std::string(m_chsimu.m_attribute.DAPP_NAME.Begin()) + '.' + ctx->contractId()->contractName()->getText());
	if (!m_chsimu.ResolveCiid(dappContractName, rvm::Scope::Global, ciid))
		return;
	rvm::TokenId token = rvm::TokenIdFromSymbol(ctx->tokenSymbol()->getText());
	if (token == rvm::TokenIdInvalid)
	{
		_LOG_WARNING("[PRD] Line " << GetLineNum() << ": Token symbol `" << ctx->tokenSymbol()->getText() << "` is ill-formatted");
		return;
	}
	m_chsimu.AddSuplliedToken(ciid, token);
}

void PredaScriptRealListener::enterLoadState(PredaScriptParser::LoadStateContext * ctx)
{
	std::string filePath(ctx->jsonFilePath()->getText());
	rt::String absoluteFilePath;
	os::File::ResolveRelativePath(m_chsimu.GetScriptDirPath() + filePath, absoluteFilePath);
	os::File statefile;
	if (!statefile.Open(absoluteFilePath.GetString()))
	{
		_LOG("[PRD] Line " << GetLineNum() << ": Unable to open state file, file path: " << filePath);
		return;
	}
	rt::String text;
	os::File::LoadText(absoluteFilePath, text);
	rt::JsonArray allStateArr(text);
	if (allStateArr.IsEmpty())
	{
		_LOG("[PRD] Line " << GetLineNum() << ": Unable to parse state file, file path: " << filePath);
		return;
	}
	rt::String_Ref stateJson;
	while (allStateArr.GetNextObject(stateJson)) {
		bool ret = false;
		if(ctx->stateScope()->ADDRESS())
			ret = ResolveStateJson(rvm::Scope::Address, stateJson);
		else if(ctx->stateScope()->SHARD())
			ret = ResolveStateJson(rvm::Scope::Shard, stateJson);
		else
			ret = ResolveStateJson(rvm::Scope::Global, stateJson);
		if (!ret) 
			return;
	}
}

void PredaScriptRealListener::enterSaveState(PredaScriptParser::SaveStateContext * ctx)
{
	os::File stateFile;
	rt::String absoluteFilePath;
	os::File::ResolveRelativePath(m_chsimu.GetScriptDirPath() + ctx->fileName()->getText(), absoluteFilePath);
	stateFile.Open(absoluteFilePath.Begin(), os::File::Normal_Write, true);
	rt::Json json;
	json.Array();
	rvm::ContractVersionId cvid = rvm::ContractVersionIdInvalid;

	if(ctx->contractId()){
		std::string contractId = ctx->contractId()->getText();
		if(ctx->contractId()->cvid())
			cvid = (rvm::ContractVersionId)rt::String_Ref(contractId).ToNumber<uint64_t>();
		else{
			std::string dappContractName = ctx->contractId()->contractName()->dappName? contractId : (std::string(m_chsimu.m_attribute.DAPP_NAME.Begin()) + contractId);
			rvm::ConstString contract = {dappContractName.data(), (uint32_t)dappContractName.size()};
			cvid = m_chsimu.GetContractByName(&contract);
		}
	}
	if(ctx->stateScope()->ADDRESS()){
		m_chsimu.GetStateJson(rvm::Scope::Address, cvid, json);
		_LOG("[PRD]: Address states Written to: " << ctx->fileName()->getText());
	}
	else if(ctx->stateScope()->SHARD()){
		m_chsimu.GetStateJson(rvm::Scope::Shard, cvid, json);
		_LOG("[PRD]: Shard states Written to: " << ctx->fileName()->getText())
	}
	stateFile.Write(json.GetInternalString());
	stateFile.Close();
}

void PredaScriptRealListener::enterConfigAddress(PredaScriptParser::ConfigAddressContext * ctx)
{
	int add = 0;
	if (ctx->numberLiteral()) {
		std::string numStr = ctx->numberLiteral()->getText();
		if (numStr.length() > 7 || (add = std::stoi(numStr)) > 100000) {
			_LOG("[PRD] Line " << GetLineNum() << ": Number of addresses to be allcoated cannot exceed 1000000");
			add = 10;
		}
		else if (add <= 0) {
			_LOG("[PRD] Line " << GetLineNum() << ": Illegal input for number of addresses to be allcoated");
			add = 10;
		}
	}
	else
		add = 10;

	uint32_t shardNum = m_chsimu.GetShardCount();

	uint32_t add_per = (add + shardNum - 1) / shardNum;
	add = add_per * shardNum;

	uint32_t old = (uint32_t)m_users.size();
	m_users.resize(old + add);

	uint32_t* count = (uint32_t*)alloca(sizeof(uint32_t) * shardNum);
	rt::Zero(count, sizeof(uint32_t) * shardNum);

	for(uint32_t i = old; i < m_users.size();)
	{
		auto& a = m_users[i];
		m_randomizer.Randomize(a);
		rvm::ADDRESS_SET_SECSUITE(a, rvm::SecSuite::Ed25519);

		auto& co = count[m_chsimu.GetShardIndex(a)];
		if(co < add_per)
		{
			i++;
			co++;
		}
	}

	_LOG("[PRD]: " << add << " addresses added and evenly distributed in shards");
}

void PredaScriptRealListener::enterConfigRandomizer(PredaScriptParser::ConfigRandomizerContext* ctx) 
{ 
	if (ctx->numberLiteral())
		new (&m_randomizer) rt::Randomizer(std::stoi(ctx->numberLiteral()->getText()));
	else
		new (&m_randomizer) rt::Randomizer((uint32_t)os::Timestamp::Get());
}

void PredaScriptRealListener::enterNormalLog(PredaScriptParser::NormalLogContext* ctx)
{
	std::string str = ctx->stringLiteral()->getText();
	_LOG(str.substr(1, str.length() - 2));
}

void PredaScriptRealListener::enterLogHighlight(PredaScriptParser::LogHighlightContext * ctx)
{
	std::string str = ctx->stringLiteral()->getText();
	_LOG_HIGHLIGHT("[HIGHLIGHT] " + str.substr(1, str.length() - 2));
}

void PredaScriptRealListener::enterLogWarning(PredaScriptParser::LogWarningContext * ctx)
{
	std::string str = ctx->stringLiteral()->getText();
	_LOG_HIGHLIGHT("[WARNING] " + str.substr(1, str.length() - 2));
}

void PredaScriptRealListener::enterLogError(PredaScriptParser::LogErrorContext * ctx)
{
	std::string str = ctx->stringLiteral()->getText();
	_LOG_HIGHLIGHT("[ERROR] " + str.substr(1, str.length() - 2));
}

void PredaScriptRealListener::enterStopWatchRestart(PredaScriptParser::StopWatchRestartContext * ctx)
{
	_LOG("[PRD]: Stopwatch restarted");
	m_stopWatch.Restart();
	m_stopWatch.SetOutputMillisecond();
	m_stopWatchPendingTxnCount = m_chsimu.GetPendingTxnsCount();
	m_stopWatchExecutedTxnCount = m_chsimu.GetExecutedTxnsCount();
}

void PredaScriptRealListener::enterStopWatchReport(PredaScriptParser::StopWatchReportContext * ctx)
{
	uint64_t lapsed = rt::max<long long>(1LL, m_stopWatch.TimeLapse());

	_LOG_HIGHLIGHT("[PRD]: Stopwatch: "<< lapsed <<" msec\n"
					"[PRD]: Order: "<< m_chsimu.GetShardOrder() <<", "
					"TPS:"<< (m_stopWatchPendingTxnCount - m_chsimu.GetPendingTxnsCount()) * 1000 / lapsed<<", "
					"uTPS:"<< (m_chsimu.GetExecutedTxnsCount() - m_stopWatchExecutedTxnCount) * 1000 / lapsed
	);
}

void PredaScriptRealListener::enterVizBlock(PredaScriptParser::VizBlockContext * ctx)
{
	if(!m_chsimu.EnableViz()) return;
	if (!isShardScopeCorrect(ctx->shardScope()))
		return;
	std::vector<uint32_t> shardIds;
	ResolveShardIdFromShardScope(ctx->shardScope(), shardIds);
	int64_t blockHeight = ctx->numberLiteral() ? (std::stoi(ctx->numberLiteral()->getText())) : -1;
	rt::Json json;
	json.Array();
	for (auto shardId : shardIds) {
		if (!m_chsimu.VizBlock(shardId, blockHeight, json))
			return;
	}

	std::string vizCmd = "viz.block " + ctx->shardScope()->getText() + (ctx->numberLiteral() ? (':' + ctx->numberLiteral()->getText()) : "");
	VIZ_QUERY_SECTION_BEGIN(m_chsimu.m_vizInfo.vizJson, "Block", vizCmd);
	m_chsimu.m_vizInfo.vizJson.Object(json);
	VIZ_SECTION_END;
}

void PredaScriptRealListener::enterVizAddr(PredaScriptParser::VizAddrContext * ctx)
{
	if(!m_chsimu.EnableViz()) return;
	if (!isAddressScopeCorrect(ctx->addressScope()))
		return;
	std::vector<uint32_t> userIds;
	ResolveUserIdFromAddressScope(ctx->addressScope(), userIds);
	std::string contractName = ctx->contractName() ? ctx->contractName()->getText() : "";
	rt::Json json;
	json.Array();
	for (auto userId : userIds) {
		m_chsimu.VizAddr(contractName, m_users[userId], userId, json);
	}

	std::string vizCmd = "viz.addr " + ctx->addressScope()->getText() + (ctx->contractName() ? ' ' + contractName : "");
	VIZ_QUERY_SECTION_BEGIN(m_chsimu.m_vizInfo.vizJson, "Addr", vizCmd);
	m_chsimu.m_vizInfo.vizJson.Object(json);
	VIZ_SECTION_END;
}

void PredaScriptRealListener::enterVizShard(PredaScriptParser::VizShardContext * ctx)
{
	if(!m_chsimu.EnableViz()) return;
	if (!isShardScopeCorrect(ctx->shardScope()))
		return;
	std::vector<uint32_t> shardIds;
	ResolveShardIdFromShardScope(ctx->shardScope(), shardIds);
	std::string contractName = ctx->contractName() ? ctx->contractName()->getText() : "";
	rt::Json json;
	json.Array();
	for(auto shardId : shardIds)
		m_chsimu.VizShard(contractName, shardId, json);

	std::string vizCmd = "viz.shard " + ctx->shardScope()->getText() + (ctx->contractName() ? ' ' + contractName : "");
	VIZ_QUERY_SECTION_BEGIN(m_chsimu.m_vizInfo.vizJson, "Shard", vizCmd);
	m_chsimu.m_vizInfo.vizJson.Object(json);
	VIZ_SECTION_END;
}

void PredaScriptRealListener::enterVizTxn(PredaScriptParser::VizTxnContext * ctx)
{
	if(!m_chsimu.EnableViz())
		return;
	std::string txnIdentifier = ctx->txnReturnInfo()->getText();
	if (m_txnRecords.find(txnIdentifier) == m_txnRecords.end()) {
		_LOG("[PRD] Line " << GetLineNum() << ": Identifier " << txnIdentifier << " does not exist.");
		return;
	}
	rt::Json json;
	json.Array();
	if(ctx->numberLiteral())
	{
		int txnId = std::stoi(ctx->numberLiteral()->getText());
		if (txnId < 0) {
			_LOG("[PRD] Line " << GetLineNum() << ": Invalid index.");
			return;
		}
		if (txnId > m_txnRecords[txnIdentifier].size() - 1) {
			_LOG("[PRD] Line " << GetLineNum() << ": Index out of range.");
			return;
		}
		if (!m_chsimu.VizTxn(m_txnRecords[txnIdentifier][txnId], json))
			return;
	}
	else
	{
		for (auto txn : m_txnRecords[txnIdentifier]) {
			if (!m_chsimu.VizTxn(txn, json))
				return;
		}
	}
	std::string vizCmd = "viz.txn " + txnIdentifier + (ctx->numberLiteral() ? "[" + ctx->numberLiteral()->getText() + "]" : "");
	VIZ_QUERY_SECTION_BEGIN(m_chsimu.m_vizInfo.vizJson, "Txn", vizCmd);
	m_chsimu.m_vizInfo.vizJson.Object(json);
	VIZ_SECTION_END;
}

void PredaScriptRealListener::enterVizTrace(PredaScriptParser::VizTraceContext * ctx)
{
	if (!m_chsimu.EnableViz())
		return;
	std::string txnIdentifier = ctx->txnReturnInfo()->getText();
	if (m_txnRecords.find(txnIdentifier) == m_txnRecords.end()) {
		_LOG("[PRD] Line " << GetLineNum() << ": Identifier " << txnIdentifier << " does not exist.");
		return;
	}
	rt::Json json;
	json.Array();
	if (ctx->numberLiteral())
	{
		int txnId = std::stoi(ctx->numberLiteral()->getText());
		if (txnId < 0) {
			_LOG("[PRD] Line " << GetLineNum() << ": Invalid index.");
			return;
		}
		if (txnId > m_txnRecords[txnIdentifier].size() - 1) {
			_LOG("[PRD] Line " << GetLineNum() << ": Index out of range.");
			return;
		}
		if (!m_chsimu.VizTrace(m_txnRecords[txnIdentifier][txnId], json))
			return;
	}
	else
	{
		for (auto txn : m_txnRecords[txnIdentifier]) {
			if (!m_chsimu.VizTrace(txn, json))
				return;
		}
	}
	std::string vizCmd = "viz.trace " + ctx->txnReturnInfo()->getText() + (ctx->numberLiteral() ? "[" + ctx->numberLiteral()->getText() + "]" : "");
	VIZ_QUERY_SECTION_BEGIN(m_chsimu.m_vizInfo.vizJson, "Trace", vizCmd);
	m_chsimu.m_vizInfo.vizJson.Object(json);
	VIZ_SECTION_END;
}

void PredaScriptRealListener::enterVizSection(PredaScriptParser::VizSectionContext * ctx)
{
	if(!m_chsimu.EnableViz()) return;
	std::string str = ctx->stringLiteral()->getText();
	if (str.empty())
		return;
	VIZ_SECTION_BEGIN(m_chsimu.m_vizInfo.vizJson, "Section");
	m_chsimu.m_vizInfo.vizJson.String(str.substr(1, str.length() - 2));
	VIZ_SECTION_END
}

void PredaScriptRealListener::enterVizProfiling(PredaScriptParser::VizProfilingContext * ctx)
{
	if(!m_chsimu.EnableViz()) return;
	rt::Json json;
	json.Array();
	m_chsimu.VizProfiling(json);
	VIZ_QUERY_SECTION_BEGIN(m_chsimu.m_vizInfo.vizJson, "Profiling", "viz.profiling");
	m_chsimu.m_vizInfo.vizJson.Object(json);
	VIZ_SECTION_END
}

void PredaScriptRealListener::enterVizUintScope(PredaScriptParser::VizUintScopeContext * ctx)
{
	if(!m_chsimu.EnableViz()) return;
	std::vector<uint32_t> scopeLen;
	ResolveScopeLenFromUintScope(ctx->uintScope(), scopeLen);
	rt::Json json;
	json.Array();
	for(auto s : scopeLen)
		m_chsimu.VizUintScope(ctx->contractName()->getText(), s, ctx->scopeTarget()->getText(), json);

	std::string vizCmd = "viz.uint_scope " + ctx->uintScope()->getText() + ' ' + ctx->contractName()->getText() + ':' + ctx->scopeTarget()->getText();
	VIZ_QUERY_SECTION_BEGIN(m_chsimu.m_vizInfo.vizJson, "Uint_scope", vizCmd);
	m_chsimu.m_vizInfo.vizJson.Object(json);
	VIZ_SECTION_END
}
bool PredaScriptRealListener::ResolveIssueTxn(PredaScriptParser::IssueTxnContext * ctx, std::vector<oxd::SimuTxn*>& out)
{
	out.clear();
	// 1. resolve random values and identifiers
	std::string instantiatedJsonParameterStr, instantiatedSuppliedTokens;
	if (!ResolveJsonParameters(ctx->jsonParameters(), instantiatedJsonParameterStr) || !ResolveSuppliedTokens(ctx->suppliedTokens(), instantiatedSuppliedTokens))
		return false;
	// 2. check and get contract function info
	ContractFunction cf;
	rvm::ContractInvokeId ciid;
	if(!m_chsimu.GetContractFunction(ctx->contractId()->getText(), ctx->functionName()->getText(), instantiatedJsonParameterStr, cf, ciid))
		return false;
	// 3. check function scope
	if(rvm::CONTRACT_ENGINE(cf.Contract) != rvm::EngineId::SOLIDITY_EVM && !isScopeTargetCorresponded(rvm::CONTRACT_SCOPE(ciid), ctx->scope()))
		return false;
	// 4. try compose txn
	SimuTxn* txn = nullptr;
	if (rvm::CONTRACT_ENGINE(cf.Contract) == rvm::EngineId::SOLIDITY_EVM)
	{
		if (ctx->scope() && ctx->scope()->addressScope())
			AttachSolFunctionScope(b32a(m_users[0]).GetString(), instantiatedJsonParameterStr);
		AttachSolFunctionName(ctx->functionName()->getText(), instantiatedJsonParameterStr);
	}
	auto ret = m_chsimu.ComposeTxn(ciid, cf.Op, instantiatedJsonParameterStr, "", txn);
	if(0 != ret)
		return false;
	_SafeRelease(txn);
	// 5. prepare txns
	uint32_t count = ctx->count() ? std::stoi(ctx->count()->numberLiteral()->getText()) : 1;
	struct preparedTxnsInfo
	{
		uint32_t shard_id;
		std::string json_parameters;
		std::string supplied_tokens;
	};
	std::vector<preparedTxnsInfo> preparedTxnsBuffer;			// <shardId, txn>
	for(uint32_t i = 0; i < count; ++i)
	{
		bool ifAllUsers = false;
		uint32_t usrNum = CheckIfAllUsers(ctx->jsonParameters()) ? (uint32_t)m_users.size() : 1;
		std::vector<uint32_t> ids;		// shardId for shardScope and globalScope, usrId for addressScope
		if (!ResolveIdsFromScope(ctx->scope(), ids))
			continue;
		for(auto id : ids)
		{
			m_currentUserId4ComposeTxn = 0;
			for(uint32_t j = 0; j < usrNum; ++j)
			{
				preparedTxnsInfo txn;
				txn.shard_id = id;
				std::string jsonParameters, suppliedTokens;
				if (!ResolveJsonParameters(ctx->jsonParameters(), jsonParameters) || !ResolveSuppliedTokens(ctx->suppliedTokens(), suppliedTokens))
					continue;
				if (rvm::CONTRACT_ENGINE(cf.Contract) == rvm::EngineId::SOLIDITY_EVM)
				{
					if (ctx->scope() && ctx->scope()->addressScope())
						AttachSolFunctionScope(b32a(m_users[id]).GetString(), jsonParameters);
					AttachSolFunctionName(ctx->functionName()->getText(), jsonParameters);
				}
				++m_currentUserId4ComposeTxn;
				txn.json_parameters = jsonParameters;
				txn.supplied_tokens = suppliedTokens;
				preparedTxnsBuffer.emplace_back(txn);
			}
			m_currentUserId4ComposeTxn = 0;
		}
	}
	// 6. compose and issue txns parrelly
	std::string suppliedTokens = ctx->suppliedTokens() ? ctx->suppliedTokens()->getText() : "";
	count = (uint32_t)preparedTxnsBuffer.size();
	auto loop = [&](int i) {
		if(i >= (int)count)
			return false;
		SimuTxn* txn = nullptr;
		auto ret = m_chsimu.ComposeTxn(ciid, cf.Op, rt::String_Ref(preparedTxnsBuffer[i].json_parameters), rt::String_Ref(preparedTxnsBuffer[i].supplied_tokens), txn);
		if(0 != ret) 
			return false;
		if (ctx->scope() && ctx->scope()->addressScope()) {
			auto& addr = m_users[preparedTxnsBuffer[i].shard_id];
			txn->Target = ScopeTarget(addr);
			txn->TargetIndex = preparedTxnsBuffer[i].shard_id;
			txn->ShardIndex = m_chsimu.GetShardIndex(addr);
		}
		else {
			txn->ShardIndex = preparedTxnsBuffer[i].shard_id;
		}
		EnterCSBlock(m_CS);
		out.push_back(txn);
		return true;
	};
	if(count > 100)
		os::ParallelLoop(loop, (int)0, (int)count);
	else {
		for (int i = 0; i < (int)count; ++i)
			loop(i);
	}
	return true;
}

bool PredaScriptRealListener::ResolveJsonParameters(const std::string& in, std::string& out)
{
	ScriptParseTreeBuilder builder(in);
	PredaScriptParser::JsonParametersContext* ctx = dynamic_cast<PredaScriptParser::JsonParametersContext*>(builder.jsonParameters());
	if (!ctx)
		return false;
	return ResolveJsonParameters(ctx, out);
}

bool PredaScriptRealListener::ResolveJsonParameters(PredaScriptParser::JsonParametersContext* ctx, std::string& out)
{
	out = '{';
	if(!ctx->jsonParameter().empty())
	{
		for(auto v : ctx->jsonParameter())
		{
			std::string s;
			if (!ResolveJsonParameter(v, s)) {
				out = "";
				return false;
			}
			out += s;
			out += ", ";
		}
		out.pop_back();
		out.back() = '}';
	}
	else
		out += '}';
	return true;
}

bool PredaScriptRealListener::ResolveJsonParameter(PredaScriptParser::JsonParameterContext* ctx, std::string& out)
{
	out = ctx->jsonKey()->getText() + ": ";
	std::string jsonValue;
	if (!ResolveJsonValue(ctx->jsonValue(), jsonValue)) {
		out = "";
		return false;
	}
	out += jsonValue;
	return true;
}

bool PredaScriptRealListener::ResolveJsonValue(PredaScriptParser::JsonValueContext* ctx, std::string& out)
{
	if (ctx->primaryValue())
		return ResolvePrimaryValue(ctx->primaryValue(), out);
	else if (ctx->jsonParameters())
		return ResolveJsonParameters(ctx->jsonParameters(), out);
	else if (ctx->identifier()) {
		out = ctx->identifier()->getText();
		return true;
	}
	return false;
}

bool PredaScriptRealListener::ResolvePrimaryValue(PredaScriptParser::PrimaryValueContext* ctx, std::string& out)
{
	if (ctx->concreteValue())
		return ResolveConcreteValue(ctx->concreteValue(), out);
	else if (ctx->toBeAssignedValue())
		return ResolveToBeAssignedValue(ctx->toBeAssignedValue(), out);
	else if (ctx->arrayValue())
		return ResolveArrayValue(ctx->arrayValue(), out);
	return false;
}

bool PredaScriptRealListener::ResolveConcreteValue(PredaScriptParser::ConcreteValueContext* ctx, std::string& out)
{
	if (ctx->numberLiteral() || ctx->boolLiteral() || ctx->hexLiteral())
		out = ctx->getText();
	else if (ctx->stringLiteral())
	{
		std::string innerStr = ctx->stringLiteral()->getText().substr(1, ctx->stringLiteral()->getText().length() - 2);
		ScriptParseTreeBuilder builder(innerStr);
		auto varCtx = builder.toBeAssignedValue();
		if (nullptr == varCtx) {
			out = ctx->getText();
		}
		else {
			if (!ResolveToBeAssignedValue(dynamic_cast<PredaScriptParser::ToBeAssignedValueContext*>(varCtx), out)) {
				out = "";
				return false;
			}
			if (!out.empty())
				out = '"' + out + '"';
		}
	}
	return true;
}

bool PredaScriptRealListener::ResolveArrayValue(PredaScriptParser::ArrayValueContext* ctx, std::string& out)
{
	out = '[';
	if(!ctx->jsonValue().empty())
	{
		for(auto v : ctx->jsonValue())
		{
			std::string s;
			if (!ResolveJsonValue(v, s)) {
				out = "";
				return false;
			}
			out += s;
			out += ", ";
		}
		out.pop_back();
		out.back() = ']';
	}
	else
		out += ']';
	return true;
}

bool PredaScriptRealListener::ResolveBigintRandom(uint32_t bitwidth, std::string& out)
{
	uint32_t digits = (uint32_t)((double)bitwidth * 3.321928 + 0.99999999);
	out.resize(digits);
	out[0] = (GetRandomUint32() % 9) + '1';
	for(uint32_t i = 1; i < digits; ++i)
		out[i] = (GetRandomUint32() % 10) + '0';
	return true;
}

bool PredaScriptRealListener::ResolveToBeAssignedValue(PredaScriptParser::ToBeAssignedValueContext* ctx, std::string& out)
{
	if (ctx->intExpression())
	{
		return ResolveIntExpression(ctx->intExpression(), out);
	}
	else if (ctx->bigintRandom())
	{
		uint32_t bitWidth = std::stoi(ctx->bigintRandom()->numberLiteral()->getText());
		return ResolveBigintRandom(bitWidth, out);
	}
	else if (ctx->addressScope())
	{
		return ResolveAddressScope(ctx->addressScope(), out);
	}
	return false;
}

bool PredaScriptRealListener::ResolveIdsFromScope(PredaScriptParser::ScopeContext* ctx, std::vector<uint32_t>& out)
{
	if (!ctx) {
		out.push_back(rvm::GlobalShard);
	}
	else if(ctx->shardScope())
	{
		return ResolveShardIdFromShardScope(ctx->shardScope(), out);
	}
	else if(ctx->addressScope())
	{
		return ResolveUserIdFromAddressScope(ctx->addressScope(), out);
	}
	return true;
}

bool PredaScriptRealListener::ResolveShardIdFromAddressScope(PredaScriptParser::AddressScopeContext* ctx, std::vector<uint32_t>& shardIds)
{
	shardIds.clear();
	std::vector<uint32_t> userIds;
	if (!ResolveUserIdFromAddressScope(ctx, userIds))
		return false;
	for(auto userId : userIds)
		shardIds.push_back(m_chsimu.GetShardIndex(m_users[userId]));
	return true;
}

bool PredaScriptRealListener::ResolveShardIdFromShardScope(PredaScriptParser::ShardScopeContext* ctx, std::vector<uint32_t>& shardIds)
{
	shardIds.clear();
	if (ctx->numberLiteral()) {
		uint32_t shardId = std::stoi(ctx->numberLiteral()->getText());
		if(shardId < m_chsimu.GetShardCount())
			shardIds.push_back(shardId);
	}
	else if (ctx->identifier())
		shardIds.push_back(0);
	else if (ctx->RANDOM())
		shardIds.push_back(GetRandomUint32(0, m_chsimu.GetShardCount() - 1));
	else if (ctx->ALL())
	{
		for (uint32_t i = 0; i < m_chsimu.GetShardCount(); ++i)
			shardIds.push_back(i);
	}
	else
		shardIds.push_back(rvm::GlobalShard);
	return true;
}

bool PredaScriptRealListener::ResolveShardIdFromAddressScope(PredaScriptParser::AddressScopeContext* ctx, std::vector<std::pair<uint32_t, rvm::Address*>>& out)
{
	out.clear();
	std::vector<uint32_t> userIds;
	if (!ResolveUserIdFromAddressScope(ctx, userIds))
		return false;
	for(auto userId : userIds)
		out.push_back({m_chsimu.GetShardIndex(m_users[userId]), &m_users[userId]});
	return true;
}

bool PredaScriptRealListener::ResolveUserIdFromAddressScope(PredaScriptParser::AddressScopeContext* ctx, std::vector<uint32_t>& out)
{
	out.clear();
	if(ctx->numberLiteral())
	{
		uint32_t userId = std::stoi(ctx->numberLiteral()->getText());
		if(userId < m_users.size())
			out.push_back(userId);
	}
	else if(ctx->identifier())
		out.push_back(0);
	else if(ctx->RANDOM())
	{
		uint32_t userId = GetRandomUint32(0, (uint32_t)m_users.size() - 1);
		out.push_back(userId);
	}
	else if(ctx->ALL())
	{
		for(uint32_t i = 0; i < m_users.size(); ++i)
			out.push_back(i);
	}	
	else if (ctx->ed25519Address())
	{
		if (ctx->ed25519Address()->getText().length() != 66)
			return false;
		int userId = AddNewUser(ctx->ed25519Address()->getText());
		out.push_back(userId);
	}
	return true;
}

bool PredaScriptRealListener::ResolveScopeLenFromUintScope(PredaScriptParser::UintScopeContext* ctx, std::vector<uint32_t>& out)
{
	static constexpr std::array<uint32_t, 5> uintScope({32, 64, 128, 256, 512});
	out.clear();
	if(ctx->ALL()){
		for(auto u : uintScope)
			out.push_back(u);
	}
	else{
		uint32_t scopeLen = std::stoi(ctx->numberLiteral()->getText());
		if(std::find(uintScope.begin(), uintScope.end(), scopeLen) != uintScope.end())
			out.push_back(scopeLen);
	}
	return true;
}

bool PredaScriptRealListener::ResolveDeployArgsData(PredaScriptParser::ContractPropertiesContext* ctx, std::vector<uint8_t>& args)
{
	// Args data structure
	// | num of contracts | str length | Contract 1's filePath str | str length | Contract 1's jsonParams str | ... 
	//args.resize(ctx->getText().size() + sizeof(uint32_t) * ctx->contractProperty().size() * 2 + sizeof(uint32_t));
	uint32_t contractsNum = (uint32_t)ctx->contractProperty().size();
	if (!contractsNum) {
		_LOG("[PRD] Line " << GetLineNum() << ": Missing argments json.");
		return false;
	}
	args.resize(args.size() + sizeof(uint32_t));
	std::copy(&contractsNum, &contractsNum + 1, args.begin());
	for(auto prop : ctx->contractProperty())
	{
		std::string jsonParamStr = "";
		if (prop->jsonParameters() && !ResolveJsonParameters(prop->jsonParameters(), jsonParamStr)) {
			_LOG("[PRD] Line " << GetLineNum() << ": Invalid: deploy args");
			return false;
		}
		std::string filePath = prop->predaFile()? prop->predaFile()->getText() : prop->xtlFile()->getText();
		uint32_t predaFileLength = (uint32_t)filePath.length();
		uint32_t jsonLength = (uint32_t)jsonParamStr.length();
		size_t oldSize = args.size();
		size_t appendSize = sizeof(uint32_t) * 2 + predaFileLength + jsonLength;
		args.resize(oldSize + appendSize);
		auto it = args.begin() + oldSize;
		std::copy(&predaFileLength, &predaFileLength + 1, it);
		it += sizeof(uint32_t);
		std::copy(filePath.begin(), filePath.end(), it);
		it += predaFileLength;
		std::copy(&jsonLength, &jsonLength + 1, it);
		it += sizeof(uint32_t);
		if (jsonLength) {
			std::copy(jsonParamStr.begin(), jsonParamStr.end(), it);
		}
	}
	return true;
}

bool PredaScriptRealListener::ResolveModifyState(PredaScriptParser::ContractIdContext* contractIdCtx, PredaScriptParser::ScopeContext* scopeCtx, PredaScriptParser::JsonParametersContext* jsonCtx, bool isSettingWholeState)
{
	SimuState* pState = nullptr;
	rvm::Scope scope = rvm::Scope::Global;
	rvm::ContractInvokeId ciid;
	std::string dappContractName = contractIdCtx->cvid() ? contractIdCtx->cvid()->getText() : 
															(contractIdCtx->contractName()->dappName? contractIdCtx->contractName()->getText() : std::string(m_chsimu.m_attribute.DAPP_NAME.Begin()) + '.' + contractIdCtx->contractName()->getText());
	// shard
	if(scopeCtx && scopeCtx->shardScope()){
		if(!m_chsimu.ResolveCiid(dappContractName, rvm::Scope::Shard, ciid))
			return false;
		std::vector<uint32_t> shardIds;
		ResolveShardIdFromShardScope(scopeCtx->shardScope(), shardIds);
		for(auto shardId : shardIds)
		{
			std::string json;
			ResolveJsonParameters(jsonCtx, json);
			if(0 == m_chsimu.ComposeState(ciid, rt::String_Ref(json), pState, shardId, {nullptr, 0}, isSettingWholeState))
				m_chsimu.SetState(ciid, pState, shardId);
		}
	}
	// address
	else if(scopeCtx && scopeCtx->addressScope()){
		if(!m_chsimu.ResolveCiid(dappContractName, rvm::Scope::Address, ciid))
			return false;
		std::vector<std::pair<uint32_t, rvm::Address*>> shardIds;
		ResolveShardIdFromAddressScope(scopeCtx->addressScope(), shardIds);
		for(auto shardId : shardIds)
		{
			std::string json;
			ResolveJsonParameters(jsonCtx, json);
			if(0 == m_chsimu.ComposeState(ciid, rt::String_Ref(json), pState, shardId.first, ScopeKeyPOD(*shardId.second), isSettingWholeState))
				m_chsimu.SetState(ciid, pState, shardId.first, shardId.second);
		}
	}
	// global
	else
	{
		if(!m_chsimu.ResolveCiid(dappContractName, rvm::Scope::Global, ciid))
			return false;
		std::string json;
		ResolveJsonParameters(jsonCtx, json);
		if(0 == m_chsimu.ComposeState(ciid, rt::String_Ref(json), pState, rvm::GlobalShard, {nullptr, 0}, isSettingWholeState))
			m_chsimu.SetState(ciid, pState);
	}
	return true;
}

bool PredaScriptRealListener::ResolveIntExpression(PredaScriptParser::IntExpressionContext* ctx, std::string& out)
{
	out.clear();
	int left = 0, right = 0;
	if(2 == ctx->intExpression().size()){
		std::string lExpr, rExpr;
		ResolveIntExpression(ctx->intExpression(0), lExpr);
		ResolveIntExpression(ctx->intExpression(1), rExpr);
		left = std::stoi(lExpr);
		right = std::stoi(rExpr);
	}
	switch(ctx->type){
		case 0:
		// *
		out = std::to_string(left * right);
		break;
		case 1:
		// /
		if(0 != right)
			out = std::to_string(left / right);
		break;
		case 2:
		// +
		out = std::to_string(left + right);
		break;
		case 3:
		// -
		out = std::to_string(left - right);
		break;
		case 4:
		// intRandom
		return ResolveIntRandom(ctx->intRandom(), out);
		break;
		case 5:
		// numberLiteral
		out = ctx->numberLiteral()->getText();
		break;
		default:
		break;
	}
	return true;
}

bool PredaScriptRealListener::ResolveSuppliedTokens(PredaScriptParser::SuppliedTokensContext* ctx, std::string& out)
{
	if (!ctx || ctx->token().empty())
	{
		out = "";
		return true;
	}
	out += '(';
	for (PredaScriptParser::TokenContext* token_ctx : ctx->token())
	{
		if (token_ctx->intExpression())
		{
			std::string int_expr;
			if (!ResolveIntExpression(token_ctx->intExpression(), int_expr))
			{
				out = "";
				return false;
			}
			out += int_expr + token_ctx->identifier()->getText() + ',';
		}
		else if(token_ctx->numberLiteral())
			out += token_ctx->numberLiteral()->getText() + token_ctx->identifier()->getText() + ',';
	}
	out.back() = ')';
	return true;
}

bool PredaScriptRealListener::ResolveIntRandom(PredaScriptParser::IntRandomContext* ctx, std::string& out)
{
	if (!ctx->randomRange()) {
		_LOG("[PRD] Line " << GetLineNum() << ": Expecting argument list for function: 'random'");
		return false;
	}
	else {
		std::string min, max;
		ResolveIntExpression(ctx->randomRange()->min, min);
		ResolveIntExpression(ctx->randomRange()->max, max);
		ResolveInt64Random(std::stol(min), std::stol(max), out);
	}
	return true;
}

bool PredaScriptRealListener::ResolveAddressScope(PredaScriptParser::AddressScopeContext* ctx, std::string& out)
{
	out.clear();
	uint32_t userId = (uint32_t)m_users.size();
	if(ctx->numberLiteral())
	{
		userId = std::stoi(ctx->numberLiteral()->getText());
	}
	else if(ctx->RANDOM())
	{
		userId = GetRandomUint32(0, (uint32_t)m_users.size() - 1);
	}
	else if(ctx->ALL())
	{
		userId = m_currentUserId4ComposeTxn;
	}
	if (userId < m_users.size()) {
		rt::tos::Base32CrockfordLowercaseOnStack<> addrStr(&m_users[userId], sizeof(rvm::ConstAddress));
		out += addrStr.Begin();
	}
	else {
		_LOG("[PRD] Line " << GetLineNum() << ": Address index is out of range");
		return false;
	}
	return true;
}

bool PredaScriptRealListener::CheckIfAllUsers(PredaScriptParser::JsonParametersContext* ctx)
{
	for(auto jsonParam : ctx->jsonParameter())
	{
		if(jsonParam->jsonValue()->primaryValue() && CheckIfAllUsers(jsonParam->jsonValue()->primaryValue()))
			return true;
		else if(jsonParam->jsonValue()->jsonParameters() && CheckIfAllUsers(jsonParam->jsonValue()->jsonParameters()))
			return true;
	}
	return false;
}

bool PredaScriptRealListener::CheckIfAllUsers(PredaScriptParser::PrimaryValueContext* ctx)
{
	if(ctx->toBeAssignedValue() && ctx->toBeAssignedValue()->addressScope() && ctx->toBeAssignedValue()->addressScope()->ALL())
		return true;
	else if(ctx->concreteValue() && ctx->concreteValue()->stringLiteral() && ctx->concreteValue()->stringLiteral()->getText().find("@all") != std::string::npos)
		return true;
	else if(ctx->arrayValue()){
		for(auto jsonVar : ctx->arrayValue()->jsonValue()){
			if(jsonVar->jsonParameters() && CheckIfAllUsers(jsonVar->jsonParameters()))
				return true;
			else if(jsonVar->primaryValue() && CheckIfAllUsers(jsonVar->primaryValue()))
				return true;
		}
	}
	return false;
}

bool PredaScriptRealListener::ResolveStateJson(rvm::Scope scope, rt::String_Ref stateJson)
{
	rt::JsonObject obj(stateJson);
	rt::JsonArray stateArr(obj.GetValueRaw("States"));
	rt::String_Ref stateStr;
	rt::String cmdStr;
	rt::String_Ref target;
	while (stateArr.GetNextObject(stateStr))
	{
		rt::JsonObject stateObj(stateStr);
		bool CIDexist = false;
		rt::String_Ref CVIDStr = stateObj.GetValue("CVID");
		rvm::ContractInvokeId ciid;
		if (!m_chsimu.ResolveCiid(CVIDStr, scope, ciid))
			return false;
		SimuState* pState = nullptr;
		switch (scope)
		{
		case rvm::Scope::Shard:
		{
			rt::String_Ref shardIdStr = obj.GetValue("ShardIndex");
			if (shardIdStr == "#g") {
				m_chsimu.ResolveCiid(CVIDStr, rvm::Scope::Global, ciid);
				if (0 == m_chsimu.ComposeState(ciid, stateObj.GetValue("State"), pState, rvm::GlobalShard, { nullptr, 0 }, false))
					m_chsimu.SetState(ciid, pState);
			}
			else {
				uint32_t shardId = shardIdStr.TrimLeft(1).ToNumber<uint32_t>();
				if (shardId >= m_chsimu.GetShardCount()) {
					_LOG("[PRD] Line " << GetLineNum() << ": Invalid shardId: " << stateJson);
					return false;
				}

				if (0 == m_chsimu.ComposeState(ciid, stateObj.GetValue("State"), pState, shardId, { nullptr, 0 }, false))
					m_chsimu.SetState(ciid, pState, shardId);
			}
			break;
		}
			break;
		case rvm::Scope::Address:
		{
			bool exist = false;
			rt::String_Ref target = obj.GetValue("Address", exist);
			int userId = 0;
			if (!exist || (userId = AddNewUser(target)) < 0)
			{
				_LOG("[PRD] Line " << GetLineNum() << ": Invalid address state " << stateJson);
				return false;
			}
			const rvm::Address& addr = m_users[userId];
			uint32_t shardId = m_chsimu.GetShardIndex(addr);
			if (0 == m_chsimu.ComposeState(ciid, stateObj.GetValue("State"), pState, shardId, ScopeKeyPOD(addr), false))
				m_chsimu.SetState(ciid, pState, shardId, &addr);
		}
			break;
		default:
			break;
		}
	}
	return true;
}

bool PredaScriptRealListener::isScopeTargetCorresponded(rvm::Scope scope, PredaScriptParser::ScopeContext* tCtx)
{
	switch (scope) {
	case rvm::Scope::Global:
		if (nullptr == tCtx || (tCtx->shardScope() && "#g" == tCtx->shardScope()->getText()))
			return true;
		else
			_LOG("[PRD] Line " << GetLineNum() << ": Global target should be denoted with '#g' or none");
		break;
	case rvm::Scope::Shard:
		if (tCtx->shardScope())
			return isShardScopeCorrect(tCtx->shardScope());
		else
			_LOG("[PRD] Line " << GetLineNum() << ": Shard target should be denoted with '#'");
		break;
	case rvm::Scope::Address:
		if (tCtx->addressScope())
			return isAddressScopeCorrect(tCtx->addressScope());
		else
			_LOG("[PRD] Line " << GetLineNum() << ": Address target should be denoted with '@'");
		break;
	default:
		return false;
	}
	return false;
}

bool PredaScriptRealListener::isAddressScopeCorrect(PredaScriptParser::AddressScopeContext* ctx)
{
	if (ctx->numberLiteral()) {
		int userId = std::stoi(ctx->numberLiteral()->getText());
		if (userId < 0) {
			_LOG("[PRD] Line " << GetLineNum() << ": Target index must only contain digits");
		}
		else if (userId >= (int)m_users.size()) {
			_LOG("[PRD] Line " << GetLineNum() << ": Address index is out of range");
		}
		else
			return true;
	}
	else if (ctx->identifier()) {
		_LOG("[PRD] Line " << GetLineNum() << ": Target index must only contain digits");
	}
	else
		return true;
	return false;
}

bool PredaScriptRealListener::isShardScopeCorrect(PredaScriptParser::ShardScopeContext* ctx) 
{
	if (ctx->numberLiteral()) {
		int shardId = std::stoi(ctx->numberLiteral()->getText());
		if (shardId < 0) {
			_LOG("[PRD] Line " << GetLineNum() << ": Target index must only contain digits");
		}
		else if (shardId >= (int)m_chsimu.GetShardCount()) {
			_LOG("[PRD] Line " << GetLineNum() << ": Shard index is out of range");
		}
		else
			return true;
	}
	else if (ctx->identifier()) {
		_LOG("[PRD] Line " << GetLineNum() << ": Target index must only contain digits");
	}
	else
		return true;
	return false;
}

int PredaScriptRealListener::AddNewUser(rt::String_Ref userAddr)
{
	static std::map<rt::String, uint32_t> userAddr2Id;
	rvm::Address addr;
	if (!((oxd::SecureAddress*)&addr)->FromString(userAddr))
		return -1;
	auto it = userAddr2Id.find(userAddr);
	if (it != userAddr2Id.end())
		return (int)(it->second);
	else {
		auto ret = m_users.size();
		m_users.emplace_back(addr);
		userAddr2Id[userAddr] = (uint32_t)ret;
		return (int)ret;
	}
	return 0;
}

void PredaScriptRealListener::AttachSolFunctionName(const std::string& functionName, std::string& jsonParameters)
{
	jsonParameters = "{\"__sol__function__name__\": \"" + functionName + "\", \"args\":" + jsonParameters +  "}";
}

void PredaScriptRealListener::AttachSolFunctionScope(const std::string& scope, std::string& jsonParameters)
{
	jsonParameters.pop_back();
	if (jsonParameters.length() > 1)
		jsonParameters += ", ";
	jsonParameters += "\"_scope\": \"" + scope + "\"}";
}

}