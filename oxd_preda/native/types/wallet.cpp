#include "wallet.h"


namespace rvm
{

bool CoinsWallet::Withdraw(TokenId aid, CoinsMutable& get, CoinsWalletMutable& residue, bool allow_overflow) const	// residue = this - get
{
	ASSERT(get.IsZero());

	auto& org = GetAmount(aid);
	if(org < get.GetAmount())
	{
		if(allow_overflow)
		{
			get.GetModifiableAmount() = org;
			get.SetId(aid);

			residue.Assign(*this);
			residue.Remove(aid);

			return true;
		}
		else
			return false;
	}

	BigNumMutable res_amount;
	res_amount.Sub(org, get.GetAmount());
	get.SetId(aid);
	ASSERT(res_amount.IsNonNegative());

	residue.Assign(*this);

	if(res_amount.IsZero())
		residue.Remove(aid);
	else
		residue.Set(aid, RvmImmutableTypeCompose(res_amount), RVMPTR_TAKE);

	return true;
}

void CoinsWalletMutable::Deposit(const Coins& x)
{
	if(!x.IsZero())
	{
		auto* exi = Get(x.GetId());
		if(exi)
		{
			BigNumMutable res_amount;
			res_amount.Add(*exi, x.GetAmount());
			Set(x.GetId(), res_amount);
		}
		else
			Set(x.GetId(), x.GetAmount());
	}
}

bool NonFungibleVault::Withdraw(NonfungibleId aid, NonFungibleToken& get, NonFungibleVaultMutable& residue) const	// residue = this - get
{
	ASSERT(get.IsZero());
	residue.Empty();
	new (&residue) NonFungibleVaultMutable(*this);

	if(residue.Remove((uint64_t)aid))
	{
		get.NonFungible = aid;
		return true;
	}
	else
	{
		residue.Empty();
		return false;
	}
}

bool NonFungibleVault::WithdrawSet(const NonFungibleVault& idSet, NonFungibleVaultMutable& residue) const	// residue = this - get
{
	ASSERT(residue.IsEmpty());
	residue.Assign(*this);
	bool result = false;
	idSet.Iterate([&result, &residue](const NonFungibleVault::Range& range){
		result = residue.Remove(range);
		if(!result){
			residue.Empty();
			return false;
		}
		return true;
	});
	return result;
}

bool NonFungibleVault::WithdrawRange(const NonFungibleTokenRanged& id_range, NonFungibleVaultMutable &residue) const
{
	ASSERT(residue.IsEmpty());
	residue.Assign(*this);
	return residue.Remove(NonFungibleVaultMutable::T_RANGE{});
}

void NonFungibleVaultMutable::Deposit(const NonFungibleVault& x)
{
	x.Iterate([this](const NonFungibleVault::Range& range){
		Insert(range);
	});
}

void NonFungibleVaultMutable::Deposit(const NonFungibleToken& x)
{
	if(!x.IsZero())
	{
		Insert((uint64_t)x.NonFungible);
	}
}

void NonFungibleVaultMutable::Deposit(const NonFungibleTokenRanged& x)
{
	if(!x.IsZero())
	{
		Insert(_SC::T_RANGE{(uint64_t)x.NonFungibleStart, x.Count});
	}
}

void NonFungibleVaultMutable::Mint(NonfungibleId nf_base_id, uint32_t pn)
{
	ASSERT(_details::NONFUNGIBLE_PIECEIDX(nf_base_id) == 0);
	ASSERT(pn <= _details::NONFUNGIBLE_ID_PIECE_MAXCOUNT(nf_base_id));
	if(pn == 0){
		Insert((uint64_t)nf_base_id);
	}
	else
	{
		_details::ConsecutiveRange<uint64_t, LONGLONG> in_range({(uint64_t)nf_base_id, (LONGLONG)pn});
		Insert(in_range);
	}
}

NonFungibleArtworkData::NonFungibleArtworkData(const rt::String_Ref& name_str)
{
	if(name_str.GetLength() >= RVM_STRING_SIZEMAX)goto FAILED;

	rt::Zero(*this);
	*(rt::String_Ref*)this = name_str;

	if(name_str.IsEmpty())goto FAILED;

	_PieceMode = *(TxCoreNonFungibleMode*)name_str.Begin();

	if((_PieceMode&NFMODE_PIECE_COUNT_BITMASK) == 1)
		goto FAILED;

	{
		const uint8_t* base = (const uint8_t *)_p;
		const uint8_t* end = (const uint8_t*)name_str.End();
		const uint8_t* p = base + sizeof(TxCoreNonFungibleMode);

		//TimeStamp comes before name
		p += sizeof(uint64_t);

		if(IsHashed())
			p += sizeof(HashValue);
		
		if(IsNamed())
		{
			if(p + sizeof(NAME_LEN) >= end)goto FAILED;
			p += sizeof(NAME_LEN) + (*(NAME_LEN*)p);
		}

		if(IsPieceHashed() || IsPieceNamed())
		{
			uint32_t co = GetPieceCount();
			if(co > NONTRIVIAL_PIECE_MAXCOUNT)
				goto FAILED;

			for(uint32_t i = 0; i < co; i++)
			{
				_PieceOffsets[i] = (uint32_t)(p - base);
				if(IsPieceHashed())p += sizeof(HashValue);

				
				if(IsPieceNamed())
				{
					if(p + sizeof(NAME_LEN) >= end)goto FAILED;
					p += sizeof(NAME_LEN) + (*(NAME_LEN*)p);
				}
			}
		}
		_SignatureOffset = (uint16_t)(p - base);
	}

	return;

FAILED:
	_PieceMode = NFMODE_ZERO;
}

bool NonFungibleArtworkData::Compose(rt::String& namespec, const rt::String_Ref& json_str, uint64_t timestamp, oxd::SecSuiteId ssid, const void *sk, uint32_t sk_size)
{
	namespec.SetLength(sizeof(TxCoreNonFungibleMode));
	TxCoreNonFungibleMode mode = NFMODE_ZERO;

	namespec += rt::DS(timestamp);

	rt::String_Ref str;
	rt::String s;
	HashValue hash;
	NAME_LEN strleng = 0;

	rt::JsonObject json(json_str);
	rt::String_Ref series = json.GetValue("series");
	str = json.GetValue("hash");
	if(!str.IsEmpty())
	{
		if(((oxd::SecDataBlock<RVM_HASH_SIZE>&)hash).FromString(str))
		{
			mode = (TxCoreNonFungibleMode)(mode | NFMODE_HASHED);
			namespec += rt::DS(hash);
		}
		else
			return false;
	}
	

	s = json.GetValueUnescaped("name");
	if(!s.IsEmpty())
	{
		if(s.GetLength() <= NFMODE_NAME_MAXLEN)
		{
			mode = (TxCoreNonFungibleMode)(mode | NFMODE_NAMED);
			strleng = (NAME_LEN)s.GetLength();
			namespec += rt::DS(strleng) + s;
		}
		else
			return false;
	}

	if((mode & (NFMODE_HASHED | NFMODE_NAMED)) == 0)
		return false;

	if(!series.IsEmpty())
	{
		if(series[0] == '[')
		{	// the length of the array is the amount of issuance
			rt::JsonArray pieces(series);
			rt::String_Ref piece;
			if(!pieces.GetNextObject(piece))
				return false;

			rt::JsonObject json(piece);
			str = json.GetValue("hash");
			if(!str.IsEmpty())
				if(((oxd::SecDataBlock<RVM_HASH_SIZE>&)hash).FromString(str))
				{	
					mode = (TxCoreNonFungibleMode)(mode | NFMODE_PIECE_HASHED);
					namespec += rt::DS(hash);
				}
				else
					return false;

			s = json.GetValueUnescaped("name");
			if(!s.IsEmpty())
				if(s.GetLength() <= NFMODE_NAME_MAXLEN)
				{
					mode = (TxCoreNonFungibleMode)(mode | NFMODE_PIECE_NAMED);
					strleng = (NAME_LEN)s.GetLength();
					namespec += rt::DS(strleng) + s;
				}
				else
					return false;

			if((mode & (NFMODE_PIECE_HASHED|NFMODE_PIECE_NAMED)) == 0)
				return false;

			mode = (TxCoreNonFungibleMode)(mode + 1);
			if((mode&NFMODE_PIECE_COUNT_BITMASK) > NONTRIVIAL_PIECE_MAXCOUNT)
				return false;

			while(pieces.GetNextObject(piece))
			{
				mode = (TxCoreNonFungibleMode)(mode + 1);
				if((mode&NFMODE_PIECE_COUNT_BITMASK) > NONTRIVIAL_PIECE_MAXCOUNT)
					return false;

				rt::JsonObject json(piece);

				str = json.GetValue("hash");
				if(mode&NFMODE_PIECE_HASHED)
				{
					if(str.IsEmpty() || !((oxd::SecDataBlock<RVM_HASH_SIZE>&)hash).FromString(str))
						return false;
					namespec += rt::DS(hash);
				}
				else
					if(!str.IsEmpty())
						return false;
			
				s = json.GetValue("name");
				if(mode&NFMODE_PIECE_NAMED)
				{
					if(s.IsEmpty() || s.GetLength() > NFMODE_NAME_MAXLEN)
						return false;
					strleng = (uint8_t)s.GetLength();
					namespec += rt::DS(strleng) + s;
				}
				else if(!s.IsEmpty())return false;
			}

			if((mode&NFMODE_PIECE_COUNT_BITMASK) == 1)
				return false;
		}
		else
		{
			// series should be a number, indicate the amount of issuance
			int amount;
			series.ToNumber(amount);
			if(amount != 1)
			{
				if(amount > 1 && amount <= NFMODE_PIECE_COUNT_BITMASK)
					mode = (TxCoreNonFungibleMode)((mode& (~NFMODE_PIECE_COUNT_BITMASK)) | amount);
				else
					return false;
			}
		}
	}

	if(ssid != oxd::SEC_SUITE_NONE)
	{
		mode = (TxCoreNonFungibleMode)(mode | NFMODE_ARTIST_SIGNED);
		*(TxCoreNonFungibleMode*)namespec.Begin() = mode;

		oxd::SecuritySuite ss(ssid);
		if(!ss.IsValid() || ss.PrivateKeySize() != sk_size)return false;

		LPBYTE pk = (LPBYTE)_alloca(ss.PublicKeySize());
		ss.DerivePublicKey(sk, pk);

		namespec += rt::DS(&ssid, 1) + rt::DS(pk, ss.PublicKeySize());

		uint32_t sign_size = ss.SignatureSize();
		LPBYTE sign = (LPBYTE)_alloca(sign_size);

		ss.Sign(sk, namespec.Begin(), (UINT)namespec.GetLength(), sign);
		namespec += rt::DS(sign, sign_size);
	}
	else
		*(TxCoreNonFungibleMode*)namespec.Begin() = mode;

	return true;
}

void NonFungibleArtworkData::Jsonify(rt::Json& append) const
{
	append.Object((
		J_IF(IsNamed(), J(name) = rt::JsonEscapeString(GetPrimaryName())),
		J_IF(IsHashed(), J(hash) = oxd::b32str(GetPrimaryHash())),
		J(timestamp) = GetTimeStamp()
	));

	if(IsArtistSigned())
	{
		Address u;
		GetArtistAddress(u);
		append.AppendKeyAndEscapedValue("signer", oxd::b32address(u));
	}

	if(GetPieceCount())
	{
		if(IsPieceNamed() || IsPieceHashed())
		{
			auto s = append.ScopeAppendingKey("series");
			append.Array();
			for(uint32_t i=0; i<GetPieceCount(); i++)
			{
				append.AppendElement((
					J_IF(IsPieceNamed(), J(name) = rt::JsonEscapeString(GetPieceName(i))),
					J_IF(IsPieceHashed(), J(hash) = oxd::b32str(GetPieceHash(i)))
					));
			}
		}
		else
			append<<(J(series) = GetPieceCount());
	}
}

rt::String_Ref NonFungibleArtworkData::GetPrimaryName() const
{
	ASSERT(!IsEmpty());
	ASSERT(IsNamed());
	return ((NF_String*)(_p + sizeof(TxCoreNonFungibleMode) + (IsHashed()?sizeof(HashValue):0) + sizeof(uint64_t)))->Str();
}

rt::String_Ref NonFungibleArtworkData::GetPrimaryNameSizeRestricted() const
{
	rt::String_Ref ret = GetPrimaryName();
	if(ret.GetLength() > RVM_NONFUNGIBLE_PRIMARY_SIZEMAX)
		return ret.SubStr(0, RVM_NONFUNGIBLE_PRIMARY_SIZEMAX).TrimTrailingIncompleteUTF8Character();
	else
		return ret;
}

const HashValue& NonFungibleArtworkData::GetPrimaryHash() const
{
	ASSERT(!IsEmpty());
	ASSERT(IsHashed());
	return *((HashValue*)(_p + sizeof(TxCoreNonFungibleMode) + sizeof(uint64_t)));
}

rt::String_Ref NonFungibleArtworkData::GetPieceName(uint32_t i) const
{
	ASSERT(!IsEmpty());
	ASSERT(IsPieceNamed());
	ASSERT(i<GetPieceCount());

	auto p = _p + _PieceOffsets[i];

	if(IsPieceHashed())p += sizeof(HashValue);
	return ((NF_String*)(p))->Str();
}

const HashValue& NonFungibleArtworkData::GetPieceHash(uint32_t i) const
{
	ASSERT(!IsEmpty());
	ASSERT(IsPieceNamed());
	ASSERT(i<GetPieceCount());

	return *(HashValue*)(_p + _PieceOffsets[i]);
}
uint64_t NonFungibleArtworkData::GetTimeStamp() const
{
	ASSERT(!IsEmpty());
	return *(uint64_t*)(_p + sizeof(TxCoreNonFungibleMode));
}
bool NonFungibleArtworkData::GetArtistAddress(Address& addr) const
{
	ASSERT(!IsEmpty());
	ASSERT(IsArtistSigned());

	oxd::SecuritySuite ss((oxd::SecSuiteId&)_p[_SignatureOffset]);
	if(!ss.IsValid())return false;

	ss.DeriveAddress(_p + _SignatureOffset + 1, (oxd::SecureAddress*)&addr);
	return true;
}

bool NonFungibleArtworkData::VerifyArtistSignature() const
{
	ASSERT(!IsEmpty());
	ASSERT(IsArtistSigned());

	if(_SignatureOffset >= _len)return false;

	auto* p = _p + _SignatureOffset;
	oxd::SecSuiteId ssid = (oxd::SecSuiteId)*(BYTE*)p++;
	static_assert(sizeof(oxd::SecSuiteId) == 1, "sizeof(SecSuiteId) should be 1");

	oxd::SecuritySuite ss(ssid);
	if(!ss.IsValid())return false;

	int pk_size = ss.PublicKeySize();
	int sig_size = ss.SignatureSize();

	if(pk_size + sig_size != End() - p)return false;

	return ss.VerifySignature(p, p + pk_size, _p, _SignatureOffset + 1 + pk_size);
}

bool NonFungibleArtworkData::VerifySize() const
{
	if(IsEmpty())return false;
	if(IsArtistSigned())
	{
		if(_SignatureOffset > _len)return false;

		auto* p = _p + _SignatureOffset;
		oxd::SecSuiteId ssid = (oxd::SecSuiteId)*(BYTE*)p++;

		oxd::SecuritySuite ss(ssid);
		if(!ss.IsValid())return false;

		int pk_size = ss.PublicKeySize();
		int sig_size = ss.SignatureSize();

		if(pk_size + sig_size != End() - p)return false;
		return true;
	}
	else
		return _SignatureOffset == _len;
}

} // namespace rvm
