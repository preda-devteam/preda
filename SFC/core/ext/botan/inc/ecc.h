#pragma once
//////////////////////////////////////////////////////////////////////
// System Foundation Classes(SFC)
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials provided
//       with the distribution.
//     * Neither the name of SFC.  nor the names of its
//       contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//////////////////////////////////////////////////////////////////////


#include "botan_inc.h"
#include "datablock.h"


namespace sec
{
/** \defgroup botan botan
* @ingroup ext
*  @{
*/
/** \defgroup Enums_botan Enums_botan
* @ingroup botan
*  @{
*/
enum _tagECCMethods
{
	ECDSA_SECP256K1 = 1,
	ECDSA_SECP256R1
/** @}*/
//  return "secp256r1";
//  return "secp384r1";
//  return "secp521r1";
//  return "brainpool256r1";
//  return "brainpool384r1";
//  return "brainpool512r1";
//  return "x25519";

};

namespace _details
{
template<int CRYTOMETHOD>
struct ECC;
	template<> struct ECC<ECDSA_SECP256K1>
	{
		static const int KeySize = 32;
		typedef Botan::ECDSA_PrivateKey		PrivateKey;
		typedef Botan::ECDSA_PublicKey		PublicKey;
		static LPCSTR	ECGroupName(){ return "secp256k1"; }
	};
	template<> struct ECC<ECDSA_SECP256R1>
	{
		static const int KeySize = 32;
		typedef Botan::ECDSA_PrivateKey		PrivateKey;
		typedef Botan::ECDSA_PublicKey		PublicKey;
		static LPCSTR	ECGroupName(){ return "secp256r1"; }
	};
INLFUNC LPCSTR EmsaName(){ return "EMSA1(SHA-256)"; }
INLFUNC LPCSTR Eme1Name(){ return "EME1(SHA-256)"; }
} // namespace _details

template<int CRYTOMETHOD>
class Keypair
{
public:
	static const int KeySize = _details::ECC<CRYTOMETHOD>::KeySize;
	typedef DataBlock<_details::ECC<CRYTOMETHOD>::KeySize, true> PrivateKey;
	typedef DataBlock<_details::ECC<CRYTOMETHOD>::KeySize, false> PublicKey;

protected:
	PrivateKey	_SK;
	PublicKey	_PK;

public:
	Keypair() = default;
	Keypair(const rt::String_Ref& pk, const rt::String_Ref& sk){ _PK.FromBase32(pk); _SK.FromBase32(sk); }
	const PublicKey& PK() const { return _PK; }
	const PrivateKey& SK() const { return _SK; }
	bool operator == (const Keypair& x){ return _SK == x._SK && _PK == x._PK; }
	bool  Generate(Botan::RandomNumberGenerator* pRNG = NULL)
	{	try{
			rt::ObjectPlaceHolder<Botan::AutoSeeded_RNG>	SysRNG;
			if(pRNG == NULL){ pRNG = SysRNG.Init(); }

			Botan::EC_Group group(_details::ECC<CRYTOMETHOD>::ECGroupName());
			for(;;)
			{
				typename _details::ECC<CRYTOMETHOD>::PrivateKey sk(*pRNG, group);
				if(sk.public_point().get_affine_x().get_bit(0) == sk.public_point().get_affine_y().get_bit(0))
				{
					memcpy(&_SK, sk.private_value().get_word_vector().data(), KeySize);
					memcpy(&_PK, sk.public_point().get_affine_x().get_word_vector().data(), KeySize);
					break;
				}
			}

			return true;
		}catch(...){ return false; }
	}
	bool  SetPrivateKey(const PrivateKey& k)
	{	try{
			Botan::AutoSeeded_RNG rng;
			Botan::BigInt s;
			Botan::BigIntAssign(s, k);
			typename _details::ECC<CRYTOMETHOD>::PrivateKey sk(rng, Botan::EC_Group(_details::ECC<CRYTOMETHOD>::ECGroupName()), s);
			memcpy(&_SK, sk.private_value().get_word_vector().data(), KeySize);
			memcpy(&_PK, sk.public_point().get_affine_x().get_word_vector().data(), KeySize);
			return true;
		}catch(...){ return false; }
	}
	bool	IsValid(bool deep_check = false) const
	{	try{
			Botan::AutoSeeded_RNG rng;
			Botan::BigInt s;
			Botan::BigIntAssign(s, _SK);
			typename _details::ECC<CRYTOMETHOD>::PrivateKey sk(rng, Botan::EC_Group(_details::ECC<CRYTOMETHOD>::ECGroupName()), s);
			return sk.check_key(rng, deep_check);
		}catch(...){ return false; }
	}
};

namespace _details
{

struct _RNG_Base
{
	rt::ObjectPlaceHolder<Botan::AutoSeeded_RNG>	__SysRNG;
	Botan::RandomNumberGenerator*	_pRNG;
	void	_RngCtor(Botan::RandomNumberGenerator* rng)
	{	if(rng){ _pRNG = rng; }
		else{ _pRNG = __SysRNG.Init(); }
	}
};

template<int CRYTOMETHOD>
class _PrivateKeyOp: public _RNG_Base
{
protected:
	rt::ObjectPlaceHolder<typename _details::ECC<CRYTOMETHOD>::PrivateKey>	_SK;
public:
	bool SetPrivateKey(const typename Keypair<CRYTOMETHOD>::PrivateKey& sk)
	{	try{
			Botan::BigInt s;
			Botan::BigIntAssign(s, sk);
			_SK.Reinit(*_pRNG, Botan::EC_Group(_details::ECC<CRYTOMETHOD>::ECGroupName()), s);
		}catch(...){ return false; }
		return true;
	}
};

template<bool sec>
class _Result;
	template<> class _Result<false>
	{
	protected:
		std::vector<Botan::byte>	_LastResult;
	public:
		rt::String_Ref	GetResult() const { return rt::String_Ref((LPCSTR)_LastResult.data(), _LastResult.size()); }
		UINT			GetResultSize() const { return (UINT)_LastResult.size(); }
		LPCBYTE			GetResultData() const { return _LastResult.data(); }
	};
	template<> class _Result<true>
	{
	protected:
		Botan::secure_vector<Botan::byte>	_LastResult;
	public:
		rt::String_Ref	GetResult() const { return rt::String_Ref((LPCSTR)_LastResult.data(), _LastResult.size()); }
		UINT			GetResultSize() const { return (UINT)_LastResult.size(); }
		LPCBYTE			GetResultData() const { return _LastResult.data(); }
	};

} // namespace _details


template<int CRYTOMETHOD>
class Signer: protected _details::_PrivateKeyOp<CRYTOMETHOD>
{
	typedef _details::_PrivateKeyOp<CRYTOMETHOD> _SC;
public:
	static const int SignatureSize = 64;
	typedef DataBlock<SignatureSize>	Signature;

public:
	rt::ObjectPlaceHolder<Botan::PK_Signer>	_Signer;

public:
	Signer(const typename Keypair<CRYTOMETHOD>::PrivateKey& sk, Botan::RandomNumberGenerator* rng = NULL)
	{	_SC::_RngCtor(rng);
		VERIFY(SetPrivateKey(sk));
	}
	Signer(Botan::RandomNumberGenerator* rng = NULL){ _SC::_RngCtor(rng); }
	bool SetPrivateKey(const typename Keypair<CRYTOMETHOD>::PrivateKey& sk)
	{	if(_SC::SetPrivateKey(sk))
		{	try{
				_Signer.Reinit(_SC::_SK, *_SC::_pRNG, _details::EmsaName());
			}catch(...){ return false; }
			return true;
		}else return false;
	}
	void Sign(const rt::String_Ref& d, Signature& signature_out){ Sign(d.Begin(), d.GetLength(), signature_out); }
	void Sign(LPCVOID data, UINT size, Signature& signature_out)
	{	try{
			auto sig = _Signer->sign_message((const Botan::byte*)data, size, *_SC::_pRNG);
			ASSERT(sig.size() == SignatureSize);
			signature_out = *(Signature*)sig.data();
		}catch(...){ ASSERT(0); }
	}
};

namespace _details
{

template<int CRYTOMETHOD>
class _PublicKeyOp
{
protected:
	rt::ObjectPlaceHolder<typename _details::ECC<CRYTOMETHOD>::PublicKey>	_PK;
public:
	bool SetPublicKey(const typename Keypair<CRYTOMETHOD>::PublicKey& pk)
	{	try{
			Botan::EC_Group group(_details::ECC<CRYTOMETHOD>::ECGroupName());
			auto& curve = group.get_curve();

			Botan::BigInt x, y;
			Botan::BigIntAssign(x, pk);
			
			//y = Botan::decompress_point(true, x, curve.get_curve());
			Botan::BigInt xpow3 = x * x * x;
			const Botan::BigInt& p = curve.get_p();
			
			Botan::BigInt g = curve.get_a() * x;
			g += xpow3;
			g += curve.get_b();
			g = g % p;
			
			y = Botan::ressol(g, p);
			
			if(y < 0)throw Botan::Illegal_Point("error during EC point decompression");
			if(y.get_bit(0) != x.get_bit(0))y = p - y;

			_PK.Reinit(group, Botan::PointGFp(curve, x, y));
			return true;
		}catch(...){}
		return false;
	}
};

} // namespace _details


template<int CRYTOMETHOD>
class SignatureVerifier: protected _details::_PublicKeyOp<CRYTOMETHOD>
{
	typedef _details::_PublicKeyOp<CRYTOMETHOD> _SC;
public:
	static const int SignatureSize = 64;
	typedef DataBlock<SignatureSize>	Signature;

protected:
	rt::ObjectPlaceHolder<Botan::PK_Verifier>	_Verifier;

public:
	SignatureVerifier(){}
	SignatureVerifier(const typename Keypair<CRYTOMETHOD>::PublicKey& pk){ VERIFY(SetPublicKey(pk)); }

	bool SetPublicKey(const typename Keypair<CRYTOMETHOD>::PublicKey& pk)
	{	if(_SC::SetPublicKey(pk))return _Verifier.Reinit(_SC::_PK, _details::EmsaName());
		return false;
	}
	bool Verify(const rt::String_Ref& d, const Signature& signa){ return Verify(d.Begin(), d.GetLength(), signa); }
	bool Verify(LPCVOID data, UINT size, const Signature& signa)
	{	try{
			return _Verifier->verify_message((const Botan::byte*)data, size, (const Botan::byte*)&signa, SignatureSize);
		}catch(...){ ASSERT(0); }
		return false;
	}
}; 

template<int CRYTOMETHOD>
class Encrypter: protected _details::_PublicKeyOp<CRYTOMETHOD>,
				 protected _details::_RNG_Base,
				 public _details::_Result<false>
{
	typedef _details::_PublicKeyOp<CRYTOMETHOD> _SC;
protected:
	rt::ObjectPlaceHolder<Botan::PK_Encryptor_EME>	_Encrypter;

public:
	Encrypter(const typename Keypair<CRYTOMETHOD>::PublicKey& pk, Botan::RandomNumberGenerator* rng = NULL)
	{	_details::_RNG_Base::_RngCtor(rng);
		VERIFY(SetPublicKey(pk));
	}
	Encrypter(Botan::RandomNumberGenerator* rng = NULL){ _details::_RNG_Base::_RngCtor(rng); }
	bool SetPublicKey(const typename Keypair<CRYTOMETHOD>::PublicKey& pk)
	{	if(_SC::SetPublicKey(pk))return _Encrypter.Reinit(_SC::_PK, *_SC::_pRNG, _details::Eme1Name());
		return false;
	}
	bool Encrypt(LPCVOID p, UINT sz)
	{	try{
			_Result::_LastResult = _Encrypter->encrypt((const Botan::byte*)p, sz, *_pRNG);
		}catch(...){ return false; }
		return _Result::_LastResult.size() >= sz;
	}
	bool Encrypt(const rt::String_Ref& s){ return Encrypt((const Botan::byte*)s.Begin(), s.GetLength()); }
};


template<int CRYTOMETHOD>
class Decrypter: protected _details::_PrivateKeyOp<CRYTOMETHOD>,
				 public _details::_Result<true>
{
	typedef _details::_PrivateKeyOp<CRYTOMETHOD> _SC;
protected:
	rt::ObjectPlaceHolder<Botan::PK_Decryptor_EME>	_Decrypter;
public:
	Decrypter(Botan::RandomNumberGenerator* rng = NULL){ _SC::_RngCtor(rng); }
	Decrypter(const typename Keypair<CRYTOMETHOD>::PrivateKey& pk, Botan::RandomNumberGenerator* rng = NULL){ _SC::_RngCtor(rng); VERIFY(SetPrivateKey(pk)); }

	bool SetPrivateKey(const typename Keypair<CRYTOMETHOD>::PrivateKey& pk)
	{	if(_SC::SetPrivateKey(pk))return _Decrypter.Reinit(_SC::_SK, *_SC::_pRNG, _details::EmsaName());
		return false;
	}
	bool Decrypt(LPCVOID p, UINT sz)
	{	try{
			_Result::_LastResult = _Decrypter->decrypt((const Botan::byte*)p, sz);
		}catch(...){ return false; }
		return true;
	}
	bool Decrypt(const rt::String_Ref& s){ return Decrypt((const Botan::byte*)s.Begin(), s.GetLength()); }
};
/** @}*/
} // namespace sec
