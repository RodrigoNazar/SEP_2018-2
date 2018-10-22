#ifndef _LAB9_MSP_H_
#define _LAB9_MSP_H_

#include <msp430.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define LED1_ON	 	P6OUT |= BIT5
#define LED2_ON	 	P3OUT |= BIT4
#define LED3_ON	 	P3OUT |= BIT3
#define LED4_ON	 	P1OUT |= BIT6
#define LED5_ON		P4OUT |= BIT0
#define LED6_ON		 P3OUT |= BIT7

#define LED1_OFF	 P6OUT &= ~BIT5
#define LED2_OFF	 P3OUT &= ~BIT4
#define LED3_OFF	 P3OUT &= ~BIT3
#define LED4_OFF	 P1OUT &= ~BIT6
#define LED5_OFF	 P4OUT &= ~BIT0
#define LED6_OFF	 P3OUT &= ~BIT7

uint8_t temperatura;

void USART_Init();

void Calcular_Temp(uint8_t temp);

void Init_Pins(void);

void PWM_Init(void);

#endif // _LAB9_MSP_H_
