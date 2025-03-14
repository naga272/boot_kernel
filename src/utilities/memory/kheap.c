#include "kernel.h"
#include "kheap.h"
#include "heap.h"

struct heap         kernel_heap;
struct heap_table   kernel_heap_table;

extern void panic(const uchar*);


void kheap_init()
{
    /*
    *   Funzione che definisce il numero totale di blocchi di heap disponibili per il kernel
    * */
    int total_table_entries     = OS_HEAP_SIZE_BYTES / OS_HEAP_BLOCK_SIZE;  // restituisce 256000
    kernel_heap_table.entries   = (HEAP_BLOCK_TABLE_ENTRY*) (OS_HEAP_TABLE_ADDRESS);
    kernel_heap_table.total     = total_table_entries;

    void *end = (void*) (OS_HEAP_ADDRESS + OS_HEAP_SIZE_BYTES); // fine heap
    
    u32 response = heap_create(&kernel_heap, (void*) (OS_HEAP_ADDRESS), end, &kernel_heap_table);
    
    if (response != 0) {
        panic((const uchar*)"critical error! Impossibile allocare la memoria per il kernel");
    }
}


void* kmalloc(size_t size) 
{
    /*
    *    Funzione usata per allocare blocchi di memoria.
    *    Ogni blocco e' grande 4096 bytes. Se vengono richiesti per esempio 50 bytes, la funzione comunque restituisce 4096.
    *    Se vengono richiesti 4097 bytes, la funzione restituisce 2 blocchi (4096 * 2).
    *    La dimensione dei blocchi e' definita all'interno di config.h.
    */
    return heap_malloc(&kernel_heap, size);
}


void kfree(void* ptr)
{
    heap_free(&kernel_heap, ptr);
}
