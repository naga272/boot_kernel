#include "stdlib.h"


void* memset(void* ptr, int c, size_t size)
{
    char *ptr_c = (char*) ptr;
    for (size_t i = 0; i < size; i++)
        ptr_c[i] = c;

    return ptr;
}


#if defined(CODE_FOR_HEAP)

void* malloc(size_t size)
{
    void *tmp = current_address;
    current_address += size;
    return tmp;
}


void* calloc(size_t size)
{
    void *tmp = current_address;
    current_address += size;
    return memset(tmp, 0, size);
}

#endif
