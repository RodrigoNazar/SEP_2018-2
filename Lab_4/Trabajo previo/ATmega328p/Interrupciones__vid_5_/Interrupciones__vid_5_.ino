# define F_CPU 16000000 // 16 MHz
# include <avr/io.h>
# include <util/delay.h>
# include <avr/interrupt.h>

# define LED_ON      PORTB |= (1<<PORTB5)
# define LED_OFF     PORTB &= ~(1<<PORTB5)
# define LED_ TOGGLE PINB  |= (1<<PINB5)
# define SWITCH_PRESSED !(PINB & (1<<PINB7))

ISR(PCINT0_vect){ // Buscamos en el datasheet el vector de PCINT0, buscamos en la página de las librerías y pillamos esta función
                  // Movemos la unidad lógica del problema acá. Ahora, el código entrará en esta función una vez se precione el switch.
      if (SWITCH_PRESSED){
      LED_ON;
    }
    else
    {
      LED_OFF;
    }
}

int main(void)
{
  DDRB |= (1<<DDB5);
  DDRB &= ~(1<<DDB7);
  
  // El puerto B es un puerto bidireccional de 8 bits con resistencias de pull up (el PB7 es del botón). 
  // Si queremos realizar la interrupción con respecto a ese pin, vemos que está asociado al PCINT7 (pág 104).
  // Yendo al resumen de los registros (pág 429) notamos que el registro es parte del pin llamado PCMSK0 (Port C mask)
  // Después buscamos en el datasheets external interrupts y vemos PIN CHANGE MASK REGISTER 0
  // Este pin es enabled asignandole un 1 en el respectivo pin change interrupt (PCINT7) en este caso (pág 96 datasheet).
  
  PCMSK0 |= (1<<PCINT7);

  // Después se busca el registro de control que acciona el pin change interrupt (pág 92), que se activa con un 1 en PCIE0 (por defecto, creo).
  
  PCICR |= (1<<PCIE0);

  
  sei(); // Global interrupt enable de la librería <avr/interrupt.h> después revisar linea de ISR
  
  while(1){ // Hay que dejar el while 1
    

  }
}



