# define F_CPU 16000000 // 16 MHz
# include <avr/io.h>
# include <util/delay.h>
# include <avr/interrupt.h>

# define LED_ON             PORTB |= (1<<PORTB5)
# define LED_OFF            PORTB &= ~(1<<PORTB5)
# define LED_TOGGLE        PINB  |= (1<<PINB5)
# define SWITCH_PRESSED    !(PINB & (1<<PINB7))

ISR(TIMER1_COMPA_vect) // Cambiamos las interrupciones para prender y apagar el led
{
  LED_ON;
}

ISR(TIMER1_COMPB_vect) // Cambiamos las interrupciones para prender y apagar el led
{
  LED_OFF;
}

/////////////////////////////////////////

void Timer_frequency(uint8_t freq){
  TCCR1B |= (1<< CS12) | (1<<WGM12); // Preescalado del clock es 256 y Estamos en ctc mode 

  // Ahora hay que cambiar el tipo de interrupción que usamos

  // Formula para sacar la frecuencia en la página 196
  TIMSK1 |= (1<<OCIE1A);
  OCR1A = (F_CPU/(freq*2*256)-1); 
}

/////////////////////////////////////////

void PWM_Init( void ){ // Cambiamos esta función de Timer_freq a PWM Init}
                       // Queremos hacer la PWM lo más precisa posible. Vamos a la descripcion de los registros y en la pag 173 notamos que para sacar el preescalado
                       // del clock, hay que CS10 debe tener un 1
  TCCR1B |= (1<< CS10) | (1<<WGM12); 
  TIMSK1 |= (1<<OCIE1A) | (1<<OCIE1B); // Interrupción que prende el LED | Interrupción que lo apaga
  OCR1A = (F_CPU/(10000*2*1)-1); // (F_CPU/(10000*2*1)-1) = 800; Lo que indica 10 kHz sample
  OCR1B = 10; // OCR1B = Output compare register 1 b. DUTY CICLE 1/80
}


int main(void)
{
  DDRB |= (1<<DDB5);
  DDRB &= ~(1<<DDB7);

  
  
  PWM_Init();

  sei();

  
  while(1){

  }
}
