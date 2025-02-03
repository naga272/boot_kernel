#include "config.h"

#include "utilities/video/print/video.h"
#include "utilities/video/panic/panic.h"


// default colore dei caratteri del terminale (in futuro potrebbe cambiare il colore in base alle situazioni)
extern u16 terminal_row;  // tiene traccia a quale riga del monitor sto scrivendo (max value VGA_HEIGHT)
extern u16 terminal_col;  // tiene traccia della colonna del monitor da dove sto scrivendo (max value VGA_WIDTH)

extern uint16_t set_char_terminal(char c, char colour);
extern void terminal_put_char(int x, int y, char c, char colour);
extern void terminal_writechar(char c, char colour);
extern void print(const unsigned char* string);


/*
* Quando si entra in azione la procedura panic() l'interrupt 0x21 deve essere bloccato, l'user non deve poter scrivere.
* L'unica azione che e' concessa e' quella di riavviare tramite tasto della macchina
*/
extern void idt_set(int interrupt_no, void* address);
extern void no_interrupt_handler();



void panic()
{
    /*
    * Funzione che viene applicata quando le cose stanno andando davvero male. Obbliga l'utente a riavviare la macchina dal tasto fisico.
    */
    int i = 0;
    terminal_row = 0;
    terminal_col = 0;

    idt_set(0x21, no_interrupt_handler);    // disabilito l'int21h

    while (terminal_col <= VGA_HEIGHT) {
        
        while (terminal_row <= VGA_WIDTH) {
            
            if (msg[i] != '\0') {
                
                if (msg[i] != '\n') {
                    terminal_put_char(terminal_row, terminal_col, msg[i], BG_BLU_C_WHITE);
                    terminal_row++;
                } else {    // devo fare letteralmente il ritorno a capo, colorando gli spazi a destra con il colore blu (di default e' nero)
                    while (terminal_row <= VGA_WIDTH) {
                        terminal_put_char(terminal_row, terminal_col, ' ', BG_BLU_C_WHITE);
                        terminal_row++;
                    }
                    terminal_col++;
                    terminal_row = 0;
                }
                i++;
            } else { // colora per le restanti terminal_row 
                terminal_put_char(terminal_row, terminal_col, ' ', BG_BLU_C_WHITE);
                terminal_row++;
            }
        }
        terminal_col++;
        terminal_row = 0;
    }

}