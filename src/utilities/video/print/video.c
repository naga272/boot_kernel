#include "utilities/stdlib/stdlib.h"

#define settings_video

#include "utilities/video/print/video.h"

#undef settings_video


extern uchar keyboard_buffer[OS_SIZE_SHELL_COMMAND];
extern u32 counter_buffer;


u16 set_char_terminal(char c, char colour)
{
    /*
    *   abbiamo un unsigned int a 16 bit.
    *   colour va a occupare gli 8 bit piu' significativi,
    *   c invece va a occupare gli 8 bit meno significativi.
    *   in questo modo posso passare il colore + carattere a 0xb8000 con una sola chiamata
    */
    return (colour << 8) | c;
}


void terminal_put_char(u32 x, u32 y, char c, char colour)
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

        case '\b':
            if (terminal_col != 0)
                terminal_col--;

            terminal_put_char(terminal_col, terminal_row, ' ', colour);
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


void print(const uchar* string)
{
    /*
    * Stampa in output una stringa
    */
    for(size_t i = 0; string[i] != '\0'; i++)
        terminal_writechar(string[i], actual_color_terminal);
}


void terminal_initialize(char colore)
{
    /*
    *   Funzione usata all'interno di kernel.c nella funzione kernel_main.
    *   setta lo screen col colore nero
    **/
    video_mem = (u16*) (0xb8000);
    
    memset((void*) keyboard_buffer, 0, (size_t) OS_SIZE_SHELL_COMMAND); 
    counter_buffer = 0;
    
    for (u32 y = 0; y < VGA_HEIGHT; y++) 
        for (u32 x = 0; x < VGA_WIDTH; x++) 
            terminal_put_char(x, y, ' ', colore);
}


u16 get_terminal_row()
{
    return terminal_row;
}


u16 get_terminal_column()
{
    return terminal_col;
}


char get_actual_color_terminal()
{
    return actual_color_terminal;
}


void set_terminal_row(u16 new_row)
{
    terminal_row = new_row;
}


void set_terminal_column(u16 new_column)
{
    terminal_col = new_column;
}


void set_actual_color_terminal(char new_color)
{
    actual_color_terminal = new_color;
}