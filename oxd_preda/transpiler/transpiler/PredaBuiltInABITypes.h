#pragma once

#include "BaseTranspiler.h"
#include "PredaTranspiler.h"

namespace transpiler {

	// Built-in block struct
	struct BuiltInBlockStructType : public ConcreteType {
		BuiltInBlockStructType(PredaTranspilerContext *inTranspilerContext);
		void Init();
		static std::shared_ptr<BuiltInBlockStructType> CreateType(PredaTranspilerContext *inTranspilerContext);

		PredaTranspilerContext *pTranspilerContext = nullptr;
	};

	// Built-in transaction struct
	struct BuiltInTransactionStructType : public ConcreteType {
		BuiltInTransactionStructType(PredaTranspilerContext *inTranspilerContext);
		void Init();
		static std::shared_ptr<BuiltInTransactionStructType> CreateType(PredaTranspilerContext *inTranspilerContext);

		PredaTranspilerContext *pTranspilerContext = nullptr;
	};

	// Built-in event struct
	struct BuiltInEventStructType : public ConcreteType {
		BuiltInEventStructType(PredaTranspilerContext *inTranspilerContext);
		void Init();
		static std::shared_ptr<BuiltInEventStructType> CreateType(PredaTranspilerContext *inTranspilerContext);

		PredaTranspilerContext *pTranspilerContext = nullptr;
	};

	// Built-in debug struct
	struct BuiltInDebugStructType : public ConcreteType {
		BuiltInDebugStructType(PredaTranspilerContext *inTranspilerContext);
		void Init();
		static std::shared_ptr<BuiltInDebugStructType> CreateType(PredaTranspilerContext *inTranspilerContext);

		PredaTranspilerContext *pTranspilerContext = nullptr;
	};
}
