# define F_CPU 16000000 // 16 MHz
# include <avr/io.h>
# include <util/delay.h>
# define LED_0 PORTB0
# define LED_1 PORTB1
# define LED_2 PORTB2
# define LED_3 PORTB3
# define LED_4 PORTB4
# define boton PINB7
# define boton2 PIND1

int main(){
 DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4);
 DDRB &= ~(1<<DDB7);
// DDRD |= (1<<DDD0);
// DDRD &= ~(1<<DDD1);
// PORTD |= (1<<DDD0);
 // Setea como outputs los pines PB del 0 al 4
 // También el PD0 como output
 // PB7 y PD1 son imputs, al activarle las resistencias de pull up

  int patron = 0;
  while(1){

    if ((!(PINB & (1<<boton)))) //Queremos que el boton esté low (!) PINB es el registro de lectura, 
    { //lo comparamos con el estado en que estamos interesados, (1<<PINB7)
      _delay_ms (70);
      if ((!(PINB & (1<<boton))) )
    {
      _delay_ms (70);
      if ((!(PINB & (1<<boton))) )
    {
      if (patron == 0)
      {
      PORTB |= (1 << LED_0 );
      PORTB = ~(1 << LED_1) & ~(1 << LED_2) & ~(1 << LED_3) & ~(1 << LED_4); // Siempre será 0, 0 and cualquier cosa = 0
      patron++;
      }
      else if (patron == 1)
      {
      PORTB |= (1 << LED_1);
      PORTB = ~(1 << LED_0) & ~(1 << LED_2) & ~(1 << LED_3) & ~(1 << LED_4);
      patron++;
      }
      else if (patron == 2)
      {
      PORTB |= (1 << LED_2);
      PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_3) & ~(1 << LED_4);
      patron++;
      }
      else if (patron == 3)
      {
      PORTB |= (1 << LED_3);
      PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_2) & ~(1 << LED_4);
      patron++;
      }
      else if (patron == 4)
      {
      PORTB |= (1 << LED_4);
      PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_2) & ~(1 << LED_3);
      patron = 0;
      
      }
      while (!(PINB & (1<<boton))){  // No cambia de estado si se sigue presionando el boton
      }

    }
   }
 }
}
   return 0;
}


// I/O pins tienen diodos de protección (cuando el voltaje es muy alto, drenan la corriente a tierra o a Vcc si es muy bajo)
// VCC = 2.4V - 5.5V Min: -0.5  Max VCC + 0.5 (página 365)
// La suma de las corrientes en en los puertos C algo no debe pasar los 100mA (pag 367)

