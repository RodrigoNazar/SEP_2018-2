#include <msp430.h>

#include "USART.h"

int main(void)
{
  
  WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  USART_Init();
  
  while (1){
    for ( volatile uint32_t i=0; i< 100000; i ++) ;
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
  }
}
