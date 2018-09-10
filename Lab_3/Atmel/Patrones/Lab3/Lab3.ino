# define F_CPU 16000000 // 16 MHz
# include <avr/io.h>
# include <util/delay.h>
# define LED_0 PORTB0
# define LED_1 PORTB1
# define LED_2 PORTB2
# define LED_3 PORTB3
# define LED_4 PORTB4

int main(){
 DDRB |= (1<<DDB0) | (1<<DDB1) | (1<<DDB2) | (1<<DDB3) | (1<<DDB4);
 // Setea como outputs los pines PB del 0 al 4

  int patron = 0;
  while(1){
  
    // Patron 1
    
   while ((patron >= 0) & (patron <10) ){
   
    PORTB |= (1 << LED_0 );
    PORTB = ~(1 << LED_1) & ~(1 << LED_2) & ~(1 << LED_3) & ~(1 << LED_4); // Siempre será 0, 0 and cualquier cosa = 0
    _delay_ms (150) ;
    PORTB |= (1 << LED_1);
    PORTB = ~(1 << LED_0) & ~(1 << LED_2) & ~(1 << LED_3) & ~(1 << LED_4);
    _delay_ms (150) ;
    PORTB |= (1 << LED_2);
    PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_3) & ~(1 << LED_4);
    _delay_ms (150) ;
    PORTB |= (1 << LED_3);
    PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_2) & ~(1 << LED_4);
    _delay_ms (150) ;
    PORTB |= (1 << LED_4);
    PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_2) & ~(1 << LED_3);
    _delay_ms (150) ;
    patron++;   
    }
  
    // Patron 2
    
   while ((patron >= 10) & (patron < 16)){
    
    PORTB |= (1 << LED_0 );
    PORTB = ~(1 << LED_1) & ~(1 << LED_2) & ~(1 << LED_3) & ~(1 << LED_4);
    _delay_ms (100) ;
    PORTB |= (1 << LED_1);
    PORTB = ~(1 << LED_0) & ~(1 << LED_2) & ~(1 << LED_3) & ~(1 << LED_4);
    _delay_ms (100) ;
    PORTB |= (1 << LED_2);
    PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_3) & ~(1 << LED_4);
    _delay_ms (100) ;
    PORTB |= (1 << LED_3);
    PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_2) & ~(1 << LED_4);
    _delay_ms (100) ;
    PORTB |= (1 << LED_4);
    PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_2) & ~(1 << LED_3);
    _delay_ms (100) ;
    // Para el otro lado
    PORTB |= (1 << LED_3 );
    PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_2) & ~(1 << LED_4);
    _delay_ms (100) ;
    PORTB |= (1 << LED_2);
    PORTB = ~(1 << LED_0) & ~(1 << LED_1) & ~(1 << LED_3) & ~(1 << LED_4);
    _delay_ms (100) ;
    PORTB |= (1 << LED_1);
    PORTB = ~(1 << LED_0) & ~(1 << LED_2) & ~(1 << LED_3) & ~(1 << LED_4);
    _delay_ms (100) ;
    patron++;   
   }
  
   // Patron 3
   
   while ((patron >=16) & (patron < 25)){
    
    PORTB = (1 << LED_0 ) | (1 << LED_2 ) | (1 << LED_4 ); // Siempre es 1, porque 1 or cualquier cosa = 1
    PORTB = ~(1 << LED_1) & ~(1 << LED_3);
    _delay_ms (300) ;
    PORTB = (1 << LED_1) | (1 << LED_3 );
    PORTB = ~(1 << LED_0) & ~(1 << LED_2) & ~(1 << LED_4);
    _delay_ms (300) ;
    patron++;
    if (patron == 24){
    patron = 0;   
    }
   }
  }
   return 0;
}


