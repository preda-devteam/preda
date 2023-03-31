#include "bigint.h"

namespace prlrt {
	CBigInt::CBigInt()
	{
	}

	void CBigInt::Assign(const CBigInt* a)
	{
		m_bigNum = a->m_bigNum;
	}
	void CBigInt::AssignString(const char* a, uint32_t len)
	{
		m_bigNum.FromString(rt::String_Ref(a, len));
	}
	void CBigInt::AssignInt64(int64_t a)
	{
		m_bigNum = a;
	}
	void CBigInt::AssignUint64(uint64_t a)
	{
		m_bigNum = a;
	}

	// conversion
	// 1: overflow
	// 0: success
	//-1: underflow
	int CBigInt::ToInt64(int64_t* out) const
	{
		if (m_bigNum.GetLength() > 1)
			return m_bigNum.GetSign() ? -1 : 1;
		if ((m_bigNum.GetLength() && *m_bigNum.Data() == 0) || m_bigNum.GetLength() == 0)
		{
			*out = 0;
			return 0;
		}

		if (m_bigNum.GetSign())
		{
			if (*m_bigNum.Data() > 0x8000000000000000ULL)
				return -1;
			*out = -(int64_t)*m_bigNum.Data();
		}
		else
		{
			if (*m_bigNum.Data() >= 0x8000000000000000ULL)
				return 1;
			*out = *m_bigNum.Data();
		}

		return 0;
	}
	int CBigInt::ToUint64(uint64_t* out) const
	{
		if (m_bigNum.GetLength() > 1)
			return m_bigNum.GetSign() ? -1 : 1;
		if ((m_bigNum.GetLength() && *m_bigNum.Data() == 0) || m_bigNum.GetLength() == 0)
		{
			*out = 0;
			return 0;
		}

		if (m_bigNum.GetSign())
			return -1;
		*out = *m_bigNum.Data();
		return 0;
	}

	// operators
	void CBigInt::Add(const CBigInt* a, const CBigInt* b)
	{
		m_bigNum.Add(a->m_bigNum, b->m_bigNum);
	}
	void CBigInt::AddInplace(const CBigInt* a)
	{
		m_bigNum += a->m_bigNum;
	}
	void CBigInt::Sub(const CBigInt* a, const CBigInt* b)
	{
		m_bigNum.Sub(a->m_bigNum, b->m_bigNum);
	}
	void CBigInt::SubInplace(const CBigInt* a)
	{
		m_bigNum -= a->m_bigNum;
	}
	void CBigInt::Mul(const CBigInt* a, const CBigInt* b)
	{
		m_bigNum.Mul(a->m_bigNum, b->m_bigNum);
	}
	void CBigInt::Mul_Uint32(const CBigInt* a, uint32_t b)
	{
		m_bigNum.Mul(a->m_bigNum, b);
	}
	void CBigInt::Mul_Int32(const CBigInt* a, int b)
	{
		m_bigNum.Mul(a->m_bigNum, b);
	}
	void CBigInt::MulInplace_Int32(int a)
	{
		m_bigNum *= a;
	}
	void CBigInt::MulInplace_Uint32(uint32_t a)
	{
		m_bigNum *= a;
	}
	void CBigInt::Div_Uint32(const CBigInt* a, uint32_t b, uint32_t* remainder)
	{
		m_bigNum.Div(a->m_bigNum, b, remainder);
	}
	void CBigInt::Div(const CBigInt* a, const CBigInt* b, CBigInt* remainder /* = nullptr */)
	{
		m_bigNum.Div(a->m_bigNum, b->m_bigNum, remainder ? &remainder->m_bigNum : nullptr);
	}
	void CBigInt::Mod(const CBigInt* a, const CBigInt* b)
	{
		rvm::BigNumMutable tmp;
		tmp.Div(a->m_bigNum, b->m_bigNum, &m_bigNum);
	}
	void CBigInt::ShiftRightInplace(int a)
	{
		m_bigNum >>= a;
	}
	void CBigInt::ShiftLeftInplace(int a)
	{
		m_bigNum <<= a;
	}
	void CBigInt::Negate(const CBigInt* a)
	{
		m_bigNum = a->m_bigNum;
		m_bigNum.FlipSign();
	}
	void CBigInt::NegateInplace()
	{
		m_bigNum.FlipSign();
	}
	bool CBigInt::IsNegative()
	{
		return m_bigNum.IsNegative();
	}
	// compare
	int CBigInt::Compare(const CBigInt* a) // a < b:-1, a == b:0, a > b:1
	{
		return BN_Compare(m_bigNum, a->m_bigNum);
	}

	// serialization
	uint32_t CBigInt::InitFromEmbedded(const uint8_t* in, uint32_t in_size)
	{
		auto& a = *(const rvm::BigNum*)in;
		if (in_size && a.GetEmbeddedSize() <= in_size)
		{
			m_bigNum = a;
			return a.GetEmbeddedSize();
		}
		else
		{
			m_bigNum = rvm::BigNumMutable();
			return 0;
		}
	}
	uint32_t CBigInt::GetEmbeddedSize() const
	{
		return rvm::BigNum::GetEmbeddedSize(m_bigNum);
	}
	void CBigInt::Embed(uint8_t* out) const
	{
		((rvm::BigNum*)out)->Embed(m_bigNum);
	}
	bool CBigInt::IsEmbeddable() const
	{
		return rvm::BigNum::IsEmbeddable(m_bigNum);
	}

	const char* CBigInt::GetString() const
	{
		((::rvm::BigNumMutable*)&m_bigNum)->ToString(m_stringCache);
		return m_stringCache.GetString();
	}
}