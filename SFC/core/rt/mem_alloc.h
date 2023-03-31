#pragma once
#include "runtime_base.h"


namespace rt
{
class Json;

namespace _details
{
#ifdef PLATFORM_DEBUG_BUILD	
LPVOID	TrackMemoryAllocation(LPVOID p, SIZE_T sz, bool no_ctor, LPCSTR type, UINT co, LPCSTR fn, LPCSTR func, UINT line);
void	UntrackMemoryAllocation(LPCVOID p);
void	DumpTrackedMemoryAllocation(bool verbose = false);
template<typename T>
T*		TrackMemoryNew(T* p, LPCSTR type, LPCSTR fn, LPCSTR func, UINT line){ TrackMemoryAllocation(p, sizeof(T), false, type, 1, fn, func, line); return p; }
void	TrackedMemoryAllocationStatistic(rt::Json& json_out);
#endif

/**
 * @brief 32byte Aligned Memory allocation and free 
 * 
 * 1. use 32byte-Aligned Memory is optimized for cache hitting rate on CPUs of PIII and above
 * 
 * 2. Add prefix and suffix bytes to allocated memory block to detect buffer overflow
 * @param size 
 * @return LPVOID 
 */
LPVOID	Malloc32AL(size_t size);   ///< size in byte
void	Free32AL(LPCVOID ptr_in);
LPVOID	Malloc8AL(size_t size);   ///< size in byte
void	Free8AL(LPCVOID ptr_in);
} // namespace _details

extern void	EnableMemoryExceptionInThread(bool throw_e);  // default is disabled
extern bool	IsMemoryExceptionEnabledInThread();

} // namespace rt


#ifdef PLATFORM_DEBUG_BUILD

#define _Malloc8AL(type, co)		_Malloc32AL(type, co)
#define _Malloc32AL(type, co)		((type*)rt::_details::TrackMemoryAllocation(rt::_details::Malloc32AL(sizeof(type)*(co)), sizeof(type)*(co), true, #type , (UINT)(co), __FILE__, __FUNCTION__, __LINE__))

#define _SafeFree8AL_ConstPtr(ptr)	_SafeFree32AL_ConstPtr(ptr)
#define _SafeFree32AL_ConstPtr(ptr)	{ auto* __p__ = ptr; if(__p__){ rt::_details::UntrackMemoryAllocation(__p__); rt::_details::Free32AL(__p__); }}
#define _SafeDel_ConstPtr(ptr)		{ auto* __p__ = ptr; if(__p__){ rt::_details::UntrackMemoryAllocation(__p__); delete __p__; } }
#define _SafeDelArray_ConstPtr(ptr)	{ auto* __p__ = ptr; if(__p__){ rt::_details::UntrackMemoryAllocation(__p__); delete [] __p__; } }

#define _New(...)					(rt::_details::TrackMemoryNew(rt::IsMemoryExceptionEnabledInThread()? new __VA_ARGS__ : new (std::nothrow) __VA_ARGS__, #__VA_ARGS__, __FILE__, __FUNCTION__, __LINE__))
#define _NewArray(type, co)			((type*)rt::_details::TrackMemoryAllocation(rt::IsMemoryExceptionEnabledInThread()? new type[co] : new (std::nothrow) type[co], sizeof(type)*co, false, #type, (UINT)(co), __FILE__, __FUNCTION__, __LINE__))

#define _DumpMemoryAllocations		{ rt::_details::DumpTrackedMemoryAllocation(true); }

#else // #ifdef PLATFORM_DEBUG_BUILD

#define _Malloc8AL(type, co)		((type*)rt::_details::Malloc8AL(sizeof(type)*(co)))
#define _Malloc32AL(type, co)		((type*)rt::_details::Malloc32AL(sizeof(type)*(co)))

#define _SafeFree8AL_ConstPtr(ptr)	{ rt::_details::Free8AL(ptr); }
#define _SafeFree32AL_ConstPtr(ptr)	{ rt::_details::Free32AL(ptr); }
#define _SafeDel_ConstPtr(x)		{ if(x){delete (x); } }
#define _SafeDelArray_ConstPtr(x)	{ if(x){delete [] (x); } }

#define _New(...)					(rt::IsMemoryExceptionEnabledInThread()? new __VA_ARGS__ : new (std::nothrow) __VA_ARGS__)
#define _NewArray(type, co)			(rt::IsMemoryExceptionEnabledInThread()? new type[co] : new (std::nothrow) type[co])

#define _DumpMemoryAllocations		{}

#endif // #ifdef PLATFORM_DEBUG_BUILD

#define _SafeFree8AL(ptr)			{ _SafeFree8AL_ConstPtr(ptr); ptr = nullptr; }
#define _SafeFree32AL(ptr)			{ _SafeFree32AL_ConstPtr(ptr); ptr = nullptr; }
#define _SafeDel(ptr)				{ _SafeDel_ConstPtr(ptr); ptr = nullptr; }
#define _SafeDel_Untracked(ptr)		{ if(ptr){ delete ptr; ptr = nullptr; }}
#define _SafeDelArray(ptr)			{ _SafeDelArray_ConstPtr(ptr); ptr = nullptr; }

#define _EnlargeTo32AL(num)			((((num) + 0x7)&(~((SIZE_T)0x7))))
#define _Alloca32AL(sz)				((LPVOID)_EnlargeTo32AL((SIZE_T)alloca(sz + 4)))
#define _StackNew(type)				new (alloca(sizeof(type))) type

#ifndef PLATFORM_WIN
#define _alloca alloca
#endif

namespace rt
{

#define EnterPoolAllocatorScope(x)		rt::PooledAllocator::Scope MARCO_JOIN(_CS_Holder_,__COUNTER__)(x);

//////////////////////////////////////////////////////////////////////////////////
//	Single-thread memory allocator (optimized for speed, memory amplication is 2x)
//
//	Memory blocks are organized as 
//	~:= BlockOrderSlot[_BlockOrderMax - _BlockOrderMin + 1]
//		BlockOrderSlot:= BlockBank[BlockBankCount], dynamic sized
//						 BlockBank:= Block[BlockCount], fixed size

class PooledAllocator // not thread-safe
{
public:
	enum CompactPolicy
	{
		CompactNo = 0,
		CompactCasual,
		CompactAggressive
	};
	struct Scope
	{
		PooledAllocator& _;
		Scope(PooledAllocator& pla):_(pla){ pla.Apply(); }
		~Scope(){ _.Unapply(); }
	};
protected:
	uint32_t			_BlockOrderMin = 5;		// 32
	uint32_t			_BlockOrderMax = 20;	// 16MB
	CompactPolicy		_CompactPolicy = CompactCasual;
	uint32_t			_DefaultBankByteSize = 4U*1024U*1024U;

	struct BlockBank;
	struct BlockOrderSlot;

	BlockOrderSlot**	_OrderSlots; //[_BlockOrderMax - _BlockOrderMin + 1];

	static uint32_t		_BlockOrder(uint32_t size){ return 32 - (int)rt::LeadingZeroBits(size); }
	uint32_t			_BlockOrderSlotIndex(uint32_t size){ return rt::max(0, (int)_BlockOrder(size) - (int)_BlockOrderMin); }
	uint32_t			_BlockBankDefaultCapacity(uint32_t order){ return rt::max(4U, rt::min(_DefaultBankByteSize>>order, 4096U)); }

	uint64_t			_TotalSizeReserved = 0;
	uint64_t			_TotalSizeInUsed = 0;
	uint32_t			_TotalAllocated = 0;

protected:
#pragma pack(push, 1)
	struct BlockBank;
	struct BlockOrderSlot // collection of BlockBank, up to 64k BlockBank(s)
	{
		PooledAllocator*_pAllocator;
		uint8_t			Order;
		uint16_t		BlockBankCount;
		uint16_t		BlockBankAvail; // # of blocks remains
		uint16_t		BlockBankOccupied;
		uint16_t		BlockBankIdStack[1]; // size = BlockCount
		// followed by (BlockBank*)[BlockBankCount]

		uint32_t		GetSize() const { return (sizeof(uint16_t) + sizeof(BlockBank*))*BlockBankCount + offsetof(BlockOrderSlot, BlockBankIdStack); }
		BlockBank**		GetBlockBanks(){ return (BlockBank**)&BlockBankIdStack[BlockBankCount]; }
		void			Release();
		void*			Allocate(uint32_t size){ return BlockBankAvail?GetBlockBanks()[BlockBankIdStack[BlockBankAvail-1]]->Allocate(size):nullptr; }
	
		void			MakeBankUnavailable(uint16_t id);
		void			MakeBankAvailable(uint16_t id);
		void			MakeBankOccupied(uint16_t id){ BlockBankOccupied++; }
		void			MakeBankUnoccupied(uint16_t id);

		static BlockOrderSlot* Create(PooledAllocator* alloc, uint32_t order, uint16_t capacity, uint16_t bank_size, BlockOrderSlot* move_from = nullptr); // move_from will be released
	};
	struct BlockBank	// collection of Block, up to 64k Block(s)
	{
		BlockOrderSlot*	_pSlot;
		uint16_t		Id;
		uint32_t		BlockSize;	// = Block::GetSize()
		uint16_t		BlockCount; // # of blocks reserved for allocation
		uint16_t		BlockAvail; // # of blocks remains
		uint16_t		BlockIdStack[1]; // size = BlockCount
		// followed by  uint16_t BlockCount; // allow location BlockBank from Block
		// followed by Block[BlockCount]

		uint32_t		GetSize() const { return BlockSize*BlockCount + sizeof(uint16_t)*((uint32_t)BlockCount+1) + offsetof(BlockBank, BlockIdStack); }
		bool			IsEmpty() const { return BlockCount == BlockAvail; }
		void			Release(){ delete [] (uint8_t*)this; }
		auto*			GetBlocks() const { return (const Block*)&BlockIdStack[(uint32_t)BlockCount+1]; }
		auto*			GetBlocks(){ return (Block*)&BlockIdStack[(uint32_t)BlockCount+1]; }
		auto&			GetBlock(uint16_t i) const { return *(const Block*)(((uint8_t*)&BlockIdStack[(uint32_t)BlockCount+1]) + BlockSize*i); }
		auto&			GetBlock(uint16_t i){ return *(Block*)(((uint8_t*)&BlockIdStack[(uint32_t)BlockCount+1]) + BlockSize*i); }
		void*			Allocate(uint32_t size);
		void			Free(uint16_t id);

		static BlockBank* Create(BlockOrderSlot* slot, uint32_t order, uint16_t capacity);
	};
	struct Block
	{
		uint32_t		RequestedSize;
		uint16_t		Id;	// #th block in this bank
		uint8_t			Order;
		uint8_t			Data[1]; // available size = (1U<<Order)
		uint32_t		GetSize() const { return (1U<<Order) + (uint32_t)offsetof(Block, Data); }
		BlockBank&		GetBank();
		uint32_t		Free();
		static Block&	GetBlockFromDataPtr(const void* ptr){ return *(Block*)(((uint8_t*)ptr) - offsetof(Block, Data)); }
	};

#pragma pack(pop)

	void		_Compact(int order);
	void		_CompactAggressive(BlockOrderSlot*& slot);

public:
	PooledAllocator(int order_max = 20, int order_min = 5, CompactPolicy compact = CompactCasual, uint32_t bank_size = 4U*1024U*1024U);
	~PooledAllocator();
	void*		Allocate(uint32_t size);
	void		Free(const void* ptr){ _TotalSizeInUsed -= Block::GetBlockFromDataPtr(ptr).Free(); _TotalAllocated--; }
	void		Compact();
	uint64_t	GetTotalSizeReserved(){ return _TotalSizeReserved; }
	uint64_t	GetTotalSizeAllocated(){ return _TotalSizeInUsed; }
	uint32_t	GetTotalAllocated(){ return _TotalAllocated; }
	void		AssertIntergrity();

	// To replace the underlying default memory allocation for all related classes
	void		Apply();
	void		Unapply();
};

} // namespace rt