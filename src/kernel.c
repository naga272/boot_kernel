
#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#include "utilities/string/string.c"
#include "utilities/video/video.c"
#include "idt/idt.h"


// Dichiarazione della funzione Rust
extern int rust_return_int();


void kernel_main()
{
    terminal_initialize();
    print("Hello World\ncome state?\tciao");

    // testo che mi consente di capire come collegare codice rust nel kernel (mi serve per l'icps)    
    char a = rust_return_int();

    terminal_put_char(10, 10, a, BIANCO);

    // inizializza gli interrupt
    idt_init();
}
