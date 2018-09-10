/* 
La comunicación serial USART tiene tres partes escenciales:
- Generador de Clock: XCKn - Se usa para transferencia de información sincrona
- Transmisor: TxDn - consists of a single write buffer, a serial Shift Register, Parity Generator and Control logic for handling different serial frame formats.
- Receptor: RxDn - includes a Parity Checker, Control logic, a Shift Register and a two level receive buffer (UDRn). Can detect Frame Error, Data OverRun and Parity Errors.
El registro de control comparte las tres partes.
 */

#include <avr/io.h>

// Macro que calcula el correcto valor del registro de bound
#define FOSC 16000000 // Velocidad de
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

// Inicialización del Usart

void USART_Init( unsigned int ubrr)
{
  /*Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  
  /*Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0); // Reciver enable 0 y Transmitter enable 0 (USART0 --> REGISTER DESCRIPTION --> USART Control and Status Register n B)
  // RXENn: Writing this bit to one enables the USART Receiver.
  // TXENn: Writing this bit to one enables the USART Transmitter.
  
  /* Set frame format: 8data */
  // Descripción en USART0 --> REGISTER DESCRIPTION --> USART Control and Status Register n C
  // Sacamos el (1<<USBS0) por que queremos que sea de 1stop bit
  // UCSZ00: Largo de la información Data size = 8
  UCSR0C = (3<<UCSZ00);
}


// Receptor
// Notamos que retorna un char
unsigned char USART_Receive( void ) // The function simply waits for data to be present in the receive buffer by checking the RXCn Flag, before reading
                                    // the buffer and returning the value.
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) )
;
/* Get and return received data from buffer */
return UDR0;
}

// Transmisor
void USART_Transmit( unsigned char data )
{
  /* Wait for empty transmit buffer */
  while ( !( UCSR0A & (1<<UDRE0)) )
  ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
}


int main( void )
{

  USART_Init(MYUBRR); // Llamado de la inicialización del Usart usando el macro MYUBRR = FOSC/16/BAUD-1


  // Queremos transmitir un caracter
  while(1){

  USART_Transmit( USART_Receive( ) );
    
  }
  return 0;
}






