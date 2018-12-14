/* $Id: cgascr.cc 5834 2013-10-08 17:04:08Z os $ */

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse kann man auf den Bildschirm des PCs zugreifen.    */
/* Der Zugriff erfolgt direkt auf der Hardwareebene, d.h. ueber den Bild-    */
/* schirmspeicher bzw. die I/O-Ports der Grafikkarte.                        */
/*****************************************************************************/

#include "machine/cgascr.h"

int breite = 80;
int hoehe = 25;

// Gibt ein Zeichen an der (x,y).Koordinate mit den gewünschten Farbeinstellungen aus
void CGA_Screen::show(int x, int y, char c, unsigned char attrib){

    char *CGA_Start = (char *) 0xb8000;
    char *pos;

    pos = CGA_Start + 2*(x + y*breite);
    *pos = c;
    pos++;
    *pos = attrib;
}

// Setzt Cursor an Stelle (x,y)
void CGA_Screen::setpos(int x, int y){
    int pos = (x + y*breite);

    outb(0x3d4, 14);
    outb(0x3d5, pos >> 8);

    outb(0x3d4, 15);
    outb(0x3d5, pos % 256);
}

// Findet (x,y)-Koordinate des Cursors heruas
void CGA_Screen::getpos(int &x, int &y){

    outb(0x3d4, 14);
    int pos = inb(0x3d5) << 8;
 
    outb(0x3d4, 15);
    pos = pos + inb(0x3d5);
    
    x = pos % breite;
    y = pos / breite;
}

//Hilfsfunktion: Löscht erste Zeile und kopiert den Rest eine Zeile nach oben
void CGA_Screen::scrolldown(){
    char *CGA_Start = (char *) 0xb8000;
    setpos(0,0);

    for(int j = 0; j<hoehe; j++){
        for(int i = 0; i<breite; i++){
            char *alt = CGA_Start + 2*(i + (j+1)*breite);
            char *neu = CGA_Start + 2*(i + j*breite);
            *neu = *alt;
            char *attrib = (CGA_Start + 2*(i + (j+1)*breite)) + 1;
                        
            print(neu, 1, *attrib);
            neu = neu+2;
            alt = alt + 2;
        }
    }
    setpos(0,hoehe-1);
}

//Gibt eine beliebig lange Zeichenkette aus
void CGA_Screen::print(char* text, int length, unsigned char attrib){
    int x, y;
    getpos(x,y);
    setpos(x,y);
    
    for( int i = 0; i < length; i++){
        if(x == 80){
            y++;
            x = 0;
        }
        if(*text == '\n'){
            y++;
            x = 0;
            text++;
        }
        if(y>=hoehe){
            scrolldown();
            y = 24;
        }

        show(x, y, *text, attrib);
        x++;
        text++;
    }
    setpos(x,y);
}