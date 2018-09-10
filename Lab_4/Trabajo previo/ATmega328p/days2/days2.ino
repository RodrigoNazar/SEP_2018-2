#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_ON     PORTB |= (1<<PORTB5);
#define LED_OFF    PORTB &= ~(1<<PORTB5);

uint16_t voltaje;

void termometro(void);

// Intervalos de Temperatura en valores ADC
long t_m12= 983;
long t_0 =  956;
long t_12 = 922; 
long t_24 = 850;    
long t_36 = 820;
long t_48 = 702;
long t_60 = 600;

ISR(ADC_vect)
{
  voltaje = ADC;
}

ISR(TIMER1_COMPA_vect)
{
  LED_ON
}
ISR(TIMER1_COMPB_vect)
{
  LED_OFF
}
  
void PWM(void)
{
  TCCR1B |= (1 << CS10) | (1 << WGM12);  // No prescalar, CTC mode
  TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); // Output Compare IQR
  OCR1A = 8000 ;
  OCR1B = 0 ;
}

void ADC_init(void)
{
  ADMUX |= (1 << REFS0) | (1 << MUX0); // Vcc = 3.3V , ADC1 -> PC1;
  ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADIE);
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // prescaler 128 --> 125kHz
  //ADCSRB |= (1 << ADTS1) | (1 << ADTS0); //Auto trigger T0A
  sei();
}

int main(void)
{
  DDRB |= (1<<DDB5);
  DDRD |= (1<<DDD0) | (1<<DDD1) | (1<<DDD2) | (1<<DDD3) | (1<<DDD4) | (1<<DDD5) | (1<<DDD6) ; //PORTD 0-6 Output
  PORTD &= ~(1<<PORTD1) & ~(1<<PORTD2) & ~(1<<PORTD3) & ~(1<<PORTD4) & ~(1<<PORTD5) & ~(1<<PORTD0) & ~(1<<PORTD6); //LEDS low

  ADC_init();
  PWM();
    while (1)
    {
    termometro(); 
    }
  return 0;
}

void termometro(void)
{
  if (voltaje <= t_60)
  {
    PORTD |= (1<<PORTD6) | (1<<PORTD0) | (1<<PORTD1) | (1<<PORTD2) | (1<<PORTD3) | (1<<PORTD4) | (1<<PORTD5);
    OCR1B = 7999 ;
  }
  else if (voltaje <= t_48)
  {
    PORTD |= (1 << PORTD5) | (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2) | (1 << PORTD3) | (1 << PORTD4);
    PORTD &= ~(1 << PORTD6);
    OCR1B = 5870 ;
  }
  else if (voltaje <= t_36)
  {
    PORTD |= (1 << PORTD4) | (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2) | (1 << PORTD3);
    PORTD &= ~(1 << PORTD5) & ~(1 << PORTD6);
    OCR1B = 4124 ;
  }
  else if (voltaje <= t_24)
  {
    PORTD |= (1 << PORTD3) | (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2);
    PORTD &= ~(1 << PORTD5) & ~(1 << PORTD4) & ~(1 << PORTD6);
    OCR1B = 2574 ;
  }
  else if (voltaje <= t_12)
  {
    PORTD |= (1 << PORTD2) | (1 << PORTD0) | (1 << PORTD1);
    PORTD &= ~(1 << PORTD5) & ~(1 << PORTD4) & ~(1 << PORTD3) & ~(1 << PORTD6);
    OCR1B = 1265 ;
  }
  else if (voltaje <= t_0)
  {
    PORTD |= (1 << PORTD1) | (1 << PORTD0);
    PORTD &= ~(1 << PORTD5) & ~(1 << PORTD4) & ~(1 << PORTD3) & ~(1 << PORTD2) & ~(1 << PORTD6);
    OCR1B = 568 ;
  }
  else if (voltaje <= t_m12)
  {
    PORTD |= (1 << PORTD0);
    PORTD &= ~(1 << PORTD1) & ~(1 << PORTD2) & ~(1 << PORTD3) & ~(1 << PORTD4) & ~(1 << PORTD5) & ~(1 << PORTD6);
    OCR1B = 100 ;
  }
  else
  {
    PORTD &= ~(1<<PORTD1) & ~(1<<PORTD2) & ~(1<<PORTD3) & ~(1<<PORTD4) & ~(1<<PORTD5) & ~(1<<PORTD0) & ~(1<<PORTD6);
    OCR1B = 0 ;
  }
}


