/***************************************************
 * This is an example program to demonstrate the
 * successful implementation of the USART's
 * init and send functions.
 *
 * Connect your developer board to a PC and configure
 * a terminal emulator with the appropriate baud rate
 * in order to see the test message below.
 *
 * Note that you will have to reconfigure it several times
 * to see the output with all the different parameters.
 *
 * Hint: You can not connect your terminal to this board
 * and avrdude at the same time. Disconnect your terminal
 * software when loading a new program into the flash!
 *
 * This code is in the public domain.
 *
 ****************************************************/

// Libraries used
 #include "msp430.h"


// Have a look at both the .h and the .c file, there is code missing.
#include "USART_implement_me.h"



/* The main function */
int main(void)
{
	WDTCTL = WDTPW + WDTHOLD; // Stop WDT

    // Configuraciones del USART
	struct USART_configuration config_57600_8N1 = {57600, 0, 8, 1};
    struct USART_configuration config_9600_8N2 = {9600, 0, 8, 2};
    struct USART_configuration config_19200_7N1 = {19200, 0, 7, 1};
    struct USART_configuration config_19200_7E2 = {19200, 1, 7, 2};

  
//	// Initialise the serial communication interface and print a test string
//        Error_checking(USART_Init(config_57600_8N1));
//        __delay_cycles(10000);
//	USART_Transmit_String("Congratulations! You are now sending test messages at 57600 8N1.\r\n");

	// Initialise the serial communication interface and print a test string
        Error_checking(USART_Init(config_9600_8N2));
	__delay_cycles(10000);
	USART_Transmit_String("Change your terminal settings and reset the MCU to see 9600 8N2.\r\n");
//
//	// Initialise the serial communication interface and print a test string
//        Error_checking(USART_Init(config_19200_7N1));
//	__delay_cycles(10000);
//	USART_Transmit_String("With the wrong settings, you will see nothing but gibberish at 19200 7N1.\r\n");
//
//	// Initialise the serial communication interface and print a test string
//        Error_checking(USART_Init(config_19200_7E2));
//	__delay_cycles(10000);
//	USART_Transmit_String("Even parity and two stop bits have limited use. But 19200 7E2 is great for annoying students.\r\n");


	// Play dead
	while(1){
}
}
