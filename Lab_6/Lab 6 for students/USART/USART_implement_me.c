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
 * This file will be given to you in an 'empty' state. The function bodies are
 * provided, but not their content. You are supposed to add the proper code
 * and complete these functions.
 * 
 * Hint 1: RTFM! The Atmel device datasheets contain all information necessary.
 * 
 * Hint 2: We do not expect you to write the most performant or exceptionally
 * well-engineered code, but it should work. If in doubt, sacrifice speed for
 * reliability. If you are bored, rewrite the entire library in assembler and
 * squeeze the last microsecond out of it.
 * 
 ****************************************************/


// MCU Clock Speed - needed for baud rate value computation
#define F_CPU	16000000UL

#include <avr/io.h>
#include <string.h>

#include "USART_implement_me.h"


// The initialisation function. Call it once from your main() program before
// issuing any USART commands with the functions below!
//
// Call it at any time to change the USART communication parameters.
//
// Returns zero in case of success, non-zero for errors.
uint8_t USART_Init(struct USART_configuration config)
{
	// Add your code here. Don't forget that this function is supposed
	// to return an error code if something goes wrong!
}



// Transmits a single character
void USART_Transmit_char(uint8_t data)
{
	// Add your code here. Wait, didn't you already
	// write this in the past?
}



// Transmits a given string
void USART_Transmit_String(char* string)
{
	// Add your code here.
 	// Hint: Pointers are fun and might make it very
	// easy to process a string and send it char by char.
}