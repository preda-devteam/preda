#pragma once
#include "big_num.h"


namespace rvm
{
class Coins;
class CoinsMutable;
class NonFungibleToken;
class NonFungibleVault;
class NonFungibleVaultMutable;

// representing fungible tokens
#pragma pack(push, 1)
class Coins
{
	TYPETRAITS_DECLARE_NON_POD;
	RVM_IMMUTABLE_TYPE(Coins)

	friend class Shard;
	friend class CoinsMutable;

protected:
	TokenId		CoinId;		// what coin it is
	BigNum		Amount;		// MOVE semantics, never be copied

public:
	Coins(decltype(0) x);
	TokenId		GetId() const { return CoinId; }
	auto		GetSymbol() const { return rt::DS(CoinId).GetLengthRecalculated(); }
	auto&		GetAmount() const { return Amount; }
	bool		IsZero() const { return CoinId == TokenIdInvalid || Amount.IsZero(); }
	void		Jsonify(rt::Json &append) const;
	UINT		GetEmbeddedSize() const { return sizeof(TokenId) + Amount.GetEmbeddedSize(); }
	void		Withdraw(CoinsMutable &get, CoinsMutable &residue) const; // residue = this - get
	bool		IsCoreCoin() const { return Amount.IsPositive() && CoinId == TokenIdCoreCoin; }
	template <typename T_Coin>
	UINT		Embed(const T_Coin &c)
				{
					CoinId = c.CoinId;
					UINT ret = Amount.Embed(c.Amount) + sizeof(TokenId);
					rt::_CastToNonconst(&c)->CoinId = TokenIdInvalid; // clear to zero after embedding state out
					return ret;
				}
	UINT		Embed(rvm::TokenId t, const BigNumRef& a);

	template <typename T_Coin>
	static UINT GetEmbeddedSize(const T_Coin &c) { return sizeof(TokenId) + BigNum::GetEmbeddedSize(c.Amount); }
	static UINT GetEmbeddedSizeByAmount(const BigNumRef &c) { return sizeof(TokenId) + BigNum::GetEmbeddedSize(c); }
	template <typename T_Coin>
	static bool IsEmbeddable(const T_Coin &c){ return BigNum::IsEmbeddable(c.Amount); }
	static bool IsEmbeddableByAmount(const BigNumRef &c){ return BigNum::IsEmbeddable(c); }
	static void		GetTypeSignature(rt::String &n) { n += rt::SS("token"); }
	static auto&	Zero(){ static const Coins _zero(0); return _zero; }
};
#pragma pack(pop)

class CoinsMutable
{
	friend class Coins;
	friend class Shard;
	friend class SchedulingExecutionContext;

protected:
	TokenId			CoinId; // what coin it is
	BigNumMutable	Amount; // MOVE semantics, never be copied
	void			_AlignCoinId(CoinsMutable &x) const;

public:
	void	Empty() { CoinId = TokenIdInvalid; Amount.SetZero(); }
	bool	IsZero() const { return CoinId == TokenIdInvalid || Amount.IsZero(); }
	auto	GetId() const { return CoinId; }
	void	SetId(TokenId id){ CoinId = id; }
	auto&	GetAmount() const { return Amount; }
	auto	GetModifiableAmount() -> BigNumMutable &; // CoinId will be set to zero

	CoinsMutable() { CoinId = TokenIdInvalid; }
	CoinsMutable(TokenId coin_id) : CoinId(coin_id) {}
	CoinsMutable(const CoinsMutable &x) = delete;
	CoinsMutable(CoinsMutable &&x) : CoinId(x.GetId()) { rt::Swap(Amount, x.Amount); }
	~CoinsMutable() { ASSERT(IsZero()); }

	void	Deposit(const Coins &a); // new_total = this + to_merge
	void	TransferTo(CoinsMutable &x);
	void	TransferTo(CoinsMutable &x, const BigNumRef &b);
	void	Merge(const Coins &a, const Coins &b);	 // new_total = this + to_merge
	void	Merge(CoinsMutable &a, const Coins &b); // new_total = this + to_merge
	void	Mint(TokenId aid, const BigNumRef &amount);
	bool	FromString(const rt::String_Ref &str);
	bool	JsonParse(const rt::String_Ref &str) { return FromString(str.TrimQuotes()); }
};

#pragma pack(push, 1)
class NonFungibleToken // TXN ARG only
{
	friend class NonFungibleVault;
	friend class NonFungibleVaultMutable;

	TokenId NonFungible;
	TYPETRAITS_DECLARE_POD;

public:
	NonFungibleToken(decltype(0) x);
	auto		GetId() const { return NonFungible; }
	bool		IsZero() const { return NonFungible == TokenIdInvalid; }
	static void GetTypeSignature(rt::String &n) { n += rt::SS("nonfungible"); }
};

class NonFungibleTokenRanged // TXN ARG only
{
	friend class NonFungibleVault;
	friend class NonFungibleVaultMutable;

	TokenId	NonFungibleStart;
	UINT	Count;
	TYPETRAITS_DECLARE_POD;

public:
	NonFungibleTokenRanged(TokenId s, UINT c):NonFungibleStart(s),Count(c){}
	NonFungibleTokenRanged(decltype(0) x);
	bool		IsZero() const { return Count == 0 || NonFungibleStart == TokenIdInvalid; }
	static void GetTypeSignature(rt::String &n) { n += rt::SS("nonfungible_range"); }
};

// class NonFungibleTokenSet
// {
// 	NonFungibleVaultMutable NonFungibleSet;
// 	TYPETRAITS_DECLARE_NON_POD;

// public:
// 	NonFungibleToken(decltype(0) x)
// 	{
// 		ASSERT(x == 0);
// 	}
// 	auto GetId() const
// 	{
// 		return NonFungibleSet;
// 	}
// 	bool IsZero() const
// 	{
// 		return true
// 	}
// 	// static auto&	Zero(){

// 	// }
// 	static void GetTypeSignature(rt::String &n)
// 	{
// 		n += rt::SS("nonfungible set");
// 	}
// 	bool Set(const NonFungibleVault &idSet)
// 	{
// 		/ NonFungibleSet.Assign(idSet);
// 		return true;
// 	}
// };
#pragma pack(pop)

} // namespace rvm