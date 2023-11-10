#include "coins.h"
#include "typetraits.h"


namespace rvm
{

Coins::Coins(decltype(0) x) : Amount(0)
{
	ASSERT(x == 0);
	CoinId = TokenIdInvalid;
}

void Coins::Withdraw(CoinsMutable& get, CoinsMutable& residue) const	// residue = this - get
{	
	ASSERT(residue.IsZero());
	ASSERT(get.IsZero());

	residue.Amount.Sub(Amount, get.Amount);
	ASSERT(residue.Amount.IsNonNegative());
	residue.CoinId = CoinId;
	get.CoinId = CoinId;
}

void Coins::Jsonify(rt::Json &append) const 
{
	if(CoinId == TokenIdInvalid)
	{
		append.Number(0);
	}
	else
	{
		auto& s = append.GetInternalString();
		s += '"';
		Amount.ToString(s);
		s += ':';
		s += GetSymbol();
		s += '"';
	}
}

void CoinsMutable::_AlignCoinId(CoinsMutable &x) const
{
	if(x.CoinId != TokenIdInvalid)
	{
		ASSERT(x.CoinId == CoinId);
	}
	else
		x.CoinId = CoinId;
}

bool CoinsMutable::FromString(const rt::String_Ref& str)
{
	if(str == "0")
	{
		Empty();
		return true;
	}
	else
	{
		rt::String_Ref seg[3];
		if(	str.Split(seg, 3, ':') == 2 && 
			!seg[0].IsEmpty() && 
			seg[1].GetLength() >= rvm::TokenNameSizeMin && seg[1].GetLength() <= rvm::TokenNameSizeMax
		)
		{
			Amount.FromString(seg[0]);
			rt::Zero(CoinId);
			seg[1].CopyTo((char*)&CoinId);

			return true;
		}
	}

	return false;
}

BigNumMutable& CoinsMutable::GetModifiableAmount()	// CoinId will be set to zero
{
	ASSERT(IsZero());
	CoinId = TokenIdInvalid;
	return Amount;
}

void CoinsMutable::TransferTo(CoinsMutable& x)
{
	if(x.IsZero())
	{
		_AlignCoinId(x);
		x.Amount = Amount;
	}
	else
	{
		_AlignCoinId(x);
		x.Amount += Amount;
	}

	Amount.SetZero();
}

void CoinsMutable::TransferTo(CoinsMutable& x, const BigNumRef& b)
{
	if(x.IsZero())
	{
		_AlignCoinId(x);
		Amount -= b;
		ASSERT(Amount.IsNonNegative());

		x.Amount = b;
	}
	else
	{
		_AlignCoinId(x);
		Amount -= b;
		ASSERT(Amount.IsNonNegative());

		x.Amount += b;
	}
}

void CoinsMutable::Merge(const Coins& a, const Coins& b)
{	
	ASSERT(IsZero());

	if(a.IsZero())
	{
		if(b.IsZero())
		{
			Amount = 0;
			return;
		}
		CoinId = b.GetId();
		Amount = b.Amount;
	}
	else
	{
		if(b.IsZero())
		{
			CoinId = a.GetId();
			Amount = a.Amount;
		}
		else
		{
			ASSERT(a.GetId() == b.GetId());
					
			Amount.Add(a.Amount, b.Amount);
			CoinId = a.GetId();
		}
	}
}

void CoinsMutable::Mint(TokenId aid, const BigNumRef& amount)
{
	ASSERT(aid != TokenIdCoreCoin);
	ASSERT(CoinId == TokenIdInvalid);
	
	Amount = amount;
	ASSERT(Amount.IsNonNegative());

	CoinId = aid;
}

void CoinsMutable::Merge(CoinsMutable& a, const Coins& b)
{	
	ASSERT(IsZero());

	if(b.IsZero())
	{
		a.TransferTo(*this);
	}
	else
	{
		ASSERT(a.GetId() == b.GetId());
					
		Amount.Add(a.Amount, b.Amount);
		CoinId = a.GetId();
		a.Empty();
	}
}

void CoinsMutable::Deposit(const Coins& a)
{	
	if(a.IsZero())return;

	if(IsZero())
	{
		SetId(a.GetId());
		Amount = a.Amount;
	}
	else
	{
		ASSERT(a.GetId() == CoinId);
		Amount += a.Amount;
	}
}

NonFungibleToken::NonFungibleToken(decltype(0) x)
{
	ASSERT(x == 0);
	NonFungible = TokenIdInvalid;
}

NonFungibleTokenRanged::NonFungibleTokenRanged(decltype(0) x)
{
	ASSERT(x == 0);
	NonFungibleStart = TokenIdInvalid;
	Count = 0;
}

//namespace _details
//{
//
//void SetCoinId(CoinsMutable& cm, TokenId coin_id)
//{
//	ASSERT(coin_id < TokenIdInvalid);
//	*((TokenId*)&cm) = coin_id;
//}
//
//void SetCoins(Coins& cm, TokenId coin_id, const BigNumMutable& a)
//{
//	ASSERT(coin_id < TokenIdInvalid);
//	struct __coin: public Coins
//	{	
//		void set(TokenId coin_id, const BigNumMutable& a)
//		{
//			typedef _details::_Embed<BigNum, BigNumMutable> BigNumType;
//			CoinId = coin_id;
//			BigNumType::Set((LPBYTE)&Amount, a);
//		}
//	};
//
//	((__coin*)&cm)->set(coin_id, a);
//}
//
//} // namespace _details
} // namespace rvm
