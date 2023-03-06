#pragma once
#include "typetraits.h"


namespace rvm
{

///////////////////////////////////////////////////////////////////
// Serialization layout of compound type with fixed/dynamic number of members: contract, struct, class, array, vector, set, map
//
// (PATTERN_FLAG: lower 4bits of first byte)
// Offset Type Size (lower bits #0-1): defines size of count value and offset value
// 0:8b, 1:16b, 2:24b, 3:32b
// Offset Table Count (lower bits #2-3): defines # of offset tables attached.
//
// memory layout
// PATTERN_FLAG = 0: [Flag:4b][Count: 4b]<[OffsetTable: 1*Count bytes]><ActualData ... >
// PATTERN_FLAG = 1: [Flag:4b][Count:12b]<[OffsetTable: 2*Count bytes]><ActualData ... >
// PATTERN_FLAG = 2: [Flag:4b][Count:20b]<[OffsetTable: 3*Count bytes]><ActualData ... >
// PATTERN_FLAG = 3: [Flag:4b][Count:28b]<[OffsetTable: 4*Count bytes]><ActualData ... >
// 
// ** offset table = [Ending offset of element0][Ending offset of element1] ... [Ending offset of element#count-1]
//                                                                               ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  <-= also is the total size of all embedded elements


#pragma pack(push, 1)
template<typename OFF, int ElementCount>
class StructTypeHeaderT
{
	static const int		PATTERN_FLAG_BITS = 4;
	typedef OFF				OFFSET_VALUE_TYPE;
	static const int		OFFSET_VALUE_MAX = rt::TypeTraits<OFF>::MaxVal();

	static_assert(rt::NumericTraits<OFF>::IsUnsigned, "StructTypeHeader::ValueT must be unsigned");
	static_assert(sizeof(OFF)<=4, "StructTypeHeader::ValueT should not exceed 32-bit");

	OFF						_Offsets[1 + ElementCount];
public:
	static const int		Flag = (sizeof(OFF)-1) | (1<<2);   // we have 1 offset table attached

	static uint32_t	GetSize(){ return sizeof(_Offsets); }
	uint32_t		GetStateSize() const { return sizeof(_Offsets) + _Offsets[ElementCount]; }
	auto			GetBaseAddress() const -> const uint8_t* { return (const uint8_t*)&_Offsets[ElementCount+1]; }
	uint8_t*		GetBaseAddress(){ return (uint8_t*)&_Offsets[ElementCount+1]; }
	uint32_t		GetOffset(int i) const { ASSERT(i < ElementCount); return _Offsets[i+1]; }
	template<int ELE_IDX>
	uint32_t		GetOffset() const {	ASSERT(ELE_IDX < ElementCount); return _Offsets[1+ELE_IDX]; }
	template<typename T>
	auto&			Get(int i) const { return *(T*)(i?(GetBaseAddress() + GetOffset(i-1)):GetBaseAddress()); }
	template<typename T, int ELE_IDX>
	auto&			Get() const { return *(T*)(ELE_IDX?(GetBaseAddress() + GetOffset<ELE_IDX-1>()):GetBaseAddress()); }

	StructTypeHeaderT(){ Empty(); }
	void			Empty(){ _Offsets[0] = Flag; }
	void			Finalize(){ _Offsets[0] = (ElementCount<<PATTERN_FLAG_BITS) | Flag; }
	bool			IsEmpty() const { return (_Offsets[0] >> PATTERN_FLAG_BITS) == 0; }
	bool			IsValid() const 
					{	return	((*(uint32_t*)&_Offsets[0])&0x3 == sizeof(OFF)/8) && 
								(((*(uint32_t*)&_Offsets[0])>>2) == 1) &&
								(((uint32_t)_Offsets[0]) >> PATTERN_FLAG_BITS) == ElementCount;
					}
	OFF*			GetOffsetTable(){ return _Offsets + 1; }
	void			SetOffsetTable(const OFF* p)
					{	memcpy(&_Offsets[1], p, sizeof(OFF)*ElementCount);
						Finalize();
					}
};

class StructTypeHeader
{
	static const int	PATTERN_FLAG_BITS = 4;
	uint8_t				_Offsets[4];	// variable length field, ideally can be 1 byte long.
										// However, GetElementCount() is always accessing the first 4 bytes, hence adding 3 bytes of padding here
	int					_ValueSize() const { return 1 + (_Offsets[0]&0x3); }
	uint32_t			_Bitmask() const { return 0xffffffffU >> (32 - _ValueSize()*8); }
public:
	uint32_t			GetElementCount() const { return (((*(uint32_t*)_Offsets))&_Bitmask()) >> PATTERN_FLAG_BITS; }
	uint32_t			GetStateSize() const 
						{	uint32_t valsz = _ValueSize();
							uint32_t ele_val = GetElementCount()*valsz;
							return ele_val + valsz + (((*(uint32_t*)(_Offsets + ele_val)))&_Bitmask());
						}
	uint32_t			GetOffset(int i) const { return ((*(uint32_t*)(_Offsets + (i+1)*_ValueSize())))&_Bitmask();	}
	void				UpdateOffsetTable(LPCVOID p){ memcpy(&_Offsets[_ValueSize()], p, _ValueSize()*GetElementCount()); }
	static uint32_t		GetOffsetTypeSize(uint8_t first_byte){ return (first_byte&0x3) + 1; }
	static uint32_t		GetElementCount(const uint8_t* first_value, uint32_t valsz){ return ((*(uint32_t*)first_value)&(0xffffffffU >> (32 - valsz*8))) >> PATTERN_FLAG_BITS; }
	static uint32_t		GetSize(uint32_t valsz, uint32_t ele_co){ return valsz*(ele_co+1); }
};
#pragma pack(pop)

static_assert(sizeof(StructTypeHeader) == RVM_STRUCT_HEADER_SIZE);

} // namespace rvm