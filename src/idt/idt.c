
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
*/


#include "config.h"
#include "idt/idt.h"
#include "io/io.h"
#include "stdlib/stdlib.h"

#include "enigma/keyboard.h"    // definizione tastiera itialiana standard QZERTY
#include "enigma/enigma.h"


struct idt_desc idt_descriptors[OS_TOTAL_INTERRUPTS];   // ogni elemento rappresenta un'interrupt
struct idtr_desc idtr_descriptor;                       // rappresenta il registro idtr (interrupt descriptor table register)


// funzioni che si trovano in idt.asm 
extern void idt_load(struct idtr_desc* ptr); // (carica la idt)
extern void no_interrupt(); // usato per l'assegnamento di una funzione di default agli interrupt
extern void int21h();       // interrupt per la tastiera


void no_interrupt_handler()
{
    /*
    *   Funzione che viene chiamata quando viene generato un interrupt non gestito. 
    *   Invia un segnale di "End of Interrupt" (EOI) al PIC (Programmable Interrupt Controller) 
    *   per indicare che l'interrupt è stato gestito.
    */
    outb(0x20, 0x20);
}


void int21h_handler()
{
    /*
    *   Funzione che gestisce l'interrupt 0x21 (tastiera). 
    *   Quando viene premuto un tasto, questa funzione stampa un messaggio e invia un EOI al PIC. 
    */
    
    // insb(0x60) legge il codice del tasto dalla porta 0x60 (in al, 0x60)
    // per poi convertirlo nel codice del tasto in un carattere
    // keyboard_map_<tipo tastiera> definita in enigma.h (sono definite solo QZERTY e QWERTY)
    uchar 
        container,
        c_crypt;

    // cattura il segnale da tastiera e lo mappo
    container = keyboard_map_QZERTY[insb(0x60)] - 32;

    if (container >= (u8) 'A' && container <= (u8) 'Z') {
        /*  
        *   ight, fino a qui sono sopravvisuto, questo controllo serve a evitare un bug per gli interrupt 
        *   (prende dei caratteri che non vengono letti da tastiera, penso che avvenga una sorta di overflow). 
        *   Dato che a me servono solo i caratteri da 'A' alla 'Z' e non ho tempo per starci dietro, 
        *   posso risolverla facilmente col controllo (DO KISS).
        */

        /* INIZIO FASE PLUGBOARD */
        c_crypt = m_plugboard(container);

        /* INIZIO FASE ROTORI*/ 
        c_crypt = rotore1[(u8) c_crypt - (u8) 'A'];
        rotore1 = gira_rotore(rotore1);
        count_rotore1++;

        // passaggio al secondo rotore
        c_crypt = rotore2[(u8) c_crypt - (u8) 'A'];

        // passaggio al terzo rotore
        c_crypt = rotore3[(u8) c_crypt - (u8) 'A'];
    
        if (count_rotore1 == 26) {
            count_rotore1 = 1;
            count_rotore2++;
            rotore2 = gira_rotore(rotore2);
        
            if (count_rotore2 == 26) {
                count_rotore2 = 1;
                rotore2 = gira_rotore(rotore3);
            }
        }
    
        /* INIZIO FASE RIFLETTORE */
        c_crypt = m_riflettore(c_crypt);


        /* INIZIO FASE ROTORI REVERSE */  
        c_crypt = rotore1[(u8) c_crypt - (u8) 'A'];

        c_crypt = rotore2[(u8) c_crypt - (u8) 'A'];
        
        c_crypt = rotore3[(u8) c_crypt - (u8) 'A'];        


        /* INIZIO FASE PLUGBOARD */
        c_crypt = m_plugboard(c_crypt);


        /* OUTPUT FINALE */
        terminal_writechar(c_crypt, actual_color_terminal);
    }
    outb(0x20, 0x20);
}


void idt_set(int interrupt_no, void* address)
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

    for (int i = 0; i < OS_TOTAL_INTERRUPTS; i++)
        idt_set(i, no_interrupt);

    idt_set(0x21, int21h);

    // Load the interrupt descriptor table
    idt_load(&idtr_descriptor);
}
