#include "../os/multi_thread.h"
#include "json.h"


namespace rt
{

namespace _details
{
thread_local bool				g_IsMemoryExceptionEnabled = false;
thread_local PooledAllocator*	g_pPooledAllocatorOverride = nullptr;
} // namespace _details

bool IsMemoryExceptionEnabledInThread()
{
	return _details::g_IsMemoryExceptionEnabled;
}

void EnableMemoryExceptionInThread(bool y)
{
	_details::g_IsMemoryExceptionEnabled = y;
}

namespace _details
{
///////////////////////////////////////////////////////////////////////////////////////////////////
//// 32byte Aligned Memory allocation layout
//// additional 32+1+4 bytes (or 32+1+8 bytes in Win64) is added to every memory block
//// 
////                 |----  Offset  ----|
//// /-- LEN-BYTE --\/-- Prefix bytes -\#/---------- User block -----------\/-- Suffix bytes --\
//// UUUUUUUUUUUUUUUUU ......... UUUUUUUUUUUUUUUUUUUUUUUUUU .... UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU
//// ^                                  ^^
//// |Original                          ||
//// \ allocated        reserved offset /\ first aligned address after LEN-BYTE, the return 
////
//// 1. LEN-BYTE (size_t) indicates the size of User block
//// 
//// 2. If the p is returned by malloc and subtracted by 8, then &p[32-p%32] is the output address
////    and the offset=32-p%32 is saved at p[offset-1] as one byte the legal range of offset is from
////    1 to 32, and this value will be checked when free and used to calculate the original address
//// 
//// 3. The Prefix bytes (size=offset-1) and Suffix bytes (size=33-offset) will be check to ensure 
////    no boundary memory written occurred (buffer overflow)
/////////////////////////////////////////////////////////////////////////////////////////////////////

LPVOID Malloc32AL(size_t size)   //size in byte
{
#pragma warning(disable:4244 4127)	// conversion from 'int' to 'BYTE', possible loss of data
									// conditional expression is constant
	LPBYTE p;
	//32 for alignment, 1 for suffix, 4(or 8) for LEN-BYTE
	uint32_t alloc_size = (uint32_t)size+32+1+(uint32_t)sizeof(size_t);
	if(_details::g_pPooledAllocatorOverride)
	{
		p = (LPBYTE)g_pPooledAllocatorOverride->Allocate(alloc_size);
	}
	else
	{
		if(g_IsMemoryExceptionEnabled)
		{
			if(size >= alloc_size)
				throw std::bad_alloc();

			p = new BYTE[alloc_size];
		}
		else
		{
			if(size >= alloc_size)
				return nullptr;

			p = new(std::nothrow) BYTE[alloc_size];
		}
	}

#if defined CPF_MEMORY_LEAK_ADDRESS
	if( p == (LPBYTE)CPF_MEMORY_LEAK_ADDRESS )
	{	ASSERT(0);
		//Leaked memory block is located, check [Call Stack] for high-level code
	}
#endif

	if(p)
	{	//Record user block size for determining the high boundary of the memory block
		*((size_t*)p) = size; //size of User block
		p += sizeof(size_t);
		int offset;
		offset = 32 - (int)( ((size_t)p) & 0x1f);	// align to 32
		p[offset-1] = offset;	//Store offset

#if defined CPF_MEMORY_LEAK_ADDRESS
		if( &p[offset] == (LPBYTE)CPF_MEMORY_LEAK_ADDRESS )
		{	ASSERT(0);
			//abnormal used memory block is located, check [Call Stack] for high-level code
		}
#endif
		//Additional guard bytes is set for detecting broundry-overwriting, 
		//which will be checked when memory free. 
		int i;
		for(i=0;i<offset-1;i++)p[i] = 0x61+i;				//Set prefix bytes to 0x61+i = "abcde..."
		for(i=0;i<33-offset;i++)p[offset+size+i] = 0x41+i;	//Set suffix bytes to 0x41+i = "ABCDE..."

#ifdef CPF_REPORT_MEMORY_ACTIVITY
		_LOG("User block [0x"<<((LPVOID)&p[offset])<<"] allocated.\n");
#endif

		return &p[offset];
	}
	else  //Allocation failed
	{	
#ifdef CPF_REPORT_MEMORY_ACTIVITY
		_LOG("\n\nOut of memory: Failed to allocate "<<((size+41)/1024)<<"KB memory block!\7\n");
#endif
		ASSERT(0);
		return nullptr;
	}
}

void Free32AL(LPCVOID ptr_in)
{
	if( ptr_in ) //NULL pointer is allowed but take no effect
	{	
#ifdef CPF_REPORT_MEMORY_ACTIVITY
		_LOG(_T("User block [0x")<<ptr_in<<_T("] try to free.\n"));
#endif
		LPCBYTE ptr = reinterpret_cast<LPCBYTE>(ptr_in);

		bool Prefix_Err_Detected = false; 
		bool Suffix_Err_Detected = false;
		size_t user_block_size = ((size_t)(-1));
		int offset = ptr[-1];
		if( offset <=32 && offset>0 )
		{	//Detect buffer overrun
			user_block_size = *((size_t*)&ptr[-offset-sizeof(size_t)]);
#if defined(PLATFORM_DEBUG_BUILD)
			memset((LPVOID)ptr_in, 0xdd, user_block_size);
#endif
			int i; 
			for(i=0;i<offset-1;i++)
			{// check prefix bytes
				if( ptr[-(offset-i)] == 0x61+i ){}
				else{ Prefix_Err_Detected = true; break; }
			}
			for(i=0;i<33-offset;i++)
			{// check suffix bytes
				if( ptr[user_block_size+i] == 0x41+i ){}
				else{ Suffix_Err_Detected = true; break; }
			}

			if( !Prefix_Err_Detected && !Suffix_Err_Detected )
			{	
				//ensure heap correctness 
				//_CheckHeap;
			
#ifdef CPF_SECURE_MEMORY_RELEASE
				rt::Zero((LPVOID)ptr_in, user_block_size);	// security enforcement
#endif
				auto* actual = &ptr[-offset-sizeof(size_t)];
				if(_details::g_pPooledAllocatorOverride)
					g_pPooledAllocatorOverride->Free(actual);
				else
					delete [] actual;
				return;
			}
		}
		else{ Prefix_Err_Detected = true; }

		LPCSTR emsg = nullptr;
		if(Prefix_Err_Detected && Suffix_Err_Detected)
		{	emsg = ("Both low and high");	}
		else if( Prefix_Err_Detected )
		{	emsg = ("Low");	}
		else if( Suffix_Err_Detected )
		{	emsg = ("High");	}
		else{ ASSERT(0); }

		_LOG("Abnormal block at 0x"<<((LPVOID)ptr)<<", "<<emsg<<" boundry was overwritten.");

		ASSERT(0);
	}
}
#pragma warning(default:4244 4127)

LPVOID Malloc8AL(size_t size)
{
	if(_details::g_pPooledAllocatorOverride)
	{
		return g_pPooledAllocatorOverride->Allocate((uint32_t)size);
	}
	else
	{
		if(g_IsMemoryExceptionEnabled)
		{
			return new BYTE[size];
		}
		else
		{
			return new(std::nothrow) BYTE[size];
		}
	}
}

void Free8AL(LPCVOID ptr_in)
{
	if(_details::g_pPooledAllocatorOverride)
		g_pPooledAllocatorOverride->Free(ptr_in);
	else
		delete [] (BYTE*)ptr_in;
}

} // namespace _details


#ifdef PLATFORM_DEBUG_BUILD
namespace _details
{

bool _TMA_Exit = false;

struct _TMA
{
	struct MemBlock
	{
		SIZE_T		Size;
		UINT		MemoSize;
		char		Memo[1];
	};

	os::CriticalSection _CS;
	rt::hash_map<SIZE_T, MemBlock*>	_TrackedMemory;
	~_TMA(){ _TMA_Exit = true; }
};

_TMA& _GetTMA()
{
	static _TMA _;
	return _;
}

LPVOID TrackMemoryAllocation(LPVOID p, SIZE_T sz, bool no_ctor, LPCSTR type, UINT co, LPCSTR fn, LPCSTR func, UINT line)
{
	if(_TMA_Exit || p == nullptr)return p;

	EnterCSBlock(_GetTMA()._CS);
	ASSERT(_GetTMA()._TrackedMemory.find((SIZE_T&)p) == _GetTMA()._TrackedMemory.end());

	// make sure zero memory footprint on heap
	LPCSTR s1 = no_ctor?"Malloc<":"New<";
	LPCSTR s2, s3;

	rt::String_Ref type_trim = rt::String_Ref(type).TrimAfter('(');  // remove ctor arguments

	if(co>1)
	{	auto x = type_trim + '[' + ']';
		s2 = ALLOCA_C_STRING(x);
	}
	else
	{	s2 = ALLOCA_C_STRING(type_trim);
	}

	{	auto x = rt::SS("> by ") + func + "() in " + rt::String_Ref(fn).GetFileName() + ':' + line;
		s3 = ALLOCA_C_STRING(x);
	}

	auto s = rt::SS() + s1 + s2 + s3;

	_TMA::MemBlock* n;
	UINT memo_size = (UINT)s.GetLength();
	if(IsMemoryExceptionEnabledInThread())
		n = (_TMA::MemBlock*) new BYTE[memo_size + sizeof(_TMA::MemBlock)];
	else
		n = (_TMA::MemBlock*) new (std::nothrow) BYTE[memo_size + sizeof(_TMA::MemBlock)];

	ASSERT(n);
	n->Size = sz;
	n->MemoSize = memo_size;
	n->Memo[s.CopyTo(n->Memo)] = 0;

	_GetTMA()._TrackedMemory[(SIZE_T&)p] = n;
	return p;
}

void UntrackMemoryAllocation(LPCVOID p)
{
	if(_TMA_Exit)return;

	if(p)
	{
		LPBYTE to_be_del;
		{	EnterCSBlock(_GetTMA()._CS);
			auto it = _GetTMA()._TrackedMemory.find((SIZE_T&)p);
			ASSERT(it != _GetTMA()._TrackedMemory.end());
			to_be_del = (LPBYTE)it->second;
			_GetTMA()._TrackedMemory.erase(it);
		}

		delete [] to_be_del;
	}
}

void DumpTrackedMemoryAllocation(bool verbose)
{
	if(_TMA_Exit)return;

	if(verbose)_LOGC(" ");

	EnterCSBlock(_GetTMA()._CS);
	SIZE_T tot = 0;
	if(_GetTMA()._TrackedMemory.size())
	{
		if(verbose)_LOGC("Dump Tracked Memory Blocks ("<<_GetTMA()._TrackedMemory.size()<<"):");
		for(auto it = _GetTMA()._TrackedMemory.begin(); it != _GetTMA()._TrackedMemory.end(); it++)
		{
			_LOGC("[0x"<<it->first<<"] "<<it->second->Size<<"B "<<it->second->Memo);
			if(verbose)
			{
				auto x = rt::String_Ref((LPCSTR)it->first, rt::min(72, (int)it->second->Size));
				LPSTR d = ALLOCA_C_STRING(x);
				for(int i=0; d[i]; i++)
					if(d[i]<' ')d[i] = ' ';
				_LOGC("    = \""<<d<<'"');
			}
			tot += it->second->Size;
		}
		if(verbose)_LOGC("Tracked memory blocks take "<<rt::tos::FileSize<>(tot));
	}
	else
	{	if(verbose)_LOGC("No tracked memory blocks");
	}
}

void TrackedMemoryAllocationStatistic(rt::Json& json)
{
	static const UINT top_alloc_max = 16;

	rt::TopWeightedValues<rt::String_Ref, top_alloc_max*3, ULONGLONG>	top_alloc;

	ULONGLONG total_size = 0;
	ULONGLONG total_memo_size = 0;
	ULONGLONG total_block = 0;

	{	EnterCSBlock(_GetTMA()._CS);
		for(auto it = _GetTMA()._TrackedMemory.begin(); it != _GetTMA()._TrackedMemory.end(); it++)
		{
			total_size += it->second->Size;
			total_memo_size += it->second->MemoSize + sizeof(_TMA::MemBlock);
			top_alloc.Sample(rt::String_Ref(it->second->Memo), it->second->Size);
		}
		total_block = _GetTMA()._TrackedMemory.size();

		// make sure zero memory footprint on heap
		// dump strings to stack, so that we can safely release the lock then compose the json output
		for(UINT i=0; i<top_alloc_max; i++)
		{
			rt::String_Ref& a = top_alloc.Get(i);
			LPSTR memo = (LPSTR)_alloca(a.GetLength());
			a.CopyTo(memo);
			a._p = memo;
		}
	}

	json.Object((
		J(TotalAllocation) = total_size,
		J(TotalBlocks) = total_block,
		J(TotalMemo) = total_memo_size
	));

	{	auto scope = json.ScopeAppendingKey("TopAllocators");
		json.Array();
		for(UINT i=0; i<10; i++)
		{
			rt::String_Ref memo;
			ULONGLONG size;
			UINT count;
			if(!top_alloc.Get(i, &memo, &size, &count))break;
			json << (
				J(Allocator) = rt::JsonEscapeString(memo),
				J(TotalSize) = size,
				J(TotalBlocks) = count
			);
		}
	}
}

} // namespace _details
#endif // #ifdef PLATFORM_DEBUG_BUILD

PooledAllocator::BlockBank* PooledAllocator::BlockBank::Create(BlockOrderSlot* slot, uint32_t order, uint16_t capacity)
{
	uint32_t block_size = (1U<<order) + (uint32_t)offsetof(Block, Data);
	uint32_t obj_size = block_size*capacity + sizeof(uint16_t)*((uint32_t)capacity+1) + offsetof(BlockBank, BlockIdStack);

	auto* b = (BlockBank*) new(std::nothrow) uint8_t[obj_size];
	b->_pSlot = slot;
	b->BlockSize = block_size;
	b->BlockCount = capacity;
	b->BlockAvail = capacity;
	for(uint16_t id=0; id<capacity; id++)
		b->BlockIdStack[capacity - id - 1] = id;

	uint8_t* p = (uint8_t*)b->GetBlocks();
	((uint16_t*)p)[-1] = capacity;

	for(uint16_t i=0; i<capacity; i++, p+=block_size)
	{
		auto& blk = *(Block*)p;
		blk.Order = (uint8_t)order;
		blk.Id = i;
		blk.RequestedSize = 0xffffffffU;
#if defined(PLATFORM_DEBUG_BUILD)
		memset(blk.Data, 0xcd, (size_t)1<<order);
#endif
	}

	return b;
}

void* PooledAllocator::BlockBank::Allocate(uint32_t size)
{
	if(BlockAvail)
	{
		if(BlockAvail == BlockCount)
		{
			_pSlot->MakeBankOccupied(Id);
		}

		BlockAvail--;
		auto& b = GetBlock(BlockIdStack[BlockAvail]);
#if defined(PLATFORM_DEBUG_BUILD)
		memset(b.Data, 0xcd, (size_t)1<<b.Order);
#endif
		if(BlockAvail == 0) // this bank turns to unavailable
		{
			_pSlot->MakeBankUnavailable(Id);
		}

		b.RequestedSize = size;
		return b.Data;
	}

	return nullptr;
}

void PooledAllocator::BlockBank::Free(uint16_t id)
{
#if defined(PLATFORM_DEBUG_BUILD)
	ASSERT(BlockAvail < BlockCount);
	for(uint32_t i=0; i<BlockAvail; i++)
		ASSERT(BlockIdStack[i] != id);
#endif

	BlockIdStack[BlockAvail++] = id;
	if(BlockAvail == 1) // this bank turns to available
	{
		_pSlot->MakeBankAvailable(Id);
	}
	else if(IsEmpty())
	{
		_pSlot->MakeBankUnoccupied(Id);
	}
}

void PooledAllocator::BlockOrderSlot::Release()
{
	BlockBank**	from = GetBlockBanks();
	for(uint32_t i=0; i<BlockBankCount; i++)
		_SafeRelease_ConstPtr(from[i]);

	delete [] (uint8_t*)this;
}

PooledAllocator::BlockOrderSlot* PooledAllocator::BlockOrderSlot::Create(PooledAllocator* alloc, uint32_t order, uint16_t capacity, uint16_t bank_size, PooledAllocator::BlockOrderSlot* move_from)
{
	uint32_t obj_size = (sizeof(uint16_t) + sizeof(BlockBank*))*capacity + (uint32_t)offsetof(BlockOrderSlot, BlockBankIdStack);
	auto* s = (BlockOrderSlot*)new(std::nothrow) uint8_t[obj_size];
	s->_pAllocator = alloc;
	s->Order = order;
	s->BlockBankCount = capacity;
	s->BlockBankAvail = 0;
	s->BlockBankOccupied = 0;
	//for(uint32_t id = 0; id<capacity; id++)
	//	BlockBankIdStack[capacity - id - 1] = id;

	BlockBank** to = s->GetBlockBanks();
	uint32_t to_count = 0;

	if(move_from)
	{
		// should be compatible
		ASSERT(order == move_from->Order);
		bank_size = move_from->GetBlockBanks()[0]->BlockCount;

		BlockBank**	from = move_from->GetBlockBanks();
		uint32_t from_count = move_from->BlockBankCount;

		for(uint32_t i=0; i<from_count; i++)
		{
			if(!from[i]->IsEmpty())
			{
				ASSERT(to_count < capacity); // capacity should be able to carry all non-empty banks
				(to[to_count++] = from[i])->_pSlot = s;
				from[i] = nullptr;
			}
		}

		for(uint32_t i=0; i<from_count && to_count < capacity; i++)
		{
			if(from[i])
			{
				(to[to_count++] = from[i])->_pSlot = s;
				from[i] = nullptr;
			}
		}

		move_from->Release();
	}

	while(to_count<capacity)
	{
		to[to_count++] = BlockBank::Create(s, order, bank_size);
	}

	for(uint32_t id = capacity; id>0;)
	{
		id--;
		to[id]->Id = id;
		if(to[id]->BlockAvail)
			s->BlockBankIdStack[s->BlockBankAvail++] = id;

		if(!to[id]->IsEmpty())
			s->BlockBankOccupied++;
	}

	return s;
}

void PooledAllocator::BlockOrderSlot::MakeBankUnavailable(uint16_t id)
{
	BlockBankAvail--;
	ASSERT(id == BlockBankIdStack[BlockBankAvail]); // always consume bank at stack top
}

void PooledAllocator::BlockOrderSlot::MakeBankAvailable(uint16_t id)
{
#if defined(PLATFORM_DEBUG_BUILD)
	ASSERT(BlockBankAvail < BlockBankCount);
	for(uint32_t i=0; i<BlockBankAvail; i++)
		ASSERT(BlockBankIdStack[i] != id);
#endif

	BlockBankIdStack[BlockBankAvail++] = id;
}

void PooledAllocator::BlockOrderSlot::MakeBankUnoccupied(uint16_t id)
{
	BlockBankOccupied--;

	auto cp = _pAllocator->_CompactPolicy;
	if(cp != CompactNo)
		_pAllocator->_Compact(Order);
}

PooledAllocator::BlockBank& PooledAllocator::Block::GetBank()
{
	auto* p = ((uint8_t*)this) - ((1U<<Order) + (uint32_t)offsetof(Block, Data))*Id;
	p-=2;
	return *(BlockBank*)(p - (*(uint16_t*)p)*sizeof(uint16_t) - offsetof(BlockBank, BlockIdStack));
}

uint32_t PooledAllocator::Block::Free()
{
#if defined(PLATFORM_DEBUG_BUILD)
	auto* alloc = GetBank()._pSlot->_pAllocator;
	ASSERT(Order >= alloc->_BlockOrderMin);
	ASSERT(Order <= alloc->_BlockOrderMax);
	memset(Data, 0xdd, (size_t)1<<Order);
#endif

	auto ret = RequestedSize;
	RequestedSize = 0xffffffffU;

	GetBank().Free(Id); 
	return ret;
}

void* PooledAllocator::Allocate(uint32_t size)
{
	uint32_t order_index = _BlockOrderSlotIndex(size);
	uint32_t order = order_index + _BlockOrderMin;

	if(order > _BlockOrderMax)return nullptr;

	auto& slot = _OrderSlots[order_index];
	if(!slot)
	{
		slot = BlockOrderSlot::Create(this, order, 1, _BlockBankDefaultCapacity(order), nullptr);
		_TotalSizeReserved += slot->GetBlockBanks()[0]->BlockCount*(1U<<order);
	}
	
	if(slot->BlockBankAvail == 0)
	{
		uint32_t add;
		switch (_CompactPolicy)
		{
		case rt::PooledAllocator::CompactNo:			add = slot->BlockBankCount;			break;
		case rt::PooledAllocator::CompactCasual:		add = slot->BlockBankCount/2;		break;
		case rt::PooledAllocator::CompactAggressive:	add = slot->BlockBankCount/16;		break;
		default: ASSERT(0);
		}

		add = rt::max(1U, add);
		_TotalSizeReserved += slot->GetBlockBanks()[0]->BlockCount*(1U<<order)*add;
		slot = BlockOrderSlot::Create(this, order, slot->BlockBankCount + add, _BlockBankDefaultCapacity(slot->Order), slot);
	}

	void* ptr = slot->Allocate(size);
	if(ptr)
	{
		_TotalAllocated++;
		_TotalSizeInUsed += size;
		return ptr;
	}

	return nullptr;
}

PooledAllocator::PooledAllocator(int order_max, int order_min, CompactPolicy compact, uint32_t bank_size)
{
	ASSERT(order_max > order_min);

	_BlockOrderMin = order_min;
	_BlockOrderMax = order_max;
	_CompactPolicy = compact;
	_DefaultBankByteSize = bank_size;

	typedef BlockOrderSlot* LPBLOCKORDERSLOT;
	_OrderSlots = new(std::nothrow) LPBLOCKORDERSLOT[order_max - order_min + 1];
	rt::Zero(_OrderSlots, sizeof(LPBLOCKORDERSLOT)*(order_max - order_min + 1));
}

void PooledAllocator::_Compact(int order)
{
	ASSERT(_CompactPolicy != CompactNo);

	auto& slot = _OrderSlots[order-_BlockOrderMin];
	if(_CompactPolicy == CompactCasual)
	{
		if(slot->BlockBankOccupied)
		{
			if(slot->BlockBankOccupied < slot->BlockBankCount/4)
			{
				_TotalSizeReserved -= slot->GetBlockBanks()[0]->BlockCount*(1U<<slot->Order)*(slot->BlockBankCount - slot->BlockBankCount/4);
				slot = BlockOrderSlot::Create(this, slot->Order, slot->BlockBankCount/4, 0, slot);
			}
		}
	}
	else if(_CompactPolicy == CompactAggressive)
	{
		ASSERT(slot->BlockBankOccupied < slot->BlockBankCount);
		_CompactAggressive(slot);
	}
}

void PooledAllocator::_CompactAggressive(BlockOrderSlot*& slot)
{
	if(slot->BlockBankOccupied)
	{
		if(slot->BlockBankOccupied < slot->BlockBankCount)
		{
			_TotalSizeReserved -= slot->GetBlockBanks()[0]->BlockCount*(1U<<slot->Order)*(slot->BlockBankCount - slot->BlockBankOccupied);
			slot = BlockOrderSlot::Create(this, slot->Order, slot->BlockBankOccupied, 0, slot);
		}
	}
	else
	{
		_TotalSizeReserved -= slot->GetBlockBanks()[0]->BlockCount*(1U<<slot->Order)*slot->BlockBankCount;
		_SafeRelease(slot);
	}
}

void PooledAllocator::Compact()
{
	for(uint32_t i=0; i<=_BlockOrderMax-_BlockOrderMin; i++)
	{
		auto& slot = _OrderSlots[i];
		if(slot)_CompactAggressive(slot);
	}
}

void PooledAllocator::AssertIntergrity()
{
#if defined(PLATFORM_DEBUG_BUILD)
	uint64_t used = 0;
	uint64_t reserved = 0;
	uint32_t allocated = 0;
	for(uint32_t i=0; i<=_BlockOrderMax-_BlockOrderMin; i++)
	{
		auto& slot = _OrderSlots[i];
		if(slot)
		{
			uint32_t avail = 0;
			uint32_t occupied = 0;
			for(uint32_t b=0; b<slot->BlockBankCount; b++)
			{
				auto* bank = slot->GetBlockBanks()[b];
				if(bank->BlockAvail)avail++;
				if(!bank->IsEmpty())occupied++;

				uint32_t block_avail = 0;
				for(uint32_t k=0; k<bank->BlockCount; k++)
				{
					auto& blk = bank->GetBlock(k);
					if(blk.RequestedSize == 0xffffffffU)
					{
						block_avail++;
					}
					else
					{
						used += blk.RequestedSize;
						allocated++;
					}

					reserved += 1ULL<<blk.Order;
				}

				ASSERT(block_avail == bank->BlockAvail);
			}

			ASSERT(slot->BlockBankAvail == avail);
			ASSERT(slot->BlockBankOccupied == occupied);
		}
	}

	ASSERT(used == _TotalSizeInUsed);
	ASSERT(reserved == _TotalSizeReserved);
	ASSERT(allocated == _TotalAllocated);
#endif
}

namespace _details
{

struct PooledAllocatorStack
{
	static const uint32_t	STACK_DEPTH = 32;
	PooledAllocator*		_Stack[STACK_DEPTH];
	uint32_t				_StackPosNext = 0;

	PooledAllocatorStack() = default;
	~PooledAllocatorStack(){ ASSERT(_StackPosNext==0); }
	auto*	Get(){ return _StackPosNext?_Stack[_StackPosNext-1]:nullptr; }
	void	Push(PooledAllocator* p)
			{	
				ASSERT(Get() == g_pPooledAllocatorOverride);
				ASSERT(_StackPosNext<=STACK_DEPTH);  // overflow
				_Stack[_StackPosNext++] = p;
				g_pPooledAllocatorOverride = p;
			}
	void	Pop(PooledAllocator* p)
			{
				ASSERT(Get() == p);
				_StackPosNext--;
				g_pPooledAllocatorOverride = Get();
			}
	bool	IsStacked(PooledAllocator* p) const
			{
				for(uint32_t i=0; i<_StackPosNext; i++)
					if(_Stack[i] == p)return true;
				return false;
			}
};

thread_local PooledAllocatorStack _CurrentPooledAllocator;

} // namespace _details

void PooledAllocator::Apply()
{
	_details::_CurrentPooledAllocator.Push(this);
}

void PooledAllocator::Unapply()
{
	_details::_CurrentPooledAllocator.Pop(this);
}

PooledAllocator::~PooledAllocator()
{
	ASSERT(!_details::_CurrentPooledAllocator.IsStacked(this));

	for(auto i=0U; i<= _BlockOrderMax - _BlockOrderMin; i++)
		_SafeRelease_ConstPtr(_OrderSlots[i]);

	typedef BlockOrderSlot* LPBLOCKORDERSLOT;
	delete [] (LPBLOCKORDERSLOT*)_OrderSlots;
}

} // namespace rt