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


// Libraries used
#include "msp430.h"
#include "USART_implement_me.h"


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

    P4SEL |= BIT4;          // P4.4/UCA1TXD: Transmisor de data en el modo USCI_A1 UART
                            // Este pin escribe información en P4.4/UCA1TXD
                            // Luego, se activa TXD y la data llega a EZFET_UARTRXD.
                            // (Página 55 de slau533) Donde EZFET es el usb de la tarjeta.


    UCA1CTL1 |= UCSWRST;    // Resetea la USCI: Universal serial communication interface y la deja listo para operar
                            // Es un software reset enable:
                            // 0b = Disabled. USCI reset released for operation.
                            // 1b = Enabled. USCI logic held in reset state.
                            // Página 24 documento uart

    UCA1CTL1 |= UCSSEL_2;   // Seleciona el clock a utilizar.
                            // En este caso se selecciona el SMCLK. Un clock interno de 1MHz.
                            // En las opciones también está el ACLK y UCAxCLK. ACLK es un clock de baja
                            // frecuencia (32kHz tipicamente). UCAxCLK es un clock externo.

    UCA1BR1 = 0;            // UCAxBR0 es el registro baund rate control 0. Es un registro de 7 bits que realiza un preescalado
                            // del clock para tener el baund rate correcto. El preescalado del clock es (UCAxBR0 + UCAxBR1 × 256)

    int error = 0;          // Error de retorno


    // BAUND RATE
    // Buscar en el datasheet por UCAxBR0
    switch(config.baud)
    {
    case 9600:
          UCA1BR0 = 104;            // Baud Rate 9600
          UCA1MCTL = BIT1;          // Modulación de la señal serial
          break;

    case 19200:
          UCA1BR0 = 52;             // Baud Rate 19200
          UCA1MCTL = BIT1;
          break;

    case 57600:
          UCA1BR0 = 18;             // Baud Rate 57600
          UCA1MCTL = BIT1;
          break;

    default:
          UCA1BR0 = 18;             // Baud Rate 57600
          UCA1MCTL = BIT1;
          error = 1;
    }

    // PARIDAD
    // Buscar en el datasheet por UCAxCTL0
    switch(config.parity)
    {
    case 0:
        UCA1CTL0 &= ~BIT7;       // Sin paridad
        break;

    case 1:
        UCA1CTL0 = BIT7 + BIT6;  // PAR
        break;

    case 2:
        UCA1CTL0 |= BIT7;
        UCA1CTL0 &= ~BIT6;       // IMPAR
        break;

    default:
        UCA1CTL0 &= ~BIT7;
        error = 1;
        break;
    }

    // STOP BITS
    // Buscar en datasheet por UCAxCTL0
      switch(config.n_stop)
    {
    case 1: UCA1CTL0 &= ~BIT3;
        break;

    case 2: UCA1CTL0 |= BIT3;
        break;

    default:
          UCA1CTL0 &= ~BIT3;
          error = 1;
          break;
    }

    // BITS DE DATA
    // Buscar en datasheet por UCAxCTL0
       switch(config.n_data)
    {
    case 7:
        UCA1CTL0 |= BIT4;               // 7-bits
        break;

    case 8:
        UCA1CTL0 &= ~BIT4;              // 8-bits
        break;

    default:
          UCA1CTL0 &= ~BIT4;
          error = 1;
          break;
    }

    UCA1CTL1 &= ~UCSWRST;  // USCI in operation mode
    return error;          // Buscar por UCAxCTL1
}



// Transmits a single character
void USART_Transmit_char(uint8_t data)
{
	// Add your code here. Wait, didn't you already
	// write this in the past?

    while (UCA1STAT & UCBUSY);  // UCA1STAT es registro de 8 bits, donde el primero es UCBUSY
                                // Si UCBUSY es 1 USCI está transmitiendo
                                // Si es 0, USCI está inactivo

    UCA1TXBUF = data;           // UCAxRXBUF: Registro de recepción del buffer.
                                // Este registro carga la información que se debe transmitir
                                // Pag 27 del documento uart
}



// Transmits a given string
void USART_Transmit_String(char* string)
{
	// Add your code here.
 	// Hint: Pointers are fun and might make it very
	// easy to process a string and send it char by char.

    while (*string != '\0')             // Mientras no se tenga el caracter finalizador de strings
    {
    USART_Transmit_char(*string);       // Se transmitirá el arreglo de caracteres
    string++;
    }
}


void Error_checking(int error)
{
   if (error == 1)
   {
    UCA1CTL0 &= ~UC7BIT;            //configuraciones de baud rate 57600_8N1 por defecto
    UCA1MCTL = BIT1;                // para enviar el mensaje de error
    UCA1BR0 = 18;
    UCA1CTL0 &= ~BIT7;
    UCA1CTL0 &= ~BIT3;
    __delay_cycles(10000);
    USART_Transmit_String("Se ha ingresado una configuracion invalida.\r\n");
    while (1);                      // No sigue ejecutando el código si se tiene que error == 1
   }
   else
   {;}
}
