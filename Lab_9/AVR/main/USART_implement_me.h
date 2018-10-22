#ifndef LAB9_AVR_H_
#define LAB9_AVR_H_

#define F_CPU 16000000UL
#define BAUD1 57600
#define BAUD2 19200
#define BAUD3 9600
#define BRATE1 F_CPU/16/BAUD1-1
#define BRATE2 F_CPU/16/BAUD2-1
#define BRATE3 F_CPU/16/BAUD3-1

#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <math.h>
#include <stdint.h>
#include <util/delay.h>

struct USART_configuration
{
	uint16_t baud;

	uint8_t data;

	uint8_t parity;

	uint8_t stopb;
};

float resistencia;
float temperatura;
float ADCvalue;

uint8_t USART_Init(struct USART_configuration config);

void USART_Transmit_Char(uint8_t data);

void ADC_init(void);

uint8_t calcular_temp(uint16_t valor);

uint16_t ADC_Read(void);

#endif /* LAB9_AVR_H_ */
