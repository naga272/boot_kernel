
#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#include "utilities/string/string.c"
#include "utilities/video/video.c"
#include "utilities/idt/idt.h"
#include "utilities/io/io.h"


// Dichiarazione della funzione Rust (programma main ICPS)
extern int icps_init();


void kernel_main()
{
    terminal_initialize();
    print("Hello World\ncome state?\tciao\n");

    // inizializza gli interrupt
    idt_init();    

    enable_interrupts();
    // panic("Screen of the dead activated! \nCritical error! D:");
}
