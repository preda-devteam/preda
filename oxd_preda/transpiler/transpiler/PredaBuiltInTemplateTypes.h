 #pragma once

#include "BaseTranspiler.h"
#include "PredaTranspiler.h"

namespace transpiler {

	// Built-in array template type
	struct BuiltInArrayType : public TemplateType
	{
		BuiltInArrayType(PredaTranspilerContext *inTranspilerContext, std::string arrayTypeName);

		virtual ConcreteTypePtr InstantiateTemplate(const std::vector<ConcreteTypePtr> &templateParams);

		// Unique instance of type definition
		static std::shared_ptr<BuiltInArrayType> CreateType(PredaTranspilerContext *inTranspilerContext, std::string arrayTypeName);

		PredaTranspilerContext *pTranspilerContext = nullptr;
	};

	// Built-in map template type
	struct BuiltInMapType : public TemplateType
	{
		BuiltInMapType(PredaTranspilerContext *inTranspilerContext, std::string mapTypeName);

		virtual ConcreteTypePtr InstantiateTemplate(const std::vector<ConcreteTypePtr> &templateParams);

		// Unique instance of type definition
		static std::shared_ptr<BuiltInMapType> CreateType(PredaTranspilerContext *inTranspilerContext, std::string mapTypeName);

		PredaTranspilerContext *pTranspilerContext = nullptr;
	};
}
