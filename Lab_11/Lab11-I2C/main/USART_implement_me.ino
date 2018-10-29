#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include "USART_implement_me.h"

//--------------------------------
uint8_t USART_Init(struct USART_configuration config)
{

	uint16_t ubrr = FOSC/config.baud/16 - 1;

	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	UCSR0B |= (1<<RXEN0) | (1<<RXCIE0);

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


uint8_t USART_Receive(node_t *p_head, uint8_t data)
{
	if (data != '\n')
	{
		append(p_head, data);
		return 0;
	}
	else return 1;
}


// Transmits a given string
void USART_Transmit(char* string)
{
	while (*string != '\0')
	{
		append(head_t, *string);
		string++;
	}
	UCSR0B |= (1<<TXEN0) | (1<<UDRIE0);
}

uint8_t Send_Linked_list(volatile uint8_t *salida)
{

	if (actual_node_t->next != NULL)
	{
		*salida = (actual_node_t->next->val);
		actual_node_t = actual_node_t->next;
		return 0;
	}
	else return 1;
}


void Transfer_Info_Buffers()
{
	while (actual_node_r->next != NULL)
	{
		uint8_t data = actual_node_r->next->val;
		append(head_t, data);
		actual_node_r = actual_node_r->next;
	}
	actual_node_r = head_r;
	//reset_list(head_r, 'r');
}


void linked_list_init()
{
	head_r = malloc(sizeof(node_t));
	head_t = malloc(sizeof(node_t));
	head_r->val = ' ';
	head_t->val = ' ';
	head_r->next = NULL;
	head_t->next = NULL;
	actual_node_r = head_r;
	actual_node_t = head_t;
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

void reset_list(node_t *p_head,char tipo)
{
	node_t *node = p_head;
	while(node != NULL )
	{
		p_head = p_head->next;
		free(node);
		node = p_head;
	}
	push(&p_head, ' ');

	if (tipo == 'r')
	actual_node_r = head_r;
	else
	actual_node_t = head_t;
}
