#ifndef KHEAP_H
    #define KHEAP_H

#include <stddef.h>

// funzione che inizializza l'heap del kernel.
void kheap_init();
void* kmalloc(size_t);
void kfree(void*);

#endif