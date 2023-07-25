#pragma once
#include "../abi/vm_types.h"
#include "../../../oxd_libsec/oxd_libsec.h"


#define RVM_IMMUTABLE_TYPE(T)		T() = delete;						\
									T(const T&) = delete;				\
									T& operator = (const T&) = delete;	\

#define RVM_BLOBDATA_SIZEMAX				16000*1024		// must < 16,000 KB
#define RVM_STRING_SIZEMAX					64000			// must < 64,000 B
#define RVM_SMALLARRAY_SIZEMAX				4096
#define RVM_NONFUNGIBLE_PRIMARY_SIZEMAX		16
#define RVM_STRUCT_HEADER_SIZE				4

static_assert(sizeof(rvm::Address) == sizeof(oxd::SecureAddress));
