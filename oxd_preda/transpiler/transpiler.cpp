// sol2cpp.cpp : Defines the entry point for the console application.
//

#include <fstream>
#include <sstream>

#include "antlr4-runtime.h"

#include "PredaRealListener.h"
#include "transpiler.h"

//static void f(transpiler::ConcreteTypePtr tmp, int level)
//{
//	for (int i = 0; i < level; i++)
//		std::cout << "\t";
//	std::cout << int(tmp->typeCategory) << " " << tmp->inputName << std::endl;
//	for (auto &itor : tmp->innerConcreteTypes)
//		f(itor.second, level + 1);
//}

class CTranspiler : public transpiler::ITranspiler {
private:
	PredaRealListener m_listener;
	PredaPreCompileListener m_preListener;
	std::string m_outputCode;
	std::string m_sourceCodeStr;
	antlr4::ANTLRInputStream m_inputStream;
	PredaLexer m_lexer;
	antlr4::CommonTokenStream m_tokenStream;
	PredaParser m_parser;
	antlr4::tree::ParseTree *m_pParseTree;
	transpiler::PredaTranspilerOptions m_options;
public:
	CTranspiler(const char *options = nullptr)
		: m_lexer(&m_inputStream)
		, m_tokenStream(&m_lexer)
		, m_parser(&m_tokenStream)
		, m_pParseTree(nullptr)
	{
		if (options)
		{
			std::istringstream iss(options);
			std::string option;
			while (iss >> option)
			{
				if (option == "disabledebugprint")
					m_options.bDisableDebugPrint = true;
			}
		}
		m_listener.SetOptions(&m_options);

		m_lexer.removeErrorListeners();
		m_lexer.addErrorListener(&m_listener);
		m_parser.removeErrorListeners();
		m_parser.addErrorListener(&m_listener);
	}
	
	virtual ~CTranspiler()
	{
	}
	
	const char* GetVersion() override
	{
		return "0.0.1";
	}
	virtual void Release() override
	{
		delete this;
	}
	virtual bool BuildParseTree(const char *sourceCode) override
	{
		m_sourceCodeStr = std::string(sourceCode);
		m_inputStream.load(m_sourceCodeStr);
		m_pParseTree = m_parser.predaSource();
		if (m_listener.m_errorPortal.m_errors.size() > 0)
		{
			return false;
		}
		return true;
	}
	virtual bool PreCompile(const char *dAppName) override
	{
		if (m_pParseTree == nullptr)
			return false;

		PredaParseTreeWalker walker;
		m_preListener.SetContractDAppNameId(dAppName);
		walker.walk(&m_preListener, m_pParseTree);

		return true;
	}
	virtual bool Compile(const char *dAppName, transpiler::IContractSymbolDatabase *pContractSymbolDatabase) override
	{
		if (dAppName == nullptr)
			return false;
		if (m_pParseTree == nullptr)
			return false;

		PredaParseTreeWalker walker;

		m_listener.SetContractDAppNameId(dAppName);
		m_listener.SetWalker(&walker);
		m_listener.SetContractSymbolDatabase(pContractSymbolDatabase);

		walker.walk(&m_listener, m_pParseTree);

		if (m_listener.m_errorPortal.m_errors.size() != 0)
			return false;

		m_outputCode = m_listener.codeSerializer.GetCode();

		//f(m_listener.m_transpilerCtx.globalType, 0);
		
		return true;
	}
	virtual uint32_t GetNumCompileErrors() const override
	{
		return uint32_t(m_listener.m_errorPortal.m_errors.size());
	}
	virtual const char* GetCompileErrorMsg(uint32_t errorIdx) const override
	{
		if (errorIdx >= (uint32_t)m_listener.m_errorPortal.m_errors.size())
			return nullptr;
		return m_listener.m_errorPortal.m_errors[errorIdx].message.c_str();
	}
	virtual void GetCompileErrorPos(uint32_t errorIdx, uint32_t &line, uint32_t &pos) const override
	{
		if (errorIdx >= (uint32_t)m_listener.m_errorPortal.m_errors.size())
			return;
		line = m_listener.m_errorPortal.m_errors[errorIdx].line;
		pos = m_listener.m_errorPortal.m_errors[errorIdx].pos;
	}
	virtual transpiler::ErrorCode GetCompileErrorCode(uint32_t errorIdx) const override
	{
		if (errorIdx >= (uint32_t)m_listener.m_errorPortal.m_errors.size())
			return transpiler::ErrorCode::NoError;
		return m_listener.m_errorPortal.m_errors[errorIdx].code;
	}
	virtual uint32_t GetNumCompileWarnings() const override
	{
		return uint32_t(m_listener.m_errorPortal.m_warnings.size());
	}
	virtual const char* GetCompileWarningMsg(uint32_t warningIdx) const override
	{
		if (warningIdx >= (uint32_t)m_listener.m_errorPortal.m_warnings.size())
			return nullptr;
		return m_listener.m_errorPortal.m_warnings[warningIdx].message.c_str();
	}
	virtual void GetCompileWarningPos(uint32_t warningIdx, uint32_t &line, uint32_t &pos) const override
	{
		if (warningIdx >= (uint32_t)m_listener.m_errorPortal.m_warnings.size())
			return;
		line = m_listener.m_errorPortal.m_warnings[warningIdx].line;
		pos = m_listener.m_errorPortal.m_warnings[warningIdx].pos;
	}
	virtual const char* GetOutput() const override
	{
		return m_outputCode.c_str();
	}

	virtual const char* GetDAppName() const override
	{
		//has two options because batchCompiler does not call build trees and pre compile, thus wont have pre listener.
		//and pre processing needs Dapp name and contract before m_listener is built
		if(m_preListener.m_currentContractName.empty()){
			return m_listener.m_currentDAppName.c_str();
		}
		return m_preListener.m_currentDAppName.c_str();
	}
	virtual const char* GetContractName() const override
	{
		if(m_preListener.m_currentContractName.empty()){
			return m_listener.m_currentContractName.c_str();
		}
		return m_preListener.m_currentContractName.c_str();
	}
	virtual const char* GetContractComment() const override
	{
		return  m_listener.m_currentDoxygenComment.c_str();
	}
	virtual const char* GetContractExportUniqueIdentifierString() const override
	{
		return m_listener.m_currentContractUniqueIdentifierStr.c_str();
	}
	virtual uint32_t GetNumImportedContracts() const override
	{
		return uint32_t(m_listener.m_importedContracts.size());
	}
	virtual const char* GetImportedContractFullName(uint32_t contractIdx) const override
	{
		if (contractIdx >= uint32_t(m_listener.m_importedContracts.size()))
			return nullptr;
		return m_listener.m_importedContracts[contractIdx].c_str();
	}

	// functions
	virtual uint32_t GetNumExportedFunctions() const override
	{
		return uint32_t(m_listener.m_exportedFunctionsMeta.size());
	}
	virtual const char* GetExportedFunctionName(uint32_t functionIdx) const override
	{
		if (functionIdx >= uint32_t(m_listener.m_exportedFunctionsMeta.size()))
			return nullptr;
		return m_listener.m_exportedFunctionsMeta[functionIdx].name.c_str();
	}
	virtual const char* GetExportedFunctionComment(uint32_t functionIdx) const override
	{
		if (functionIdx >= uint32_t(m_listener.m_exportedFunctionsMeta.size()))
			return nullptr;
		return m_listener.m_exportedFunctionsMeta[functionIdx].doxygenComment.c_str();
	}
	virtual uint32_t GetExportedFunctionFlag(uint32_t functionIdx) const override
	{
		if (functionIdx >= uint32_t(m_listener.m_exportedFunctionsMeta.size()))
			return 0;
		return m_listener.m_exportedFunctionsMeta[functionIdx].flags;
	}
	virtual const char* GetExportedFunctionReturnType(uint32_t functionIdx) const override
	{
		if (functionIdx >= uint32_t(m_listener.m_exportedFunctionsMeta.size()))
			return nullptr;
		return m_listener.m_exportedFunctionsMeta[functionIdx].returnType.c_str();
	}
	virtual const char* GetExportedFunctionParameterType(uint32_t functionIdx, uint32_t paramIdx) const override
	{
		if (functionIdx >= uint32_t(m_listener.m_exportedFunctionsMeta.size()))
			return nullptr;
		if (paramIdx >= uint32_t(m_listener.m_exportedFunctionsMeta[functionIdx].parameterType.size()))
			return nullptr;
		return m_listener.m_exportedFunctionsMeta[functionIdx].parameterType[paramIdx].c_str();
	}
	virtual const char* GetExportedFunctionParameterName(uint32_t functionIdx, uint32_t paramIdx) const override
	{
		if (functionIdx >= uint32_t(m_listener.m_exportedFunctionsMeta.size()))
			return nullptr;
		if (paramIdx >= uint32_t(m_listener.m_exportedFunctionsMeta[functionIdx].parameterName.size()))
			return nullptr;
		return m_listener.m_exportedFunctionsMeta[functionIdx].parameterName[paramIdx].c_str();
	}
	virtual uint32_t GetExportedFunctionNumParameters(uint32_t functionIdx) const override
	{
		if (functionIdx >= uint32_t(m_listener.m_exportedFunctionsMeta.size()))
			return 0;
		return uint32_t(m_listener.m_exportedFunctionsMeta[functionIdx].parameterType.size());
	}

	virtual int32_t GetGlobalDeployFunctionExportIndex() const override
	{
		return m_listener.m_globalDeployFunctionExportIdx;
	}
	virtual int32_t GetShardScaleoutFunctionExportIndex() const override
	{
		return m_listener.m_shardScaleOutFunctionExportIdx;
	}

	// interfaces
	virtual uint32_t GetNumExportedInterfaces() const override
	{
		return uint32_t(m_listener.m_exportedInterface.size());
	}
	virtual const char* GetExportedInterfaceName(uint32_t interfaceIdx) const override
	{
		return m_listener.m_exportedInterface[interfaceIdx].name.c_str();
	}

	virtual uint32_t GetNumExportedInterfaceFunctions(uint32_t interfaceIdx) const override
	{
		return uint32_t(m_listener.m_exportedInterface[interfaceIdx].functions.size());
	}
	virtual const char* GetExportedInterfaceFunctionName(uint32_t interfaceIdx, uint32_t functionIdx) const override
	{
		return m_listener.m_exportedInterface[interfaceIdx].functions[functionIdx].name.c_str();
	}
	virtual const char* GetExportedInterfaceFunctionComment(uint32_t interfaceIdx, uint32_t functionIdx) const override
	{
		return m_listener.m_exportedInterface[interfaceIdx].functions[functionIdx].doxygenComment.c_str();
	}
	virtual uint32_t GetExportedInterfaceFunctionFlag(uint32_t interfaceIdx, uint32_t functionIdx) const override
	{
		return m_listener.m_exportedInterface[interfaceIdx].functions[functionIdx].flags;
	}
	virtual const char* GetExportedInterfaceFunctionReturnType(uint32_t interfaceIdx, uint32_t functionIdx) const override
	{
		return m_listener.m_exportedInterface[interfaceIdx].functions[functionIdx].returnType.c_str();
	}
	virtual const char* GetExportedInterfaceFunctionParameterType(uint32_t interfaceIdx, uint32_t functionIdx, uint32_t paramIdx) const override
	{
		return m_listener.m_exportedInterface[interfaceIdx].functions[functionIdx].parameterType[paramIdx].c_str();
	}
	virtual const char* GetExportedInterfaceFunctionParameterName(uint32_t interfaceIdx, uint32_t functionIdx, uint32_t paramIdx) const override
	{
		return m_listener.m_exportedInterface[interfaceIdx].functions[functionIdx].parameterName[paramIdx].c_str();
	}
	virtual uint32_t GetExportedInterfaceFunctionNumParameters(uint32_t interfaceIdx, uint32_t functionIdx) const override
	{
		return uint32_t(m_listener.m_exportedInterface[interfaceIdx].functions[functionIdx].parameterType.size());
	}

	// implemented interfaces
	virtual uint32_t GetNumImplementedInterfaces() const override
	{
		return uint32_t(m_listener.m_implementedInterfaces.size());
	}
	virtual const char* GetImplementedInterfaceName(uint32_t interfaceIdx) const override
	{
		return m_listener.m_implementedInterfaces[interfaceIdx].fullName.c_str();
	}
	virtual uint32_t GetNumImplementedInterfaceFunctions(uint32_t interfaceIdx) const override
	{
		return uint32_t(m_listener.m_implementedInterfaces[interfaceIdx].functionIds.size());
	}
	virtual int32_t GetImplementedInterfaceFunctionExportIndex(uint32_t interfaceIdx, uint32_t functionIdx) const override
	{
		if (functionIdx >= uint32_t(m_listener.m_implementedInterfaces[interfaceIdx].functionIds.size()))
			return -1;
		return int32_t(m_listener.m_implementedInterfaces[interfaceIdx].functionIds[functionIdx]);
	}

	virtual const char* GetScopeStateVariableSignature(transpiler::ScopeType scope) const override
	{
		return m_listener.m_stateVariableSignature[uint8_t(scope)].c_str();
	}
	virtual uint32_t GetNumScopeStateVariable(transpiler::ScopeType scope) const override
	{
		return (uint32_t)m_listener.m_stateVariableDoxygenComment[uint8_t(scope)].size();
	}
	virtual const char* GetScopeStateVariableComment(transpiler::ScopeType scope, uint32_t varIdx) const override
	{
		return m_listener.m_stateVariableDoxygenComment[uint8_t(scope)].at(varIdx).c_str();
	}
	virtual bool ScopeStateVariableHasAsset(transpiler::ScopeType scope) const override
	{
		return m_listener.m_stateVariableHasAsset[uint8_t(scope)];
	}
	virtual bool ScopeStateVariableHasBlob(transpiler::ScopeType scope) const override
	{
		return m_listener.m_stateVariableHasBlob[uint8_t(scope)];
	}

	virtual uint32_t GetNumEnumTypes() const override
	{
		return (uint32_t)m_listener.m_exportedEnums.size();
	}
	virtual const char* GetEnumDoxygenComment(uint32_t enumTypeIdx) const override
	{
		return m_listener.m_exportedEnums[enumTypeIdx].doxygenComment.c_str();
	}
	virtual const char* GetEnumTypeName(uint32_t enumTypeIdx) const override
	{
		if (enumTypeIdx >= (uint32_t)m_listener.m_exportedEnums.size())
			return nullptr;
		return m_listener.m_exportedEnums[enumTypeIdx].name.c_str();
	}
	virtual uint32_t GetNumEnumerators(uint32_t enumTypeIdx) const override
	{
		if (enumTypeIdx >= (uint32_t)m_listener.m_exportedEnums.size())
			return 0;
		return uint32_t((m_listener.m_exportedEnums[enumTypeIdx]).enumerators.size());
	}
	virtual const char* GetEnumerator(uint32_t enumTypeIdx, uint32_t enumeratorIdx) const override
	{
		if (enumTypeIdx >= (uint32_t)m_listener.m_exportedEnums.size())
			return nullptr;
		if (enumeratorIdx >= uint32_t(m_listener.m_exportedEnums[enumTypeIdx].enumerators.size()))
			return nullptr;
		return m_listener.m_exportedEnums[enumTypeIdx].enumerators[enumeratorIdx].c_str();
	}

	virtual uint32_t GetNumStructTypes() const override
	{
		return uint32_t(m_listener.m_exportedStructs.size());
	}
	virtual const char* GetStructTypeName(uint32_t structTypeIdx) const override
	{
		if (structTypeIdx >= uint32_t(m_listener.m_exportedStructs.size()))
			return nullptr;
		return m_listener.m_exportedStructs[structTypeIdx].name.c_str();
	}
	virtual const char* GetStructDoxygenComment(uint32_t structTypeIdx) const override
	{
		if (structTypeIdx >= uint32_t(m_listener.m_exportedStructs.size()))
			return nullptr;
		return m_listener.m_exportedStructs[structTypeIdx].doxygenComment.c_str();
	}
	virtual uint32_t GetNumStructMembers(uint32_t structTypeIdx) const override
	{
		if (structTypeIdx >= uint32_t(m_listener.m_exportedStructs.size()))
			return 0;
		return uint32_t(m_listener.m_exportedStructs[structTypeIdx].members.size());
	}
	virtual const char* GetStructMemberType(uint32_t structTypeIdx, uint32_t memberIdx) const override
	{
		if (structTypeIdx >= uint32_t(m_listener.m_exportedStructs.size()))
			return nullptr;
		if (memberIdx >= uint32_t(m_listener.m_exportedStructs[structTypeIdx].members.size()))
			return nullptr;
		return m_listener.m_exportedStructs[structTypeIdx].members[memberIdx].first.c_str();
	}
	virtual const char* GetStructMemberName(uint32_t structTypeIdx, uint32_t memberIdx) const override
	{
		if (structTypeIdx >= uint32_t(m_listener.m_exportedStructs.size()))
			return nullptr;
		if (memberIdx >= uint32_t(m_listener.m_exportedStructs[structTypeIdx].members.size()))
			return nullptr;
		return m_listener.m_exportedStructs[structTypeIdx].members[memberIdx].second.c_str();
	}

	virtual uint32_t GetNumDirectDependentContracts() const override
	{
		return (uint32_t)m_preListener.m_dependentContracts.size();
	}
	virtual const char* GetDirectDependentContractName(uint32_t contractIdx) const override
	{
		return m_preListener.m_dependentContracts[contractIdx].c_str();
	}
};

extern "C"{
#if	defined(__linux__) || defined(__linux) || defined(__APPLE__)
	__attribute__((visibility("default"))) transpiler::ITranspiler* CreateTranspilerInstance(const char *options)
#elif defined(_WIN32)
	__declspec(dllexport) transpiler::ITranspiler* CreateTranspilerInstance(const char *options)
#endif
	{
		return new CTranspiler(options);
	}
}
