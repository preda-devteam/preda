#pragma once
#include "compound.h"


namespace rvm
{

#define RVM_STRUCT_WITH_1_MEMBER(name1)	\
			static const LPCSTR* AllNames(){ static const LPCSTR n[] = {#name1}; return n; } \
			static_assert(MemberCount == 1, "Definition of the Struct type is not single member"); \
			auto&	name1(){ return _Member<0>(); }	\
			auto&	name1() const { return _Member<0>(); }	\

#define RVM_STRUCT_WITH_2_MEMBER(name1, name2)	\
			static const LPCSTR* AllNames(){ static const LPCSTR n[] = {#name1, #name2}; return n; } \
			static_assert(MemberCount == 2, "Definition of the Struct type is not 2-members"); \
			auto&	name1() const { return _Member<0>(); }	\
			auto&	name2() const { return _Member<1>(); }	\
			auto&	name1(){ return _Member<0>(); }	\
			auto&	name2(){ return _Member<1>(); }	\
		
#define RVM_STRUCT_WITH_3_MEMBER(name1, name2, name3)	\
			static const LPCSTR* AllNames(){ static const LPCSTR n[] = {#name1, #name2, #name3}; return n; } \
			static_assert(MemberCount == 3, "Definition of the Struct type is not 3-members"); \
			auto&	name1() const { return _Member<0>(); }	\
			auto&	name2() const { return _Member<1>(); }	\
			auto&	name3() const { return _Member<2>(); }	\
			auto&	name1(){ return _Member<0>(); }	\
			auto&	name2(){ return _Member<1>(); }	\
			auto&	name3(){ return _Member<2>(); }	\

#define RVM_STRUCT_WITH_4_MEMBER(name1, name2, name3, name4)	\
			static const LPCSTR* AllNames(){ static const LPCSTR n[] = {#name1, #name2, #name3, #name4}; return n; } \
			static_assert(MemberCount == 4, "Definition of the Struct type is not 4-members"); \
			auto&	name1() const { return _Member<0>(); }	\
			auto&	name2() const { return _Member<1>(); }	\
			auto&	name3() const { return _Member<2>(); }	\
			auto&	name4() const { return _Member<3>(); }	\
			auto&	name1(){ return _Member<0>(); }	\
			auto&	name2(){ return _Member<1>(); }	\
			auto&	name3(){ return _Member<2>(); }	\
			auto&	name4(){ return _Member<3>(); }	\

#define RVM_STRUCT_WITH_5_MEMBER(name1, name2, name3, name4, name5)	\
			static const LPCSTR* AllNames(){ static const LPCSTR n[] = {#name1, #name2, #name3, #name4, #name5}; return n; } \
			static_assert(MemberCount == 5, "Definition of the Struct type is not 5-members"); \
			auto&	name1() const { return _Member<0>(); }	\
			auto&	name2() const { return _Member<1>(); }	\
			auto&	name3() const { return _Member<2>(); }	\
			auto&	name4() const { return _Member<3>(); }	\
			auto&	name5() const { return _Member<4>(); }	\
			auto&	name1(){ return _Member<0>(); }	\
			auto&	name2(){ return _Member<1>(); }	\
			auto&	name3(){ return _Member<2>(); }	\
			auto&	name4(){ return _Member<3>(); }	\
			auto&	name5(){ return _Member<4>(); }	\

#define RVM_STRUCT_WITH_6_MEMBER(name1, name2, name3, name4, name5, name6)	\
			static const LPCSTR* AllNames(){ static const LPCSTR n[] = {#name1, #name2, #name3, #name4, #name5, #name6}; return n; } \
			static_assert(MemberCount == 6, "Definition of the Struct type is not 6-members"); \
			auto&	name1() const { return _Member<0>(); }	\
			auto&	name2() const { return _Member<1>(); }	\
			auto&	name3() const { return _Member<2>(); }	\
			auto&	name4() const { return _Member<3>(); }	\
			auto&	name5() const { return _Member<4>(); }	\
			auto&	name6() const { return _Member<5>(); }	\
			auto&	name1(){ return _Member<0>(); }	\
			auto&	name2(){ return _Member<1>(); }	\
			auto&	name3(){ return _Member<2>(); }	\
			auto&	name4(){ return _Member<3>(); }	\
			auto&	name5(){ return _Member<4>(); }	\
			auto&	name6(){ return _Member<5>(); }	\

#define RVM_STRUCT_WITH_7_MEMBER(name1, name2, name3, name4, name5, name6, name7)	\
			static const LPCSTR* AllNames(){ static const LPCSTR n[] = {#name1, #name2, #name3, #name4, #name5, #name6, #name7}; return n; } \
			static_assert(MemberCount == 7, "Definition of the Struct type is not 7-members"); \
			auto&	name1() const { return _Member<0>(); }	\
			auto&	name2() const { return _Member<1>(); }	\
			auto&	name3() const { return _Member<2>(); }	\
			auto&	name4() const { return _Member<3>(); }	\
			auto&	name5() const { return _Member<4>(); }	\
			auto&	name6() const { return _Member<5>(); }	\
			auto&	name7() const { return _Member<6>(); }	\
			auto&	name1(){ return _Member<0>(); }	\
			auto&	name2(){ return _Member<1>(); }	\
			auto&	name3(){ return _Member<2>(); }	\
			auto&	name4(){ return _Member<3>(); }	\
			auto&	name5(){ return _Member<4>(); }	\
			auto&	name6(){ return _Member<5>(); }	\
			auto&	name7(){ return _Member<6>(); }	\

namespace _details
{

#pragma pack(push, 1)
template<typename OFFSET_TYPE, typename FRONT, typename... REST>
struct _StructDef
{
	using REST_DEF = _StructDef<OFFSET_TYPE, REST...>;
	typedef FRONT Type;
	static const UINT MemberCount = 1 + REST_DEF::MemberCount;

	template<typename ARG, typename... REST_ARGS>
	static bool IsEmbeddable(const ARG& ob, const REST_ARGS & ... rest)
	{	return _Embed<FRONT, ARG>::IsEmbeddable(ob) && REST_DEF::IsEmbeddable(rest...);
	}

	template<typename ARG, typename... REST_ARGS>
	static UINT	EmbedForward(LPBYTE buf, const ARG& ob, const REST_ARGS & ... rest)
				{	UINT sz = _Embed<FRONT, ARG>::Set(buf, ob);
					return sz + REST_DEF::EmbedForward(buf + sz, rest...);
				}
	template<typename ARG, typename... REST_ARGS>
	static UINT	EmbedSizeWithOffset(OFFSET_TYPE* offset, const ARG& ob, const REST_ARGS & ... rest)
				{	UINT sz = _Embed<FRONT, ARG>::GetEmbeddedSize(ob);
					ASSERT(sz < (1ULL<<(sizeof(offset[0])*8)));
					offset[0] = offset[-1] + sz;
					return REST_DEF::EmbedSizeWithOffset(offset + 1, rest...);
				}
	static void	CompareOffset(const OFFSET_TYPE* a, const OFFSET_TYPE* b, int& large_co, int& small_co)
				{	if(a[0] < b[0])large_co++;
					else if(a[0] > b[0])small_co++;
					REST_DEF::CompareOffset(a+1, b+1, large_co, small_co);
				}
};
	template<typename OFFSET_TYPE, typename END>
	struct _StructDef<OFFSET_TYPE, END>
	{
		typedef END Type;
		static const UINT MemberCount = 1;

		template<typename ARG, typename... REST_ARGS>
		static bool IsEmbeddable(const ARG& ob, const REST_ARGS & ... rest) {	return _Embed<END, ARG>::IsEmbeddable(ob); }
		template<typename ARG, typename... REST_ARGS>
		static UINT	EmbedForward(LPBYTE buf, const ARG& ob, const REST_ARGS & ... rest){ return _Embed<END, ARG>::Set(buf, ob); }
		template<typename ARG, typename... REST_ARGS>
		static UINT	EmbedSizeWithOffset(OFFSET_TYPE* offset, const ARG& ob)
		{	
			UINT sz = _Embed<END, ARG>::GetEmbeddedSize(ob);
			ASSERT(sz < (1ULL<<(sizeof(offset[0])*8)));
			offset[0] = offset[-1] + sz;
			return offset[0]; 
		}
		static void	CompareOffset(const OFFSET_TYPE* a, const OFFSET_TYPE* b, int& large_co, int& small_co)
					{	if(a[0] < b[0])large_co++;
						else if(a[0] > b[0])small_co++;
					}
	};
#pragma pack(pop)

template<int IDX_R, typename CONTRACT_DEF, bool stop = (IDX_R == CONTRACT_DEF::MemberCount)>
struct _StructMemberType
{	typedef typename _StructMemberType<IDX_R, typename CONTRACT_DEF::REST_DEF>::MemberType MemberType;
};
	template<int IDX_R, typename CONTRACT_DEF>
	struct _StructMemberType<IDX_R, CONTRACT_DEF, true>
	{	typedef typename CONTRACT_DEF::Type MemberType;
	};

template<typename STATE, int IDX = 0, bool stop = (IDX == STATE::MemberCount)>
struct _MemberIteration
{
	static void Jsonify(const STATE& s, rt::String& append)
	{
		auto& x = s.template _Member<IDX>();
		append += '"' + rt::String_Ref(s.template _Name<IDX>()) + '"' + ':';
		RvmTypeJsonify(x, (rt::Json&)append);
		append += ',';
		_MemberIteration<STATE, IDX+1>::Jsonify(s, append);
	}
	static void GetTypeSignature(rt::String& n)
	{
		RvmTypeSignature<typename _StructMemberType<STATE::MemberCount - IDX, typename STATE::MemberList>::MemberType>::Get(n);
		n += ' ';
		n += rt::String_Ref(STATE::template _Name<IDX>());
		n += ';';
		_MemberIteration<STATE, IDX+1>::GetTypeSignature(n);
	}
};
	template<typename STATE, int IDX>
	struct _MemberIteration<STATE, IDX, true>
	{	static void Jsonify(const STATE& s, rt::String& append){ append.Shorten(1); }
		static void GetTypeSignature(rt::String& n){}
	};

#pragma pack(push, 1)
template<typename StructType, int MEM_INCL = StructType::MemberCount>
struct _StructMutableDef: public _StructMutableDef<StructType, MEM_INCL-1>
{
	typedef typename StructType::OffsetValueType*	LPOFFSETVALUETYPE;
	typedef typename _StructMemberType<StructType::MemberCount - (MEM_INCL-1), typename StructType::MemberList>::MemberType	Type;
	typedef typename TypeTraits<Type>::Mutable		Mutable;
	typedef _Embed<Type, Mutable>					Embed;

	Mutable	Member;

	bool	JsonParse(const rt::JsonObject& json)
			{	bool exist = false;
				rt::String_Ref a = json.GetValueRaw(StructType::template _Name<MEM_INCL-1>(), exist);
				if(!exist || !RvmTypeJsonParse(Member, a))return false;
				return _StructMutableDef<StructType, MEM_INCL-1>::JsonParse(json);
			}
	UINT	GetEmbeddedSize() const
			{	return Embed::GetEmbeddedSize(Member) + _StructMutableDef<StructType, MEM_INCL-1>::GetEmbeddedSize();
			}
	bool	IsEmbeddable() const
			{	return (Embed::IsEmbeddable(Member) && _StructMutableDef<StructType, MEM_INCL-1>::IsEmbeddable());
			}
	UINT	Set(LPBYTE& p, LPOFFSETVALUETYPE& off) const
			{	UINT ret = _StructMutableDef<StructType, MEM_INCL-1>::Set(p, off);
				UINT sz = Embed::Set(p, Member);
				*off = off[-1] + sz;
				p += sz;
				off++;
				return ret + sz;
			}
	UINT	Set(LPBYTE p) const
			{	UINT ret = _StructMutableDef<StructType, MEM_INCL-1>::Set(p);
				UINT sz = Embed::Set(p + ret, Member);
				return ret + sz;
			}
};
	template<typename StructType>
	struct _StructMutableDef<StructType, 1>
	{
		typedef typename StructType::OffsetValueType*	LPOFFSETVALUETYPE;
		typedef typename _StructMemberType<StructType::MemberCount, typename StructType::MemberList>::MemberType	Type;
		typedef typename TypeTraits<Type>::Mutable		Mutable;
		typedef _Embed<Type, Mutable>					Embed;

		Mutable	Member;

		bool	JsonParse(const rt::JsonObject& json)
				{	bool exist = false;
					rt::String_Ref a = json.GetValue(StructType::template _Name<0>(), exist);
					if(!exist || !RvmTypeJsonParse(Member, a))return false;
					return true;
				}
		UINT	GetEmbeddedSize() const
				{	return Embed::GetEmbeddedSize(Member);
				}
		bool	IsEmbeddable() const
				{	return Embed::IsEmbeddable(Member);
				}
		UINT	Set(LPBYTE& p, LPOFFSETVALUETYPE& off) const
				{	UINT sz = Embed::Set(p, Member);
					*off = off[-1] + sz;
					p += sz;
					off++;
					return sz;
				}
		UINT	Set(LPBYTE p) const { return Embed::Set(p, Member); }
	};
	template<typename StructType>
	struct _StructMutableDef<StructType, 0>
	{
		typedef typename StructType::OffsetValueType*	LPOFFSETVALUETYPE;

		bool	JsonParse(const rt::JsonObject& json){ return true; }
		UINT	GetEmbeddedSize() const { return 0; }
		bool	IsEmbeddable() const { return true; }
		UINT	Set(LPBYTE& p, LPOFFSETVALUETYPE& off) const { ASSERT(0); return 0; }
		UINT	Set(LPBYTE p) const { return 0; }
	};

#pragma pack(pop)
} // namespace _details


template<typename StructType>
class StructMutable: public _details::_StructMutableDef<StructType>
{
	typedef _details::_StructMutableDef<StructType> _SC;
public:
	typedef StructMutable		MutableType;
	typedef StructType			ImmutableType;
	UINT	GetEmbeddedSize() const
			{	return _SC::GetEmbeddedSize() + sizeof(typename StructType::OffsetValueType)*(1 + StructType::MemberCount);
			}
};

#pragma pack(push, 1)
template<typename OFFSET_TYPE, typename T_Derived, typename... MEMBERS>
class Struct
{
public:
	typedef _details::_StructDef<OFFSET_TYPE, MEMBERS...>	MemberList;
	static const UINT										MemberCount = MemberList::MemberCount;
	typedef OFFSET_TYPE										OffsetValueType;
	typedef StructTypeHeaderT<OffsetValueType, MemberCount> HeaderType;
	typedef StructMutable<T_Derived>						MutableType;
	typedef T_Derived										ImmutableType;

protected:
	HeaderType	Header;
	BYTE		Data[1];

public:
	UINT		GetEmbeddedSize() const { return Header.GetStateSize(); }
	template<UINT IDX>
	auto&		_Member()
				{	typedef typename _details::_StructMemberType<MemberList::MemberCount - IDX, MemberList>::MemberType RET;
					static_assert(IDX<MemberCount, "Member index out-of-range");
					if(!Header.IsEmpty())
						return Header.template Get<RET, IDX>();
					else
						return (RET&)rvm::RvmTypeZero<RET>();
				}
	template<UINT IDX>
	const auto&	_Member() const { return rt::_CastToNonconst(this)-> template _Member<IDX>(); }
	template<UINT IDX> static
	LPCSTR 		_Name(){ return T_Derived::AllNames()[IDX]; }
	bool		IsEmpty() const { return Header.IsEmpty(); }
	void		Jsonify(rt::Json& json) const 
				{	auto& append = (rt::String&)json;
					append += '{';
					_details::_MemberIteration<Struct>::Jsonify(*this, append);
					append += '}';
				}
	static UINT	GetEmbeddedSize(const MutableType& t){ return t.GetEmbeddedSize(); }
	static bool	IsEmbeddable(const MutableType& t){ return t.IsEmbeddable(); }
	static bool	IsEmbeddable(const ImmutableType& t){ return true; }
	UINT		Embed(const MutableType& t)
				{	auto* off = Header.GetOffsetTable();
					off[-1] = 0;
					LPBYTE p = Header.GetBaseAddress();
					UINT sz = t.Set(p, off);
					Header.Finalize();
					return Header.GetSize() + sz;
				}
	template<typename... ARGS>
	static auto	Compose(ARGS&& ... args)
				{	OFFSET_TYPE	offset_table[MemberList::MemberCount+1] = {0};
					UINT size = MemberList::EmbedSizeWithOffset(offset_table + 1, args...);
					Struct* ret = (Struct*)_Malloc8AL(BYTE, size + sizeof(HeaderType));
					ret->Header.SetOffsetTable(offset_table + 1);
					MemberList::EmbedForward(ret->Data, args...);
					return (T_Derived*)ret;
				}
	static const T_Derived& Zero()
				{	static const OFFSET_TYPE _ = HeaderType::Flag;
					return *(const T_Derived*)&_;
				}
	static void	GetTypeSignature(rt::String& n)
				{	n += rt::SS("struct:") + MemberList::MemberCount + '{';
					_details::_MemberIteration<Struct>::GetTypeSignature(n);
					n += '}';
				}
	TYPETRAITS_DECLARE_NON_POD;
};
#pragma pack(pop)

} // namespace rvm