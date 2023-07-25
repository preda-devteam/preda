#pragma once
#include "../abi/vm_interfaces.h"

namespace rvm
{

struct ShardIndexString: public rt::tos::Number
{
	ShardIndexString(uint32_t si): rt::tos::Number(si)
	{
		if(si == rvm::GlobalShard){ _p[0] = 'g'; _len = 1; }
	}
};

class StringStreamImpl : public rvm::StringStream
{
	rt::String	_intl;
	rt::String* _str;
	SIZE_T		_base;
	SSIZE_T		_last_append_pos;
public:
	virtual void				Append(const char* str, uint32_t len) override { *_str += rt::String_Ref(str, len); }
	virtual char*				AppendBegin(uint32_t over_estimated_len) override;
	virtual void				AppendEnd(uint32_t finalized_len) override;
	virtual rvm::ConstString	GetString() override;
	auto&						Empty(){ _str->Empty(); return *this; }
	operator					rt::String_Ref() const { return *_str; }
	StringStreamImpl();
	StringStreamImpl(rt::String& str);
	~StringStreamImpl() { ASSERT(_last_append_pos == -1); }
};

class DataBufferImpl : public rvm::DataBuffer
{
	rt::BufferEx<uint8_t>		_Data;
public:
	virtual uint8_t*			SetSize(uint32_t len) override
	{
		_Data.ChangeSize(len);
		return _Data;
	}
	virtual const uint8_t*		GetData() override
	{
		return _Data;
	}
	virtual uint32_t			GetSize() override
	{
		return (uint32_t)_Data.GetSize();
	}

	DataBufferImpl&				Empty()
	{
		_Data.ShrinkSize(0);
		return *this;
	}
	rvm::ConstData				GetRvmConstData() const
	{
		return { _Data.Begin(), (uint32_t)_Data.GetSize() };
	}
};

extern void Signature_Jsonify(rt::Json& json, const rt::String_Ref& scope_name, const rt::String_Ref& signature, bool structSig);
extern void BlockchainRuntime_DebugPrint(rvm::DebugMessageType type, const rvm::ConstString* text, const rvm::ExecutionState* ctx, const rvm::Contract* contract, int32_t line);
extern void CompiledModules_Jsonify(rt::Json& json, rvm::CompiledModules* built);

} // namespace rvm