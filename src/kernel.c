
#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#include "utilities/string/string.c"
#include "utilities/idt/idt.h"
#include "utilities/io/io.h"


#define settings_video
#include "utilities/video/video.c"


// Dichiarazione della funzione Rust (programma main ICPS)
extern int icps_init();
extern void int21h_handler();


void kernel_main()
{
    terminal_initialize();
    
    // inizializza gli interrupt
    idt_init();    

    enable_interrupts();
}
