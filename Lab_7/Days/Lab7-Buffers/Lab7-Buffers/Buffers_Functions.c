/*
 * Buffers_Functions.c
 *
 * Created: 20-04-2018 9:55:32
 *  Author: Vicente
 */ 
// MCU Clock Speed - needed for baud rate value computation

#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include "Buffers_Info.h"


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
	/*Set baud rate */
	uint16_t ubrr = FOSC/config.baud/16 - 1;
	
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	//Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	
	switch (config.n_data)
	{
		case 5: UCSR0C &= ~(1<<UCSZ02) & ~(1<<UCSZ01) & ~(1<<UCSZ00);
		break;
		case 6: UCSR0C &= ~(1<<UCSZ02) & ~(1<<UCSZ01);
		UCSR0C |=  (1<<UCSZ00);
		break;
		case 7: UCSR0C &= ~(1<<UCSZ02);
		UCSR0C |=  (1<<UCSZ01) | (1<<UCSZ00);
		break;
		case 8: UCSR0C |= (3<<UCSZ00);
		break;
		default: UCSR0C |= (3<<UCSZ00);
	}
	
	switch (config.n_stop)
	{
		case 1: UCSR0C &= ~(1<<USBS0);
		break;
		case 2: UCSR0C |= (1<<USBS0);
		break;
		default: UCSR0C &= ~(1<<USBS0);
	}
	
	switch (config.parity)
	{
		case 0: UCSR0C &= ~(1<<UPM01) & ~(1<<UPM00);	// None parity
		break;
		case 2: UCSR0C |= (1<<UPM01) | (1<<UPM00);		// Odd parity
		break;
		case 1: UCSR0C |= (1<<UPM01);					// Even parity
		UCSR0C &= ~(1<<UPM00);
		break;
		default: UCSR0C &= ~(1<<USBS0);
	}
	return 0;
}

// Transmits a single character
void USART_Transmit_char(uint8_t data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

// Transmits a given string
void USART_Transmit_String(char* string)
{
	while (*string != '\0')
	{
		USART_Transmit_char(*string);
		string++;
	}
}

// Receives a single character
char USART_Receive_char(void)
{
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) );
	/* Get and return received data from buffer */
	return UDR0;
}

// Receives a '\n' terminated string and writes it into a supplied buffer.
// The buffer must be guaranteed to handle at least bufflen bytes.
// Returns the number of bytes written into the buffer.
uint8_t USART_Receive_String(node_t *p_head)
{
	char c = USART_Receive_char();
	int contador = 0;
	while (c != '\n')
	{
		append(p_head, c);
		c = USART_Receive_char();
		contador++;
	}
	return contador;
}
	
node_t *linked_list_init() 
{
	node_t *head = NULL;
	head = malloc(sizeof(node_t));
	head->val = ' ';
	head->next = NULL;
	return head;
}

void append(node_t *p_head, uint8_t value)
{
	node_t *current = p_head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = malloc(sizeof(node_t));
	current->next->val = value;
	current->next->next = NULL;
}

void push(node_t ** head, uint8_t value) 
{
	node_t * new_node;
	new_node = malloc(sizeof(node_t));

	new_node->val = value;
	new_node->next = *head;
	*head = new_node;
}

void clear_list(node_t *p_head)
{
	node_t *node = p_head;
	while(node != NULL )
	{
		p_head = p_head->next;
		free(node);
		node = p_head;
	}
	push(&p_head, ' ');
}

void print_list(node_t * p_head) {
	node_t * current = p_head;

	while (current != NULL)
	{
		USART_Transmit_char(current->val);
		current = current->next;
	}
	clear_list(p_head);
}




