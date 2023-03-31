#pragma once
#include "../../bin/compile_env/include/runtime_interface.h"
#include "../../native/types/big_num.h"


namespace prlrt {
	struct CBigInt {
		rvm::BigNumMutable m_bigNum;

	public:
		CBigInt();

		// assign
		void Assign(const CBigInt* a);
		void AssignString(const char* a, uint32_t len);
		void AssignInt64(int64_t a);
		void AssignUint64(uint64_t a);

		// conversion
		// 1: overflow
		// 0: success
		//-1: underflow
		int ToInt64(int64_t* out) const;
		int ToUint64(uint64_t* out) const;

		// operators
		void Add(const CBigInt* a, const CBigInt* b);
		void AddInplace(const CBigInt* a);
		void Sub(const CBigInt* a, const CBigInt* b);
		void SubInplace(const CBigInt* a);
		void Mul(const CBigInt* a, const CBigInt* b);
		void Mul_Uint32(const CBigInt* a, uint32_t b);
		void Mul_Int32(const CBigInt* a, int b);
		void MulInplace_Int32(int a);
		void MulInplace_Uint32(uint32_t a);
		void Div_Uint32(const CBigInt* a, uint32_t b, uint32_t* remainder = nullptr);
		void Div(const CBigInt* a, const CBigInt* b, CBigInt* remainder = nullptr);
		void Mod(const CBigInt* a, const CBigInt* b);
		void ShiftRightInplace(int a);
		void ShiftLeftInplace(int a);
		void Negate(const CBigInt* a);
		void NegateInplace();
		bool IsNegative();

		// compare
		int Compare(const CBigInt* a); // a < b:-1, a == b:0, a > b:1

		// serialization
		uint32_t InitFromEmbedded(const uint8_t* in, uint32_t in_size);
		uint32_t GetEmbeddedSize() const;
		void	 Embed(uint8_t* out) const;
		bool     IsEmbeddable() const;

		// convert to string
		mutable rt::String m_stringCache;
		const char* GetString() const;
	};
}