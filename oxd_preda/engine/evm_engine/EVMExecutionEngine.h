#pragma once
#ifdef ENABLE_EVM
#include "../../native/abi/vm_interfaces.h"
#include "EVMContractData.h"
#ifdef _WIN32
	#pragma warning(push)
	#pragma warning(disable:4068 4819)
#endif
#include <evmc/evmc.hpp>
#ifdef _WIN32
	#pragma warning(pop)
#endif

namespace preda_evm {
	class ContractDatabase;

	class EVMHost;

	enum class ExecutionResult : uint8_t {
		NoError = 0,
		ContractNotFound = 1,
		InvalidFunctionId = 2,
		FunctionSignatureMismatch = 3,
		ExecutionError = 4,
		//ContractStateExceedsSizeLimit			= 5,
		//SerializeOutContractStateError		= 6,
		SystemErrorBegin = 128,
		CannotLoadLibrary = 128,
		CannotCreateContractInstance = 129,
		MapContractStateError = 130,
	};

	class EVMExecutionEngine : public rvm::ExecuteUnit
	{
	private:
		evmc::VM m_vm;
		ContractDatabase* m_pDB;
		static constexpr unsigned int CREATE_STORE_GAS = 1;
		static constexpr unsigned int GAS_PRICE = 1;
	public:
		ContractDatabase* contractDatabase() const {
			return m_pDB;
		}

		evmc::Result RunCreate(
			EVMHost& host,
			const evmc_message& msg
		);
		evmc::Result Run(
			EVMHost &host,
			const evmc_message &msg
		);

		EVMExecutionEngine(ContractDatabase* pDB);
		virtual ~EVMExecutionEngine() {}

		virtual rvm::InvokeResult Invoke(rvm::ExecutionContext* executionContext, uint32_t gas_limit, const rvm::ContractModuleID *contract_deployment_id, rvm::OpCode opCode, const rvm::ConstData* args_serialized) override;
		virtual rvm::InvokeResult Deploy(rvm::ExecutionContext* exec, uint32_t gas_limit, rvm::CompiledModules* linked, const rvm::ConstData* deploy_args, rvm::ContractModuleID* contract_deployment_ids, rvm::InterfaceModuleID** interface_deployment_ids, rvm::LogMessageOutput* log_msg_output) override;

		virtual void Release() override;
		virtual void GetExceptionMessage(uint16_t except, rvm::StringStream* str) const override;
	private:
			bool ParseSolArgument(const rt::JsonObject& args_json, const ContractCompileData& compileData, uint64_t& value, std::string& data, rvm::OpCode opCode) const;
	};
}
#endif