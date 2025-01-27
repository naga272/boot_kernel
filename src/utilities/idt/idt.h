#ifndef IDT_H
#define IDT_H

#include <stdint.h>


/*
* L'interrupt descriptor table descrive come gli interrupt vengono chiamati in protected mode.
* Una istanza della struct @idt_desc == a una singola voce dell'idt
* 
* La struct @idt_desc DEVE AVERE IL SEGUENTE ORDINE:
* @offset_1:    la "parte bassa" dell'indirizzo della routine da eseguire
* @selector:    contiene la routine di gestione dell'interrupt. Per le routine non usate, il campo viene settato a 0
* @zero:        non usabile, da settare a 0
* @type_attr:   tipi e attributi dell'entry. definisce il tipo di gate(interrupt gate e trap gate) e i privilegi richiesti
* @offset_2:    la "parte alta" dell'indirizzo della routine da eseguire
*
* 
* Invece la struct @idtr_desc rappresenta lo stato del registro idtr (interrupt descriptor table register)
* La struct @idtr_desc DEVE AVERE IL SEGUENTE ORDINE:
* @limit:   grandezza max della idt (sizeof(idt_desc[OS_TOTAL_INTERRUPTS]) - 1)
* @base:    indirizzo da dove parte la tabella idt_desc[OS_TOTAL_INTERRUPTS]
*
* Le struct non devono avere padding aggiunto dal compilatore, quindi uso __attribute__((packed))
*/

struct idt_desc
{
    u16 offset_1; // Offset bits 0 - 15
    u16 selector; // Selector thats in our GDT
    u8 zero; // Does nothing, unused set to zero
    u8 type_attr; // Descriptor type and attributes
    u16 offset_2; // Offset bits 16-31
} __attribute__((packed));

 
struct idtr_desc
{
    u16 limit; // Size of descriptor table -1
    u32 base; // Base address of the start of the interrupt descriptor table
} __attribute__((packed));


void idt_init();
void enable_interrupts();
void disable_interrupts();

#endif
