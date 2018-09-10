/* 
La comunicación serial USART tiene tres partes escenciales:
- Generador de Clock: XCKn - Se usa para transferencia de información sincrona
- Transmisor: TxDn - consists of a single write buffer, a serial Shift Register, Parity Generator and Control logic for handling different serial frame formats.
- Receptor: RxDn - includes a Parity Checker, Control logic, a Shift Register and a two level receive buffer (UDRn). Can detect Frame Error, Data OverRun and Parity Errors.
El registro de control comparte las tres partes.
 */

#include <avr/io.h>

#include "Lab5-USART.h" // Carga los valores de los macros



///////////////// Inicialización del Usart /////////////////

void USART_Init( uint16_t ubrr)
{
  
  /*Set baud rate */
  // Valores rellenados por los macros del archivo .h
  UBRR0H = (unsigned char)(ubrr>>8); // USART Baud Rate Register High
  UBRR0L = (unsigned char)ubrr;      // USART Baud Rate Register Low
  
  //Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Reciver enable 0 y Transmitter enable 0 (USART0 --> REGISTER DESCRIPTION --> USART Control and Status Register n B)
                                  // RXENn: Escribiendo este bit en 1, enciende el USART Reciever
                                  // TXENn: Escribiendo este bit en 1, enciende el USART Transmitter.
  
  /* Set frame format: 8data, 1stop bit */
  UCSR0C = (3<<UCSZ00); // Descripción en USART0 --> REGISTER DESCRIPTION --> USART Control and Status Register n C
                        // Sacamos el (1<<USBS0) por que queremos que sea de 1stop bit
                        // UCSZ00: Largo de la información Data size = 8
}



///////////////// Receptor /////////////////
// Notamos que retorna un char
// The function simply waits for data to be present in the receive buffer by checking the RXCn Flag, before reading the buffer and returning the value.

unsigned char USART_Receive( void )
{
  /* Wait for data to be received */
  while ( !(UCSR0A & (1<<RXC0)) ); // RXC0: Septimo bit del registro UCSR0A. El bit es 1 cuando hay data sin leer en el buffer de recepción
                                   // y es 0 cuando el buffer está vacío. Los demás bits de UCSR0A son para otras configuraciones de usart (pág 203)
  /* Get and return received data from buffer */
  return UDR0; // UDR0: USART Data Register 0. Registro en el que se almacena la información leida del buffer de recepción
}


///////////////// Transmisor /////////////////
// 
void USART_Transmit_char( uint8_t data )
{
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) ); // De la misma forma que la función anterior, UDRE0 es el sexto bit del registro UCSR0A. El bit indica si
                                     // el buffer de transmisión (UDRn) está listo para transferir data. Si UDRE0 es 1, el buffer está vacío y
                                     // listo para cargarse de información.
  /* Put data into buffer, sends the data */
  UDR0 = data; // Carga la información en el buffer de transmición UDRn (UDR0)
}






