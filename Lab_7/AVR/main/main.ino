
// MCU Clock Speed - needed for delay.h

#include <avr/io.h>
#include "Buffers_Info.h"

int main(void)
{
  // Initialize the serial communication interface
  struct USART_configuration config_57600_8N1 = {57600, 8, 0, 1};
  USART_Init(config_57600_8N1);
  node_t *head = linked_list_init();

  while(1)
  {
    // Print a welcome message
    USART_Transmit_String("Welcome to the first test. Please send a single character from your terminal.\r\n");
    
    // Show the received character
    char c = USART_Receive_char();
    USART_Transmit_String("I received an ");
    USART_Transmit_char(c);
    USART_Transmit_String(".\r\n\r\n");
    
    
    // Print a welcome message
    USART_Transmit_String("Welcome to the Second test. Please send a properly terminated string.\r\n\r\n");
    
    int i = USART_Receive_String(head);
    char len[] = "";
    sprintf(len, "%d", i); 
    USART_Transmit_String("I received this line:");
    // Show the received string
    print_list(head);
    USART_Transmit_String("  Largo: ");
    USART_Transmit_String(len);
    USART_Transmit_String(".\r\n\r\n");
  }
}

