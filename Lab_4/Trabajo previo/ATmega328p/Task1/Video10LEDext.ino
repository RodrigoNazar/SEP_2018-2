# define F_CPU 16000000 // 16 MHz
# include <avr/io.h>
# include <util/delay.h>
# include <avr/interrupt.h>

# define LED_ON             PORTB |= (1<<PORTB0)
# define LED_OFF            PORTB &= ~(1<<PORTB0)
# define LED_TOGGLE        PINB  |= (1<<PINB0)
# define SWITCH_PRESSED    !(PINB & (1<<PINB7))

ISR(TIMER1_COMPA_vect) 
{
  LED_ON;
}

ISR(TIMER1_COMPB_vect)
{
  LED_OFF;
}

/////////////////////////////////////////

void Timer_frequency(uint8_t freq){
  TCCR1B |= (1<< CS12) | (1<<WGM12);


  TIMSK1 |= (1<<OCIE1A);
  OCR1A = (F_CPU/(freq*2*256)-1); 
}

/////////////////////////////////////////

void PWM_Init( void ){
  
  TCCR1B |= (1<< CS10) | (1<<WGM12); 
  TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B);
  OCR1A = (F_CPU/(10000*2*1)-1); 
  OCR1B = 10; 
}

/////////////////////////////////////////

// Creamos una nueva función para subir gradualmente la pwm

void miliS_timer( uint8_t milliS){ // La variable es un entero de 8 bits que representa los milisegundos
  TCCR0A |= (1<<WGM01); // Página 138 Set to CTC mode

  // Después, queremos el máximo de preescalado del clock de 1024

  TCCR0B |= (1<<CS02) | (1<<CS00); // Set preescaler to 1024

  OCR0A = milliS*7,8125-1; // Contador del timer - OUTPUT COMPARE REGISTER 0 A IS ASSIGNED TO (F_CPU/(f*2*N)-1) f=1000 y N =1024

  // Enable the interrupt
  TIMSK0 = (1<<OCIE0A);// Iterrupt mask register
}


/////////////////////////////////////////

// Interrupción con lógica para incrementar el duty cycle

ISR(TIMER0_COMPA_vect){
  // Timer de 16 bits
  uint16_t period = OCR1A; // Output compare register A
  uint16_t duty = OCR1B;

  if (duty < period){
    duty++;
  }
  else{
    duty = 0;
  }
  
  OCR1B = duty;
}



int main(void)
{
  DDRB |= (1<<DDB0);
  DDRB &= ~(1<<DDB7);

  
  miliS_timer(5); // La resolcución del timer es de 800
  PWM_Init();

  sei();

  
  while(1){

  }
}
