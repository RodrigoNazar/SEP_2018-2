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

#include <stdint.h>
#include <stdio.h>

#define FOSC 16000000
#define F_CPU 16000000UL

struct USART_configuration
{
	uint16_t baud;
	uint8_t n_data;
	uint8_t parity;
	uint8_t n_stop;
};

// Nodo de la lista ligada
struct node
{
	uint8_t val;				// Valor del nodo
	struct node *next;			// Puntero que apunta a la dirección del nodo siguiente
};

typedef struct node node_t; //	Esto permite evitar usar struct antes de cada definicion

node_t *linked_list_init();

void append(node_t *p_head, uint8_t value);

void push(node_t ** head, uint8_t value);

void clear_list(node_t *p_head);

void print_list(node_t * p_head);


// Call once to initialize USART communication
uint8_t USART_Init(struct USART_configuration config);

// Transmits a single character
void USART_Transmit_char(uint8_t data);

// Transmits a given string
void USART_Transmit_String(char* string);

// Receives a single character
char USART_Receive_char(void);

// Receives a '\n' terminated string and writes it into a supplied buffer.
// The buffer must be guaranteed to handle at least bufflen bytes.
// Returns the number of bytes written into the buffer.
uint8_t USART_Receive_String(node_t *p_head);


#endif // _USART_IMPLEMENT_ME_H_
