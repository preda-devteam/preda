#include "Allocator.h"

namespace transpiler {

	void* Allocator::AllocateMemory(size_t size)
	{
		// Do not use malloc here, since the pointers will be later released using delete, which will cause inconsistency
		return new unsigned char[size];
	}

}
