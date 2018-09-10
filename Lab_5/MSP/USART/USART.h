#ifndef USART_H_
#define USART_H_

#include <stdint.h> // Libreria para standard integert types. como uint8_t

void USART_Init( void );
void USART_Transmit_char(uint8_t data);


#endif /* USART_H_ */