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


#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include "USART_implement_me.h"


// The initialisation function. Call it once from your main() program before
// issuing any USART commands with the functions below!
//
// Call it at any time to change the USART communication parameters.
//
// Returns zero in case of success, non-zero for errors.


///////////////////// INICIALIZADOR DE USART

uint8_t USART_Init(struct USART_configuration config)
{
 	// Add your code here. Don't forget that this function is supposed
 	// to return an error code if something goes wrong!

    int error = 0;

 	//Enable receiver and transmitter */
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
            ubrr = FOSC/57600/16 - 1;      // Página 173

            UBRR0H = (unsigned char)(ubrr>>8);    // USART Baud Rate Register High
            UBRR0L = (unsigned char)ubrr;         // USART Baud Rate Register Low
              error = 1;
}



    // Número de bits
 	switch (config.n_data)
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
 	switch (config.n_stop)
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



// Transmits a single character
///////////////////// TRANSMISOR DE CHARACTER
void USART_Transmit_char(uint8_t data)
{
 	/* Wait for empty transmit buffer */
 	while ( !( UCSR0A & (1<<UDRE0)) );      // UDRE0 es el sexto bit del registro UCSR0A. El bit indica si
                                            // el buffer de transmisión (UDRn) está listo para transferir data. Si UDRE0 es 1,
                                            // el buffer está vacío y listo para cargarse de información.
 	/* Put data into buffer, sends the data */
    UDR0 = data;                             // Carga la información en el buffer de transmición UDRn (UDR0)
}



// Transmits a given string
// Un string es un array de chars, al tomar char* string tomamos la dirección
// del primer elemento del array
 ///////////////////// TRANSMISOR DE STRING
void USART_Transmit_String(char* string)       // Toma la dirección del primer elemento del array
{
	while (*string != '\0')                     // Busca el valor al que apunta el puntero del array
                                                // hasta que se encuentra con el string de término
	{
		USART_Transmit_char(*string);
		string++;                                // Sigue recorriendo el string
	}
}



// Receives a single character
// The function simply waits for data to be present in the receive buffer by
// checking the RXCn Flag, before reading the buffer and returning the value.
///////////////////// RECEPTOR DE CHARACTER
char USART_Receive_char(void)
{
 	/* Wait for data to be received */
 	while ( !(UCSR0A & (1<<RXC0)) );  // RXC0: Septimo bit del registro UCSR0A.
                                      // El bit es 1 cuando hay data sin leer en el buffer de recepción
                                      // y es 0 cuando el buffer está vacío. (pág 203)

 	/* Get and return received data from buffer */
 	return UDR0;      // UDR0: USART Data Register 0. Registro en el que se almacena la información leida del buffer de recepción.
}



// Receives a '\n' terminated string and writes it into a supplied buffer.
// The buffer must be guaranteed to handle at least bufflen bytes.
// Returns the number of bytes written into the buffer.
///////////////////// RECEPTOR DE STRING
uint8_t USART_Receive_String(node_t *p_head)   // Recibe una lista ligada inicializada
{
 	char c = USART_Receive_char();              // Toma los caracteres uno a uno ingresado por la consola
 	while (c != '\n')                           // Mientras el caracter ingresado no sea la tecla ENTER
 	{
 		append(p_head, c);                      // Se agrega a la lista ligada el nodo de proveniente de la
                                            // dicrección p_head y el valor del caracter c
 		c = USART_Receive_char();               // Toma nuevamente el valor del caracter enviado por consola
 	}
 	return 0;
}



///////////////////// INICIALIZADOR DE LISTA LIGADA
node_t *linked_list_init()
{
	node_t *head = NULL;                // Crea un nodo 'cabeza'
	head = malloc(sizeof(node_t));      // Asigna el número especificado de
                                        // bytes para guardar el nodo
	head->val = ' ';                    // Por defecto el char de inicio es ' '
	head->next = NULL;                  // No tenemos otro nodo
	return head;                        // Retorna la lista inicializada
}



///////////////////// AGREGA UN NODO A LA LISTA LIGADA
void append(node_t *p_head, uint8_t value)           // Recibo el nodo de proveniente de la
{                                                    // dicrección p_head y el valor del caracter
	node_t *current = p_head;                        // Guardamos la dirección del nodo inicial
	while (current->next != NULL)                    // Mientras el nodo tenga un nodo siguiente
	{
		current = current->next;                     // Pasamos de nodo en nodo hasta que llegamos al final
	}

    // Encontramos en nodo final
	current->next = malloc(sizeof(node_t));          // Se asigna el número de bits necesario para
                                                     // guardar el nodo
	current->next->val = value;                      // El valor del nodo será el caracter que se ingresa
	current->next->next = NULL;                      // El nodo siguiente es NULL
}



///////////////////// APPEND PARA UN NODO VACÍO
void push(node_t ** head, uint8_t value)        // ** Indica doble puntero (dirección de la dirección)
{
	node_t * new_node;                          // Se instancia un nuevo nodo
	new_node = malloc(sizeof(node_t));          // Se asigna el número de bits necesario para el nodo
	new_node->val = value;                      // Asigna el valor al nuevo nodo
	new_node->next = *head;                     // Revisa el valor del último nodo de la lista recién borrada (NULL)
	*head = new_node;                           // Sobreescribe el último nodo como el nuevo nodo cabeza
}



///////////////////// QUITA LOS ELEMENTOS DE LA LISTA
void clear_list(node_t *p_head)                      // Recibo el nodo de proveniente de la
{                                                    // dicrección p_head y el valor del caracter
	node_t *node = p_head;                           // Tomamos el nodo
	while(node != NULL )                             // Mientras el nodo no esté vacío
	{
		p_head = p_head->next;                       // Guarda el nodo siguiente
		free(node);                                  // Libera el bloque de memoria del nodo
		node = p_head;                               // Actualiza el valor de node, para seguir en el loop
	}
	push(&p_head, ' ');                              // Deja el valor del primer nodo de la lista en ' '
}



///////////////////// TRASMITE LA LISTA CARACTER POR CARACTER
 void print_list(node_t * p_head)                     // Recibo el nodo de proveniente de la
 {                                                    // dicrección p_head y el valor del caracter
 	node_t * current = p_head;                        // Tomamos el nodo
  // node_t * libre;
 	while (current != NULL)
 	{
 		USART_Transmit_char(current->val);
    // libre = current;
 		current = current->next;
    // free(libre);
 	}
 	clear_list(p_head);
  // push(&p_head, ' ');
 }







 void Error_checking(int error)
 {
    if (error == 1)
    {
     USART_Transmit_String("Se ha ingresado una configuracion invalida.\r\n");
     while (1);                      // No sigue ejecutando el código si se tiene que error == 1
    }
    else
    {;}
 }
