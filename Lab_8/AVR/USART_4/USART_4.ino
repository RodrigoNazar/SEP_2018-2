/***************************************************
 * This is an example program to demonstrate the
 * successful implementation of the USART's
 * interrupt functions.
 *
 * Connect your developer board to a PC and configure
 * a terminal emulator with the appropriate baud rate.
 *
 * Hint: You can not connect your terminal to this board
 * and avrdude at the same time. Disconnect your terminal
 * software when loading a new program into the flash!
 *
 * This code is in the public domain.
 *
 ****************************************************/



#include <avr/io.h>
#include <util/delay.h>
#include "USART_implement_me.h"



/* The main function */
int main(void)
{
    // You already lerned how to configure that button, remember?

    struct USART_configuration config_57600_8N1 = {57600, 8, 0, 1};
    struct USART_configuration config_9600_8N1 = {9600, 8, 0, 1};

    lista_entrada = linked_list();
    lista_salida = linked_list();

    Error_checking(USART_Init(config_9600_8N1));

    //Global interrupts
    sei(); // Set interrupts

    //Interrupts for button
    PCMSK0 |= (1<<PCINT7);  // Pin Change mask register 0.
                            // Aqui esta el 7 que corresponde al boton: PB7.
                            // Pin Change Interrupt source 7.

    PCICR |= (1<<PCIE0);    //pin change interrupt 0 is enabled. Pin change interrupt control register.
                            // Any change on any enabled PCINT[7:0] pin will cause an interrupt.
                            //Any change on any enabled PCINT[0:7] pin will cause an interrupt

    Transmit_string("\nPlease send some characters from your terminal.\n");

    while (1){

        //Transmit_string("\nHemos vuelto.\n");
        _delay_ms (200);
        delete_list(lista_salida);
//          Transmit_string("Volvimos exitosamente\n");
//          _delay_ms(200);
//
//          node_t *actual = lista_salida;
//          while (actual->next != NULL){
//
//            node_t *actual2 = actual;
//            actual = actual->next;
//            free(actual2);
//          }
//
//          node_t *lista_salida = NULL;
//          lista_salida = malloc(sizeof(node_t));
//          lista_salida->val = ' ';
//          lista_salida->next = NULL;
//
//
    }
}



// Interrupt de recepción de datos
// USART, Rx Complete
// Se activa cuando hay un caracter en el buffer UDR0
ISR(USART_RX_vect) // Una vez hay un caracter almacenado en el buffer, lo guarda en el registro UDR0
{
    // Transmit_string("\nRx\n");
    if (recieve_data(lista_entrada,UDR0)) // Tiene como parámetros una lista (caracteres ya escritos)
                                                 // y el buffer UDR0, donde va a parar el ultimo caracter que envío.
    {
        copy_lists(lista_entrada, lista_salida);
        // delete_list(lista_entrada);
        UCSR0B &= ~(1<<RXEN0) & ~(1<<RXCIE0);   // USART Control and Status Register 0 B
                                                // RXEN0==0: disabled reciever. RXCIE0==0: disables interrupt
        UCSR0B |= (1<<TXEN0)|(1<<UDRIE0);      // TXEN0==1: transmit enabled. UDRIE0==1: USART Data Register Empty Interrupt Enable 0. (enables interrupt)
  }
}


// Interrupción de transmición
// USART Data Register Empty
// Entra al interrupt cuando UDR0 está vacío y listo para recibir información y mandarla
ISR(USART_UDRE_vect)  // rutina de interrupcion se activa cuando mando algo
{

    if (Transmit_list(&UDR0))
    {
        // Transmit_string("\nUDRE\n");
        // Transmit_list(lista_salida);
        delete_list(lista_salida);
        UDR0 = '\n';
        UCSR0B &= ~(1<<TXEN0) & ~(1<<UDRIE0);  // recieve enabled, transmit disabled
        UCSR0B |= (1<<RXEN0) | (1<<RXCIE0);
    }
}



// Interrupt se activa cuando aprieto el boton.
ISR(PCINT0_vect) {                                          // Una vez activada la interrupción
  if (!(PINB & (1<<PINB7)))                                 // Si el pin está en tierra
  {
    Transmit_string("Estas apretando el boton.\n");           // Está aprentando el botón
  }
  else Transmit_string("Dejaste de apretar el boton.\n");     // En otro caso no lo hace
}
