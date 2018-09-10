# include <msp430.h>  // Libreria que incluye las definiciones apropiadas para configurar los IO
# include <stdint.h> // Librería que permite el uso de cosas como uint32_t

// MSPgcc

int main ( void )
{
  WDTCTL = WDTPW | WDTHOLD ; // Stop watchdog timer , it runs by default .
  // Esta línea se ocupa muchas veces al inicio de los programas de la MSP, lo que hace es desactivar el
  // watchdog timer, el que puede resetear el aparato cada cierto tiempo
  // Página 42 del datasheet
  
  // P1DIR |= 0x01 ; // Port1 direction register , Pin0 as output
  // To set a specific pin as output or input, we write a '1' or '0' on the appropriate bit of the register.
  // P1DIR = <PIN7><PIN6><PIN5><PIN4><PIN3><PIN2><PIN1><PIN0>
  // Since we want to blink the on-board red LED, we want to set the direction of Port 1, Pin 0 (P1.0) as an output
  // We do that by writing a 1 on the PIN0 bit of the P1DIR register
  // P1DIR = <PIN7><PIN6><PIN5><PIN4><PIN3><PIN2><PIN1><PIN0>
  // P1DIR |= 0000 0001
  // P1DIR |= 0x01 <-- this is the hexadecimal conversion of 0000 0001
  P1DIR |= BIT0;

  while (1) // Infinite loop
  {
    // P1OUT ^= 0x01 ; // Toggle P1 .0 ( XOR ) Pagina 55 del Datasheet
    P1OUT ^= BIT0;
    for ( volatile uint32_t i=0; i< 20000; i ++) ; // B u s y w a i t delay
    // uint32_t denota una variable de 32 bits de largo
  }

  return 0;
}


/*
Especificaciones de la tarjeta:
- Microcontrolador de 16 bits
- 128KB of flash memory
- 8KB of RAM
- clk de 25 MHz
- Operación entre 1.8V - 3.6V
- Interfases seriales
- ADC de 12 bits
- Comparador análogo  
*/
