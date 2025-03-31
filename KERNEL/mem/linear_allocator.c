#include <mem/linear_allocator.h>
#include <string.h>
#include <stdio.h>

void linalloc_init(struct MemoryAllocator* alloc)
{
    struct LinAllocPD* private_data = (struct LinAllocPD*) alloc->private_data;
    private_data->curr_offset = 0;
    //printf("[Linear Allocator]: Initialized allocator of size %d bytes at 0x%08x\n\r", alloc->size, alloc->buffer);
}

void* linalloc_alloc(struct MemoryAllocator* alloc, size_t size, size_t alignment)
{
    struct LinAllocPD* private_data = (struct LinAllocPD*) alloc->private_data;
    unsigned char* curr_ptr = alloc->buffer + private_data->curr_offset;

    // Align to whatever is set in alignment
    unsigned int modulo = (unsigned int) curr_ptr & (alignment - 1);
    if (modulo)
    {
        curr_ptr += alignment - modulo;
        private_data->curr_offset += alignment - modulo;
    }

    if (private_data->curr_offset + size <= alloc->size)
    {
        // We have enough memory left, so allocate it
        private_data->curr_offset += size;
        memset(curr_ptr, 0, size);

        //printf("[Linear Allocator]: Allocated %d bytes at 0x%08x\n\r", size, curr_ptr);
        return curr_ptr;
    }
    //printf("[Linear Allocator]: Out of memory\n\r", size, curr_ptr);
    // Not enough memory, return NULL
    return NULL;
}

void* linalloc_free(struct MemoryAllocator* alloc, void* ptr)
{
    // No free functionality
    //printf("[Linear Allocator]: Free called but not implemented\n\r");
    return NULL;
}

struct MemoryAllocatorOps linalloc_ops =
{
    .init = linalloc_init,
    .alloc = linalloc_alloc,
    .free = linalloc_free
};