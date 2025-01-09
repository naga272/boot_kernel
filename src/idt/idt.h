#ifndef IDT_H
#define IDT_H

#include <stdint.h>


/*
* L'interrupt descriptor table descrive come gli interrupt vengono chiamati in protected mode.
* Gli interrupt possono essere mappati ovunque in memoria
* La struct @idt_descr DEVE AVERE IL SEGUENTE ORDINE:
* @offset_1:    la "parte bassa" dell'indirizzo della routine da eseguire
* @selector:    contiene la routine di gestione dell'interrupt. Per le routine non usate, il campo viene settato a 0
* @zero:        non usabile, da settare a 0
* @type_attr:   tipi e attributi dell'entry. definisce il tipo di gate(interrupt gate e trap gate) e i privilegi richiesti
* @offset_2:    la "parte alta" dell'indirizzo della routine da eseguire
*
* la struct non deve avere pudding aggiunto dal compilatore
*/

struct idt_desc
{
    uint16_t offset_1; // Offset bits 0 - 15
    uint16_t selector; // Selector thats in our GDT
    uint8_t zero; // Does nothing, unused set to zero
    uint8_t type_attr; // Descriptor type and attributes
    uint16_t offset_2; // Offset bits 16-31
} __attribute__((packed));

 
struct idtr_desc
{
    uint16_t limit; // Size of descriptor table -1
    uint32_t base; // Base address of the start of the interrupt descriptor table
} __attribute__((packed));


void idt_init();

#endif