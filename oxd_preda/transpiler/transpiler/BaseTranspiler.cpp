#include <assert.h>

#include "BaseTranspiler.h"

namespace transpiler {

	void ThisPtrStack::Push(ConcreteTypePtr thisType, bool isConst)
	{
		ThisPtrStackItem newItem;
		newItem.thisType = thisType;
		newItem.bIsConstPtr = isConst;
		stack.push_back(newItem);
	}

	void ThisPtrStack::Pop()
	{
		assert(stack.size() > 0);
		stack.pop_back();
	}

	FunctionContext::LocalScope::LocalScope(ScopeType inType, ConcreteTypePtr inConcreteType)
	{
		scopeType = inType;
		concreteType = inConcreteType;
	}

	FunctionContext::FunctionContext()
	{
	}

	bool FunctionContext::IsInsideFunction()
	{
		return localScopes.size() > 0;
	}

	void FunctionContext::PushFunctionScope(ConcreteTypePtr type)
	{
		assert(localScopes.size() == 0);
		localScopes.emplace_back(LocalScope::Scope_Function, type);
	}

	void FunctionContext::PushAddtionalLocalScope(LocalScope::ScopeType scopeType, const char *debugName)
	{
		assert(localScopes.size() > 0);
		if (localScopes.size() == 0)
			return;

		ConcreteTypePtr type = localScopes.back().concreteType->CreateInnerUnnamedScopeType(debugName);
		localScopes.emplace_back(scopeType, type);
	}

	void FunctionContext::PopScope()
	{
		assert(localScopes.size() > 0);
		if (localScopes.size() > 0)
			localScopes.pop_back();

		if (localScopes.size() == 0)
		{
			functionRef.functionIdentifier = nullptr;
			functionRef.overloadIndex = 0;
		}
	}

	FunctionSignature* FunctionContext::GetFunctionSignature()
	{
		return functionRef.GetSignature();
	}

	bool FunctionContext::IsInsideLoopBlock()
	{
		for (int i = (int)localScopes.size() - 1; i >= 0; i--)
		{
			LocalScope::ScopeType scopeType = localScopes[i].scopeType;
			if (scopeType == LocalScope::Scope_For
				|| scopeType == LocalScope::Scope_While
				|| scopeType == LocalScope::Scope_DoWhile)
			{
				return true;
			}
		}

		return false;
	}

	bool FunctionContext::IsInsideBranchBlock()
	{
		for (int i = (int)localScopes.size() - 1; i >= 0; i--)
		{
			LocalScope::ScopeType scopeType = localScopes[i].scopeType;
			if (scopeType == LocalScope::Scope_For
				|| scopeType == LocalScope::Scope_If
				|| scopeType == LocalScope::Scope_Else
				|| scopeType == LocalScope::Scope_ElseIf
				|| scopeType == LocalScope::Scope_While
				|| scopeType == LocalScope::Scope_DoWhile)
			{
				return true;
			}
		}

		return false;
	}

	BaseTranspilerContext::BaseTranspilerContext()
	{
		globalType = Allocator::New<ConcreteType>(ConcreteType::SystemReservedType);
		globalType->inputName = "____global";
		globalType->outputFullName = "____global";
		globalType->exportName = "____global";
	}

}
