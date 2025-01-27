#include "kheap.h"
#include "heap.h"

struct heap         kernel_heap;
struct heap_table   kernel_heap_table;


void kheap_init()
{
    int total_table_entries     = OS_HEAP_SIZE_BYTES / OS_HEAP_BLOCK_SIZE;  // restituisce 256000
    kernel_heap_table.entries   = 0x00;
    kernel_heap_table.total     = total_table_entries;
}