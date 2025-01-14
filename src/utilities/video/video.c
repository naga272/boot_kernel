#include "utilities/video/video.h"
#include <stdarg.h>


uint16_t set_char_terminal(char c, char colour)
{
    /*
    *   abbiamo un unsigned int a 16 bit.
    *   colour va a occupare gli 8 bit piu' significativi,
    *   c invece va a occupare gli 8 bit meno significativi.
    *   in questo modo posso passare il colore + carattere a 0xb8000 con una sola chiamata
    */
    return (colour << 8) | c;
}


void terminal_put_char(int x, int y, char c, char colour)
{
    /*
    *   Stampa un carattere c di colore colour alla colonna x della riga y del monitor
    * Argv:
    *   - x:        colonna schermo
    *   - y:        row schermo
    *   - c:        carattere da stampare
    *   - colour:   colore del carattere
    */
    video_mem[(y * VGA_WIDTH) + x] = set_char_terminal(c, colour); 
}


void terminal_writechar(char c, char colour)
{
    /*
    *   A differenza di terminal_put_char non posso decidere in quale colonna / riga mettere un carattere
    */

    switch (c) {
        case '\n':
            terminal_col = 0;
            terminal_row++;
            break;

        case '\t':
            terminal_col += 8;
            break;
        
        default:
            terminal_put_char(terminal_col, terminal_row, c, colour);
            terminal_col++;

            if (terminal_col == VGA_WIDTH) {
                terminal_col = 0;
                terminal_row++;
            }
            break;
    }
}


void print(const char* string)
{
    /*
    * Stampa in output una stringa
    */
    for(size_t i = 0; string[i] != '\0'; i++)
        terminal_writechar(string[i], actual_color_terminal);
}

/*
int printf(const char* vect, ...)
{
    // printf personale (DA COMPLETARE)
    int 
        len_ptr_printed = 0,
        index,
        special_char = 0;


    va_list argv;
    va_start(argv, vect);


    for (size_t i = 0; vect[i] != '\0'; i++) {
    
        if (vect[i] == '%') {
            switch (vect[i + 1]) {
                case 'd':
                    index = va_arg(arv, int); 
                    goto exit_from_switch;
                
                case 'c': 
                    index = va_arg(arv, char);
                    goto exit_from_switch;
                
                case 's': 
                    goto exit_from_switch;
                
                case 'f': 
                    goto exit_from_switch;
                
                default: 
                    goto exit_from_switch;
            }

            exit_from_switch:
                special_char = 1;

        } else if (special_char != 1) {
            // terminal_writechar()
        }

        len_ptr_printed++;
    }
    return len_ptr_printed;
}
*/


void terminal_initialize()
{
    /*
    *   Funzione usata all'interno di kernel.c nella funzione kernel_main.
    *   setta lo screen col colore nero
    **/
    video_mem = (uint16_t*) (0xb8000);

    for (int y = 0; y < VGA_HEIGHT; y++) 
        for (int x = 0; x < VGA_WIDTH; x++) 
            terminal_put_char(x, y, ' ', NERO);
}

