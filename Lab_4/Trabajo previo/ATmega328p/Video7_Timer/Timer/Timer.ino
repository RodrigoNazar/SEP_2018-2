# define F_CPU 16000000 // 16 MHz
# include <avr/io.h>
# include <util/delay.h>
# include <avr/interrupt.h>

# define LED_ON             PORTB |= (1<<PORTB5)
# define LED_OFF            PORTB &= ~(1<<PORTB5)
# define LED_TOGGLE        PINB  |= (1<<PINB5)
# define SWITCH_PRESSED    !(PINB & (1<<PINB7))

ISR(TIMER1_OVF_vect)
{
  LED_TOGGLE;
}



int main(void)
{
  DDRB |= (1<<DDB5);
  DDRB &= ~(1<<DDB7);

  ////////////////////////VIDEO 7
  // Timer set up (pág 173)

  TCCR1B |= (1<< CS12); // Hay que poner un 1 en CS12 para contar hasta 256 (clkI/O/256 (From prescaler))

  //Luego buscamos el registro del interrupt para que sirva 
  // TC1 - 16-bit Timer/Counter1 with PWM -->  Register Description --> Timer/Counter 1 Interrupt Mask Register
  // Para activarlo 

  TIMSK1 |= (1<<TOIE1);

  sei(); // Activa los interrupts

  // Finalmente debemos implementar nuestra rutina de interrupción
  // Vamos a Interrupts --> Interrupt Vectors in ATmega328/P --> el vector de overflow (TIMER1_OVF) -->
  // Vamos a la descripción de la librería <avr/interrupt.h> y buscamos por TIMER1_OVF --> Buscamos la función de interrupt ISR que está arriba



  
  
  while(1){

  }
}


