#include <functional>
#include "../../../oxd_libsec/oxd_libsec.h"
#include "typetraits.h"
#include "abi_def_impl.h"


namespace rvm
{

ShardIndexString::ShardIndexString(uint32_t si): rt::tos::Number(si)
{
	if(si == rvm::GlobalShard){ _p[0] = 'g'; _len = 1; }
}

char* StringStreamImpl::AppendBegin(uint32_t over_estimated_len)
{
	ASSERT(_last_append_pos == -1);
	_last_append_pos = _str->GetLength();
	return _str->Extend(over_estimated_len);
}

void StringStreamImpl::AppendEnd(uint32_t finalized_len)
{
	ASSERT(_last_append_pos >= 0);
	_str->SetLength(_last_append_pos + finalized_len);
	_last_append_pos = -1;
}

rvm::ConstString StringStreamImpl::GetString()
{
	ASSERT(_last_append_pos == -1);
	return { _str->Begin() + _base, (uint32_t)(_str->GetLength() - _base) };
}

StringStreamImpl::StringStreamImpl(rt::String& str)
{
	_base = str.GetLength();
	_last_append_pos = -1;
	_str = &str;
}

StringStreamImpl::StringStreamImpl()
{
	_base = 0;
	_last_append_pos = -1;
	_str = &_intl;
}

uint8_t* DataBufferImpl::SetSize(uint32_t len)
{
	_Data.ChangeSize(len);
	return _Data;
}

DataBufferImpl&	DataBufferImpl::Empty()
{
	_Data.ShrinkSize(0);
	return *this;
}

ConstData DataBufferImpl::GetRvmConstData() const
{
	return { _Data.Begin(), (uint32_t)_Data.GetSize() };
}

void BlockchainRuntime_DebugPrint(rvm::DebugMessageType type, const rvm::ConstString* text, const rvm::ExecutionState* ctx, const rvm::Contract* contract, int32_t line)
{
	ASSERT(text);

	thread_local rt::String log;
	log = rt::SS("[PRD]");
	static const rt::SS sep(": ");
	rt::tos::Timestamp<true,false> timestamp(os::Timestamp::LocalDateTime());
	if(contract && ctx)
	{

		rvm::ContractInvokeId cid = ctx->GetContractId();
		auto scope = rvm::CONTRACT_SCOPE(cid);

		rt::String addr;
		rt::String initiatorAddr;
		if (ctx->GetInvokeType() == rvm::InvokeContextType::RelayInbound)
		{
			initiatorAddr = ' ' + oxd::SecureAddress::String(*ctx->GetInitiator(), true);
		}
		
		if (scope == rvm::Scope::Address)
		{
			auto target = ctx->GetScopeTarget();
			ASSERT(target.Size == sizeof(rvm::Address));
			addr = rt::SS(" ") + oxd::SecureAddress::String(*(rvm::Address*)target.Data, true);
		}
		log += sep + rt::SS("[") + timestamp + rt::SS("]") + addr + rt::SS(" [#") + ShardIndexString(ctx->GetShardIndex()) + rt::SS("] [h:") + ctx->GetBlockHeight() + ']';
		if (ctx->GetInvokeType() == rvm::InvokeContextType::RelayInbound)
		{
			log += rt::SS(" <=") + initiatorAddr + rt::SS(" [#") + ShardIndexString(ctx->GetOriginatedShardIndex()) + rt::SS("] [h:") + ShardIndexString((uint32_t)ctx->GetOriginatedBlockHeight()) + ']';
		}
		log += ' ' + contract->GetName().Str();
		if(line >= 0)
		{
			log += rt::SS(", line ") + line;
		}
	}

	switch(type)
	{
	case rvm::DebugMessageType::Verbose:		_LOG_VERBOSE(log<<sep<<text->Str()); break;
	case rvm::DebugMessageType::Informational:	_LOG(log<<sep<<text->Str()); break;
	case rvm::DebugMessageType::Highlight:		_LOG_HIGHLIGHT(log<<sep<<text->Str()); break;
	case rvm::DebugMessageType::Warning:		_LOG_WARNING(log<<sep<<text->Str()); break;
	case rvm::DebugMessageType::Error:			_LOG_ERROR(log<<sep<<text->Str()); break;
	default: ASSERT(0);
	}
}

void Signature_Jsonify(rt::Json& json, const rt::String_Ref& name, const rt::String_Ref& signature, bool structSig)
{
	rt::String_Ref var[1024];
	uint32_t i = 2;

	std::function<void(rt::String&, uint32_t)> typeLayoutToStr = [&var, &i, &typeLayoutToStr](rt::String& varType, uint32_t size)
	{
		static const rt::SS sz_array("array");
		static const rt::SS sz_map("map");
		rt::String_Ref curType = var[i++];
		if (curType == sz_array && i + 2 <= size)
		{
			varType += sz_array + '(';
			typeLayoutToStr(varType, size);
			varType += ')';
		}
		else if (curType == sz_map && i + 3 <= size)
		{
			varType += sz_map + '(' + var[i++] + ':';
			typeLayoutToStr(varType, size);
			varType += ')';
		}
		else
		{
			varType += curType;
		}
	};
	auto getVarNameType = [&var, &i, &typeLayoutToStr](rt::String_Ref& varName, rt::String& varType, uint32_t size)
	{
		typeLayoutToStr(varType, size);
		varName = var[i++];
	};

	//stateSig example
	//struct 6 address controller uint32 current_case array chsimu.Ballot.Proposal proposals chsimu.Ballot.BallotResult last_result map int32 chsimu.Ballot.BallotResult test uint32 shardGatherRatio
	//struct [number of var] [var #0's member data type] (inner data type if array or map) [var #0's member identifier] [var #1's member data type] [var #1's member identifier] 
	uint32_t co = signature.Split<true>(var, sizeofArray(var), " ");
	if(co < 2)return;
	int32_t numMember = var[1].ToNumber<int32_t>();
	rt::String_Ref varName;
	rt::String varType;
	for(; i < co; )
	{
		if(structSig)
		{
			json.Object(J(scope)=name);
			auto ss = json.ScopeAppendingKey("layout");
			json.Array();
			for(int32_t j = 0; j < numMember; j++)
			{
				getVarNameType(varName, varType, co);
				auto sss = json.ScopeAppendingElement();
				json.Object((J(identifier) = varName, J(dataType) = varType));
				varType.Empty();
			}
		}
		else
		{
			for(int32_t j = 0; j < numMember; j++)
			{
				getVarNameType(varName, varType, co);
				auto sss = json.ScopeAppendingElement();
				json.Object((J(name) = varName, J(scope) = name, J(dataType) = varType));
				varType.Empty();
			}
		}
	}
}

void CompiledModules_Jsonify(rt::Json& json, rvm::CompiledModules* built)
{
	ASSERT(built);
	json.Array();

	uint32_t count = built->GetCount();
	for(uint32_t i=0; i<count; i++)
	{
		auto contract_scope = json.ScopeAppendingElement();
		auto* contract = built->GetContract(i);
		auto name = contract->GetName();
		auto flag = contract->GetFlag();
		json.Object((
			J(contract) = name.Str(),
			J(engine) = rt::EnumStringify(built->GetEngineId()),
			J(hash) = rt::tos::Base32CrockfordLowercaseOnStack<>(*contract->GetModuleID()),
			J(finalized) = (bool)(flag&rvm::ContractFlag::DeployFinalized)
		));

		{	// interface implemented
			auto scpdef_scope = json.ScopeAppendingKey("ImplmentedInterfaces");
			json.Array();

			uint32_t if_co = contract->GetInterfaceImplementedCount();
			for(uint32_t i=0; i<if_co; i++)
			{
				auto* intf = contract->GetInterfaceImplemented(i);
				if(intf)
					json.AppendElement(intf->GetFullName().Str());
			}
		}

		std::unordered_map<uint32_t, rt::String> scope_names;
		bool has_scattered_maps = false;
		uint32_t scope_count = contract->GetScopeCount();
		{
			auto stateVar_scope = json.ScopeAppendingKey("StateVariables");
			json.Array();
			for(uint32_t s = 0; s < scope_count; s++)
			{
				StringStreamImpl stateSig;
				auto scope = contract->GetScope(s);
				contract->GetStateSignature(scope, &stateSig); 
				Signature_Jsonify(json, contract->GetScopeName(s).Str(), stateSig, false);
			}
		}

		{	// scope definitions
			auto scpdef_scope = json.ScopeAppendingKey("Scopes");
			json.Object();

			// involved scopes
			uint32_t scope_count = contract->GetScopeCount();
			for(uint32_t s=0; s<scope_count; s++)
			{
				auto scope = contract->GetScope(s);
				if(rvm::SCOPE_TYPE(scope) == rvm::ScopeType::Contract)
				{
					auto scope_name = contract->GetScopeName(s);
					scope_names[(uint32_t)scope] = scope_name.Str();

					auto flag = contract->GetScopeFlag(s);
					if(scope <= rvm::Scope::Address && flag == (rvm::ScopeFlag)0)
						continue;

					json.AppendKey(scope_name.Str(), rt::EnumStringify(flag));
				}
				else has_scattered_maps = true;
			}
		}

		{	// scattered maps
			auto scpdef_scope = json.ScopeAppendingKey("ScatteredMaps");
			json.Object();
			if(has_scattered_maps)
			{
				uint32_t scope_count = contract->GetScopeCount();
				for(uint32_t s=0; s<scope_count; s++)
				{
					auto scope = contract->GetScope(s);
					if(rvm::SCOPE_TYPE(scope) > rvm::ScopeType::Contract)
					{
						rt::String_Ref prefix = 
							(rvm::SCOPE_TYPE(scope) > rvm::ScopeType::ScatteredMapOnGlobal)?"Shard":"Global";

						auto scope_name = contract->GetScopeName(s);
						json.AppendKey(scope_name.Str(), prefix + rt::SS("Map:") + rt::EnumStringify(rvm::SCOPE_KEYSIZETYPE(scope)));
					}
				}
			}
		}

		{
			auto struct_scope = json.ScopeAppendingKey("Structs");
			json.Array();
			uint32_t struct_count = contract->GetStructCount();
			for(uint32_t i = 0; i < struct_count; i++)
			{
				StringStreamImpl structSig;
				contract->GetStructSignature(i, &structSig);
				rvm::ConstString str = contract->GetStructName(i);
				Signature_Jsonify(json.ScopeAppendingElement(), str.Str(), structSig, true);
			}
		}

		{	// enum
			auto enum_scope = json.ScopeAppendingKey("Enumerables");
			json.Array();
			uint32_t enum_count = contract->GetEnumCount();
			for(uint32_t i = 0; i < enum_count; i++)
			{
				auto s = json.ScopeAppendingElement();
				json.Object((J(name) = contract->GetEnumName(i).Str()));
				auto enum_scope = json.ScopeAppendingKey("Value");
				rt::String tmp;
				StringStreamImpl structSig(tmp);
				contract->GetEnumSignature(i, (rvm::StringStream*)&structSig);
				rt::String_Ref enumator[1024];
				uint32_t co = tmp.Split<true>(enumator, sizeofArray(enumator), ",");
				json.Array();
				for(uint32_t i = 0; i < co; i++)
				{
					json.AppendElement(enumator[i]);
				}
			}
		}

		auto json_if = [&scope_names](const rvm::Interface* ifc, rt::Json& json){
			uint32_t func_count = ifc->GetFunctionCount();
			json.Array();
			for(uint32_t i=0; i<func_count; i++)
			{
				auto arr_scope = json.ScopeAppendingElement();
				auto scope = ifc->GetFunctionScope(i);
				auto op = ifc->GetFunctionOpCode(i);
				auto flag = ifc->GetFunctionFlag(i);
				json.Object(((J(name) = ifc->GetFunctionName(i).Str()), (J(flag) = rt::EnumStringify(flag)), (J(scope) = scope_names[(uint32_t)scope]), (J(opcode) = (int)op)));
			}
		};

		{	// interfaces
			auto if_scope = json.ScopeAppendingKey("Interfaces");
			json.Object();
			uint32_t if_count = contract->GetInterfaceCount();
			for(uint32_t i=0; i<if_count; i++)
			{
				auto* ifc = contract->GetInterface(i);
				auto func_scope = json.ScopeAppendingKey(ifc->GetName().Str());
				json.Object((
					J(Slot) = (int)contract->GetInterfaceSlot(i)
				));
				json_if(ifc, json);
			}
		}

		{	// functions
			auto if_scope = json.ScopeAppendingKey("Functions");
			json_if(contract, json);
		}
	}
}

void ScopeKey_Jsonify(rt::Json& json, ScopeKeySized type, const ScopeKey& scope)
{
#define ITERATE(kst)	case ScopeKeySized::kst:										\
							{	typedef kst T;											\
								ASSERT(sizeof(T) == scope.Size);						\
								rvm::TypeTraits<T>::Jsonify(*(T*)scope.Data, json);		\
							}															\
							break;

	switch((ScopeKeySized)((int)type&(int)ScopeKeySized::BaseTypeBitmask))
	{
		ITERATE(Address);
		ITERATE(UInt32);
		ITERATE(UInt64);
		ITERATE(UInt96);
		ITERATE(UInt128);
		ITERATE(UInt160);
		ITERATE(UInt256);
		ITERATE(UInt512);
	default:
		break;
	}
#undef ITERATE
}

void ScopeKey_Stringify(rt::String& append, ScopeKeySized type, const ScopeKey& scope)
{
#define ITERATE(kst)	case ScopeKeySized::kst:										\
							{	typedef kst T;											\
								ASSERT(sizeof(T) == scope.Size);						\
								rvm::TypeTraits<T>::ToString(*(T*)scope.Data, append);	\
							}															\
							break;

	switch((ScopeKeySized)((int)type&(int)ScopeKeySized::BaseTypeBitmask))
	{
		ITERATE(Address);
		ITERATE(UInt32);
		ITERATE(UInt64);
		ITERATE(UInt96);
		ITERATE(UInt128);
		ITERATE(UInt160);
		ITERATE(UInt256);
		ITERATE(UInt512);
	default:
		break;
	}
#undef ITERATE
}

} // namespace rvm