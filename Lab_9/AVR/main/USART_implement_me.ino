#include "USART_implement_me.h"

uint8_t USART_Init(struct USART_configuration config)
{
	switch(config.baud){
		case 57600:
		UBRR0H = (BRATE1 >> 8);
		UBRR0L = BRATE1;
		break;
		case 19200:
		UBRR0H = (BRATE2 >> 8);
		UBRR0L = BRATE2;
		break;
		case 9600:
		UBRR0H = (BRATE3 >> 8);
		UBRR0L = BRATE3;
		break;
	}

	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	switch(config.data){
		case 8:
		UCSR0C |= (1 << UCSZ01)|(1 << UCSZ00);
		break;
		case 7:
		UCSR0C |= (1 << UCSZ01);
	}
	switch(config.parity){
		case 0:
		break;
		case 1:
		UCSR0C |= (1 << UPM01);
	}
	switch(config.stopb){
		case 1:
		break;
		case 2:
		UCSR0C |= (1 << USBS0);
		break;
	}
}

void USART_Transmit_char(uint8_t data)
{
 	/* Wait for empty transmit buffer */
 	while ( !( UCSR0A & (1<<UDRE0)) );      // UDRE0 es el sexto bit del registro UCSR0A. El bit indica si
                                            // el buffer de transmisión (UDRn) está listo para transferir data. Si UDRE0 es 1,
                                            // el buffer está vacío y listo para cargarse de información.
 	/* Put data into buffer, sends the data */
    UDR0 = data;                             // Carga la información en el buffer de transmición UDRn (UDR0)
}


void ADC_Init(void)
{
	ADMUX = 0;                // use ADC0
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1<<ADEN);
}

uint16_t ADC_Read(void)
{
	ADCSRA |= (1<<ADSC);
	while (ADCSRA & (1<<ADSC)) ; //espera del flag
	return ADC;
}

uint8_t calcular_temp(uint16_t valor)
{
  // Obtenido de:
  // https://arduinodiy.wordpress.com/2015/11/10/measuring-temperature-with-ntc-the-steinhart-hart-formula/
	resistencia = (1023.0 / valor) - 1;
	resistencia = 100000 / resistencia;

	temperatura = resistencia / 100000; // (R/Ro)
	temperatura = log(temperatura); // ln(R/Ro)
	temperatura /= 3950; // 1/B * ln(R/Ro)
	temperatura += 1.0 / (25 + 273.15); // + (1/To)
	temperatura = 1.0 / temperatura; // Invertir
	temperatura -= 273.15; // celsius

	int8_t Tfinal = (int8_t) temperatura;
	return Tfinal;
}
