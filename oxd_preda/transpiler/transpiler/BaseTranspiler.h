#pragma once

#include <vector>
#include <string>
#include <map>
#include <cassert>

#include "Allocator.h"
#include "ConcreteType.h"
#include "TemplateType.h"

namespace transpiler {

	struct ThisPtrStack {
		struct ThisPtrStackItem {
			ConcreteTypePtr thisType;
			bool bIsConstPtr;
		};

		std::vector<ThisPtrStackItem> stack;

		void Push(ConcreteTypePtr thisType, bool isConst);
		void Pop();
	};

	struct FunctionRef
	{
		transpiler::DefinedIdentifierPtr functionIdentifier;
		size_t overloadIndex;
		
		const transpiler::FunctionSignature* GetSignature() const
		{
			if (functionIdentifier == nullptr || functionIdentifier->qualifiedType.baseConcreteType == nullptr)
				return nullptr;

			return &functionIdentifier->qualifiedType.baseConcreteType->vOverloadedFunctions[overloadIndex];
		}
		transpiler::FunctionSignature* GetSignature()
		{
			if (functionIdentifier == nullptr || functionIdentifier->qualifiedType.baseConcreteType == nullptr)
				return nullptr;

			return &functionIdentifier->qualifiedType.baseConcreteType->vOverloadedFunctions[overloadIndex];
		}

		bool operator == (const FunctionRef& rhs) const
		{
			return functionIdentifier == rhs.functionIdentifier && overloadIndex == rhs.overloadIndex;
		}
	};

	// currently this doesn't support nested function definition. e.g. function local structs with member functions.
	struct FunctionContext {
		struct LocalScope
		{
			enum ScopeType {
				Scope_Function,
				Scope_For,
				Scope_If,
				Scope_Else,
				Scope_ElseIf,
				Scope_While,
				Scope_DoWhile,
				Scope_UserBlock
			};
			ConcreteTypePtr concreteType;
			ScopeType scopeType;

			LocalScope(ScopeType inType, ConcreteTypePtr inConcreteType);
		};

		std::vector<LocalScope> localScopes;				// The local scopes of the current function, should be empty if currently outside a function
		FunctionRef functionRef;

		FunctionContext();

		void PushFunctionScope(ConcreteTypePtr type);
		void PushAddtionalLocalScope(LocalScope::ScopeType scopeType, const char *debugName);
		void PopScope();

		bool IsInsideFunction();
		FunctionSignature* GetFunctionSignature();

		bool IsInsideLoopBlock();
		bool IsInsideBranchBlock();
	};

	struct BaseTranspilerContext {
		ThisPtrStack thisPtrStack;					// The stack of this pointers
		FunctionContext functionCtx;				// the context of the current function
		ConcreteTypePtr globalType;					// type for the global namespace

		BaseTranspilerContext();
	};

}
