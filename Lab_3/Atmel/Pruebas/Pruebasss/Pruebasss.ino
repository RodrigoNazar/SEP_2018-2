# define F_CPU 16000000 // 16 MHz
# include <avr/io.h>
# include <util/delay.h>
# define LED_0 PORTB0
# define boton2 PIND2

int main(){
 DDRB |= (1<<DDB0);
 DDRD &= ~(1<<DDD1);
 PORTD |= (1<<PORT)
 PORTB |= (1<<LED_0);

 while (1){
  if(!(PIND & (1 << boton2))){
    _delay_ms(70);
    if (!(PIND & (1 << boton2))){
      _delay_ms(70);
      if(!(PIND & (1 << boton2))){
      PORTB |= (1<<LED_0);
      }
    }
  }
  else{
    PORTB &= ~(1 << LED_0);
  }
  while(!(PIND & (1 << boton2))){
    }
  }
  return 0;
 }

