#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000 // 16 MHz


#define LED_ON        PORTB |= (1<<PORTB5);
#define LED_OFF       PORTB &= ~(1<<PORTB5);
#define LED_TOGGLE    PINB |= (1<<PINB5);


ISR(TIMER1_COMPA_vect) 
{
  LED_ON;
}

ISR(TIMER1_COMPB_vect)
{
  LED_OFF;
}

ISR(ADC_vect){ 
  uint16_t duty = ADC;
  OCR1B = duty; // Representa el duty cicle
  
}

void PWM_Init_LED(void){ 
  TCCR1B |= (1<<CS10) | (1<<WGM12);  // No preescalado y modo CTC
  TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B); // Output compare IRQs

  OCR1A = 800; // (F_CPU/(10000*2*1)-1)
  OCR1B = 200;
    
}


void ADC_init(void){
  
  ADMUX |= (1<<REFS0) | (1<<MUX0); 
  ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);                         
  sei(); 
  
} 

int main(void){

  DDRB |= (1<<DDB5);
  
  ADC_init();
  PWM_Init_LED();
  PWM_Init_LED();
  
  while(1){
  }
}
