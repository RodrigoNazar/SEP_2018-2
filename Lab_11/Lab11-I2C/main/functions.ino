#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include "USART_implement_me.h"

void configure_pins(void){

  DDRB = (1<<5);  // all output; only one heartbeatLED used
  DDRC = 0x00;  // all input; the I2C special pin functions overrule this anyways
  PORTC = 0xff; // all pullups on;
  
}

void bienvenida(void){
  USART_Transmit("\r\nWelcome to the Lab 11!\r\n\r\n");
  USART_Transmit("\r\nChoose an option:\n1- Temperature senser\n2- Sine wave export\r\n\r\n");
}

void temperature_working(void){

      temperature = tmp102Read();
      USART_Transmit("Temperature: ");
      char buff[10];
      itoa(temperature, buff, 10);
      USART_Transmit(buff);
      USART_Transmit(" deg. Celsius\r\n");
      PORTB ^= (1 << PORTB5); // heartbeat LED
      _delay_ms(1000);
}

void DAC_working(void){ 
  
      dato = obtener_dato(lookup);    // Obtiene un dato de la sinusoide
      msb_out = (uint8_t)(dato>>8);   // Los bits más significativos
      lsb_out = (uint8_t)(dato);      // El bit menos significativo
      send_data(msb_out, lsb_out);    // Envío la información
      lookup++;
      if (lookup == 512) lookup = 0;
      PORTB ^= (1 << PORTB5);         // Led de parpadeo
      _delay_ms(5);
  
}

