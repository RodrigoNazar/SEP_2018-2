#include <msp430f5529.h>


void variar_duty();
int up = 1;

int main(void)
  {
    WDTCTL = WDTPW + WDTHOLD;   // Stop watchdog timer

  /*** GPIO Set-Up ***/
    P1DIR |= BIT2;          // P1.2 as Output
    P1SEL |= BIT2;          // //P1.2 set PWM

  /*** Timer0_A Set-Up ***/
    TA0CCR0 |= 512;           // PWM period
    TA0CCTL1 |= OUTMOD_7;     // CCR1 output mode = reset/set (CTC)
    TA0CCR1 |= 0;           // CCR1 PWM duty cycle
    TA0CTL |= TASSEL_1 + MC_1 + TACLR;    // SMLK, Up Mode (Counts to TA0CCR0)

  /*** Timer1_A Set-Up ***/
    TA1CCTL0 |= CCIE;       // Enable Timer1_A(CCR0) interrupts
    TA1CCR0 |= 128;          // Counter value ACLK=32768Hz/CCR0 -> ~200Hz
    TA1CTL |= TASSEL_1 + MC_1 + TACLR;    // ACCLK, upMode (TA1CCR0), clear TAR

    __bis_SR_register(GIE);       // Enter LPM3, enable interrupts (General interrupt enable)

  }

#pragma vector=TIMER1_A0_VECTOR     // Timer1 A0 interrupt service routine
   __interrupt void Timer1_A0 (void) 
   {
    variar_duty();
   }
    
void variar_duty(void)
  {
    long period = TA0CCR0;
    long duty = TA0CCR1;
    if ((duty < period) & up)
    {
      duty = duty +10;
    }
    else
    {
      up = 0;
      duty--;
      if (duty <= 0)
          up = 1;
    }
    TA0CCR1 = duty;
  }
