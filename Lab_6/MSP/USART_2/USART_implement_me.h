/***************************************************
 * This is a USART library for the ATMega328P.
 *
 * It can provide basic USART (serial) communication for any application.
 *
 * This code is in the public domain. Feel free to do with it whatever you want.
 *
 *
 *
 * FOR STUDENTS:
 *
 * This file has an incomplete struct definition. Add definitions for its
 * members! Check the other files and the lab description to find out which
 * parameters and what ranges are needed.
 *
 ****************************************************/

#ifndef _USART_IMPLEMENT_ME_H_
#define _USART_IMPLEMENT_ME_H_

#include <stdint.h> // Librería para uints



// Inicialización del struct

// Arrays sólo pueden almacenar elementos de la misma naturaleza
// Las structures no tienen esa limitación
struct USART_configuration
{
	// <add parameters here>
	// Miembros de la estructura
	uint16_t baud;
    uint8_t parity;
    uint8_t n_data;
    uint8_t n_stop;
};


// Call once to initialise USART communication
uint8_t USART_Init(struct USART_configuration config);

// Transmits a single character
void USART_Transmit_char(uint8_t data );

// Transmits a given string
void USART_Transmit_String(char* string);


#endif // _USART_IMPLEMENT_ME_H_
