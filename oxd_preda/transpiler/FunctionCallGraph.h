#pragma once

class FunctionCallGraph
{
public:
	std::map<transpiler::FunctionSignature *, std::set<transpiler::FunctionSignature *>> m_functionCallerSets;
};
