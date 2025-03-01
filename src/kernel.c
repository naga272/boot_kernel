#include "config.h"
#include "kernel.h"
#include "idt/idt.h"


void kernel_main()
{
    terminal_initialize();
    idt_init();
    enable_interrupts();
    print((const uchar*) "Welcome to my EnigmaOs!\n");
}
