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

#define FOSC 16000000
#define BUF_SIZE 20

#include <avr/io.h>				// PROGRAMACIÓN TARJETA
#include <stdint.h>				// UINTS
#include <avr/interrupt.h>		// INTERRUPCIONES

struct USART_configuration
{
	 uint16_t baud;
	 uint8_t data;
	 uint8_t parity;
     uint8_t stopbits;
};

struct node
{
	 uint8_t val;
     struct node *next;
};

typedef struct node node_t;


volatile node_t *lista_entrada;
volatile node_t *lista_salida;

node_t *linked_list();

void append(node_t *nodo, int valor);

void delete_list(node_t *nodo);

uint8_t USART_Init(struct USART_configuration config);

void copy_lists();

uint8_t recieve_data(node_t *nodo, uint8_t data);

void Transmit_string(char *string);

uint8_t Transmit_list(volatile uint8_t *data);

void push(node_t **nodo, int val);

#endif /* _USART_IMPLEMENT_ME_H_ */
