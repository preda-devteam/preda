#include "shard_data.h"
#include "simulator.h"
#include "simu_global.h"


namespace oxd
{
namespace _details
{
const rvm::Contract* GetDeployedContract(rvm::RvmEngine* engine, rvm::ContractId cid, rvm::BuildNum version)
{
	auto* cdid = Simulator::Get().GetGlobalState()->GetContractDeploymentIdentifier(cid, version);
	return cdid?engine->GetContract(cdid):nullptr;

}
} // namespace _details

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
	LPSIMUTXN txn;
	while(_Queue.Pop(txn))
		txn->Release();
}

bool PendingTxns::Push(SimuTxn* tx)
{
	bool ret = (_Queue.GetSize() == 0);
	_Queue.Push(tx);

	return ret;
}

bool PendingTxns::Push(SimuTxn** txns, uint32_t count)
{
	ASSERT(count);

	bool ret = (_Queue.GetSize() == 0);
	for(uint32_t i=0; i<count; i++, txns++)
	{
		ASSERT((*txns)->IsRelay());
		_Queue.Push(*txns);
	}

	return ret;
}

SimuTxn* PendingTxns::Pop()
{
	LPSIMUTXN txn;
	return _Queue.Pop(txn)?txn:nullptr;
}
#ifdef _VIZ
void SimuTxn::Jsonify(rvm::RvmEngine* engine, const rvm::ChainState* ps, rt::Json& append, rvm::InvokeResult* result) const
{
	append.AppendKeyAndEscapedValue("InvokeContextType", rt::EnumStringify(Type));
	char addr_buf[rvm::_details::ADDRESS_BASE32_LEN];

	if(GetScope() == rvm::Scope::Address)
	{
		rvm::_details::ADDRESS_TO_STRING(Target, addr_buf);
		append.AppendKeyAndEscapedValue("Target", rt::String(addr_buf, rvm::_details::ADDRESS_BASE32_LEN) + rt::SS(":") + 
															oxd::SecuritySuite::IdToString(Target._SSID));
		append.AppendKeyAndEscapedValue("AddressIndex", rt::String('@') + Target_index);
	}
	else if(IsRelay())
	{
		rvm::_details::ADDRESS_TO_STRING(Initiator, addr_buf);
		append << ((
			J(Initiator) = rt::String(addr_buf, rvm::_details::ADDRESS_BASE32_LEN) + rt::SS(":") + oxd::SecuritySuite::IdToString(Initiator._SSID),
			J(OriginateHeight) = OriginateHeight));
		if(OriginateShardIndex == 65535)
		{
			append << ((J(OriginateShardIndex) = "g"));
		}
		else{
			append << ((J(OriginateShardIndex) = OriginateShardIndex));
		}
		append << ((J(OriginateShardOrder) = OriginateShardOrder));
	}

	const rvm::Contract* contract = _details::GetDeployedContract(engine, rvm::_details::CONTRACT_UNSET_SCOPE(Contract), BuildNum);
	if(!contract)
	{
		append.Empty();
		return;
	}
	append << ((
		J(BuildNum) = BuildNum,
		J(Timestamp) = Timestamp,
		J(Contract) = contract->GetName().Str(),
		J(Function) = contract->GetFunctionName((uint32_t)Op).Str()
		));
	if(result)
	{
		append << ((J(InvokeResult) = rt::EnumStringify(result->Code)));
	}
	if(ArgsSerializedSize > 0)
	{
		StreamByString _((rt::String&)append);
		auto s2 = append.ScopeAppendingKey("Arguments");
		rvm::ConstData data({ ArgsSerializedData, ArgsSerializedSize });
		engine->ArgumentsJsonify(BuildNum, Contract, Op, &data, &_, ps);
	}
	append << ((J(Height) = Height));

	if(ShardIndex == 65535)
	{
		append << ((J(ShardIndex) = "g"));
	}
	else{
		append << ((J(ShardIndex) = ShardIndex));
	}
	append << ((J(ShardOrder) = ShardOrder));
}
#endif
SimuTxn* SimuTxn::Create(uint32_t args_size)
{
	auto* ret = (SimuTxn*)_Malloc8AL(uint8_t, args_size + offsetof(SimuTxn, ArgsSerializedData));
	ret->ArgsSerializedSize = args_size;

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
				_LOG_WARNING("[BC]: user index out of range: '"<<s<<"'. (Address Count: "<<simu.GetScriptAddressCount()<<')');
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
				_LOG_WARNING("[BC]: expression error: "<<Expression->GetLastError());
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

rvm::ConstData InputParametrized::ComposeState(rvm::BuildNum build_num, rvm::ContractScopeId cid, int loop_index)
{
	auto& str = _TempString();
	Evaluate(str, loop_index);

	auto& data = _TempBuffer();
	data.Empty();

	rvm::ConstString s = { str.Begin(), (uint32_t)str.GetLength() };
	if(_Simulator.GetEngine(rvm::_details::CONTRACT_ENGINE(cid))->StateJsonParse(build_num, cid, &s, &data, *_Simulator.GetGlobalShard(), &_Simulator.JsonLog))
	{
		return { data.GetData(), data.GetSize() };
	}
	else
	{
		return { nullptr, 0 };
	}
}

SimuTxn* InputParametrized::ComposeTxn(rvm::BuildNum build_num, rvm::ContractScopeId cid, rvm::OpCode opcode, int loop_index)
{
	auto& str = _TempString();
	Evaluate(str, loop_index);

	auto& data = _TempBuffer();
	data.Empty();

	rvm::ConstString s = { str.Begin(), (uint32_t)str.GetLength() };
	if(_Simulator.GetEngine(rvm::_details::CONTRACT_ENGINE(cid))->ArgumentsJsonParse(build_num, cid, opcode, &s, &data, *_Simulator.GetGlobalShard(), &_Simulator.JsonLog))
	{
		auto* txn = SimuTxn::Create(data.GetSize());
		txn->Type = rvm::InvokeContextType::Normal;
		txn->Contract = cid;
		txn->Op = opcode;
		txn->BuildNum = build_num;
		txn->Timestamp = os::Timestamp::Get();
		txn->Flag = (SimuTxnFlag)0;
		txn->OriginateHeight = 0;
		txn->OriginateShardIndex = 0;
		txn->OriginateShardOrder = 0;
		txn->Height = 0;
		txn->ShardIndex = 0;
		txn->ShardOrder = 0;
		ASSERT(txn->ArgsSerializedSize == data.GetSize());
		memcpy(txn->ArgsSerializedData, data.GetData(), data.GetSize());

		return txn;
	}
	else
	{
		_LOG("[PRD] Line " << _Simulator.GetLineNum() << ": Invalid function argument/s")
		return nullptr;
	}
}

} // namespace oxd
