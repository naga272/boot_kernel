
#ifndef VIDEO_H
#define VIDEO_H

#ifndef settings_video
#define settings_video

/* STANDARD COLOR */
#define NERO            0
#define BLU             1
#define VERDE           2
#define CIANO           3
#define ROSSO           4
#define VIOLA           5
#define MARRONE         6
#define GRIGIO          7
#define GRIGIO_SCURO    8
#define BLU_CHIARO      9
#define VERDE_CHIARO    10
#define CIANO_CHIARO    11
#define ROSSO_CHIARO    12
#define VIOLA_CHIARO    13
#define GIALLO          14
#define BIANCO          15


// default colore dei caratteri del terminale (in futuro potrebbe cambiare il colore in base alle situazioni)
char actual_color_terminal = BIANCO; 

uint16_t* video_mem = 0;
uint16_t terminal_row = 0;  // tiene traccia a quale riga del monitor sto scrivendo (max value VGA_HEIGHT)
uint16_t terminal_col = 0;  // tiene traccia della colonna del monitor da dove sto scrivendo (max value VGA_WIDTH)

#define VGA_WIDTH   80
#define VGA_HEIGHT  100

#endif

#endif