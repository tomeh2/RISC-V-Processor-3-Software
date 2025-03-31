#ifndef __LINEAR_ALLOCATOR_H_
#define __LINEAR_ALLOCATOR_H_

#include <mem/memory.h>

extern struct MemoryAllocatorOps linalloc_ops;

struct LinAllocPD
{
    size_t curr_offset;
};

#endif