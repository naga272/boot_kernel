#include "stdlib.h"

#if defined(CODE_FOR_HEAP)
void* malloc(size_t size)
{
    void *tmp = current_address;
    current_address += size;
    return tmp;
}
#endif


void* memset(void* ptr, int c, size_t size)
{
    char *ptr_c = (char*) ptr;
    for (size_t i = 0; i < size; i++)
        ptr_c[i] = c;

    return ptr;
}