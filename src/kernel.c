
#include <stdint.h>
#include <stddef.h>
#include "utilities/string/string.c"
#include "utilities/stdlib/stdlib.h"
#include "utilities/idt/idt.h"
#include "utilities/io/io.h"
#include "kernel.h"
#include "config.h"

#define prototype_fun_print
#include "utilities/video/print/video.h"
#undef prototype_fun_print

extern void panic();

// var per la shell
extern unsigned char keyboard_buffer[OS_SIZE_SHELL_COMMAND];
extern u32 counter_buffer;


// Dichiarazione della funzione Rust (programma main ICPS)
extern int icps_init();


void kernel_main()
{

    terminal_initialize();
    
    // inizializza gli interrupt
    idt_init();    

    enable_interrupts();
    // print((const unsigned char*) ">>>");
    panic();
}
