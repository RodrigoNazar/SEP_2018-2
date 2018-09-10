# define F_CPU 16000000 // 16 MHz
# include <avr/io.h>
# include <util/delay.h>
# include <avr/interrupt.h>

# define LED_ON             PORTB |= (1<<PORTB5)
# define LED_OFF            PORTB &= ~(1<<PORTB5)
# define LED_TOGGLE        PINB  |= (1<<PINB5)
# define SWITCH_PRESSED    !(PINB & (1<<PINB7))

ISR(TIMER1_COMPA_vect)
{
  LED_TOGGLE;
}

void Timer_frequency(uint8_t freq){
  TCCR1B |= (1<< CS12) | (1<<WGM12); // Preescalado del clock es 256 y Estamos en ctc mode 

  // Ahora hay que cambiar el tipo de interrupción que usamos

  // Formula para sacar la frecuencia en la página 196
  TIMSK1 |= (1<<OCIE1A);
  OCR1A = (F_CPU/(freq*2*256)-1); 
}


int main(void)
{
  DDRB |= (1<<DDB5);
  DDRB &= ~(1<<DDB7);

  // Queremos que el led parpadee de forma más precisa
  // Vamos al datasheet y vamos a TC1 - 16-bit Timer/Counter1 with PWM --> Register Description para cambiar el modo del timer
  // Vemos la tabla de la página 172 y buscamos que bits tenemos que setear en 1 para que el modo de operación sea CTC (capture and compare mode).
  // El bit es WGM12. Luego hay que setear el registro de output con ese valor. Vamos a TC1 Control Register B y el registro es TCCR1B (que ya estabamos escribiendo encima)

  Timer_frequency(10); // Hertzz

  sei();

  
  while(1){

  }
}


