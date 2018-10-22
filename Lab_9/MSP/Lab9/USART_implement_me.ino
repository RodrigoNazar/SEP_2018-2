#include "USART_implement_me.h"

void USART_Init()
{
  P4SEL |= BIT4 | BIT5;             // P4.4,5 = USCI_A1 TXD/RXD

  UCA1CTL1 = 0;
  UCA1CTL0 = 0;

  UCA1CTL1 |= UCSWRST;       // State machine in RESET
  UCA1CTL1 |= UCSSEL_2;     // SMCLK = 1048 KHz
  UCA1BR1 = 0;

  UCA1BR0 = 18;     // Baud Rate 57600
  UCA1MCTL = BIT2;  // Modulation UCBRSx=2, UCBRF=0
  UCA1CTL1 &= ~UCSWRST;  // USCI in operation mode

  UCA1IE |= UCRXIE;   // Enable USCI_A1 RX
}

void Init_Pins(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT

    P6DIR |= BIT5;
    P3DIR |= BIT7 | BIT4 | BIT3;
    P4DIR |= BIT0;
    P1DIR |= BIT6;

    P6OUT = 0;
    P3OUT = 0;
    P1OUT = 0;
}

void PWM_Init(void)
{
  /*** GPIO Set-Up ***/
    P1DIR |= BIT2;          // P1.2 as Output
    P1SEL |= BIT2;          // //P1.2 set PWM

  /*** Timer0_A Set-Up ***/
    TA0CCR0 |= 1000;           // PWM period
    TA0CCTL1 |= OUTMOD_7;     // CCR1 output mode = reset/set
    TA0CCR1 |= 0;           // CCR1 PWM duty cycle
    TA0CTL |= TASSEL_2 + MC_1;    // SMLK, Up Mode (Counts to TA0CCR0)
}


void Calcular_Temp(uint8_t temperatura)
{
	if (temperatura <= 0){
	LED1_OFF;
    LED2_OFF;
    LED3_OFF;
    LED4_OFF;
    LED5_OFF;
    LED6_OFF;
    TA0CCR1 = 0;
	}

	else if ((temperatura <= 17) and (temperatura > 0)){
    LED1_OFF;
    LED2_OFF;
    LED3_OFF;
    LED4_OFF;
    LED5_OFF;
    LED6_ON;
    TA0CCR1 = 142;
	}


	else if ((temperatura <= 20) and (temperatura > 17)){
        LED1_OFF;
        LED2_OFF;
        LED3_OFF;
        LED4_OFF;
        LED5_ON;
        LED6_ON;
    TA0CCR1 = 284;
	}

	else if ((temperatura <= 25) and (temperatura > 20)){
        LED1_OFF;
        LED2_OFF;
        LED3_OFF;
        LED4_ON;
        LED5_ON;
        LED6_ON;
    TA0CCR1 = 428;
	}

	else if ((temperatura <= 30) and (temperatura > 25)){
        LED1_OFF;
        LED2_OFF;
        LED3_ON;
        LED4_ON;
        LED5_ON;
        LED6_ON;
    TA0CCR1 = 571;
	}

	else if ((temperatura <= 40) and (temperatura > 30)){
        LED1_OFF;
        LED2_ON;
        LED3_ON;
        LED4_ON;
        LED5_ON;
        LED6_ON;
   TA0CCR1 = 714;
	}

	else {// mayor a 40;
        LED1_ON;
        LED2_ON;
        LED3_ON;
        LED4_ON;
        LED5_ON;
        LED6_ON;
    TA0CCR1 = 1000;
	}
}

