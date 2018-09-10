# include <msp430.h>
# include <stdint.h>

int main(){
  WDTCTL = WDTPW | WDTHOLD;

  P1DIR = 0b00111100;
  P2DIR = 0b00010000;
  
  int contador = 0;
  
  while(1){
    while ((contador >=0) & (contador <10)){
      P1OUT = 0b00000100;
      P2OUT = 0b00000000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      P1OUT = 0b00001000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      P1OUT = 0b00010000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      P1OUT = 0b00100000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      P1OUT = 0b00000000;
      P2OUT = 0b00010000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      contador++;
    }
    while ((contador >=10) & (contador <16)){
      //Para un lado
      P1OUT = 0b00000100;
      P2OUT = 0b00000000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      P1OUT = 0b00001000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      P1OUT = 0b00010000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      P1OUT = 0b00100000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      P1OUT = 0b00000000;
      P2OUT = 0b00010000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      // Para el otro lado
      P1OUT = 0b00100000;
      P2OUT = 0b00000000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      P1OUT = 0b00010000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      P1OUT = 0b00001000;
      for ( volatile uint32_t i=0; i< 5000; i ++) ;
      contador++;
    }
    while ((contador >=16) & (contador <40)){
      P1OUT = 0b00010100;
      P2OUT = 0b00010000;
      for ( volatile uint32_t i=0; i< 7000; i ++) ;
      P1OUT = 0b00101000;
      P2OUT = 0b00000000;
      for ( volatile uint32_t i=0; i< 7000; i ++) ;
      contador++;
      if (contador == 39){
      contador = 0;   
      }
    }
    }
  return 0;
}

// Revisar página 24 - 25 datasheet para los voltajes y corrientes

// OUTPUT: Vcc = 3V -> VMIN: Vcc-0.6 IMAX: 15mA - 6mA VMAX: Vcc
// INPUT:  Vcc = 3V -> VMIN: Vss IMAX: 15mA - 6mA VMAX: Vss+0.6
