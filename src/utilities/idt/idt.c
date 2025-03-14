#include "utilities/stdlib/stdlib.h"
#include "config.h"
#include "idt.h"
#include "utilities/io/io.h"
#include "utilities/keyboard/keyboard.h"


void terminal_writechar(char c, char colour);
void print(const uchar*);
void panic();                           // per la divisione per 0 (per il momento for fun LOL)


// colore caratteri per interrupt 21h
extern char actual_color_terminal;      
// extern unsigned char keyboard_buffer[OS_SIZE_SHELL_COMMAND];    // usata in int21h_handler
// extern u32 counter_buffer;                                      // usata in int21h_handler


/*
*   Interrupt Descriptor Table (IDT)
*   Quando eravamo in real mode, usavamo gli interrupt della interrupt vector table.
*   In protected mode si usa la interrupt descriptor table, che descrive come gli interrupt
*   vengono chiamati in protected mode (nb. gli int possono essere mappati ovunque in memoria)
*   Name        bit         Description
*   offset      46-63       The higher part of the offset to execute
*   P           47          This shoul be set to 0 for unused interrupts
*   DPL         45-46       The ring level the processor requires to call this int
*   S           44          should be set to zero for trap gates
*   Type        40-43       The type of gate 
*   zero        32-39       Unused bit
*   Selector    16-31       The selector this interrupt is bounded to IE the kernel code
*   Offset      0-15        The lower part of the offset to execute
*/


struct idt_desc idt_descriptors[OS_TOTAL_INTERRUPTS];   // ogni elemento rappresenta un'interrupt
struct idtr_desc idtr_descriptor;                       // rappresenta il registro idtr (interrupt descriptor table register)


// si trova in idt.asm (carica la idt)
extern void idt_load(struct idtr_desc* ptr);    
// extern void addc_to_kb_buffer(char c);


/*
*   GESTIONE DEGLI INTERRUPT: 
*   Quando si verifica un interrupt, il processore cerca la corrispondente voce nella IDT e chiama la funzione di gestione specificata. 
*   Se viene premuto per esempio un tasto, viene triggerato l'interrupt 0x21, e il processore chiama int21h, 
*   che a sua volta chiama int21h_handler per gestire l'evento.
*/


/*
* funzioni di gestione degli interrupt (descritte in idt.asm):
*   - no_interrupt():   e' un handler generico per interrupt non gestiti
*   - int21h():         e' specifico per l'interrupt 0x21, che è tipicamente associato alla tastiera.
*   - idt_zero():       gestisce l'interrupt 0, divisione per 0
*/
extern void no_interrupt();
extern void int21h();
extern void int20h();

void idt_zero()
{
    panic();
}


void no_interrupt_handler()
{
    /*
    *   Funzione che viene chiamata quando viene generato un interrupt non gestito. 
    *   Invia un segnale di "End of Interrupt" (EOI) al PIC (Programmable Interrupt Controller) 
    *   per indicare che l'interrupt è stato gestito.
    */
    outb(0x20, 0x20);
}

extern void kb_set_c(uchar c);
void int21h_handler()
{
    /*
    *   Funzione che gestisce l'interrupt 0x21 (tastiera). 
    *   Quando viene premuto un tasto, questa funzione stampa un messaggio e invia un EOI al PIC. 
    */
    
    // insb(0x60) legge il codice del tasto dalla porta 0x60
    // per poi convrtirlo nel codice del tasto in un carattere
    // keyboard_map definita in utilities/keyboard/keyboard.c
    u8 scancode = insb(0x60);
    
    if (scancode == SHIFT_LEFT_PRESS || scancode == SHIFT_RIGHT_PRESS)
        test.maiusc = 1;
    else if (scancode == SHIFT_LEFT_RELEASE || scancode == SHIFT_RIGHT_RELEASE)
        test.maiusc = 0;
    
    if (scancode == CAPS_LOCK_SCANCODE)
        test.capslock = !test.capslock;

    uchar c = keyboard_map_QZERTY[insb(0x60)];     

    if (c != 0) {

        if (c == '\n') {
            print((uchar*) "\n");
            //print((unsigned char*) keyboard_buffer);

            // azzero il buffer della tastiera a ogni comando
            // memset((void*) keyboard_buffer, 0, OS_SIZE_SHELL_COMMAND); 
            // counter_buffer = 0;

            print((uchar*) ">>>");
        } else {    
            terminal_writechar(
                convert_case(c), 
                actual_color_terminal
            );
            
            //counter_buffer++;
        }
    }

    outb(0x20, 0x20);
}


void int20h_handler()
{
    // scheduler();
}


void idt_set(u32 interrupt_no, void* address)
{
    /*
    *   @interrupt_no:  Numero dell'interrupt
    *   @address:       Puntatore a funzione che viene triggerato dopo un'evento
    */
    struct idt_desc* desc = &idt_descriptors[interrupt_no]; // rappresenta un singolo interrupt
    desc->offset_1  = (u32) address & 0x0000ffff;       
    desc->selector  = KERNEL_CODE_SELECTOR;
    desc->zero      = 0x00;
    desc->type_attr = 0xEE;
    desc->offset_2  = (u32) address >> 16;
}


void idt_init()
{
    memset(idt_descriptors, 0, sizeof(idt_descriptors)); // azzero tutti i campi della tabella
    
    idtr_descriptor.limit   = sizeof(idt_descriptors) - 1;
    idtr_descriptor.base    = (u32) idt_descriptors;


    for (u16 i = 0; i < OS_TOTAL_INTERRUPTS; i++)
        idt_set(i, no_interrupt);

    idt_set(0, idt_zero);
    //idt_set(0x20, int20h);
    idt_set(0x21, int21h);

    // Load the interrupt descriptor table
    idt_load(&idtr_descriptor);
}
