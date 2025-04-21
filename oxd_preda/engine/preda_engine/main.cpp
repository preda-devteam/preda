#include <memory>
#include "ContractDatabase.h"
#ifdef ENABLE_EVM
#include "../evm_engine/EVMContractDataBase.h"
#endif

extern "C" {
#if	defined(__linux__) || defined(__linux) || defined(__APPLE__)
	__attribute__((visibility("default"))) rvm::RvmEngine* CreateEngine(const char* config)
#elif defined(_WIN32)
	__declspec(dllexport) rvm::RvmEngine* CreateEngine(const char *config)
#endif
	{
		if (config == std::string("-wasm"))
			return new CContractDatabase(RuntimeMode::CWASM);
		else if (config == std::string("-native"))
			return new CContractDatabase(RuntimeMode::NATIVE);
#ifdef ENABLE_EVM
		else if (config == std::string("-evm"))
			return new xtl::ContractDatabase();
#endif
		else
			return nullptr;
	}
}

#if defined(_WIN32)
BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,  // handle to DLL module
	DWORD fdwReason,     // reason for calling function
	LPVOID lpReserved)  // reserved
{
	// Perform actions based on the reason for calling.
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		//printf("DLL_PROCESS_ATTACH\n");
		// Initialize once for each new process.
		// Return FALSE to fail DLL load.
		break;

	case DLL_THREAD_ATTACH:
		//printf("DLL_THREAD_ATTACH %u\n", GetCurrentThreadId());
		// Do thread-specific initialization.
		break;

	case DLL_THREAD_DETACH:
		//printf("DLL_THREAD_DETACH %u\n", GetCurrentThreadId());
		// Do thread-specific cleanup.
		break;

	case DLL_PROCESS_DETACH:
		//printf("DLL_PROCESS_DETACH\n");
		// Perform any necessary cleanup.
		break;
	}
	return TRUE;  // Successful DLL_PROCESS_ATTACH.
}
#endif