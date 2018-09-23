/*
 * Buffers_Info.h
 *
 * Created: 20-04-2018 9:56:13
 *  Author: Vicente
 */ 
#ifndef BUFFERS_INFO_H_
#define BUFFERS_INFO_H_

#include <stdint.h>
#include <stdio.h>

#define FOSC 16000000
#define F_CPU	16000000UL

struct USART_configuration
{
	uint16_t baud;
	uint8_t n_data;
	uint8_t parity;
	uint8_t n_stop;
};

struct node 
{
	uint8_t val;
	struct node *next;
};

typedef struct node node_t; //esto permite evitar usar struct antes de cada definicion

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


#endif /* BUFFERS_INFO_H_ */