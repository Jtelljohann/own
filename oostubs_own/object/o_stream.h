/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse O_Stream enthaelt die Definition des << Operators fuer die     */
/* wichtigsten der vordefinierten Datentypen und realisiert somit die        */
/* bekannte Ausgabefunktion der C++ iO_Stream Bibliothek. Zur Zeit wird die  */
/* Darstellung von Zeichen, Zeichenketten und ganzen Zahlen unterstuetzt.    */
/* Ein weiterer << Operator erlaubt die Verwendung von Manipulatoren.        */
/*                                                                           */
/* Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct  */
/* und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl     */
/* fuer den Zeilenumbruch definiert.                                         */
/*****************************************************************************/

#ifndef __o_stream_include__
#define __o_stream_include__

#include "object/strbuf.h"

typedef enum{
      BIN = 2,
      OCT = 8,
      DEC = 10,
      HEX = 16
} manipulator;

class O_Stream : public Stringbuffer
/* Hier muesst ihr selbst Code vervollstaendigen */         
 {
private:
      O_Stream(const O_Stream &copy); // Verhindere Kopieren
     
      manipulator man;

      void cast(long value);
      void printe(char *string, char *act);
      void castHex(char value, char *result);
      void castHex(char* ptr, char size);

public:
      O_Stream();

      void setManipulator(manipulator man);



      //Chars
      O_Stream&operator<< (unsigned char c);
      O_Stream&operator<< (char c);
      
      // Zahlen
      O_Stream&operator<< (unsigned short number);
      O_Stream&operator<< (short number);
      O_Stream&operator<< (unsigned int number);
      O_Stream&operator<< (int number);
      O_Stream&operator<< (unsigned long number);
      O_Stream&operator<< (long number);

      // Anfügen von pointern
      O_Stream&operator<< (void* pointer);


      // Anfügen von Wörtern
      O_Stream&operator<< (char* text);


      // Aufruf der Manipulatorfunktion
      O_Stream&operator<< (O_Stream& (*fkt) (O_Stream&));




};

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          M A N I P U L A T O R E N                        */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die folgenden Funktionen erhalten und liefern jeweils eine Referenz auf   */
/* ein O_Stream Objekt. Da die Klasse O_Stream einen Operator << fuer        */
/* derartige Funktionen definiert, koennen sie mit Hilfe dieses Operators    */
/* aufgerufen und sogar in weitere Eingaben eingebettet werden.              */
/* Aufgabe der Manipulatoren ist, die Darstellung der nachfolgenden Ausgaben */
/* zu beeinflussen, z.B durch die Wahl des Zahlensystems.                    */
/*---------------------------------------------------------------------------*/

// ENDL: fuegt einen Zeilenumbruch in die Ausgabe ein.
O_Stream& endl(O_Stream& x);

// BIN: waehlt das binaere Zahlensystem aus.
O_Stream& bin(O_Stream& x);

// OCT: waehlt das oktale Zahlensystem aus.
O_Stream& oct(O_Stream& x);

// DEC: waehlt das dezimale Zahlensystem aus.
O_Stream& dec(O_Stream& x);

// HEX: waehlt das hexadezimale Zahlensystem aus.
O_Stream& hex(O_Stream& x);

#endif

