/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"
#include "machine/keyctrl.h"
//#include "device/cgastr.h"
/* Hier muesst ihr selbst Code vervollstaendigen */         
         
Application::Application(){}

extern CGA_Stream kout;

void Application::action (){

   Keyboard_Controller kc;
    Key input;
    kc.set_repeat_rate(0x08,0x03);
    kout.flush();
    int x = 0;
    int y = 10;


    char zeichen;

    do{
        input = kc.key_hit();
        zeichen = input.ascii();
        if(input.valid()){
        kout.print(&zeichen, 1, 11110000);
        }
    }while(1);

}



