/***************************************************
 * This is an example program to demonstrate the
 * successful implementation of the USART's
 * receive functions.
 *
 * Connect your developer board to a PC and configure
 * a terminal emulator with the appropriate baud rate
 * in order to see the test message below.
 *
 * Hint: You can not connect your terminal to this board
 * and avrdude at the same time. Disconnect your terminal
 * software when loading a new program into the flash!
 *
 * This code is in the public domain.
 *
 ****************************************************/

#include <avr/io.h>
#include "USART_implement_me.h"

int main(void)
{
	// Initialize the serial communication interface
	struct USART_configuration config_9600_8N1 = {9600, 8, 0, 1};
	Error_checking(USART_Init(config_9600_8N1));
	node_t *head = linked_list_init();

 	while(1)
 	{
		USART_Transmit_String("\r\n\r\n");
		// Print a welcome message
    int a = 3;
		USART_Transmit_String("Welcome to the first test. Please send a single character from your terminal.\r\n");
    USART_Transmit_char("%d");
		// Show the received character
 		char c = USART_Receive_char();
 		USART_Transmit_String("I received an ");
 		USART_Transmit_char(c);
 		USART_Transmit_String(".\r\n\r\n");


 		// Print a welcome message
 		USART_Transmit_String("Welcome to the Second test. Please send a properly terminated string.\r\n\r\n");

 		USART_Receive_String(head);
 		USART_Transmit_String("I received this line:");
 		// Show the received string
 		print_list(head);
 		USART_Transmit_String("\r\n\r\n");
 	}
 }
