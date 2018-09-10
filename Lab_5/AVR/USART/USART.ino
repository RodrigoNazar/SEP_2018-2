#include <avr/io.h>
#include <avr/delay.h>

#include "Lab5-USART.h"

// Bound de 57600

int main(void)
{
    USART_Init(MYUBRR); // MYUBRR: My Usart Baud Rate Register = FOSC/16/BAUD-1, donde FOSC = 16Mhz y BAUD = 57600
  // Welcome message
  _delay_ms(1000);
  USART_Transmit_char('C');
  USART_Transmit_char('o');
  USART_Transmit_char('n');
  USART_Transmit_char('g');
  USART_Transmit_char('r');
  USART_Transmit_char('a');
  USART_Transmit_char('t');
  USART_Transmit_char('u');
  USART_Transmit_char('l');
  USART_Transmit_char('a');
  USART_Transmit_char('t');
  USART_Transmit_char('i');
  USART_Transmit_char('o');
  USART_Transmit_char('n');
  USART_Transmit_char('s');
  USART_Transmit_char('!');
  USART_Transmit_char(' ');
  USART_Transmit_char('Y');
  USART_Transmit_char('o');
  USART_Transmit_char('u');
  USART_Transmit_char(' ');
  USART_Transmit_char('g');
  USART_Transmit_char('o');
  USART_Transmit_char('t');
  USART_Transmit_char(' ');
  USART_Transmit_char('t');
  USART_Transmit_char('h');
  USART_Transmit_char('e');
  USART_Transmit_char(' ');
  USART_Transmit_char('s');
  USART_Transmit_char('e');
  USART_Transmit_char('r');
  USART_Transmit_char('i');
  USART_Transmit_char('a');
  USART_Transmit_char('l');
  USART_Transmit_char(' ');
  USART_Transmit_char('i');
  USART_Transmit_char('n');
  USART_Transmit_char('t');
  USART_Transmit_char('e');
  USART_Transmit_char('r');
  USART_Transmit_char('f');
  USART_Transmit_char('a');
  USART_Transmit_char('c');
  USART_Transmit_char('e');
  USART_Transmit_char(' ');
  USART_Transmit_char('t');
  USART_Transmit_char('o');
  USART_Transmit_char(' ');
  USART_Transmit_char('w');
  USART_Transmit_char('o');
  USART_Transmit_char('r');
  USART_Transmit_char('k');
  USART_Transmit_char('!');
  USART_Transmit_char('\r');
  USART_Transmit_char('\n');

    while (1) 
    { 
    USART_Transmit_char(USART_Receive());
    }
}
