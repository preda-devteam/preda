#include "coins.h"
#include "typetraits.h"
#include "../abi/vm_interfaces.h"


namespace rvm
{

namespace _details
{
void _AppendCoinSymbol(TokenId id, rt::String& append)
{
	const ChainState* p = _details::__ThreadLocalExecutionStatePtr();
	if(p)
	{
		auto symbol = p->GetTokenSymbol(id).Str();
		if(!symbol.IsEmpty())
		{
			append += symbol;
			return;
		}
	}

	append += '(';
	append += rt::tos::Number((uint32_t)id);
	append += ')';
}
} // namespace _details

bool CoinsMutable::FromString(const rt::String_Ref& str)
{
	const ChainState* p = _details::__ThreadLocalExecutionStatePtr();
	if(!p)return false;

	auto off = str.FindCharacter(':');
	TokenId id;

	auto ss = str.SubStr(off+1);
	ConstString symbol = { ss.Begin(), (uint32_t)ss.GetLength() };

	if(off > 0 && (id = p->GetTokenBySymbol(&symbol)) != TokenIdInvalid)
	{
		CoinId = id;
		return Amount.FromString(str.SubStr(0, off));
	}

	return false;
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

BigNumMutable& CoinsMutable::GetModifiableAmount()	// CoinId will be set to zero
{
	ASSERT(IsZero());
	CoinId = TokenIdInvalid;
	return Amount;
}

void CoinsMutable::TransferTo(CoinsMutable& x)
{
	_AlignCoinId(x);
	x.Amount += Amount;
	Amount.SetZero();
}

void CoinsMutable::TransferTo(CoinsMutable& x, const BigNumRef& b)
{
	_AlignCoinId(x);
	Amount -= b;
	ASSERT(Amount.IsNonNegative());

	x.Amount += b;
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

	ASSERT(a.GetId() == CoinId);
	Amount += a.Amount;
}

namespace _details
{

void SetCoinId(CoinsMutable& cm, TokenId coin_id)
{
	ASSERT(coin_id < TokenIdInvalid);
	*((TokenId*)&cm) = coin_id;
}

void SetCoins(Coins& cm, TokenId coin_id, const BigNumMutable& a)
{
	ASSERT(coin_id < TokenIdInvalid);
	struct __coin: public Coins
	{	
		void set(TokenId coin_id, const BigNumMutable& a)
		{
			typedef _details::_Embed<BigNum, BigNumMutable> BigNumType;
			CoinId = coin_id;
			BigNumType::Set((LPBYTE)&Amount, a);
		}
	};

	((__coin*)&cm)->set(coin_id, a);
}

} // namespace _details
} // namespace rvm
