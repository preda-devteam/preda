#pragma warning(push)
#pragma warning(disable:4244)
#include "../../SFC/core/ext/bignum/ttmath/ttmath.h"
#pragma warning(pop)
#include "../../SFC/core/ext/botan/botan.h"
#include "shard_data.h"
#include "simulator.h"
#include "simu_global.h"
#include "core_contracts.h"


namespace oxd
{

ShardStateKeyObj::ShardStateKeyObj(const ShardStateKeyObj& x)
{
	Contract = x.Contract;
	Key.Size = x.Key.Size;
	if(Key.Size)
	{
		Key.Data = _Malloc8AL(uint8_t, Key.Size);
		memcpy((void*)Key.Data, x.Key.Data, Key.Size);
	}
	else
		Key.Data = nullptr;
}

const ShardStateKeyObj& ShardStateKeyObj::operator = (const ShardStateKeyObj& x)
{
	_SafeFree8AL_ConstPtr(Key.Data);

	Contract = x.Contract;
	Key.Size = x.Key.Size;
	if(Key.Size)
	{
		Key.Data = _Malloc8AL(uint8_t, Key.Size);
		memcpy((void*)Key.Data, x.Key.Data, Key.Size);
	}
	else
		Key.Data = nullptr;

	return x;
}

bool ShardStateKeyObj::operator == (const ShardStateKeyObj& x) const
{
	return Contract == x.Contract && Key.Size == x.Key.Size && memcmp(Key.Data, x.Key.Data, Key.Size) == 0;
}

ShardStateKeyObj::ShardStateKeyObj(ShardStateKeyObj&& x)
{
	rt::Copy(*this, x);
	rt::Zero(x);
}

ShardStateKeyObj::~ShardStateKeyObj()
{
	_SafeFree8AL_ConstPtr(Key.Data);
	rt::Zero(*this);
}

PendingTxns::~PendingTxns()
{
	std::lock_guard<std::mutex> lock(_Mutex);
	for (SimuTxn *txn : _Queue)
		txn->Release();
}

bool PendingTxns::Push(SimuTxn* tx)
{
	std::lock_guard<std::mutex> lock(_Mutex);
	bool ret = (_Queue.size() == 0);
	_Queue.push_back(tx);

	return ret;
}


bool PendingTxns::Push(SimuTxn** txns, uint32_t count)
{
	ASSERT(count);

	std::lock_guard<std::mutex> lock(_Mutex);

	bool ret = (_Queue.size() == 0);
	for (uint32_t i=0; i<count; i++, txns++)
	{
		ASSERT((*txns)->IsRelay());
		_Queue.push_back(*txns);
	}

	return ret;
}

bool PendingTxns::Push_Front(SimuTxn* tx)
{
	std::lock_guard<std::mutex> lock(_Mutex);
	bool ret = (_Queue.size() == 0);
	_Queue.push_front(tx);

	return ret;
}

SimuTxn* PendingTxns::Pop()
{
	std::lock_guard<std::mutex> lock(_Mutex);

	if (_Queue.empty())
		return nullptr;

	SimuTxn* txn = _Queue.front();
	_Queue.pop_front();
	return txn;
}

void SimuTxn::Jsonify(rvm::RvmEngine* engine, rt::Json& append) const
{
	append.Object();
	append.AppendKeyWithString("InvokeContextType", rt::EnumStringify(Type));
	if(rvm::Scope scope = GetScope(); scope != rvm::Scope::Global && scope != rvm::Scope::Shard)
	{
		static const rt::SS szTarget("Target");
		rvm::ScopeKeySized kst = rvm::SCOPE_KEYSIZETYPE(scope);
		switch (kst)
		{
		case rvm::ScopeKeySized::Address:
			append.AppendKeyWithString(szTarget, oxd::SecureAddress::String(Target.addr));
			if(TargetIndex >= 0)
				append.AppendKeyWithString("AddressIndex", rt::SS() + ('@') + TargetIndex);
			break;
		case rvm::ScopeKeySized::UInt32:
			append.AppendKeyWithString(szTarget, rt::tos::Number(Target.u32) + "u32");
			break;
		case rvm::ScopeKeySized::UInt64:
			append.AppendKeyWithString(szTarget, rt::tos::Number(Target.u64) + "u64");
			break;
		case rvm::ScopeKeySized::UInt96:
			append.AppendKeyWithString(szTarget, (*(ttmath::UInt<96 / 32>*) & Target.u96).ToString() + "u96");
			break;
		case rvm::ScopeKeySized::UInt128:
			append.AppendKeyWithString(szTarget, (*(ttmath::UInt<128 / 32>*) & Target.u256).ToString() + "u128");
			break;
		case rvm::ScopeKeySized::UInt160:
			append.AppendKeyWithString(szTarget, (*(ttmath::UInt<160 / 32>*) & Target.u256).ToString() + "u160");
			break;
		case rvm::ScopeKeySized::UInt256:
			append.AppendKeyWithString(szTarget, (*(ttmath::UInt<256 / 32>*) & Target.u256).ToString() + "u256");
			break;
		case rvm::ScopeKeySized::UInt512:
			append.AppendKeyWithString(szTarget, (*(ttmath::UInt<512 / 32>*) & Target.u512).ToString() + "u512");
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	if(IsRelay())
	{
		append << ((
			J(Initiator) = oxd::SecureAddress::String(Initiator),
			J(OriginateHeight) = OriginateHeight
		));

		if(OriginateShardIndex == rvm::GlobalShard)
		{
			append << ((J(OriginateShardIndex) = "g"));
		}
		else{
			append << ((J(OriginateShardIndex) = OriginateShardIndex));
		}
		append << ((J(OriginateShardOrder) = OriginateShardOrder));
	}

	if(Type == rvm::InvokeContextType::System)
	{
		append << ((
			J(BuildNum) = 0,
			J(Timestamp) = Timestamp,
			J(Contract) = "chain.deploy",
			J(Function) = "deploy"
			));
	}
	else
	{
		const rvm::Contract* contract = RvmDeployedContract(engine, rvm::CONTRACT_UNSET_SCOPE(Contract));
		if(!contract)
		{
			append.Empty();
			return;
		}
		append << ((
			J(BuildNum) = rvm::CONTRACT_BUILD(Contract),
			J(Timestamp) = Timestamp,
			J(Contract) = contract->GetName().Str(),
			J(Function) = contract->GetFunctionName((uint32_t)Op).Str()
			));
	}

	if (HasNativeTokensSupplied())
	{
		auto& coinsArr = GetNativeTokenSupplied();
		auto walletBody = append.ScopeAppendingKey("TokenSupply");
		append.Array();
		for (uint32_t i = 0; i < coinsArr.GetCount(); i++)
		{
			auto s = append.ScopeAppendingElement();
			coinsArr[i].Jsonify(append);
		}
	}
	
	if(Type != rvm::InvokeContextType::System && ArgsSerializedSize > 0)
	{
		rvm::StringStreamImpl str_out(append.GetInternalString());
		auto s2 = append.ScopeAppendingKey("Arguments");
		rvm::ConstData data({ SerializedData + TokensSerializedSize, ArgsSerializedSize });
		engine->ArgumentsJsonify(Contract, Op, &data, &str_out);
	}
	append << ((J(Height) = Height));

	if(ShardIndex == rvm::GlobalShard)
	{
		append << ((J(ShardIndex) = "g"));
	}
	else{
		append << ((J(ShardIndex) = ShardIndex));
	}
	append << ((J(ShardOrder) = ShardOrder));
}

SimuTxn* SimuTxn::Create(uint32_t args_size, uint32_t assets_size)
{
	uint32_t size = args_size + assets_size + offsetof(SimuTxn, SerializedData);
	auto* ret = (SimuTxn*)_Malloc8AL(uint8_t, size);
	rt::Zero(ret, size);
	ret->ArgsSerializedSize = args_size;
	ret->TokensSerializedSize = assets_size;
	ret->Gas = DefaultGas;

	return ret;
}

SimuTxn* SimuTxn::Clone() const
{
	uint64_t s = GetSize();
	SimuTxn* t = (SimuTxn*)_Malloc8AL(uint64_t, s);
	memcpy(t, this, s);

	return t;
}

void SimuBlock::Release()
{
	for(uint32_t i=0; i<TxnCount; i++)
		Txns[i].Txn->Release();

	_SafeFree8AL_ConstPtr(this);
}

SimuBlock* SimuBlock::Create(uint32_t txn_count)
{
	uint32_t sz = offsetof(SimuBlock, Txns) + sizeof(ConfirmTxn)*txn_count;
	auto* ret = (SimuBlock*)_Malloc8AL(uint8_t, sz);

	rt::Zero(ret, sz);
	return ret;
}

SimuState* SimuState::Create(uint32_t size, rvm::BuildNum version, const void* data)
{
	auto* s = (SimuState*)_Malloc8AL(uint8_t, size + offsetof(SimuState, Data));
	s->Version = version;
	s->DataSize = size;

	if(data)memcpy(s->Data, data, size);
	return s;
}

InputParametrized::Symbols::Symbols(Simulator& s)
	:_random(s)
{
	BindFunction("random", &_random);
}

int64_t InputParametrized::Symbols::Random::operator() (const int64_t& x, const int64_t& y)
{
	ASSERT(y > x);
	int64_t r = y - x + 1;

	_Last = (_Last + _Simulator.GetScriptRandom64())%r;
	return _Last + x;
}

InputParametrized::Segment::Segment(const rt::String_Ref& s, bool is_static, Simulator& simu)
{
	Expression = nullptr;
	if(is_static)
	{
		Type = ST_STATIC;
		String = s;
	}
	else
	{
		if(s == "@random")
		{
			Type = ST_RANDOM_ADDRESS;
		}
		else if(s == "@all")
		{
			Type = ST_INDEXED_ADDRESS;
		}
		else if(s.StartsWith("bigint.random(") && s.Last() == ')')
		{
			Type = ST_RANDOM_BIGINT;
			Digits = (uint32_t)(s.TrimLeft(14).ToNumber<uint32_t>()*3.321928 + 0.99999999);
		}
		else if(s[0] == '@')
		{
			Type = ST_SPECIFIC_ADDRESS;
			UserIndex = s.TrimLeft(1).ToNumber<uint32_t>();
			if(UserIndex >= simu.GetScriptAddressCount())
			{
				_LOG_WARNING("[PRD]: User index out of range: '"<<s<<"'. (Address Count: "<<simu.GetScriptAddressCount()<<')');
				Type = ST_ERROR;
			}
		}
		else
		{
			// Expression
			Expression = _New(ext::Expression<int64_t>(simu.GetScriptEnvSymbols()));
			if(Expression->Compile(s, true))
			{
				Type = ST_EXPRESSION;
			}
			else
			{
				_LOG_WARNING("[PRD]: Expression error: "<<Expression->GetLastError());
				Type = ST_ERROR;
			}
		}
	}
}

bool InputParametrized::Parse(const rt::String_Ref& s)
{
	Empty();
	_bLoopIndexInvolved = false;

	rt::String_Ref seg;
	rt::CharacterSet sep('$');
	bool in_expr = false;

	while(s.GetNextToken(seg, sep))
	{
		if(!seg.IsEmpty())
		{
			if(in_expr)
			{
				rt::String_Ref expr = seg.TrimSpace();
				if(!expr.IsEmpty())
				{
					_Segments.push_back_with(expr, false, _Simulator);

					if(_Segments.Last().IsError())
						return false;

					if(_Segments.Last().IsNonStatic())
						_bIsParametrized = true;

					if(_Segments.Last().IsLoopIndexInvolved())
						_bLoopIndexInvolved = true;
				}
			}
			else
			{
				_Segments.push_back_with(seg, true, _Simulator);
			}
		}

		in_expr = !in_expr;
	}

	return true;
}

void InputParametrized::Empty()
{
	_bIsParametrized = false;
	_Segments.ShrinkSize(0);
}

void InputParametrized::Evaluate(rt::String& out, int loop_index) const
{
	out.Empty();
	for(auto& s : _Segments)
	{
		switch (s.Type)
		{
		case ST_STATIC:
			out += s.String;
			break;
		case ST_RANDOM_ADDRESS:
			{
				auto& addr = _Simulator.GetScriptRandomAddress();
				rt::tos::Base32CrockfordLowercaseOnStack<> str(&addr, sizeof(rvm::ConstAddress));
				out += str;
			}
			break;
		case ST_SPECIFIC_ADDRESS:
			{
				auto& addr = _Simulator.GetScriptAddress(s.UserIndex);
				rt::tos::Base32CrockfordLowercaseOnStack<> str(&addr, sizeof(rvm::ConstAddress));
				out += str;
			}
			break;
		case ST_INDEXED_ADDRESS:
			{
				auto& addr = _Simulator.GetScriptAddress(loop_index);
				rt::tos::Base32CrockfordLowercaseOnStack<> str(&addr, sizeof(rvm::ConstAddress));
				out += str;
			}
			break;
		case ST_EXPRESSION:
			out += rt::tos::Number(s.Expression->Evaluate());
			break;
		case ST_RANDOM_BIGINT:
			{
				auto start = out.GetLength();
				out.SetLength(start + s.Digits);
				out[start] = (_Simulator.GetScriptRandom32()%9) + '1';
				for(uint32_t i=1; i<s.Digits; i++)
					out[i + start] = (_Simulator.GetScriptRandom32()%10) + '0';
			}
			break;
		default:
			break;
		}
	}
}

bool InputParametrized::ComposeState(rvm::ConstData &out_buf, rvm::ContractInvokeId cid, int loop_index, const rt::String_Ref& existing_state)
{
	auto& str = _TempString();
	Evaluate(str, loop_index);

	rt::String derived;
	rvm::ConstString s = { str.Begin(), (uint32_t)str.GetLength() };

	if(!existing_state.IsEmpty())
	{
		rt::JsonObject(existing_state).Derive(str, derived);
		s = { derived.Begin(), (uint32_t)derived.GetLength() };
	}

	auto& data = _TempBuffer();
	data.Empty();

	if (!_Simulator.GetEngine(rvm::CONTRACT_ENGINE(cid))->StateJsonParse(cid, &s, &data, &_Simulator.JsonLog))
		return false;
	
	out_buf = { data.GetData(), data.GetSize() };
	return true;
}

SimuTxn* InputParametrized::ComposeTxn(rvm::ContractInvokeId cid, rvm::OpCode opcode, int loop_index)
{
	auto& str = _TempString();
	Evaluate(str, loop_index);

	_TokensSupplied.ShrinkSize(0);
	auto& data = _TempBuffer();
	data.Empty();

	uint32_t str_len = (uint32_t)str.GetLength();

	// parse assets supplied
	{	// <= (1000dio, 2000 eth)
		int pos = (int)str.FindString("<=");
		if(pos > 0)
		{
			str_len = pos;
			while(str[str_len] <= ' ')str_len--;

			pos = (int)str.FindCharacter('(', pos);
			if(pos < 0)return nullptr;

			int end = (int)str.FindCharacter(')', pos);
			if(end < 0)return nullptr;

			static const rt::CharacterSet sep(",;+");
			static const rt::CharacterSet_Digits dig;

			rt::String_Ref segs[65];
			uint32_t co = rt::String_Ref(&str[pos+1], &str[end]).TrimSpace().Split<true>(segs, sizeofArray(segs), sep);
			if(co == sizeofArray(segs))return nullptr;

			rvm::ArrayMutable<rvm::Coins> assets;
			assets.SetCount(co);

			rvm::CoinsMutable c;
			for(uint32_t i=0; i<co; i++)
			{
				segs[i] = segs[i].TrimSpace();

				auto p = segs[i].FindCharacterReverse(dig);
				if(p < 0)return nullptr;

				p++;
				if(!c.GetModifiableAmount().FromString(segs[i].SubStrHead(p)))
					return nullptr;

				rt::String_Ref token_name = segs[i].SubStr(p).TrimSpace();
				token_name.MakeUpper();
				c.SetId(rvm::TokenIdFromSymbol(token_name));

				auto* coin = rvm::RvmImmutableTypeCompose(c);
				assets.Set(i, coin, rvm::RVMPTR_TAKE);
			}

			typedef rvm::Array<rvm::Coins> TOKENS;
			_TokensSupplied.ChangeSize(TOKENS::GetEmbeddedSize(assets));
			if(!_TokensSupplied.GetSize())return nullptr;

			VERIFY(((TOKENS*)_TokensSupplied.Begin())->Embed(assets) == _TokensSupplied.GetSize());
		}
	}

	// parse invocation args supplied
	rvm::ConstString s = { str.Begin(), str_len };
	if(_Simulator.GetEngine(rvm::CONTRACT_ENGINE(cid))->ArgumentsJsonParse(cid, opcode, &s, &data, &_Simulator.JsonLog))
	{
		auto* txn = SimuTxn::Create(data.GetSize(), (uint32_t)_TokensSupplied.GetSize());
		txn->Type = rvm::InvokeContextType::Normal;
		txn->Contract = cid;
		txn->Op = opcode;
		txn->Timestamp = os::Timestamp::Get();
		txn->Flag = (SimuTxnFlag)0;
		txn->OriginateHeight = 0;
		txn->OriginateShardIndex = 0;
		txn->OriginateShardOrder = 0;
		txn->Height = 0;
		txn->ShardIndex = 0;
		txn->ShardOrder = 0;

		if(txn->TokensSerializedSize)
		{
			ASSERT(txn->TokensSerializedSize == _TokensSupplied.GetSize());
			memcpy(txn->SerializedData, _TokensSupplied.Begin(), _TokensSupplied.GetSize());
		}

		if(txn->ArgsSerializedSize)
		{
			ASSERT(txn->ArgsSerializedSize == data.GetSize());
			memcpy(txn->SerializedData + txn->TokensSerializedSize, data.GetData(), data.GetSize());
		}

		sec::Hash<sec::HASH_SHA256>().Calculate(((char*)txn) + sizeof(rvm::HashValue), txn->GetSize() - sizeof(rvm::HashValue), &txn->Hash);
		return txn;
	}
	else
	{
		_LOG("[PRD] Line " << _Simulator.GetLineNum() << ": Invalid function argument/s")
		return nullptr;
	}
}

bool RvmStateJsonify(rvm::ContractRepository* engine, rvm::ContractInvokeId ciid, const rvm::ConstData* contract_state, rvm::StringStream* json_out)
{
	if(contract_state == nullptr || contract_state->DataSize == 0)
	{
		json_out->Append("{}", 2);
		return true;
	}

	return engine->StateJsonify(ciid, contract_state, json_out);
}

const rvm::Contract* RvmDeployedContract(rvm::RvmEngine* engine, rvm::ContractVersionId cvid)
{
	if(rvm::CONTRACT_ENGINE(cvid) == rvm::EngineId::Core)
	{
		return CoreEngine::Get().GetContract(cvid);
	}
	else
	{
		auto* cdid = Simulator::Get().GetGlobalStates()->GetContractDeployed(cvid);
		if(cdid)return engine->GetContract(&cdid->Module);
	}

	return nullptr;
}

} // namespace oxd
