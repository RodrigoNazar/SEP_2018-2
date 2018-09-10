#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_ON     PORTB |= (1<<PORTB1);
#define LED_OFF    PORTB &= ~(1<<PORTB1);


void LEDS(void);

// Valores del ADC
long v0 = 983;  // -12
long v1 = 956;  //  0
long v2 = 922;  //  12
long v3 = 850;  //  24
long v4 = 820;  //  36
long v5 = 702;  //  48
long v6 = 600;  //  60


uint16_t val_ADC;


////////// INTERRUPCIONES //////////

ISR(ADC_vect) // ADC
{
  val_ADC = ADC;
}

ISR(TIMER1_COMPA_vect) // Prendido y apagado de del LED
{
  LED_ON
}

ISR(TIMER1_COMPB_vect)
{
  LED_OFF
}

////////// TIMERS //////////

void PWM_Init( void ){
  
  TCCR1B |= (1<< CS10) | (1<<WGM12); // No prescalar, In CTC mode the counter is cleared to zero when the counter value (TCNT1) matches either the OCR1A.
                                     // Normal mode: Cuenta hasta su valor máximo y vuelve a setearse a 0
                                     // Fast PWM: Se preocupa de trabajar a altas frecuencias
                                     // Phase Correct PWM Mode: Preocupado de conmutar cuando debe
                                     // Phase and Frequency Correct PWM Mode: provides a high resolution phase and frequency correct PWM waveform generation option
  TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B); // The Timer/Counter1 Output Compare A Match interrupt is enabled.
  OCR1A = (F_CPU/(10000*2*1)-1); // Periodo de la PWM
  OCR1B = 0;  // 
}

////////// ADC //////////

void ADC_init(void){
  // Set up del mux
  ADMUX |= (1<<REFS0) | (1<<MUX0); // Voltaje de referencia pag 317. REFS0 = 1 para voltaje de ref sea Vcc 
                                   // ADC input channel (ADC1). Buscando ADC1, notamos que está conectado al pin PC1
                                   // MUX0 = 1 es para seleccionar el ADC1

  // Set up del registro de control de status, para el reloj
  ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);  
                                   // Página 249.
                                   // ADEN: Writing this bit to one enables the ADC.
                                   // ADSC: write this bit to one to start each conversion.
                                   // ADATE: When this bit is written to one, Auto Triggering of the ADC is enabled.
                                   // ADIF: This bit is set when an ADC conversion completes and the Data Registers are updated. NO LO QUEREMOS
                                   // ADIE: the ADC Conversion Complete Interrupt is activated.
                                   // ADPS0, ADPS1 y ADPS2 Aparecen en la tabla 25-5 (pág 250)
                                   // Necesitabamos una frecuencia entre 50 kHz a 200 kHz para tener buena resolución. Como alimentamos el AVR
                                   // Con 5V, CPU_Freq es de 16MHz y notamos que 16M/128 = 125k :). Con ADPS0, ADPS1 y ADPS2 en 1, el divisor de clk es 128.

  // Setup de las interrupciones
  sei(); // Ver la segunda parte de programación
} 


int main(void)
{
  DDRB |= (1<<DDB1);
  DDRD |= (1<<DDD0) | (1<<DDD1) | (1<<DDD2) | (1<<DDD3) | (1<<DDD4) | (1<<DDD5) | (1<<DDD6) ; //PORTD 0-6 Output
  PORTD &= ~(1<<PORTD0) & ~(1<<PORTD1) & ~(1<<PORTD2) & ~(1<<PORTD3) & ~(1<<PORTD4) & ~(1<<PORTD5) & ~(1<<PORTD6); //LEDS low

  ADC_init();
  PWM_Init();
    while (1)
    {
    LEDS(); 
    }
  return 0;
}

void LEDS(void)
{
  if (val_ADC <= v6)
  {
    PORTD |= (1<<PORTD6) | (1<<PORTD0) | (1<<PORTD1) | (1<<PORTD2) | (1<<PORTD3) | (1<<PORTD4) | (1<<PORTD5);
    OCR1B = 7999 ;
  }
  else if (val_ADC <= v5)
  {
    PORTD |= (1 << PORTD5) | (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2) | (1 << PORTD3) | (1 << PORTD4);
    PORTD &= ~(1 << PORTD6);
    OCR1B = 5870 ;
  }
  else if (val_ADC <= v4)
  {
    PORTD |= (1 << PORTD4) | (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2) | (1 << PORTD3);
    PORTD &= ~(1 << PORTD5) & ~(1 << PORTD6);
    OCR1B = 4124 ;
  }
  else if (val_ADC <= v3)
  {
    PORTD |= (1 << PORTD3) | (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD2);
    PORTD &= ~(1 << PORTD5) & ~(1 << PORTD4) & ~(1 << PORTD6);
    OCR1B = 2574 ;
  }
  else if (val_ADC <= v2)
  {
    PORTD |= (1 << PORTD2) | (1 << PORTD0) | (1 << PORTD1);
    PORTD &= ~(1 << PORTD5) & ~(1 << PORTD4) & ~(1 << PORTD3) & ~(1 << PORTD6);
    OCR1B = 1265 ;
  }
  else if (val_ADC <= v1)
  {
    PORTD |= (1 << PORTD1) | (1 << PORTD0);
    PORTD &= ~(1 << PORTD5) & ~(1 << PORTD4) & ~(1 << PORTD3) & ~(1 << PORTD2) & ~(1 << PORTD6);
    OCR1B = 568 ;
  }
  else if (val_ADC <= v0)
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


