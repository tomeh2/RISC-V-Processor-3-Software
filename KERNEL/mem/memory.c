#include <mem/memory.h>

static struct MemoryAllocator* default_alloc;

void mm_init(struct MemoryAllocator* allocator)
{
    default_alloc = allocator;
    default_alloc->ops->init(default_alloc);
}

void* mm_alloc(size_t size)
{
    if (!default_alloc)
        return NULL;

    return default_alloc->ops->alloc(default_alloc, size, 4);
}

void mm_free(void* ptr)
{
    if (!default_alloc)
        return;

    default_alloc->ops->free(default_alloc, ptr);
}