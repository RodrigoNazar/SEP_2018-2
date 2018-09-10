
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL  // 16 MHz

int subida = 1;

ISR(TIMER0_COMPA_vect)
{
  uint16_t period = ICR1;
  uint16_t duty = OCR1B;
  
  if ((duty < period) & subida)
  {
    duty++;
  }
  else
    duty = 0;
  OCR1B = duty ; 
}

void timer_frequency(uint8_t frec)
{
  TCCR1B |= (1 << CS12) | (1 << WGM12) ; // prescalar 256, CTC mode
  TIMSK1 |= (1 << OCIE1A); // Output Compare IQR
  // OCR1A = F_Cpu/(2 * N * frec) - 1
  OCR1A = F_CPU / (2*frec*256) - 1 ;
}

void PWM(void)
{
  TCCR1A |= (1 << COM1B1) | (1 << WGM11);
  TCCR1B |= (1 << CS10) | (1 << WGM12) | (1 << WGM13);  // No prescalar, Fast PWM mode
  TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); // Output Compare IQR
  // OCR1A = F_Cpu/(2 * 5000) - 1
  ICR1 = 2048 ;
  OCR1B = 0 ;
}

void milliS_timer(uint8_t milliS)
{
  TCCR0A |= (1 << WGM01) ;         // CTC mode
  TCCR0B |= (1 << CS00) | (1 << CS02) ;  // prescalar 1024
  
  OCR0A = (milliS * 7.8125) - 1;
  TIMSK0 |= (1 << OCIE0A) ; 
}


int main(void)
{
  DDRB |= (1 << DDB5) | (1 << DDB2); // B2 as output
  
  milliS_timer(1);
  PWM();
  sei();          // Enable Interrupts
    
    while (1) 
    {
    }
}

