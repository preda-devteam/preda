#pragma once
#include "coins.h"
#include "struct.h"
#include "ordered_map.h"
#include "consecutive_set.h"

namespace rvm
{

class CoinsWallet;
class CoinsWalletMutable;
class NonFungibleVault;
class NonFungibleVaultMutable;

// representing a collection of fungible tokens
#pragma pack(push, 1)
class CoinsWallet : protected OrderedMap<TokenId, BigNum>
{
	friend class CoinsWalletMutable;
	typedef OrderedMap<TokenId, BigNum> _SC;
	typedef typename TypeTraits<_SC>::Mutable _SC_MUTABLE;

public:
	TYPETRAITS_DECLARE_NON_POD;
	RVM_IMMUTABLE_TYPE(CoinsWallet);

	UINT		GetAssetCount() const { return _SC::GetCount(); }
	auto		GetAssetId(UINT i) const { return _SC::_GetByPos(i).key(); }
	auto&		GetAssetAmount(UINT i) const { return _SC::_GetByPos(i).val(); }

	auto		GetAmount(TokenId aid) const -> const BigNum&;
	bool		IsEmpty() const { return _SC::IsEmpty(); }
	void		Jsonify(rt::Json &append) const { _SC::Jsonify(append); }
	bool		Withdraw(TokenId aid, CoinsMutable &get, CoinsWalletMutable &residue, bool allow_overflow = false) const; // residue = this - get

	UINT		GetEmbeddedSize() const { return _SC::GetEmbeddedSize(); }
	static UINT GetEmbeddedSize(const CoinsWallet &c) { return _SC::GetEmbeddedSize((_SC &)c); }
	static UINT GetEmbeddedSize(const CoinsWalletMutable &c) { return _SC::GetEmbeddedSize((_SC_MUTABLE &)c); }
	static bool	IsEmbeddable(const CoinsWallet &c){ return true; }
	static bool	IsEmbeddable(const CoinsWalletMutable &c) { return _SC::IsEmbeddable((_SC_MUTABLE &)c); }
	UINT		Embed(const CoinsWallet &c) { return _SC::Embed((_SC &)c); }
	UINT		Embed(const CoinsWalletMutable &c) { return _SC::Embed((_SC_MUTABLE &)c); }
	static void GetTypeSignature(rt::String &n) { n += rt::SS("wallet"); }
};
#pragma pack(pop)

class CoinsWalletMutable : protected OrderedMapMutable<TokenId, BigNum>
{
	friend class CoinsWallet;
	typedef OrderedMapMutable<TokenId, BigNum> _SC;
	TYPETRAITS_DECLARE_NON_POD;

public:
	CoinsWalletMutable() = default;
	CoinsWalletMutable(const CoinsWallet &x) : _SC(x) {}
	auto Assign(const CoinsWallet &x) -> CoinsWalletMutable&;
	bool IsEmpty() const { return _SC::IsEmpty(); }
	void Deposit(const Coins &x); // this += x
	bool JsonParse(const rt::String_Ref& str){ return false; /*_SC::JsonParse(str);*/ }  // TBD
};

#pragma pack(push, 1)
class NonFungibleVault : protected ConsecutiveSet<uint64_t, LONGLONG>
{
	friend class NonFungibleVaultMutable;
	typedef ConsecutiveSet<uint64_t, LONGLONG> _SC;
	typedef typename TypeTraits<_SC>::Mutable _SC_MUTABLE;
	TYPETRAITS_DECLARE_NON_POD;
	RVM_IMMUTABLE_TYPE(NonFungibleVault);

public:
	bool			IsEmpty() const { return !(_SC::_Count()); }
	void			Jsonify(rt::Json& append) const { _SC::Jsonify(append, true); }
	bool			Withdraw(TokenId aid, NonFungibleToken &get, NonFungibleVaultMutable &residue) const; // residue = this - get
	bool			WithdrawSet(const NonFungibleVault& id_set, NonFungibleVaultMutable &residue) const; // residue = this - get
	bool			WithdrawRange(const NonFungibleTokenRanged& id_range, NonFungibleVaultMutable &residue) const; // residue = this - get

	uint32_t		GetEmbeddedSize() const { return _SC::GetEmbeddedSize(); }
	static uint32_t GetEmbeddedSize(const NonFungibleVault &c) { return c.GetEmbeddedSize(); }
	static uint32_t GetEmbeddedSize(const NonFungibleVaultMutable &c) { return _SC::GetEmbeddedSize((_SC_MUTABLE &)c); }
	static bool		IsEmbeddable(const NonFungibleVault &c){ return true; }
	static bool		IsEmbeddable(const NonFungibleVaultMutable &c){ return _SC::IsEmbeddable((_SC_MUTABLE &)c);; }
	uint32_t		Embed(const NonFungibleVault &c) { return _SC::Embed((_SC &)c); }
	uint32_t		Embed(const NonFungibleVaultMutable &c) { return _SC::Embed((_SC_MUTABLE &)c); }
	static void		GetTypeSignature(rt::String &n) { n += rt::SS("vault"); }
};
#pragma pack(pop)

class NonFungibleVaultMutable : protected ConsecutiveSetMutable<uint64_t, LONGLONG>
{
	friend class NonFungibleVault;
	typedef ConsecutiveSetMutable<uint64_t, LONGLONG> _SC;
	TYPETRAITS_DECLARE_NON_POD;

public:
	NonFungibleVaultMutable() = default;
	NonFungibleVaultMutable(const NonFungibleVault &x) { _SC::Assign(x); }
	auto &Assign(const NonFungibleVault &x)
	{
		_SC::Assign(x);
		return *this;
	}
	bool IsEmpty() const { return _SC::IsEmpty(); }
	void Empty() { _SC::Empty(); }
	void Deposit(const NonFungibleToken &x);
	void Deposit(const NonFungibleVault &x);
	void Deposit(const NonFungibleTokenRanged& x);
	void Mint(TokenId nf_base_id, uint32_t count);
	bool JsonParse(const rt::String_Ref& str){ return _SC::JsonParse(str); }
	void Jsonify(rt::Json& append) const { _SC::Jsonify(append); }
};

enum TxCoreNonFungibleMode : uint32_t
{
	NFMODE_ZERO = 0,
	NFMODE_PIECE_COUNT_BITMASK			= 0x3ffffff,		// piece_count, shouldn't be one. 0 for non-series.

	NFMODE_HASHED						= (1u << 31),
	NFMODE_NAMED						= (1u << 30),
	NFMODE_ARTIST_SIGNED				= (1u << 28),
	NFMODE_PIECE_NAMED					= (1u << 27),
	NFMODE_PIECE_HASHED					= (1u << 26),
	NFMODE_NAME_MAXLEN					= 255,
};

static_assert((NFMODE_PIECE_COUNT_BITMASK& (NFMODE_HASHED | NFMODE_NAMED | NFMODE_ARTIST_SIGNED | NFMODE_PIECE_NAMED | NFMODE_PIECE_HASHED)) == 0, "NFMODE_PIECE_COUNT_BITMASK overlapping with some of other bit flags");

// NonFungible Naming Spec	|---------------------------------------------------------- Signing Range ----------------------------------------------------------------|
// piece_count>1			[TxCoreNonFungibleMode:32bits][TimeStamp][Hash:256bits][Name:string]<[PieceHash:256bits][PieceName:string] ...><[SecSuiteId:8bits][PubKey][Signature]>
// string => [length:8bit][charactors:length-bytes]
//

class NonFungibleArtworkData : protected rt::String_Ref
{
	typedef uint8_t	NAME_LEN;
	static const uint32_t	NONTRIVIAL_PIECE_MAXCOUNT = 1024;
	TxCoreNonFungibleMode	_PieceMode;
	uint16_t				_PieceOffsets[NONTRIVIAL_PIECE_MAXCOUNT];
	uint16_t				_SignatureOffset;

#pragma pack(push, 1)
	struct NF_String
	{
		NAME_LEN	len;
		char		str[1];
		rt::String_Ref Str() const { return rt::String_Ref(str, (size_t)len); }
	};
#pragma pack(pop)

public:
	NonFungibleArtworkData(const rt::String_Ref &name_str);

	bool IsEmpty() const { return _PieceMode == NFMODE_ZERO; }
	bool IsHashed() const {	return _PieceMode & NFMODE_HASHED; }
	bool IsNamed() const { return _PieceMode & NFMODE_NAMED; }
	bool IsPieceHashed() const { return _PieceMode & NFMODE_PIECE_HASHED; }
	bool IsPieceNamed() const {	return _PieceMode & NFMODE_PIECE_NAMED; }
	bool IsArtistSigned() const	{ return _PieceMode & NFMODE_ARTIST_SIGNED;	}

	rt::String_Ref		GetPrimaryName() const;
	rt::String_Ref		GetPrimaryNameSizeRestricted() const;
	const HashValue&	GetPrimaryHash() const; // nullptr if not available
	uint32_t			GetPieceCount() const { return _PieceMode & NFMODE_PIECE_COUNT_BITMASK; }
	rt::String_Ref		GetPieceName(uint32_t i) const;
	const HashValue&	GetPieceHash(uint32_t i) const;
	uint64_t 			GetTimeStamp() const;
	bool				GetArtistAddress(Address &addr) const;
	bool				VerifyArtistSignature() const;
	bool				VerifySize() const;
	bool				VerifyIntegrity() const { return IsArtistSigned() ? VerifyArtistSignature() : VerifySize(); }
	rt::String_Ref		GetSpecWithoutTimeStamp() const { return rt::String_Ref(_p + sizeof(TxCoreNonFungibleMode) + sizeof(uint64_t), _len - sizeof(TxCoreNonFungibleMode) - sizeof(uint64_t)); }
	static bool			Compose(rt::String &namespec, const rt::String_Ref &json, uint64_t timestamp, oxd::SecSuiteId ssid = oxd::SEC_SUITE_NONE, const void *sk = nullptr, uint32_t sk_size = 0);
	void				Jsonify(rt::Json &append) const;
};

} // namespace rvm

RVM_TYPETRAITS_DEF(CoinsWallet, CoinsWalletMutable)
RVM_TYPETRAITS_DEF(NonFungibleVault, NonFungibleVaultMutable)
