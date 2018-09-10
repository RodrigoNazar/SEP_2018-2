#include <avr/io.h>
#include <util/delay.h>
int main(){
  DDRB |= 0b00100000;
  while(1){
    PORTB ^= 0b00100000;
    _delay_ms(1000);
  }
}

