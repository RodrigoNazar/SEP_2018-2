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

#include "USART_implement_me.h"

uint8_t USART_Init(struct USART_configuration config)
{
 	// Add your code here. Don't forget that this function is supposed
 	// to return an error code if something goes wrong!

    int error = 0;

 	//Enable recieve_datar and transmitter */
 	UCSR0B = (1<<RXEN0) | (1<<TXEN0) ;    // Reciver enable 0 y Transmitter enable 0 (USART0 --> REGISTER DESCRIPTION --> USART Control and Status Register n B)
                                          // RXENn: Escribiendo este bit en 1, enciende el USART Reciever
                                          // TXENn: Escribiendo este bit en 1, enciende el USART Transmitter.
    uint16_t ubrr;
    // Baud rate
    switch (config.baud)
    {
        case 9600:
            ubrr = FOSC/config.baud/16 - 1;      // Página 173

            UBRR0H = (unsigned char)(ubrr>>8);    // USART Baud Rate Register High
            UBRR0L = (unsigned char)ubrr;         // USART Baud Rate Register Low
            break;

        case 19200:
            ubrr = FOSC/config.baud/16 - 1;      // Página 173

            UBRR0H = (unsigned char)(ubrr>>8);    // USART Baud Rate Register High
            UBRR0L = (unsigned char)ubrr;         // USART Baud Rate Register Low
            break;

        case 57600:
            ubrr = FOSC/config.baud/16 - 1;      // Página 173

            UBRR0H = (unsigned char)(ubrr>>8);    // USART Baud Rate Register High
            UBRR0L = (unsigned char)ubrr;         // USART Baud Rate Register Low
            break;

        default:                           // Configuración por defecto para enviar el error en 57600
            ubrr = FOSC/9600/16 - 1;       // Página 173

            UBRR0H = (unsigned char)(ubrr>>8);    // USART Baud Rate Register High
            UBRR0L = (unsigned char)ubrr;         // USART Baud Rate Register Low
            error = 1;
}

    // Número de bits
    switch (config.data)
    {
 		case 5:
            UCSR0C &= ~(1<<UCSZ02) & ~(1<<UCSZ01) & ~(1<<UCSZ00);
 		    break;

 		case 6:
            UCSR0C &= ~(1<<UCSZ02) & ~(1<<UCSZ01);
 		    UCSR0C |=  (1<<UCSZ00);
 		    break;

 		case 7:
            UCSR0C &= ~(1<<UCSZ02) & ~ (1<<UCSZ00);
 		    UCSR0C |=  (1<<UCSZ01);
 		    break;

 		case 8:
            UCSR0C |= (3<<UCSZ00);
 		    break;

 		default:
            UCSR0C |= (3<<UCSZ00);  // 8 bits por defecto
            error = 1;
 	}

    // Numero de bits de término
 	switch (config.stopbits)
 	{
 		case 1:
            UCSR0C &= ~(1<<USBS0);
 		    break;

 		case 2:
            UCSR0C |= (1<<USBS0);
 		    break;

 		default:
            UCSR0C &= ~(1<<USBS0); // 1 bit por defecto
            error = 1;
 	}

    // Paridad
 	switch (config.parity)
 	{
 		case 0:
            UCSR0C &= ~(1<<UPM01) & ~(1<<UPM00);	// None parity
 		    break;

 		case 2:
            UCSR0C |= (1<<UPM01) | (1<<UPM00);		// Odd parity
 		    break;

 		case 1:
            UCSR0C |= (1<<UPM01);					// Even parity
 		    UCSR0C &= ~(1<<UPM00);
 		    break;

 		default:
            UCSR0C &= ~(1<<UPM01) & ~(1<<UPM00);
            error = 1;
	}

 	return error;
}


///////// DETECCIÓN DE ERRORES
void Error_checking(int error)
{
   if (error == 1)
   {
    Transmit_string("Se ha ingresado una configuracion invalida.\r\n");
    while (1);
   }
   else
   {;}
}



////////// INICIALIZADOR DE LA LISTA LIGADA
node_t *linked_list()
{
  node_t *head = NULL;               // Crea un nodo 'cabeza'
  head = malloc(sizeof(node_t));     // Asigna el número especificado de
                                     // bytes para guardar el nodo
  head->val = ' ';                   // Por defecto el char de inicio es ' '
  head->next = NULL;                 // No tenemos otro nodo
  return head;                       // Retorna la lista inicializada
}



///////////// AGREGAR UN NODO A LA LISTA
void append(node_t *nodo, int valor)    // Recibo el nodo de proveniente de la
{                                       // dicrección p_head y el valor del caracter
  node_t *current = nodo;               // Guardamos la dirección del nodo inicial

                                        // Mientras el nodo tenga un nodo siguie
  while (current->next != NULL)         // Pasamos de nodo en nodo hasta que llegamos al final
  current = current->next;

  // Encontramos en nodo final
  current->next = malloc(sizeof(node_t));          // Se asigna el número de bits necesario para
                                                   // guardar el nodo
  current->next->val = valor;                      // El valor del nodo será el caracter que se ingresa
  current->next->next = NULL;                      // El nodo siguiente es NULL
}



///////////// LIMPIA LOS REGISTROS DE LA LISTA
void delete_list(node_t *nodo)                  // Recibo el nodo de proveniente de la
{                                               // dicrección p_head y el valor del caracter
  node_t *current = nodo;                       // Tomamos el nodo
  while(current != NULL)                        // Mientras el nodo no esté vacío
  {
    nodo = nodo->next;                          // Guarda el nodo siguiente
    free(current);                              // Libera el bloque de memoria del nodo
    current = nodo;                             // Actualiza el valor de node, para seguir en el loop
  }
  push(&nodo,' ');                              // Deja el valor del primer nodo de la lista en ' '
}



///////////////////// APPEND PARA UN NODO VACÍO
void push(node_t **nodo, int value)               // ** Indica doble puntero (dirección de la dirección)
{
  node_t *new_node;                             // Se instancia un nuevo nodo
  new_node = malloc(sizeof(node_t));            // Se asigna el número de bits necesario para el nodo
  new_node->val = value;                          // Asigna el valor al nuevo nodo
  new_node->next = *nodo;                       // Revisa el valor del último nodo de la lista recién borrada (NULL)
  *nodo = new_node;                             // Sobreescribe el último nodo como el nuevo nodo cabeza
}



////////////////////////// RECIBE INFO Y LA GUARDA EN LA LISTA
uint8_t recieve_data(node_t *nodo, uint8_t data) // Escribe cada caracter ingresado hasta el ENTER
{
  if (data != '\n')
  {
    append(nodo, data);
    return 0;
  }
  else return 1;
}



 ///////////////////// TRANSMISOR DE STRING
void Transmit_string(char *string)
{
  while (*string != '\0')
  {
    append(lista_salida, *string);
    string++;
  }
  UCSR0B |= (1<<TXEN0) | (1<<UDRIE0);
  //UDRIE0: data register empty enable
}



///////////////////// TRASPASA ELEMENTOS ENTRE LISTAS
void copy_lists(node_t *lista1, node_t *lista2) //recibe dos listas. Mientras no se acabe la lista 1, transformo la 1 a la 2.
{
    // node_t *aux;
    while (lista1->next != NULL)
    {
    append(lista2, lista1->next->val);
    // aux = lista1->next;
    // free(lista1);
    // lista1 = aux;
    lista1 = lista1->next;
    }
}



/////////////////////// SOBREESCRIBE EL UDR0 CON LA INFO
uint8_t Transmit_list(volatile uint8_t *data)
{
  if (lista_salida->next != NULL)
  {
    *data = (lista_salida->next->val);
    lista_salida = lista_salida->next;
    return 0;
  }
  else return 1;
}
