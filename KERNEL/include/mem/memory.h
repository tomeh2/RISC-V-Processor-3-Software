#ifndef __MEMORY_H_
#define __MEMORY_H_

#include <stddef.h>

struct MemoryAllocator;

struct MemoryAllocatorOps
{
    void (*init)(struct MemoryAllocator* alloc);
    void* (*alloc)(struct MemoryAllocator* alloc, size_t size, size_t alignment);
    void* (*free)(struct MemoryAllocator* alloc, void* ptr);
};

struct MemoryAllocator
{
    size_t size;
    unsigned char* buffer;
    void* private_data;
    struct MemoryAllocatorOps* ops;
};

void mm_init(struct MemoryAllocator* allocator);
void* mm_alloc(size_t size);
void mm_free(void* ptr);

#endif