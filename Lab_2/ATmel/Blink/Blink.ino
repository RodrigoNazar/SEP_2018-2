# define F_CPU 16000000UL // CPU frequency in Hz = 16M Hz define-> Variables globales
# define LED_PIN 5 // LED_PIN = 5
# include <avr/io.h> // Libreria que incluye las definiciones apropiadas para configurar los IO
# include <util/delay.h> // Libreria para delay y F_CPU

// Cross-compiler es el que tiene un Host y un Target no como un native compiler
// avrgcc

int main ( void )
{
  // sets the direction of this pin to output
  // DDRx es un registro que selecciona la dirección del pin que se quiere configurar
  // Cuando el registro DDRx está en 1m el pin Pxn se configura como output (acá es el pin PB5)
  DDRB |= (1 << LED_PIN ); // |= Asignación con OR binario Setea el pin en 1 (output)

  while (1)
  {
    // toggles the state of this pin
    PORTB ^= (1 << LED_PIN ); // ^= Asignación con XOR binario
    // b u s y w a i t s the specified time
    _delay_ms (100) ;
  }
}

/*
- 32 general purpose working registers
- 23 general purpose I/O lines
- serial programmable USARTs
- 16Mhz clk
- ADC 10-bit
- (-40°C to 85°C)
- 1.8V   - 5.5V
*/
