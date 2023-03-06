#pragma once
#include <memory>

namespace transpiler {

	//Allocator used for allocating memory, currently just a simple wrapper for operator new
	struct Allocator
	{
		template<class T, typename... Args>
		static std::shared_ptr<T> New(Args... args)
		{
			void *pMemory = AllocateMemory(sizeof(T));		// Allocate memory
			return std::shared_ptr<T>(new(pMemory) T(args...));	// Placement new
		}

		static void* AllocateMemory(size_t size);
	};

}
