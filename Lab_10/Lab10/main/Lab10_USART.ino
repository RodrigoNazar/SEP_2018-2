#include "Lab10_Info.h"


// INICIALIZACIÓN DEL USART
void USART_Init(uint16_t baud)
{
  uint16_t ubrr = FOSC / 16 / baud - 1;

  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  /* Set frame format: 8data, 1stop bit */
  UCSR0C = (3 << UCSZ00);
}


// TRASMISOR DE STRING
void USART_Transmit(char* string)
{
  while (*string != '\0')
  {
    append(head_t, *string);
    string++;
  }
  UCSR0B |= (1 << TXEN0) | (1 << UDRIE0);
}


// TRASMISOR DE LINKED LIST
uint8_t Transmit_Linked_list(volatile uint8_t *salida)
{

  if (actual_node_t->next != NULL)
  {
    *salida = (actual_node_t->next->val);
    actual_node_t = actual_node_t->next;
    return 0;
  }
  else return 1;
}


// CREADOR DE LISTA LIGADA
void linked_list_init()
{
  head_t = NULL;
  head_t = malloc(sizeof(node_t));
  head_t->val = ' ';
  head_t->next = NULL;
  actual_node_t = head_t;
}


// AGREGA UN NODO AL FINAL DE LA LISTA
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


//
void push(node_t ** head, uint8_t value)
{
	node_t * new_node;
	new_node = malloc(sizeof(node_t));

	new_node->val = value;
	new_node->next = *head;
	*head = new_node;
}


// LIMPIA LA LISTA LIGADA
void reset_list(node_t *p_head)
{
  node_t *node = p_head;
  while (node != NULL )
  {
    p_head = p_head->next;
    free(node);
    node = p_head;
  }
  push(&p_head, '-');

  actual_node_t = head_t;
}


// TRANSFORMA UN INT A UN STRING
void int2str(uint16_t dato)
{

  sprintf(str_num, "%d", dato);
}
