
#ifndef _USART_IMPLEMENT_ME_H_
#define _USART_IMPLEMENT_ME_H_

#include <stdint.h>

#define FOSC 16000000UL // Clock Speed
#define F_CPU 16000000UL

struct USART_configuration
{
	uint16_t baud;
	uint8_t parity;
	uint8_t n_data;
	uint8_t n_stop;
};

struct node
{
	uint8_t val;
	struct node *next;
};
typedef struct node node_t; //esto permite evitar usar struct antes de cada definicion


node_t *head_r;
node_t *head_t;
node_t *actual_node_r;
node_t *actual_node_t;

int borrar;

uint16_t ADC_value;
uint8_t temperatura;
uint8_t dato_enviar;
char str_num[16];

// Call once to initialize USART communication
uint8_t USART_Init(struct USART_configuration config);

uint8_t USART_Receive(node_t *p_head, uint8_t data);

// Transmits a given string
void USART_Transmit(char* string);

uint8_t Send_Linked_list(volatile uint8_t *salida);

void Transfer_Info_Buffers();
// Linked List

void linked_list_init();

void append(node_t *p_head, uint8_t value);

void push(node_t ** head, uint8_t value);

void reset_list(node_t *p_head, char tipo);

#endif // _USART_IMPLEMENT_ME_H_
