#pragma once
#include <deque>
#include "../../SFC/core/ext/bignum/ttmath/ttmath.h"
#include "../../SFC/core/ext/sparsehash/sparsehash.h"
#include "../../SFC/core/ext/concurrentqueue/async_queue.h"
#include "../../SFC/core/ext/exprtk/exprtk.h"
#include "../native/abi/vm_interfaces.h"
#include "../native/types/array.h"
#include "../native/types/coins.h"
#include "../native/types/abi_def_impl.h"
#include "../../oxd_libsec/oxd_libsec.h"

namespace oxd
{
class Simulator;

static const uint32_t		SIMU_BLOCK_INTERVAL = 5000; // msec
static const rvm::BuildNum	BUILD_NUM_INIT = rvm::BuildNumInit;

extern bool					RvmStateJsonify(rvm::ContractRepository* engine, rvm::ContractInvokeId contract, const rvm::ConstData* contract_state, rvm::StringStream* json_out);
extern const rvm::Contract* RvmDeployedContract(rvm::RvmEngine* engine, rvm::ContractVersionId cvid);

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
	HANDLE			hModule;
	rvm::RvmEngine* pEngine;
};

enum SimuTxnFlag: uint16_t
{
	TXN_RELAY		= 1<<0,
	TXN_DEFERRED	= 1<<1,
	TXN_BROADCAST	= 1<<2// to all shards
};

#pragma pack(push, 1)
struct ScopeTarget
{
	uint8_t target_size;
	union {
		rvm::Address		addr;
		uint32_t			u32;
		uint64_t			u64;
		rvm::UInt96			u96;
		rvm::UInt128		u128;
		rvm::UInt160		u160;
		rvm::UInt256		u256;
		rvm::UInt336		u336;
		rvm::UInt512		u512;
	};
	ScopeTarget(){ rt::Zero(*this); target_size = sizeof(rvm::Address); }
	auto& operator = (const ScopeTarget& x){ memcpy(this, &x, 1 + x.target_size); return x; }

	ScopeTarget(const rvm::Address& v) : ScopeTarget() { addr = v; target_size = sizeof(v); }
	ScopeTarget(const uint32_t& v)	   : ScopeTarget() { u32 = v; target_size = sizeof(v); }
	ScopeTarget(const uint64_t& v)	   : ScopeTarget() { u64 = v; target_size = sizeof(v); }
	ScopeTarget(const rvm::UInt96& v)  : ScopeTarget() { u96 = v; target_size = sizeof(v); }
	ScopeTarget(const rvm::UInt128& v) : ScopeTarget() { u128 = v; target_size = sizeof(v); }
	ScopeTarget(const rvm::UInt160& v) : ScopeTarget() { u160 = v; target_size = sizeof(v); }
	ScopeTarget(const rvm::UInt256& v) : ScopeTarget() { u256 = v; target_size = sizeof(v); }
	ScopeTarget(const rvm::UInt336& v) : ScopeTarget() { u336 = v; target_size = sizeof(v); }
	ScopeTarget(const rvm::UInt512& v) : ScopeTarget() { u512 = v; target_size = sizeof(v); }
	ScopeTarget(const rvm::ScopeKey& v) : ScopeTarget()
	{
		switch (v.Size)
		{
		case 36:
		case 4:
		case 8:
		case 12:
		case 16:
		case 32:
		case 42:
		case 64:
			target_size = uint8_t(v.Size);
			memcpy(&u512, v.Data, v.Size);
			break;
		}
	}

	TYPETRAITS_DECLARE_POD;
};

struct SimuTxn
{
	rvm::HashValue			Hash;
	rvm::InvokeContextType	Type;
	ScopeTarget				Target;			// available if GetScope() is not global or shard
	int64_t				    TargetIndex;	//Users[TargetIndex] or -1 if target is not an existing user

	uint64_t				Height; // height of the block including this txn
	uint16_t				ShardIndex; // shard index
	uint16_t				ShardOrder; // shard order

	rvm::Address			Initiator;	// available if IsRelay()
	uint64_t				OriginateHeight; // available if IsRelay()
	uint16_t				OriginateShardIndex; // available if IsRelay()
	uint16_t				OriginateShardOrder; // available if IsRelay()

	uint64_t				Timestamp;
	uint64_t				Gas;
	uint32_t				GasRedistributionWeight;
	static constexpr uint64_t DefaultGas = 10000000;

	rvm::ContractInvokeId	Contract;  // Contract with scope
	rvm::OpCode				Op;
	SimuTxnFlag				Flag;

	uint32_t				TokensSerializedSize;	// rvm::Array<rvm::Coins>, normal txn only
	uint32_t				ArgsSerializedSize;
	uint8_t					SerializedData[1];		// [TokensSerializedData][ArgsSerializedData]

	bool					IsDeferred() const { return TXN_DEFERRED&Flag; }
	bool					IsRelay() const { return (TXN_RELAY | TXN_DEFERRED) &Flag; }		// regard deferred as relay, otherwise there'll be a lot of assertion failures
	bool					IsBroadcast() const { return TXN_BROADCAST&Flag; }
	rvm::Scope				GetScope() const 
	{
		if(Type == rvm::InvokeContextType::System)
		{
			return rvm::Scope::Global;
		}
		return rvm::CONTRACT_SCOPE(Contract);
	}
	bool					HasNativeTokensSupplied() const { return TokensSerializedSize; }
	auto&					GetNativeTokenSupplied() const { ASSERT(HasNativeTokensSupplied()); return *(const rvm::Array<rvm::Coins>*)SerializedData; }
	rvm::ConstData			GetArguments() const { return { SerializedData + TokensSerializedSize, ArgsSerializedSize }; }

	uint32_t				GetSize() const { return ArgsSerializedSize + TokensSerializedSize + offsetof(SimuTxn, SerializedData); }
	void					Release(){ _SafeFree8AL_ConstPtr(this); }
	static SimuTxn*			Create(uint32_t args_size, uint32_t assets_size);
	SimuTxn*				Clone() const;
	rvm::EngineId			GetEngineId() const { return rvm::CONTRACT_ENGINE(Contract); }
	void					Jsonify(rvm::RvmEngine* engine, rt::Json& append) const;
};

struct ConfirmTxn
{
	SimuTxn*			Txn;
	uint64_t			GasBurnt;
	rvm::InvokeResult	Result;
	rt::BufferEx<std::pair<rvm::TokenId, ext::BigNumMutable>> Residual;
	void Jsonify(rvm::RvmEngine* engine, rt::Json& append) const
	{
		auto s1 = append.ScopeAppendingElement();
		Txn->Jsonify(engine, append);
		append << ((J(InvokeResult) = rt::EnumStringify(Result.Code), J(GasBurnt) = Result.GasBurnt)); 
		if (Residual.GetSize())
		{
			rt::String tokenStr;
			auto walletBody = append.ScopeAppendingKey("TokenResidual");
			append.Array();
			for (uint32_t j = 0; j < Residual.GetSize(); j++)
			{
				Residual[j].second.ToString(tokenStr);
				tokenStr += ':' + rt::DS(Residual[j].first).GetLengthRecalculated();
				append.AppendElement(tokenStr);
				tokenStr.Empty();
			}
		}
	}
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

template<typename StateType>
class ConstState
{
	const StateType*	_p;
public:
	ConstState(const rvm::ConstStateData& data)
	{	_p = (const StateType*)data.DataPtr;
		if(_p)ASSERT(_p->GetEmbeddedSize() == data.DataSize);
	}
	ConstState(const SimuState* s)
	{	if (s && s->DataSize > 0)
		{
			_p = (const StateType*)s->Data;
			ASSERT(_p->GetEmbeddedSize() == s->DataSize);
		}
		else _p = nullptr;
	}
	bool				IsEmpty() const { return _p == nullptr; }
	operator const		StateType& () const { return *_p; }
	const StateType*	operator ->() const { return _p; }

	typedef typename rvm::TypeTraits<StateType>::Mutable Mutable;
	Mutable				DeriveMutable() const { return _p?Mutable(*_p):Mutable(); }
	static auto*		CreateState(const Mutable& m, rvm::BuildNum v)
	{	uint32_t sz = StateType::GetEmbeddedSize(m);
		auto* s = SimuState::Create(sz, v);
		VERIFY(((StateType*)s->Data)->Embed(m) == sz);
		return s;
	}
};



class PendingTxns
{
protected:
	std::deque<SimuTxn*> _Queue;
	mutable std::mutex _Mutex;				// this class is only used in multiple producer, single consumer cases. Hence there's no need to use a shared_mutex for better performance.

public:
	PendingTxns() = default;
	~PendingTxns();
	bool		Push(SimuTxn* tx);							// push a txn to the back of the queue, returns true if queue was empty
	bool		Push(SimuTxn** txns, uint32_t count);		// push multiple txns to the back of the queue, returns true if queue was empty
	bool		Push_Front(SimuTxn* txn);					// push a txn to the front of the queue, returns true if queue was empty
	SimuTxn*	Pop();										// pop a txn from the front of the queue
	bool		IsEmpty() const
	{
		std::lock_guard<std::mutex> lock(_Mutex);
		return _Queue.size() == 0;
	}
	size_t		GetSize() const
	{
		std::lock_guard<std::mutex> lock(_Mutex);
		return _Queue.size();
	}
};

#pragma pack(push, 1)
struct SimuAddressContract
{
	ScopeTarget				Address;
	rvm::ContractScopeId	Id;			// contractid with scope
	bool operator == (const SimuAddressContract& x) const { return rt::IsEqual(*this, x); }

	TYPETRAITS_DECLARE_POD;
};
#pragma pack(pop)

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

	bool ShardStateJsonify(const EngineEntry* engine, rt::Json& append, rvm::ContractId target_cid, uint64_t shard_index) const
	{
		auto s = append.ScopeAppendingElement();
		append.Object();
		if(shard_index == rvm::GlobalShard)
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
		for(auto it : _State)
		{
			rvm::ContractScopeId csid = it.first;
			rvm::ContractId cid = rvm::CONTRACT_UNSET_SCOPE(csid);
			if ((uint64_t)target_cid != 0 && cid != target_cid)
				continue;
			empty = false;
			SimuState* s = it.second;
			int engine_id = (int)rvm::CONTRACT_ENGINE(cid);
			JsonifyState(csid, append, s, engine[engine_id].pEngine);
		}

		if((uint64_t)target_cid != 0 && empty)
		{
			const rvm::Contract* contract = RvmDeployedContract(engine[(int)rvm::CONTRACT_ENGINE(target_cid)].pEngine, rvm::CONTRACT_SET_BUILD(target_cid, 1));
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
	void ContractStateJsonify(const EngineEntry* engine, rt::Json& append, rvm::ContractId target_cid) const
	{
		for (auto it : _State)
		{
			rvm::ContractId cid = rvm::CONTRACT_UNSET_SCOPE(it.first.Id);
			if ((uint64_t)target_cid != 0 && cid != target_cid)
				continue;
			auto ss = append.ScopeAppendingElement();
			append.Object(
				J(Address) = oxd::SecureAddress::String(it.first.Address.addr)
			);
			SimuState* s = it.second;
			int engine_id = (int)rvm::CONTRACT_ENGINE(cid);
			auto sss = append.ScopeAppendingKey("States");
			append.Array();
			JsonifyState(it.first.Id, append, s, engine[engine_id].pEngine);
		}
	}

	void AddressStateJsonify(const EngineEntry* engine, rt::Json& append, const rt::BufferEx<User>& Users, rvm::ContractId target_cid, int shard_index,const rvm::Address* targetAddr)
	{
		std::map<rvm::Address, rt::BufferEx<std::pair<rvm::ContractScopeId, SimuState*>>, cmpAddress> states_per_addr;
		GroupAddrState(states_per_addr);
		for (auto it : states_per_addr)
		{
			rvm::Address addr = it.first;
			rt::BufferEx<std::pair<rvm::ContractScopeId, SimuState*>> state_arr = it.second;
			auto s = append.ScopeAppendingElement();
			if (targetAddr != nullptr && memcmp(&addr._, &(targetAddr->_), sizeof(rvm::Address)) != 0)
			{
				continue;
			}

			User a({ addr, rvm::ADDRESS_SHARD_DWORD(addr) });
			append.Object((
				J(Address) = oxd::SecureAddress::String(addr),
				J(AddressIndex) = rt::SS() + ('@') + Users.Find(a),
				J(ShardIndex) = rt::SS() + ('#') + shard_index
				));
			auto ss = append.ScopeAppendingKey("States");
			append.Array();
			for (std::pair<rvm::ContractScopeId, SimuState*> p : state_arr)
			{
				rvm::ContractId cid = rvm::CONTRACT_UNSET_SCOPE(p.first);
				if (target_cid != rvm::ContractIdInvalid && cid != target_cid)
					continue;
				SimuState* s = p.second;
				int engine_id = (int)rvm::CONTRACT_ENGINE(cid);
				JsonifyState(p.first, append, s, engine[engine_id].pEngine);
			}
			if (targetAddr != nullptr)
			{
				return;
			}
		}
	}

	bool ScopeStateJsonify(const EngineEntry* engine, rt::Json& append, SimuAddressContract key, uint32_t shardIndex, bool allState) const
	{
		if(allState)
		{
			for (auto it : _State)
			{
				if(it.first.Address.target_size == key.Address.target_size && rvm::CONTRACT_UNSET_SCOPE(key.Id) == rvm::CONTRACT_UNSET_SCOPE(it.first.Id))
				{
					SimuState* s = it.second;
					JsonifyScopeState(append, s, it.first, shardIndex, engine[(int)rvm::CONTRACT_ENGINE(it.first.Id)].pEngine);
				}
			}
		}
		else
		{
			SimuState* s = _State.get(key);
			if(!s)
			{
				return false;
			}
			JsonifyScopeState(append, s, key, shardIndex, engine[(int)rvm::CONTRACT_ENGINE(key.Id)].pEngine);
		}
		return true;
	}

private:
	void JsonifyScopeState(rt::Json& append, SimuState* s, const SimuAddressContract& key, uint32_t shardIndex, rvm::RvmEngine* pEngine) const
	{
		auto ss = append.ScopeAppendingElement();
		rt::String keyStr = ResolveScopeTargetName(key.Address);
		append.Object((
			J(Scope_Target) = keyStr,
			J(ShardIndex) = rt::SS() + ('#') + shardIndex
			));
		auto sss = append.ScopeAppendingKey("States");
		append.Array();
		JsonifyState(key.Id, append, s, pEngine);
	}
	rt::String ResolveScopeTargetName(const ScopeTarget& target) const
	{
		std::string tmp;
		switch (target.target_size)
		{
		case 4:
			tmp = std::to_string(target.u32);
			break;
		case 8:
			tmp = std::to_string(target.u64);
			break;
#pragma warning(push)
#pragma warning(disable:4244)
		case 16:
			((ttmath::UInt<TTMATH_BITS(128)>*) & target.u128)->ToString(tmp);
			break;
		case 32:
			((ttmath::UInt<TTMATH_BITS(256)>*) & target.u256)->ToString(tmp);
			break;
		case 64:
			((ttmath::UInt<TTMATH_BITS(512)>*) & target.u512)->ToString(tmp);
			break;
#pragma warning(pop)
		}
		return rt::String(tmp.c_str());
	}

	void JsonifyState(rvm::ContractScopeId csid, rt::Json& append, SimuState* s, rvm::RvmEngine* pEngine) const
	{
		rvm::ContractId cid = rvm::CONTRACT_UNSET_SCOPE(csid);
		const rvm::Contract* contract = RvmDeployedContract(pEngine, rvm::CONTRACT_SET_BUILD(cid, s->Version));
		if(!contract)
		{
			append.Empty();
			return;
		}
		auto arr_sec = append.ScopeAppendingElement();
		append.Object((J(Contract) = contract->GetName().Str(),
			J(CVID) = (uint64_t)rvm::CONTRACT_SET_BUILD(cid, s->Version)));
		auto sss = append.ScopeAppendingKey("State");
		rvm::StringStreamImpl str_out(append.GetInternalString());
		rvm::ConstData data{ s->Data, s->DataSize };
		RvmStateJsonify(pEngine, rvm::CONTRACT_SET_BUILD(csid, s->Version), &data, &str_out);
	}

	void GroupAddrState(std::map<rvm::Address, rt::BufferEx<std::pair<rvm::ContractScopeId, SimuState*>>, cmpAddress>& m) const
	{
		for(auto it : _State)
		{
			if(rvm::CONTRACT_SCOPE(it.first.Id) != rvm::Scope::Address)
				continue;
			rt::BufferEx<std::pair<rvm::ContractScopeId, SimuState*>> current;
			auto itor = m.find(it.first.Address.addr);
			if(itor != m.end())
			{
				current = itor->second;
			}
			current.push_back({ it.first.Id, it.second});
			m[it.first.Address.addr] = current;
		}
	}

};

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
	auto&		_TempBuffer(){ thread_local rvm::DataBufferImpl _; return _; }

	rt::BufferEx<uint8_t>	_TokensSupplied;  // rvm::Array<rvm::Coins>

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
	bool	ComposeState(rvm::ConstData &out_buf, rvm::ContractInvokeId cid, int loop_index = 0, const rt::String_Ref& existing_state = nullptr);
	auto	ComposeTxn(rvm::ContractInvokeId cid, rvm::OpCode opcode, int loop_index = 0) -> SimuTxn*;
	bool	IsError() const { return _Segments.GetSize() && _Segments.last().IsError(); }
	bool	IsParameterized() const { return _bIsParametrized; }
	bool	IsLoopIndexInvolved() const { return _bLoopIndexInvolved; }
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
