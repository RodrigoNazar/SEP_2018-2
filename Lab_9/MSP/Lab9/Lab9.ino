#include "USART_implement_me.h"

int main(void)
{
  Init_Pins();

  USART_Init();
  PWM_Init();

  __bis_SR_register(GIE);       // Enter LPM0, interrupts enabled

  while(1);

  return 0;
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
        temperatura = UCA1RXBUF;
        Calcular_Temp(temperatura);
}
