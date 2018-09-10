/*
 * Lab5_USART.h
 *
 * Created: 15-04-2018 11:44:00
 *  Author: Vicente
 */ 

#ifndef LAB5-USART_H_
#define LAB5-USART_H_

#include <stdint.h>

#define F_CPU 16000000UL
#define FOSC 16000000 // Clock Speed
#define BAUD 57600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init( uint16_t ubrr);
unsigned char USART_Receive( void );
void USART_Transmit_char( uint8_t data );


#endif /* LAB5-USART_H_ */