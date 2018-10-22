
#ifndef LAB10_INFO_H_
#define LAB10_INFO_H_

#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define FOSC 16000000
#define BAUD 9600

#define AVR_but_pressed   !(PINB & (1<<PINB7))  // Botón Avr
#define ALUM_but_pressed   !(PINB & (1<<PINB3))  //Botón Aluminio



// VARIABLES GLOBALES
uint16_t contador;
uint16_t contador_2;
uint8_t numero_led;

int tiempo;
int bouncing;

char str_num[16];



// FUNCIONES GENERALES
void Init_GPIO(void);

void milliS_timer_0(void);

void millis_50_timer_1(void);

void cambiar_led(int dir);  // dir=1: sube dir dir=0: baja



// ESTRUCTURAS
struct node
{
	uint8_t val;
	struct node *next;
};
typedef struct node node_t;

 node_t *head_t;

 node_t *actual_node_t;



// FUNCIONES DE USART
void USART_Init(uint16_t baud);

void USART_Transmit(char* string);

uint8_t Transmit_Linked_list(volatile uint8_t *salida);

void linked_list_init();

void append(node_t *p_head, uint8_t value);

void push(node_t ** head, uint8_t value);

void reset_list(node_t *p_head);

void int2str(uint16_t dato);

#endif /* LAB10_INFO_H_ */
