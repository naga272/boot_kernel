
#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#include "utilities/string/string.c"
#include "utilities/video/video.c"
#include "idt/idt.h"


void kernel_main()
{
    terminal_initialize();
    print("Hello World\ncome state?\tciao");

    // inizializza gli interrupt
    idt_init();
}
