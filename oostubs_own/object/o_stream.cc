/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse O_Stream enthaelt die Definition des << Operators fuer die     */
/* wichtigsten der vordefinierten Datentypen und realisiert somit die        */
/* bekannte Ausgabefunktion der C++ IO_Stream Bibliothek. Zur Zeit wird die  */
/* Darstellung von Zeichen, Zeichenketten und ganzen Zahlen unterstuetzt.    */
/* Ein weiterer << Operator erlaubt die Verwendung von Manipulatoren.        */
/*                                                                           */
/* Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct  */
/* und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl     */
/* fuer den Zeilenumbruch definiert.                                         */
/*****************************************************************************/

#include "object/o_stream.h"
O_Stream::O_Stream() : Stringbuffer(){
    this -> man = DEC;
}

void O_Stream::setManipulator(manipulator man){
    this -> man = man;
}

/*
 * Alle << Operatoren
*/

O_Stream& O_Stream::operator<< (unsigned char c){
    this -> put((char) c);
    return *this;
}

O_Stream& O_Stream::operator<< (char c){
    this -> put(c);
    return *this;
}

O_Stream& O_Stream::operator<< (unsigned short number){
    cast(number);
    return *this;
}

O_Stream& O_Stream::operator<< (short number){
    cast(number);
    return *this;
}

O_Stream& O_Stream::operator<< (unsigned int number){
    cast(number);
    return *this;
}

O_Stream& O_Stream::operator<< (int number){
    cast(number);
    return *this;
}

O_Stream& O_Stream::operator<< (unsigned long number){
    cast(number);
    return *this;
}

O_Stream& O_Stream::operator<< (long number){
    cast(number);
    return *this;
}

/*
 * Pointer
*/

O_Stream& O_Stream::operator<< (void* pointer){
    castHex((char*)&pointer, sizeof(void*));
    return *this;
}

O_Stream& O_Stream::operator<< (char* text){
    while(*text){
        put(*text);
        text++;
    }
    return *this;
}

O_Stream& O_Stream::operator<<(O_Stream& (*fkt) (O_Stream&)){
    return (*fkt)(*this);
}

//Cast-Methode
void O_Stream::cast(long value){
    char array[32];
    char *anfang = &array[0];
    char *ende = &array[32];

    if(value < 0){
        put('-');
        value = value * -1;
    }

    long temp = value;

    do{
        if(man != 16){
            *anfang = temp % man + '0';
            anfang++;
        }
        else{
            char x = temp % man;
            if(x > 9){
                x = x + 7;
            }
            *anfang = x + '0';
            anfang++;
        }
        temp = temp / man;
    }while(temp && anfang != ende);
    printe(&(array[0]), anfang-1);
}

//Richtig herum ausgeben
void O_Stream::printe(char *string, char *act){
    string--;
    while(string != act){
        put(*(act--));
    }
}

//caste zu HEX

void O_Stream::castHex(char value, char *result){
    if(!result) return;
    char x;

    // wieder bitweiser Vergelich
    x = (value&0x0F);
    if(x > 9)
        x+=55;
    else
        x+='0';
    result[1] = x;

    x = (value&0xF0)>>4;
    if(x > 9)
        x+=55;
    else
        x+='0';
    *result = x;
}

void O_Stream::castHex(char* ptr, char size){
    char symb[2];
    ptr+=size;
    do
    {
        castHex(*(--ptr), &(symb[0]));
        this->put(symb[0]);
        this->put(symb[1]);
        size--;
    }while(size>0);
}

// Fuegt einen Zeilenumbruch an
O_Stream& endl(O_Stream& x){
    x.put('\n');
    return x;
}

// BIN: waehlt das binaere Zahlensystem aus.
O_Stream& bin(O_Stream& x){
    x.setManipulator(BIN);
    return x;
};

// OCT: waehlt das oktale Zahlensystem aus.
O_Stream& oct(O_Stream& x){
    x.setManipulator(OCT);
    return x;
}

// DEC: waehlt das dezimale Zahlensystem aus.
O_Stream& dec(O_Stream& x){
    x.setManipulator(DEC);
    return x;
}

// HEX: waehlt das hexadezimale Zahlensystem aus.
O_Stream& hex(O_Stream& x){
    x.setManipulator(HEX);
    return x;
}
