#pragma once
#include "../abi/vm_types.h"


namespace rvm
{

enum RvmExceptionCode
{
	REXC_ASSERTION_FAILED = 0,
	REXC_DIVIDE_BY_ZERO,
	REXC_TOO_MANY_RELAY,
	REXC_INVALID_RELAY_TARGET,
	REXC_BROADCAST_SCOPE_DISALLOWED,
	REXC_OUT_OF_MEMORY,
	REXC_OUT_OF_GAS_SPLIT,
	REXC_INVALID_ARGMENTS,
};

struct InvokeException
{
#ifdef PLATFORM_DEBUG_BUILD
	LPCSTR	File;
	LPCSTR	Func;
	UINT	Line;
#endif

	RvmExceptionCode	Code;

	template<class t_Ostream>
	friend t_Ostream& operator<<(t_Ostream& Ostream, const InvokeException& x)
	{	
		Ostream << "RVM-EXCEPTION("<< (int)x.Code << "): " << x.Code;
#ifdef PLATFORM_DEBUG_BUILD
		Ostream << '\n' << x.Func << '\n' << x.File << ":L" << x.Line << '\n';
#endif
		return Ostream;
	}
};

typedef const InvokeException*		RVM_EXCEPTION_PTR;

namespace _details
{
template<typename T>
auto& _RVM_REQUIRED(T&& x, const char* file, const char* func, uint32_t line)
{
	if(x){}
	else
	{	
#ifdef PLATFORM_DEBUG_BUILD
		InvokeException e = { file, func , line, REXC_ASSERTION_FAILED };
#else
		InvokeException e = { REXC_ASSERTION_FAILED };
#endif
		throw &e;
	}
	return x;
}
template<typename T>
auto& _RVM_REQUIRED(T&& x)
{
	if(x) {}
	else
	{
#ifdef PLATFORM_DEBUG_BUILD
		InvokeException e = { "EMPTY", "EMPTY", 0, REXC_ASSERTION_FAILED };
#else
		InvokeException e = { REXC_ASSERTION_FAILED };
#endif
		throw& e;
	}
	return x;
}
} // namespace _details
} // namespace rvm



#ifdef PLATFORM_DEBUG_BUILD
#define RVM_REQUIRED(x)		::rvm::_details::_RVM_REQUIRED((x), __FILE__, __FUNCTION__ , (uint32_t)__LINE__)
#define RVM_THROW(res)	{ static const ::rvm::InvokeException e = { __FILE__, __FUNCTION__ , (UINT)__LINE__, res }; throw &e; }	
#define RVM_ASSERT(x)	{ RVM_REQUIRED(x); }
#else
#define RVM_REQUIRED(x)		::rvm::_details::_RVM_REQUIRED((x))
#define RVM_THROW(res)	{	static const ::rvm::InvokeException e = { res }; throw &e; }
#define RVM_ASSERT(x)	{}
#endif


STRINGIFY_ENUM_BEGIN(RvmExceptionCode, rvm)
	STRINGIFY_ENUM(REXC_ASSERTION_FAILED)
	STRINGIFY_ENUM(REXC_DIVIDE_BY_ZERO)
	STRINGIFY_ENUM(REXC_TOO_MANY_RELAY)
	STRINGIFY_ENUM(REXC_INVALID_RELAY_TARGET)
	STRINGIFY_ENUM(REXC_BROADCAST_SCOPE_DISALLOWED)
	STRINGIFY_ENUM(REXC_OUT_OF_MEMORY)
	STRINGIFY_ENUM(REXC_OUT_OF_GAS_SPLIT)
	STRINGIFY_ENUM(REXC_INVALID_ARGMENTS)
STRINGIFY_ENUM_END(RvmExceptionCode, rvm)

