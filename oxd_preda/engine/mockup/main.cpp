// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <iostream>

#include "../../bin/compile_env/include/inttypes.h"
#include "../../bin/compile_env/include/arraytype.h"
#include "../../bin/compile_env/include/maptype.h"
#include "../../bin/compile_env/include/tokentype.h"
#include "../../bin/compile_env/include/stringtype.h"
#include "../../bin/compile_env/include/structtype.h"
#include "../../bin/compile_env/include/address_blob_hash_types.h"
#include "../../bin/compile_env/include/biginttype.h"
#include "../../bin/compile_env/include/enumtype.h"
#include "../../bin/compile_env/include/relay.h"
#include "../../bin/compile_env/include/contexts.h"

#if defined(__linux__) || defined(__linux) || defined(__APPLE__)
#define API_EXPORT __attribute__((visibility("default")))
#elif defined(_WIN32)
#define API_EXPORT __declspec(dllexport)
#endif

#include "TranspiledCode.h"

thread_local prlrt::IRuntimeInterface* prlrt::g_executionEngineInterface = nullptr;
thread_local bool prlrt::g_inRelaySerialization = false;

//#include "../../bin/compile_env/contract_template.cpp"

#define EXPAND_STRUCT_MEMBER_LIST\
	EXPAND_STRUCT_MEMBER((__prlt_uint32), __prli_i)\
	SPLITTER\
	EXPAND_STRUCT_MEMBER((__prlt_array<__prlt_uint32>), __prli_a)
#define STRUCT_MEMBER_COUNT 2
#define STRUCT_INTERNAL_NAME ___struct_S
#define STRUCT_NAME S
#include "../../bin/compile_env/include/define_struct.h"

#define EXPAND_STRUCT_MEMBER_LIST\
	EXPAND_STRUCT_MEMBER((__prlt_uint32), __prli_i)\
	SPLITTER\
	EXPAND_STRUCT_MEMBER((__prlt_uint32), __prli_j)
#define STRUCT_MEMBER_COUNT 2
#define STRUCT_INTERNAL_NAME ___struct_S1
#define STRUCT_NAME S1
#include "../../bin/compile_env/include/define_struct.h"


//class SomeClass {
//#define EXPAND_STRUCT_MEMBER_LIST\
//	EXPAND_STRUCT_MEMBER(___uint32, i)\
//	EXPAND_STRUCT_MEMBER(___uint32, j)
//#define EXPAND_STRUCT_MEMBER_LIST_WITH_COMMA\
//	EXPAND_STRUCT_MEMBER(___uint32, i)\
//	,\
//	EXPAND_STRUCT_MEMBER(___uint32, j)
//#define STRUCT_MEMBER_COUNT 2
//#define STRUCT_INTERNAL_NAME ___struct_S1
//#define STRUCT_NAME S1
//#include "define_struct.h"
//};

void dumpa(__prlt_array<__prlt_array<__prlt_uint32>> &c)
{
	std::cout << "------------------" << std::endl;
	std::cout << c.__prli_length()._v << std::endl;
	for (uint32_t i = 0; i < c.__prli_length()._v; i++)
	{
		std::cout << c[i].__prli_length()._v << ":";
		for (uint32_t j = 0; j < c[i].__prli_length()._v; j++)
			std::cout << " " << c[i][j]._v;
		std::cout << std::endl;
	}
}

extern "C" {
	__declspec(dllexport) int Test(prlrt::IRuntimeInterface *pInterface)
	{
		prlrt::g_executionEngineInterface = pInterface;

		// test ___array
		{
			__prlt_array<__prlt_uint32> x, y;		// A = [], x = &A, B = [], y = &B
			y = x;							// y = x => y = &A (B is released because counter is 0)
			x.__prli_push(1);						// x->push(1) => A.push(1) => A = [1]
			y.__prli_push(2);						// y->push(1) => A.push(2) => A = [1, 2]
			x.__prli_pop();						// x->pop() => A.pop() => A = [1]
			y.__prli_push(4);						// y->push(4) => A.push(4) => A = [1, 4]
			x[1] = 3;						// x[1] = 3 => A[1] = 3 => A = [1, 3]

			// Now A = [1, 3]
			uint32_t answer[] = { 1,3 };
			for (uint32_t i = 0; i < x.__prli_length()._v; i++)
				assert(bool(x[i] == answer[i]));

			__prlt_array<__prlt_array<__prlt_uint32>> xx, yy;		// AA = [], xx = &AA, BB = [], yy = &BB
			xx.__prli_push(x);									// xx.push(x) => AA.push(x) => AA.push(&A) => AA = [&A]
			yy = xx;									// yy = xx => yy = &AA (BB is released because counter is 0)
			yy.__prli_push(y);									// yy.push(y) => AA.push(y) => AA.push(&A) => AA = [&A, &A]
			y.__prli_pop();									// y.pop() => A.pop() => A = [1]

			// Now A = [1], AA = [&A, &A];
			assert(bool(xx.__prli_length() == 2));				// AA.length() == [&A, &A].length() == 2
			assert(bool(xx[0].__prli_length() == 1u));			// AA[0].length() == A.length() == [1].length() == 1
			assert(bool(xx[1].__prli_length() == 1u));			// AA[1].length() == A.length() == [1].length() == 1
			assert(bool(xx[0][0] == 1));				// AA[0][0] == A[0] == 1
			assert(bool(xx[1][0] == 1));				// AA[1][0] == A[0] == 1
		}

		// test ___map
		{
			{
				__prlt_map<__prlt_uint32, __prlt_uint32> x, y;			// A = {}, x = &A, B = {}, y = &B;
				y = x;										// y = x => y = &A (B is released because counter is 0)
				x[0] = 100;									// x[0] = 100 => A[0] = 100 => A = { 0 : 100 }
				x[3000] = 10;								// x[3000] = 10 => A[3000] = 10 => A = { 0 : 100, 3000 : 10 }
				y[3000] = 1;								// y[3000] = 1 => A[3000] = 1 => A = { 0 : 100, 3000 : 1 }
				assert(bool(x[0] == 100));
				assert(bool(x[3000] == 1));
			}

			{
				__prlt_map<__prlt_uint32, __prlt_array<__prlt_uint32>> xx;	// AA = {}, xx = &AA
				__prlt_array<__prlt_uint32> x, y;					// A = [], x = &A, B = [], y = &B
				x.__prli_push(1);									// x.push(1) => A.push(1) => A = [1]
				y.__prli_push(2);									// y->push(2) => B.push(2) => B = [2]
				xx[100] = x;								// xx[100] = x => AA[100] = &A => AA = { 100: &A }
				xx[2] = y;									// xx[2] = y => AA[2] = &B => AA = { 100: &A, 2 : &B }
				__prlt_array<__prlt_uint32> z(y);					// z(y) => z = &B;
				xx[xx[100][0]] = z;							// xx[xx[100][0]] = z => xx[AA[100][0]] = z => xx[A[0]] = z => xx[1] = z => AA[1] = z => AA = { 100: &A, 2: &B, 1: &B }
				y.__prli_push(4);									// y->push(4) => B.push(4) => B = [2, 4]

				// Now xx = &AA = { 100: &A, 2 : &B, 1 : B } = { 100: [1], 2: [2, 4], 1: [2, 4] }
				assert(bool(xx[100].__prli_length() == 1));
				assert(bool(xx[100][0] == 1));
				assert(bool(xx[2].__prli_length() == 2));
				assert(bool(xx[2][0] == 2));
				assert(bool(xx[2][1] == 4));
				assert(bool(xx[1].__prli_length() == 2));
				assert(bool(xx[1][0] == 2));
				assert(bool(xx[1][1] == 4));
			}
		}

		// test struct
		{
			__prlt_array<__prlt_uint32> a;				// A = [], a = &A
			__prlt_uint32 i(1);						// i = 1
			a.__prli_push(i);							// a.push(i) => a.push(1) => A.push(1) => A = [1]
			S s = S(i, a);						// B = {i, a} => B = {1, &A}; s = &B
			s->__prli_i = 11;							// s->i = 11 => B->i = 11 => B = {11, &A}
			s->__prli_a.__prli_push(3);						// s->a.push(3) => B->a.push(3) => A.push(3) => A = [1, 3]
			s->__prli_a[0] = 5;						// s->a[0] = 5 => B->a[0] = 5 => A[0] = 5 => A = [5, 3]
			S t = s;							// t = s => t = &B;
			t->__prli_i = 100;							// t->i = 100 => B->i = 100 => B = {100, &A}

			// Now i = 1, a = &A, A = [5, 3], s = &B, t = &B, B = {100, &A} = {100, [5, 3]}
			assert(bool(i == 1));
			assert(bool(a.__prli_length() == 2));
			assert(bool(a[0] == 5));
			assert(bool(a[1] == 3));
			assert(bool(t->__prli_a.__prli_length() == 2));
			assert(bool(t->__prli_a[0] == 5));
			assert(bool(t->__prli_a[1] == 3));
			assert(bool(s->__prli_i == 100));

			__prlt_map<__prlt_uint32, S> ms;			// MS = {}, ms = &MS
			ms[s->__prli_a[1]] = s;					// ms[s->a[1]] = s => ms[B->a[1]] = s => ms[A[1]] = s => ms[3] = s => ms[3] = B => MS[3] = B => MS = {3 : B}
			ms[s->__prli_a[0]] = ms[s->__prli_a[1]];			// ms[s->a[0]] = ms[s->a[1]] => ms[B->a[0]] = ms[B->a[1]] => ms[A[0]] = ms[A[1]] => ms[5] = ms[3] => ms[5] = B => MS[5] = B => MS = {3: B, 5: B}
			ms[3]->__prli_a.__prli_push(15);					// ms[3]->a.push(15) => B->a.push(15) => A.push(15) => A = [5, 3, 15]

			// Now MS = {3 : {100, [5, 3, 15] }, 5 : {100, [5, 3, 15] }}
			assert(bool(ms[5]->__prli_a.__prli_length() == 3));
			assert(bool(a.__prli_length() == 3));
			assert(bool(a[a.__prli_length() - 1] == 15));

			prlrt::serialize_size_type sms = ms.get_serialize_size();
			uint8_t *buffer = new uint8_t[sms];
			ms.serialize_out(buffer, true);
			assert(ms.map_from_serialized_data(buffer, sms, true));
			assert(sms == 0);
			ms[100]->__prli_i = 4;
			ms[200]->__prli_a.__prli_push(200);
			ms[5]->__prli_i = 2;
			ms[3]->__prli_a.__prli_pop();
			// Now MS = {3 : {100, [5, 3] }, 5 : {2, [5, 3, 15] }, 100 : {4, [] }, 200 : {0, [200] }}
			sms = ms.get_serialize_size();
			buffer = new uint8_t[sms];
			ms.serialize_out(buffer, true);
			assert(ms.map_from_serialized_data(buffer, sms, true));
			assert(sms == 0);
		}

		// Test array serialization
		{
			__prlt_array<__prlt_uint32> a;
			a.__prli_push(0);
			__prlt_array<__prlt_array<__prlt_uint32>> b;
			b.__prli_push(__prlt_array<__prlt_uint32>());
			b[0].__prli_push(3);
			b.__prli_push(__prlt_array<__prlt_uint32>());
			b[1].__prli_push(4);
			b[1].__prli_push(5);
			//____serialize_size_type ss = a.get_serialize_size();
			prlrt::serialize_size_type sss = b.get_serialize_size();
			//std::cout << ss << " " << sss << std::endl;
			uint8_t *buffer = new uint8_t[sss];
			b.serialize_out(buffer, true);
			//const uint8_t *buffer1 = b.get_type_identifier_buffer();
			__prlt_array<__prlt_array<__prlt_uint32>> c;
			assert(c.map_from_serialized_data(buffer, sss, true));
			assert(sss == 0);
			dumpa(c);
			c[0].__prli_push(1);
			__prlt_array<__prlt_uint32> d;
			d.__prli_push(100);
			d.__prli_push(200);
			d.__prli_push(300);
			c.__prli_push(d);
			d = c[1];
			c[1].__prli_pop();
			assert(bool(d.__prli_length() == 1));
			dumpa(c);

			__prlt_array<__prlt_array<__prlt_uint32>> e;
			{
				prlrt::serialize_size_type sss = c.get_serialize_size();
				uint8_t *buffer = new uint8_t[sss];
				c.serialize_out(buffer, true);
				assert(e.map_from_serialized_data(buffer, sss, true));
				assert(sss == 0);
				dumpa(e);
			}
		}

		// test map serialization
		{
			__prlt_map<__prlt_uint32, __prlt_uint32> m;
			m[100] = 2;
			m[2] = 15;
			m[0] = 1;
			m[0] = 10;
			{
				std::cout << m[0]._v << std::endl;
			}

			__prlt_map<__prlt_uint32, __prlt_map<__prlt_uint32, __prlt_uint32>> mm;
			mm[233] = m;
			mm[174] = m;
			mm[233][10] = 20;

			{
				prlrt::serialize_size_type ms = mm.get_serialize_size();
				uint8_t *buffer = new uint8_t[ms];
				mm.serialize_out(buffer, true);
				ms = ms;
			}

			prlrt::serialize_size_type ms = m.get_serialize_size();
			uint8_t *buffer = new uint8_t[ms];
			m.serialize_out(buffer, true);
			m.map_from_serialized_data(buffer, ms, true);
			assert(ms == 0);

			mm[233] = m;
			mm[233][10] = 2;
			{
				prlrt::serialize_size_type ms = mm.get_serialize_size();
				uint8_t *buffer = new uint8_t[ms];
				mm.serialize_out(buffer, true);
				ms = ms;
			}
		}

		// test array of fixed size struct
		{
			__prlt_array<S1> as;
			S1 s;
			s->__prli_i = 1;
			s->__prli_j = 2;
			as.__prli_push(s);
			as.__prli_push(s);
			prlrt::serialize_size_type ass = as.get_serialize_size();
			uint8_t *buffer = new uint8_t[ass];
			as.serialize_out(buffer, true);
		}
		//as[0]->i = 10;

		// test exceptions
		{
			try
			{
				__prlt_uint32 i = 0u;
				//i = 0xffffffffu;
				//i++;
				//i += 1u;

				//i = 0;
				//i--;
				//i -= i + 1;

				//i = 100000u;
				//i *= i;

				//i /= i;
				//i %= i;

				__prlt_array<__prlt_uint32> a;
				//a.__prli_pop();
				//i = a[1];

				__prlt_map<__prlt_uint32, __prlt_uint32> m;
				//i = (*((const ___map<___uint32, ___uint32>*)&m))[1];
			}
			catch (prlrt::preda_exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// test other uint and int types
		{
			try {
				__prlt_uint16 i = 0xffffu;
				i++;
			}
			catch (prlrt::preda_exception &e)
			{
				std::cout << e.what() << std::endl;
			}

			try {
				__prlt_int8 i = -0x7f - 1;
				i = i * __prlt_int8(-1);
				//i = i / ___int8(-1);
				//i = i % ___int8(-1);
				//i = i - ___int8(1);
				//___int8(127)++;
			}
			catch (prlrt::preda_exception &e)
			{
				std::cout << e.what() << std::endl;
			}

			try {
				__prlt_int64 i = -0x7fffffffffffffffll - 1;
				//i = i * ___int64(-1);
				//i = i / ___int64(-1);
				//i = i % ___int64(-1);
				i = i - __prlt_int64(1);
				//___int8(127)++;
			}
			catch (prlrt::preda_exception &e)
			{
				std::cout << e.what() << std::endl;
			}

			try
			{
				__prlt_int8(__prlt_uint16(128));
				//___uint16(___int8(-10));
				//___uint16(___int32(100000));
			}
			catch (prlrt::preda_exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		// test token
		{
			try
			{
				__prlt_token token, token1;
				token.ptr->id = 1;
				token.ptr->amount = 4;
				token1.ptr->id = 2;
				token.__prli_transfer(token1, 3);
			}
			catch (prlrt::preda_exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}

		//___Contract_0x0123456789000000::___Contract_0x0123456789000000_ZombieFactory zombieFactory;
		//zombieFactory.dnaModulus = 100;
		//___uint16 ret = zombieFactory.createRandomZombie(___string("my_zombie"));

		// test string
		{
			__prlt_string a = __prlt_string("fdadf");
			__prlt_string b;
			b = __prlt_string("faf");
			__prlt_string c = a;

			prlrt::serialize_size_type ss = a.get_serialize_size();
			assert(ss == 7);
			uint8_t buf[100];
			a.serialize_out(buf, true);

			assert(bool(a == c));
			assert(bool(b < a));
			assert(bool(__prlt_string("abc") < __prlt_string("abcd")));
		}

		// test address, blob and hash
		{
			__prlt_address addr0, addr1, addr2;
			addr0.data[0] = 100;
			addr1 = addr0;
			addr2.data[0] = 50;
			assert(bool(addr0 == addr1));
			assert(bool(addr0 != addr2));
			prlrt::serialize_size_type as = addr0.get_serialize_size();
			assert(as == __prlt_address::fixed_size_in_bytes::value);
			uint8_t *buffer = new uint8_t[as];
			addr0.serialize_out(buffer, true);
			assert(addr2.map_from_serialized_data(buffer, as, true));
			assert(as == 0);
			assert(bool(addr0 == addr2));

			__prlt_blob blob0, blob1, blob2;
			blob0.data[0] = 100;
			blob1 = blob0;
			blob2.data[0] = 50;
			assert(bool(blob0 == blob1));
			assert(bool(blob0 != blob2));
			prlrt::serialize_size_type bs = blob0.get_serialize_size();
			assert(bs == __prlt_blob::fixed_size_in_bytes::value);
			buffer = new uint8_t[bs];
			blob0.serialize_out(buffer, true);
			assert(blob2.map_from_serialized_data(buffer, bs, true));
			assert(bs == 0);
			assert(bool(blob0 == blob2));

			__prlt_hash hash0, hash1, hash2;
			hash0.data[0] = 100;
			hash1 = hash0;
			hash2.data[0] = 50;
			assert(bool(hash0 == hash1));
			assert(bool(hash0 != hash2));
			prlrt::serialize_size_type hs = hash0.get_serialize_size();
			assert(hs == __prlt_hash::fixed_size_in_bytes::value);
			buffer = new uint8_t[hs];
			hash0.serialize_out(buffer, true);
			assert(hash2.map_from_serialized_data(buffer, hs, true));
			assert(hs == 0);
			assert(bool(hash0 == hash2));
		}

		// test bigint
		{
			__prlt_bigint bi0(__prlt_uint32(100));
			__prlt_bigint bi1(__prlt_uint32(100));
			__prlt_bigint bi2(__prlt_uint32(300));
			bi0 *= bi1;
			bi0 -= bi2;
			__prlt_int32 ui = __prlt_int32(bi0);
			assert(ui._v == 9700);
			assert(bool(bi0 == bi0));
			assert(bool(bi0 != bi1));
			assert(bool(bi0 > bi1));
			assert(bool(bi1 <= bi1));
			assert(bool(bi1 < bi2));
			assert(bool(bi2 >= bi2));

			try
			{
				__prlt_bigint bi = __prlt_uint64(0xfffffffffffffffflu);
				bi++;
				__prlt_uint64 u64 = __prlt_uint64(bi);
			}
			catch (prlrt::preda_exception &e)
			{
				std::cout << e.what() << std::endl;
			}

			bi0 *= bi1;
			bi0 *= bi1;
			bi0 *= bi1;
			bi0 *= bi1;
			bi0 *= bi1;
			prlrt::serialize_size_type bis = bi0.get_serialize_size();
			uint8_t *buffer = new uint8_t[bis];
			bi0.serialize_out(&buffer[0], true);
			assert(bi1.map_from_serialized_data(buffer, bis, true));
			assert(bis == 0);
			assert(bool(bi0 == bi1));
		}

		// test enum 
		{
			enum class __prlt_E__ : prlrt::enum_base_type {
				__prli_X,
				__prli_Y,
				__prli_Z,
			};

			using __prlt_E = prlrt::enum_wrapper<__prlt_E__, 3>;

			__prlt_array<__prlt_E> t;

			t.__prli_push(__prlt_E__::__prli_X);
			t.__prli_push(t[0]);
			t[0] = t[1];
			assert(bool(t[0] == t[1]));
			t[1] = __prlt_E__::__prli_Y;
			assert(bool(t[0] != t[1]));
			try {
				t[0] = __prlt_E__(3);
			}
			catch (prlrt::preda_exception &e)
			{
				std::cout << e.what() << std::endl;
			}

			prlrt::serialize_size_type ss = t.get_serialize_size();
			uint8_t *buffer = new uint8_t[ss];
			t.serialize_out(buffer, true);
			assert(t.map_from_serialized_data(buffer, ss, true));
			assert(ss == 0);
			__prlt_E e;
			e = __prlt_E__::__prli_X;
			e = e;
			ss = e.get_serialize_size();
			buffer = new uint8_t[ss];
			e.serialize_out(buffer, true);
			buffer[0] = 3;
			try {
				assert(e.map_from_serialized_data(buffer, ss, true));
			}
			catch (prlrt::preda_exception &e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		// test type identifiers
		{
			enum class __prlt_E__ : prlrt::enum_base_type {
				__prli_X,
				__prli_Y,
				__prli_Z,
			};

			using __prlt_E = prlrt::enum_wrapper<__prlt_E__, 3>;

			__prlt_E e;
			const uint8_t *ti;
			ti = __prlt_E::get_type_identifier_buffer();

			ti = __prlt_bool::get_type_identifier_buffer();
			ti = __prlt_int32::get_type_identifier_buffer();
			ti = __prlt_array<__prlt_map<__prlt_uint32, __prlt_uint32>>::get_type_identifier_buffer();
			ti = S::get_type_identifier_buffer();
			ti = __prlt_token::get_type_identifier_buffer();
			ti = __prlt_address::get_type_identifier_buffer();
			ti = __prlt_bigint::get_type_identifier_buffer();
			ti = __prlt_string::get_type_identifier_buffer();
		}

		{
			//__prlt_int32 i;
			//i = __prlt_int32(100);
			//__prli__debug.__prli_print(i);
		}

		return 0;
	}
}
