#pragma once
#include "../../SFC/core/ext/sparsehash/sparsehash.h"
#include "../../SFC/core/ext/concurrentqueue/async_queue.h"
#include "../../SFC/core/ext/exprtk/exprtk.h"
#include "../native/abi/vm_interfaces.h"
#include "../../oxd_libsec/oxd_libsec.h"


namespace oxd
{
class Simulator;

static const uint32_t		SIMU_BLOCK_INTERVAL = 5000; // msec
static const rvm::BuildNum	BUILD_NUM_INIT = (rvm::BuildNum)1;

struct ShardStateKeyObj;
struct ShardStateKey
{
	rvm::ContractScopeId	Contract;
	rvm::ScopeKey			Key;

	operator const ShardStateKeyObj& (){ return *(const ShardStateKeyObj*)this; }
};

struct ShardStateKeyObj: protected ShardStateKey
{
	friend struct ::std::hash<::oxd::ShardStateKeyObj>;

	ShardStateKeyObj(){ rt::Zero(*this); }
	ShardStateKeyObj(const ShardStateKeyObj& x);
	ShardStateKeyObj(ShardStateKeyObj&& x);
	~ShardStateKeyObj();

	const ShardStateKeyObj& operator = (const ShardStateKeyObj& x);
	bool operator == (const ShardStateKeyObj& x) const;
};

struct ScopeKeyPOD: public rvm::ScopeKey
{
	template<typename T>
	ScopeKeyPOD(const T& x)
	{	static_assert(rt::TypeTraits<T>::IsPOD);
		Data = (uint8_t*)&x;
		Size = sizeof(T);
	}
};
typedef ScopeKeyPOD _SKPOD;

struct User
{
	rvm::Address		Addr;
	uint32_t			ShardDword;
	bool				operator==(const User& u) const
	{
		return (!memcmp(Addr._, u.Addr._, RVM_HASH_SIZE) && Addr._CheckSum == u.Addr._CheckSum && (ShardDword == u.ShardDword));
	}
};

struct EngineEntry
{
	HANDLE				hModule;
	rvm::RvmEngine* pEngine;
};

struct StreamByString : public rvm::StringStream
{
	rt::String& _str;
	SIZE_T		_base;
	SSIZE_T		_last_append_pos;

	virtual void Append(const char* str, uint32_t len) override { _str += rt::String_Ref(str, len); }
	virtual char* AppendBegin(uint32_t over_estimated_len) override
	{
		ASSERT(_last_append_pos == -1);
		_last_append_pos = _str.GetLength();
		VERIFY(_str.SetLength(over_estimated_len + _str.GetLength()));
		return &_str[_last_append_pos];
	}
	virtual void AppendEnd(uint32_t finalized_len) override
	{
		ASSERT(_last_append_pos >= 0);
		_str.SetLength(_last_append_pos + finalized_len);
		_last_append_pos = -1;
	}
	virtual rvm::ConstString GetString() override
	{
		ASSERT(_last_append_pos == -1);
		return rvm::ConstString({ _str.Begin() + _base, static_cast<uint32_t>(_str.GetLength() - _base) });
	}
	StreamByString(rt::String& str) :_str(str) { _base = str.GetLength(); _last_append_pos = -1; }
	~StreamByString() { ASSERT(_last_append_pos == -1); }
};

class DataBuffer : public rvm::DataBuffer
{
	rt::BufferEx<uint8_t>		_Data;

public:
	virtual uint8_t*			SetSize(uint32_t len) override { _Data.ChangeSize(len); return _Data; }
	virtual const uint8_t*		GetData() override { return _Data; }
	virtual uint32_t			GetSize() override { return (uint32_t)_Data.GetSize(); }

	DataBuffer&					Empty(){ _Data.ShrinkSize(0); return *this; }
	rvm::ConstData				GetRvmConstData() const { return { _Data.Begin(), (uint32_t)_Data.GetSize() }; }
};

enum SimuTxnFlag: uint16_t
{
	TXN_RELAY = 0x01,
	TXN_BROADCAST = 0x02  // to all shards
};

#pragma pack(push, 1)
struct SimuTxn
{
	rvm::InvokeContextType	Type;
	rvm::Address			Target;		// available if GetScope() == SCOPE_ADDRESS
	uint64_t				Target_index; //Users[Target_index]

	uint64_t				Height; // height of the block including this txn
	uint16_t				ShardIndex; // shard index
	uint16_t				ShardOrder; // shard order

	rvm::Address			Initiator;	// available if IsRelay()
	uint64_t				OriginateHeight; // available if IsRelay()
	uint16_t				OriginateShardIndex; // available if IsRelay()
	uint16_t				OriginateShardOrder; // available if IsRelay()

	uint32_t				BuildNum;
	uint64_t				Timestamp;

	rvm::ContractScopeId	Contract;  // Contract with scope
	rvm::OpCode				Op;
	SimuTxnFlag				Flag;

	uint32_t				ArgsSerializedSize;
	uint8_t					ArgsSerializedData[1];

	bool					IsRelay() const { return TXN_RELAY&Flag; }
	bool					IsBroadcast() const { return TXN_BROADCAST&Flag; }
	rvm::Scope				GetScope() const { return rvm::_details::CONTRACT_SCOPE(Contract); }
	uint32_t				GetSize() const { return ArgsSerializedSize + offsetof(SimuTxn, ArgsSerializedData); }
	void					Release(){ _SafeFree8AL_ConstPtr(this); }
	static SimuTxn*			Create(uint32_t args_size);
	SimuTxn*				Clone() const;
	rvm::EngineId			GetEngineId() const { return rvm::_details::CONTRACT_ENGINE(Contract); }
	void					Jsonify(rvm::RvmEngine* engine, const rvm::ChainState* ps, rt::Json& append, rvm::InvokeResult* result) const;
};

struct ConfirmTxn
{
	SimuTxn*			Txn;
	uint64_t			GasBurnt;
	rvm::InvokeResult	Result;
#ifdef _VIZ
	void Jsonify(rvm::RvmEngine* engine, const rvm::ChainState* ps, rt::Json& append) const
	{
		auto s1 = append.ScopeAppendingElement();
		append.Object(J(InvokeResult) = rt::EnumStringify(Result.Code));
		Txn->Jsonify(engine, ps, append, nullptr);
	}
#endif
};

struct SimuBlock
{
	rvm::HashValue		PrevBlock;
	ULONGLONG			Height;
	uint64_t			Timestamp;
	rvm::Address		Miner;
	uint64_t			TotalGas;
	uint32_t			TxnCount;
	ConfirmTxn			Txns[1];

	uint32_t			GetSize() const { return offsetof(SimuBlock, Txns) + sizeof(ConfirmTxn)*TxnCount; }
	void				Release();
	static SimuBlock*	Create(uint32_t txn_count);
};

struct SimuState
{
	rvm::BuildNum	 	Version;
	uint32_t			DataSize;
	uint8_t				Data[1];

	void				Release(){ _SafeFree8AL_ConstPtr(this); }
	static SimuState*	Create(uint32_t size, rvm::BuildNum buildnum = (rvm::BuildNum)0, const void* data = nullptr);
};
#pragma pack(pop)


class PendingTxns
{
protected:
	typedef SimuTxn* LPSIMUTXN;
	ext::AsyncDataQueueInfinite<SimuTxn*, false, 64, true> _Queue;

public:
	PendingTxns() = default;
	~PendingTxns();
	bool		Push(SimuTxn* tx);  // true if queue was empty
	bool		Push(SimuTxn** txns, uint32_t count);  // true if queue was empty, for relay only
	SimuTxn*	Pop();
	bool		IsEmpty() const { return _Queue.GetSize() == 0; }
	size_t		GetSize() const { return _Queue.GetSize(); }
};

namespace _details
{
extern const rvm::Contract* GetDeployedContract(rvm::RvmEngine* engine, rvm::ContractId cid, rvm::BuildNum version);
} // namespace _details

template<typename KEY>
class SimuChainState
{
protected:
	ext::fast_map_ptr<KEY, SimuState>	_State;

public:
	bool	Get(const KEY& k, SimuState** out) const
			{	auto it = _State.find(k);
				if(it == _State.end())return false;
				*out = it->second;
				return true;
			}
	auto*	Get(const KEY& k) const { return _State.get(k); }
	void	Set(const KEY& k, SimuState* s, bool keep_nullptr = false)
			{	if(keep_nullptr || s)
				{	_SafeRelease_ConstPtr(_State.replace(k, s));
				}
				else
				{	auto it = _State.find(k);
					if(it != _State.end())
					{	_SafeRelease_ConstPtr(it->second);
						_State.erase(it);
					}
				}
			}
	size_t	GetSize() const { return _State.size(); }
	void	Empty()
			{	_State.foreach([](const KEY& k, SimuState* s){ _SafeRelease_ConstPtr(s); });
				_State.clear();
			}
	void	Commit(SimuChainState& to)
			{	for(auto& it : _State)to.Set(it.first, it.second);
				_State.clear();
			}
	SimuChainState() = default;
	~SimuChainState(){ Empty(); }

#ifdef _VIZ
	bool ShardStateJsonify(const EngineEntry* engine, rt::Json& append, rvm::ContractId cid, uint64_t shard_index, const rvm::ChainState* ps) const
	{
		auto s = append.ScopeAppendingElement();
		append.Object();
		if(shard_index == 65535)
		{
			append << ((J(ShardIndex) = "#g"));
		}
		else
		{
			append << ((J(ShardIndex) = rt::String("#") + shard_index));
		}
		auto ss = append.ScopeAppendingKey("States");
		append.Array();
		bool empty = true;
		for (auto it : _State)
		{
			if((uint64_t)cid != 0 && rvm::_details::CONTRACT_UNSET_SCOPE(it.first) != cid)
				continue;

			empty = false;
			auto s = append.ScopeAppendingElement();

			const rvm::Contract* contract = _details::GetDeployedContract(engine[(int)rvm::_details::CONTRACT_ENGINE(it.first)].pEngine, rvm::_details::CONTRACT_UNSET_SCOPE(it.first), it.second->Version);
			if(!contract)
			{
				append.Empty();
				return false;
			}
			append.Object(J(Contract) = contract->GetName().Str());
			auto ss = append.ScopeAppendingKey("State");
			StreamByString _((rt::String&)append);
			rvm::ConstData data{it.second->Data, it.second->DataSize};
			if(!engine[(int)rvm::_details::CONTRACT_ENGINE(it.first)].pEngine->StateJsonify(it.second->Version, it.first, &data, &_, ps))
			{
				_LOG("[PRD]: Unable to jsonify state")
				append.Empty();
				return false;
			}
		}
		if((uint64_t)cid != 0 && empty)
		{
			const rvm::Contract* contract = _details::GetDeployedContract(engine[(int)rvm::_details::CONTRACT_ENGINE(cid)].pEngine, cid, 1);
			if(contract)
			{
				append << ((rt::_JTag(contract->GetName().Str()) = rt::SS("null")));
			}
		}
		return true;
	}

	struct cmpAddress {
		bool operator()(const rvm::Address& a, const rvm::Address& b) const {
			return memcmp(a._, b._, sizeof(rvm::Address::_)) < 0;
		}
	};

	void AllAddressStateJsonify(const EngineEntry* engine, rt::Json& append, const rt::BufferEx<User>& Users, rvm::ContractId target_cid, int shard_index, const rvm::ChainState* ps)
	{
		std::map<rvm::Address, rt::BufferEx<std::pair<rvm::ContractScopeId, SimuState*>>, cmpAddress> states_per_addr;
		GroupAddrState(states_per_addr);
		for (auto it : states_per_addr)
		{
			rvm::Address addr = it.first;
			rt::BufferEx<std::pair<rvm::ContractScopeId, SimuState*>> state_arr = it.second;
			auto s = append.ScopeAppendingElement();
			char buf[rvm::_details::ADDRESS_BASE32_LEN];
			rvm::_details::ADDRESS_TO_STRING(addr, buf);
			rt::String_Ref sref(buf, rvm::_details::ADDRESS_BASE32_LEN);
			User a({addr, rvm::_details::ADDRESS_SHARD_DWORD(addr)});
			append.Object(((J(Address) = sref + rt::SS(":") + oxd::SecuritySuite::IdToString(addr._SSID)),
				(J(AddressIndex) = rt::String('@') + Users.Find(a)),
				(J(ShardIndex) = rt::String('#') + shard_index)
				));
			auto ss = append.ScopeAppendingKey("States");
			append.Array();
			for (std::pair<rvm::ContractScopeId, SimuState*> p : state_arr)
			{
				auto arr_sec = append.ScopeAppendingElement();
				rvm::ContractScopeId cid = p.first;
				if((uint64_t)target_cid != 0 && rvm::_details::CONTRACT_UNSET_SCOPE(cid) != target_cid)
				{
					continue;
				}
				SimuState* s = p.second;
				const rvm::Contract* contract = _details::GetDeployedContract(engine[(int)rvm::_details::CONTRACT_ENGINE(cid)].pEngine, rvm::_details::CONTRACT_UNSET_SCOPE(cid), s->Version);
				if(!contract)
				{
					append.Empty();
					return;
				}
				append.Object(J(Contract) = contract->GetName().Str());
				auto sss = append.ScopeAppendingKey("State");
				StreamByString _((rt::String&)append);
				rvm::ConstData data{ s->Data, s->DataSize };
				engine[(int)rvm::_details::CONTRACT_ENGINE(cid)].pEngine->StateJsonify(s->Version, cid, &data, &_, ps);
			}
		}
	}

	void AddressStateJsonify(const EngineEntry* engine, rvm::Address& Address, rt::Json& append, const rt::BufferEx<User>& Users, rvm::ContractId target_cid, int shard_index, const rvm::ChainState* ps)
	{
		auto s = append.ScopeAppendingElement();
		std::map<rvm::Address, rt::BufferEx<std::pair<rvm::ContractScopeId, SimuState*>>, cmpAddress> states_per_addr;
		GroupAddrState(states_per_addr);
		for (auto it : states_per_addr)
		{
			rvm::Address addr = it.first;
			rt::BufferEx<std::pair<rvm::ContractScopeId, SimuState*>> state_arr = it.second;
			if(memcmp(&addr._, &Address._, sizeof(rvm::Address)) != 0)
			{
				continue;
			}
			char buf[rvm::_details::ADDRESS_BASE32_LEN];
			rvm::_details::ADDRESS_TO_STRING(Address, buf);
			rt::String_Ref sref(buf, rvm::_details::ADDRESS_BASE32_LEN);
			User a({ Address, rvm::_details::ADDRESS_SHARD_DWORD(Address) });
			append.Object((J(Address) = sref + rt::SS(":") + oxd::SecuritySuite::IdToString(Address._SSID),
				J(AddressIndex) = rt::String('@') + Users.Find(a),
				(J(ShardIndex) = rt::String('#') + shard_index)));
			auto ss = append.ScopeAppendingKey("States");
			append.Array();
			for (std::pair<rvm::ContractScopeId, SimuState*> p : state_arr)
			{
				auto arr_sec = append.ScopeAppendingElement();
				rvm::ContractScopeId cid = p.first;
				if((uint64_t)target_cid != 0 && rvm::_details::CONTRACT_UNSET_SCOPE(cid) != target_cid)
				{
					continue;
				}
				SimuState* s = p.second;
				const rvm::Contract* contract = _details::GetDeployedContract(engine[(int)rvm::_details::CONTRACT_ENGINE(cid)].pEngine, rvm::_details::CONTRACT_UNSET_SCOPE(cid), s->Version);

				if(!contract)
				{
					append.Empty();
					return;
				}
				append.Object(J(Contract) = contract->GetName().Str());
				auto sss = append.ScopeAppendingKey("State");
				StreamByString _((rt::String&)append);
				rvm::ConstData data{ s->Data, s->DataSize };
				engine[(int)rvm::_details::CONTRACT_ENGINE(cid)].pEngine->StateJsonify(s->Version, cid, &data, &_, ps);
			}
		}
	}
private:
	void GroupAddrState(std::map<rvm::Address, rt::BufferEx<std::pair<rvm::ContractScopeId, SimuState*>>, cmpAddress>& m)
	{
		for (auto it : _State)
		{
			rt::BufferEx<std::pair<rvm::ContractScopeId, SimuState*>> current;
			if(m.find(it.first.Address) != m.end())
			{
				current = m.find(it.first.Address)->second;
			}
			current.push_back({ it.first.Id, it.second});
			m[it.first.Address] = current;
		}
	}
#endif
};

#pragma pack(push, 1)
struct SimuAddressContract
{
	rvm::Address			Address;
	rvm::ContractScopeId	Id;			// contractid with scope
	bool operator == (const SimuAddressContract& x) const { return rt::IsEqual(*this, x); }
};
#pragma pack(pop)

struct JsonLogError: public rvm::LogMessageOutput
{
	virtual void Log(rvm::LogMessageType type, uint32_t code, uint32_t unitIndex, uint32_t line, uint32_t lineOffset, const rvm::ConstString *message) override
	{
		_LOG_WARNING("[BC]: Json ("<<line<<':'<<lineOffset<<"): "<<message->Str());
	}
};

class InputParametrized
{
	Simulator&	_Simulator;
	auto&		_TempString(){ thread_local rt::String _; return _; }
	auto&		_TempBuffer(){ thread_local DataBuffer _; return _; }

public:
	struct Symbols: public ext::ExpressionSymbols<int64_t>
	{
		struct Random: public ext::ExpressionFunction<int64_t, 2>
		{
			Simulator&		_Simulator;
			int64_t			_Last = 0;
			Random(Simulator& s):_Simulator(s){}
			virtual int64_t operator() (const int64_t& x, const int64_t& y) override;
		};

		Random	_random;
		Symbols(Simulator& s);
	};

protected:
	enum SegmentType
	{
		ST_ERROR = 0,
		ST_STATIC,				// String = static string
		ST_SPECIFIC_ADDRESS,	// UserIndex = index of the user in text
		ST_NONSTATIC_MIN = 0xf,
		ST_EXPRESSION,			// Expression = an long integer expression
		ST_RANDOM_ADDRESS,		// (address string of a random user)
		ST_INDEXED_ADDRESS,		// _Users[_LoopIndex]
		ST_RANDOM_BIGINT,		// Bytes = number of random bytes
	};
	struct Segment
	{
		SegmentType					Type;
		union {
		uint32_t					UserIndex;
		rt::String_Ref				String;
		ext::Expression<int64_t>*	Expression;
		uint32_t					Digits;
		};

		Segment(const rt::String_Ref& s, bool is_static, Simulator& simu);
		Segment(Segment&& x){ rt::Copy(*this, x); x.Expression = nullptr; }
		~Segment(){ if(Type == ST_EXPRESSION)_SafeDel(Expression); }
		bool IsError() const { return Type == ST_ERROR; }
		bool IsNonStatic() const { return Type > ST_NONSTATIC_MIN; }
		bool IsLoopIndexInvolved() const { return Type == ST_INDEXED_ADDRESS; }
	};

	rt::BufferEx<Segment>			_Segments;
	bool							_bIsParametrized;
	bool							_bLoopIndexInvolved;

public:
	InputParametrized(Simulator& s):_Simulator(s){}
	bool	Parse(const rt::String_Ref& s);
	void	Empty();
	void	Evaluate(rt::String& out, int loop_index = 0) const;
	auto	ComposeState(rvm::BuildNum build_num, rvm::ContractScopeId cid, int loop_index = 0) -> rvm::ConstData;
	auto	ComposeTxn(rvm::BuildNum build_num, rvm::ContractScopeId cid, rvm::OpCode opcode, int loop_index = 0) -> SimuTxn*;
	bool	IsError() const { return _Segments.GetSize() && _Segments.last().IsError(); }
	bool	IsParameterized() const { return _bIsParametrized; }
	bool	IsLoopIndexInvolved() const { return _bLoopIndexInvolved; }
};

struct ShardIndexString: public rt::tos::Number
{
	ShardIndexString(uint32_t si): rt::tos::Number(si)
	{
		if(si == rvm::GlobalShard){ _p[0] = 'g'; _len = 1; }
	}
};

} // namespace oxd


namespace std
{
template<>
struct hash<::oxd::SimuAddressContract>: public ::rt::_details::hash_compare_fix<::oxd::SimuAddressContract>{};

template<>
struct hash<::oxd::ShardStateKeyObj>
{
	enum ///< parameters for hash table
	{	bucket_size = 4,	///< 0 < bucket_size
		min_buckets = 8		///< min_buckets = 2 ^^ N, 0 < N
	};
	size_t operator()(const ::oxd::ShardStateKeyObj& key) const
	{	return ::rt::_details::_HashValue(key.Key.Data, key.Key.Size, (uint64_t)key.Contract);
	}
	bool operator()(const ::oxd::ShardStateKeyObj& _Keyval1, const ::oxd::ShardStateKeyObj& _Keyval2) const
	{	return	_Keyval1.Contract == _Keyval2.Contract &&
				_Keyval1.Key.Size == _Keyval2.Key.Size &&
				memcmp(_Keyval1.Key.Data, _Keyval2.Key.Data, _Keyval1.Key.Size) == 0;
	}
};
} // namespace std

namespace ext
{
	template<>
	struct key_traits<::oxd::ShardStateKeyObj>
	{	static const ::oxd::ShardStateKeyObj empty_key(){ ::oxd::ShardStateKey empty = { (rvm::ContractScopeId)0, {nullptr, 0} }; return empty; }
		static const ::oxd::ShardStateKeyObj deleted_key(){ ::oxd::ShardStateKey deleted = { (rvm::ContractScopeId)(-1LL), {nullptr, 0} }; return deleted; }
	};
} // namespace ext
