
#include <stdint.h>
#include <stddef.h>
#include "kernel.h"
#include "utilities/string/string.c"
#include "utilities/video/video.c"


void kernel_main()
{
    terminal_initialize();
    print("Hello World\ncome state?");
}
