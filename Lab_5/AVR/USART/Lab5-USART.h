
#ifndef LAB5-USART_H_
#define LAB5-USART_H_

#include <stdint.h> // Libreria para standard integert types. como uint8_t

// Macro que calcula el correcto valor del registro de bound
#define F_CPU 16000000UL
#define FOSC 16000000 // Clock Speed
#define BAUD 57600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( uint16_t ubrr);
unsigned char USART_Receive( void );
void USART_Transmit_char( uint8_t data );


#endif /* LAB5-USART_H_ */

// La extensión .h indica Header file. Es un archivo que contiene declaraciones de funciones de C y definiciones de macros que se comparten 
// a lo largo de los otros archivos. Es análogo a usar en un código todas las partes iniciales de este, sólo que acá se separa.
