#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <array>
#if defined(_WIN32)
	#include <windows.h>
#else
	#include <dlfcn.h>
#endif
#include "../transpiler.h"
#include "../transpiler/PredaCommon.h"

typedef transpiler::ITranspiler* (*FNCreateTranspilerInstance)(const char *options);
FNCreateTranspilerInstance CreateTranspilerInstance = nullptr;

struct CContractSymbolDatabase : public transpiler::IContractSymbolDatabase
{
	std::vector<transpiler::ITranspiler *> m_compiledContracts;

	virtual transpiler::IContractSymbols* GetContractSymbols(const char *contractFullName) const override
	{
		for (auto &contract : m_compiledContracts)
		{
			if (contract->GetDAppName() + std::string(".") + contract->GetContractName() == contractFullName)
				return contract;
		}

		return nullptr;
	}

	virtual bool ContractExists(const char *dAppName, const char *contractName) const override
	{
		return GetContractSymbols((std::string(dAppName) + "." + contractName).c_str()) != nullptr;
	}
};

CContractSymbolDatabase g_database;

bool CompileFile(const char *fileName, const char *dAppName, transpiler::ITranspiler **ppTranspiler)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		std::cout << "Cannot find source file " << fileName << std::endl;
		return false;
	}
	std::string sourceCode = std::string(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());

	transpiler::ITranspiler *pTranspiler = CreateTranspilerInstance(nullptr);
	*ppTranspiler = pTranspiler;

	if (!pTranspiler->BuildParseTree(sourceCode.c_str())
		|| !pTranspiler->Compile(dAppName, &g_database))
	{
		uint32_t numCompileErrors = pTranspiler->GetNumCompileErrors();
		std::cout << "Compile " << fileName << ": " << numCompileErrors << " errors." << std::endl;
		for (uint32_t i = 0; i < numCompileErrors; i++)
		{
			uint32_t line, pos;
			pTranspiler->GetCompileErrorPos(i, line, pos);
			std::cout << "Line " << line << ", pos " << pos << ": error " << uint32_t(pTranspiler->GetCompileErrorCode(i)) << ": " << pTranspiler->GetCompileErrorMsg(i) << std::endl;
		}
		return false;
	}

	return true;
}

int main(int argc, const char **argv)
{
#if defined(_WIN32)
	HMODULE hModule = ::LoadLibraryA("transpiler.dll");
	if (hModule == NULL)
	{
		printf("Cannot load transpiler.dll, GetLastError() returns %d\n", GetLastError());
		return 0;
	}
	CreateTranspilerInstance = (FNCreateTranspilerInstance)GetProcAddress(hModule, "CreateTranspilerInstance");
#elif defined(__linux__) || defined(__linux)
	void *dllHandleAntlr = ::dlopen("./libantlr4-runtime.so.4.9.3", RTLD_LOCAL|RTLD_NOW);
	if (dllHandleAntlr == nullptr)
	{
		printf("%s\n", dlerror());
		return 0;
	}
	void *dllHandleTranspiler = ::dlopen("./transpiler.so", RTLD_LOCAL|RTLD_NOW);
	if (dllHandleTranspiler == nullptr)
	{
		printf("%s\n", dlerror());
		return 0;
	}
	CreateTranspilerInstance = (FNCreateTranspilerInstance)::dlsym(dllHandleTranspiler, "CreateTranspilerInstance");
#elif defined(__APPLE__)
	void *dllHandleTranspiler = ::dlopen("./transpiler.dylib", RTLD_LOCAL|RTLD_NOW);
	if (dllHandleTranspiler == nullptr)
	{
		printf("%s\n", dlerror());
		return 0;
	}
	CreateTranspilerInstance = (FNCreateTranspilerInstance)::dlsym(dllHandleTranspiler, "CreateTranspilerInstance");
#endif

	std::string srcFile;
	if (argc > 2)
	{
		for (int i = 1; i < argc; i++)
		{
			srcFile = argv[i];
			transpiler::ITranspiler* pTranspiler = nullptr;
			std::cout << "Compiling " << srcFile << " ..." << std::endl;
			if (!CompileFile(srcFile.c_str(), "MyDApp", &pTranspiler))
			{
				std::cout << "Compile failed" << std::endl;
				return 0;
			}

			g_database.m_compiledContracts.push_back(pTranspiler);
		}
		std::cout << argc - 1 << " files successfully compiled" << std::endl;
		return 0;
	}
	else if (argc == 2)
	{
		srcFile = argv[1];
	}
	else
		std::cout << "pass source code file as command line argument" << std::endl;

	if (0)
	{
		transpiler::ITranspiler* pTranspiler = nullptr;

		if (CompileFile("../../transpiler/testcase/interfaceA.prd", "MyDApp", &pTranspiler))
		{
			//std::cout << pTranspiler->GetOutput();
			g_database.m_compiledContracts.push_back(pTranspiler);
			if (CompileFile("../../transpiler/testcase/interfaceB.prd", "MyDApp", &pTranspiler))
			{
				std::cout << pTranspiler->GetOutput();
				g_database.m_compiledContracts.push_back(pTranspiler);
				for (uint32_t i = 0; i < pTranspiler->GetNumExportedInterfaces(); i++)
				{
					std::cout << "interface " << pTranspiler->GetExportedInterfaceName(i) << "{" << std::endl;
					for (uint32_t j = 0; j < pTranspiler->GetNumExportedInterfaceFunctions(i); j++)
					{
						std::cout << "\t" << pTranspiler->GetExportedInterfaceFunctionReturnType(i, j) << " ";
						std::cout << pTranspiler->GetExportedInterfaceFunctionName(i, j) << "(";
						for (uint32_t k = 0; k < pTranspiler->GetExportedInterfaceFunctionNumParameters(i, j); k++)
						{
							if (k > 0)
								std::cout << ", ";
							std::cout << pTranspiler->GetExportedInterfaceFunctionParameterType(i, j, k) << " " << pTranspiler->GetExportedInterfaceFunctionParameterName(i, j, k);
						}
						std::cout << "); // flags: " << pTranspiler->GetExportedInterfaceFunctionFlag(i, j) << std::endl;
					}
					std::cout << "}" << std::endl;
				}
			}
		}

		return 0;
	}

	if (0)
	{
		transpiler::ITranspiler *pTranspiler = nullptr;

		if (CompileFile("../../transpiler/testcase/cross_call_A.prd", "MyDApp", &pTranspiler))
		{
			//std::cout << pTranspiler->GetOutput();
			g_database.m_compiledContracts.push_back(pTranspiler);
			if (CompileFile("../../transpiler/testcase/cross_call_B.prd", "MyDApp", &pTranspiler))
			{
				//std::cout << pTranspiler->GetOutput();
				g_database.m_compiledContracts.push_back(pTranspiler);
				if (CompileFile("../../transpiler/testcase/cross_call_C.prd", "MyDApp", &pTranspiler))
				{
					std::cout << pTranspiler->GetOutput();
					g_database.m_compiledContracts.push_back(pTranspiler);
				}
			}
		}

		return 0;
	}

	if (1)
	{
		transpiler::ITranspiler *pTranspiler = nullptr;
		if (srcFile == "")
		{
			std::string s;
			std::cin >> s;
			srcFile = std::string("../../transpiler/testcase/") + s + ".prd";
			//srcFile = "../../transpiler/testcase/basic.prd";
			//srcFile = "../../transpiler/testcase/test.prd";
			//srcFile = "../../transpiler/testcase/cross_call_A.prd";
			//srcFile = "../../transpiler/testcase/compile_error.prd";
			//srcFile = "../../transpiler/testcase/bigint.prd";
			//srcFile = "../../transpiler/testcase/literal.prd";
			//srcFile = "../../transpiler/testcase/token.prd";
			//srcFile = "../../transpiler/testcase/zombie.prd";
			//srcFile = "../../transpiler/testcase/debug_ctx.prd";
			std::cout << "defaulting to " << srcFile << std::endl;
		}
		if (CompileFile(srcFile.c_str(), "MyDApp", &pTranspiler))
 		{
 			std::cout << "Transcompiled code:" << std::endl << std::endl;
 			std::cout << pTranspiler->GetOutput();

 			std::cout << std::endl;
 			std::cout << "Exported functions: " << pTranspiler->GetNumExportedFunctions() << std::endl;
 			for (uint32_t i = 0; i < pTranspiler->GetNumExportedFunctions(); i++)
 			{
				std::cout << i;
				if (const char *p = pTranspiler->GetExportedFunctionReturnType(i); p[0] != 0)
					std::cout << " " << p;
				std::cout << " " << pTranspiler->GetExportedFunctionName(i) << "(";
 				for (uint32_t j = 0; j < pTranspiler->GetExportedFunctionNumParameters(i); j++)
 				{
 					if (j > 0)
 						std::cout << ", ";
 					std::cout << pTranspiler->GetExportedFunctionParameterType(i, j) << " " << pTranspiler->GetExportedFunctionParameterName(i, j);
 				}
 				{
 					std::string str;
 					uint32_t flags = pTranspiler->GetExportedFunctionFlag(i);

					uint32_t scope = flags & uint32_t(transpiler::ScopeType::Mask);
					if (scope >= 1 && scope <= 8)
					{
						static std::array<std::string, 8> scopeNames = { "global", "shard", "address", "uint16", "uint32", "uint64", "uint256", "uint512" };
						str += "@" + scopeNames[scope - 1];
					}
					else
 						assert(0);
 					flags &= ~uint32_t(transpiler::ScopeType::Mask);

 #define PARSE_FLAG(x)\
 	if (flags & uint32_t(transpiler::FunctionFlags::x))\
 	{\
 		str += " | "#x;\
 		flags &= ~uint32_t(transpiler::FunctionFlags::x);\
 	}
 					PARSE_FLAG(CallableFromTransaction);
 					PARSE_FLAG(CallableFromRelay);
 					PARSE_FLAG(CallableFromOtherContract);
 					PARSE_FLAG(CallableFromSystem);
 					PARSE_FLAG(IsConst);
 					PARSE_FLAG(HasRelayScopeStatement);
					PARSE_FLAG(HasRelayShardsStatement);
					PARSE_FLAG(HasRelayGlobalStatement);
					PARSE_FLAG(GlobalStateDependency);

 					if (flags != 0)
 					{
 						char s[100];
 #if defined(_WIN32)
 						sprintf_s(s, "0x%x | ", flags);
 #else
 						sprintf(s, "0x%x | ", flags);
 #endif
 						str = s + str;
 					}

 					std::cout << "); // " << str << std::endl;
 				}
 			}
			std::cout << "global_deploy_function: " << pTranspiler->GetGlobalDeployFunctionExportIndex() << std::endl;
			std::cout << "shard_scale_out_function: " << pTranspiler->GetShardScaleoutFunctionExportIndex() << std::endl;

 			std::cout << std::endl;
			std::array<transpiler::ScopeType, 10> scopes = { transpiler::ScopeType::Global,transpiler::ScopeType::Shard,transpiler::ScopeType::Address, transpiler::ScopeType::Uint32,
				transpiler::ScopeType::Uint64, transpiler::ScopeType::Uint96, transpiler::ScopeType::Uint128, transpiler::ScopeType::Uint160, transpiler::ScopeType::Uint256, transpiler::ScopeType::Uint512 };
			std::array<std::string, 10> scopeNames = { "global", "shard", "address", "uint32", "uint64", "uint96", "uint128", "uint160", "uint256", "uint512" };
			static_assert(scopeNames.size() == scopes.size());
			for (int i = 0; i < (int)scopes.size(); i++)
			{
				if (pTranspiler->GetNumScopeStateVariable(scopes[i]) > 0)
				{
					std::cout << scopeNames[i] << " var : " << pTranspiler->GetScopeStateVariableSignature(scopes[i]) << std::endl;
					bool hasAsset = pTranspiler->ScopeStateVariableHasAsset(scopes[i]);
					bool hasBlob = pTranspiler->ScopeStateVariableHasBlob(scopes[i]);
					if (hasAsset || hasBlob)
						std::cout << scopeNames[i] << " var has asset and blob : " << hasAsset << " " << hasBlob << std::endl;
				}
			}

 			std::cout << std::endl;
 			for (uint32_t i = 0; i < pTranspiler->GetNumEnumTypes(); i++)
 			{
 				std::cout << pTranspiler->GetEnumTypeName(i) << ":";
 				for (uint32_t j = 0; j < pTranspiler->GetNumEnumerators(i); j++)
 					std::cout << " " << pTranspiler->GetEnumerator(i, j);
 				std::cout << std::endl;
 			}
 			std::cout << std::endl;
 			for (uint32_t i = 0; i < pTranspiler->GetNumStructTypes(); i++)
 			{
 				std::cout << pTranspiler->GetStructTypeName(i) << std::endl;
 				for (uint32_t j = 0; j < pTranspiler->GetNumStructMembers(i); j++)
 					std::cout << "\t" << pTranspiler->GetStructMemberType(i, j) << " " << pTranspiler->GetStructMemberName(i, j) << std::endl;
 			}
 		}

		if (pTranspiler)
			pTranspiler->Release();
	}
	return 0;
}
