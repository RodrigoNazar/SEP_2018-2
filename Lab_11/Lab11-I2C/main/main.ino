
#include "USART_implement_me.h"
#include "I2C_implement_me.h"


int main(void)
{
	// Pin configurations
	configure_pins();

	struct USART_configuration config_57600_8N1 = {57600, 0, 8, 1};

	USART_Init(config_57600_8N1);
	linked_list_init();

	I2C_init();

	sei();
  
	// Welcome message
  bienvenida();

	while(1)
	{
		if (tipo == 1)
		{
			temperature_working();
		}
		else if (tipo == 0)
		{
			DAC_working();
		}
	}
}


ISR(USART_RX_vect)
{
	uint8_t data;
	data = UDR0;
	if (data == '1')
	{
		USART_Transmit("\r\nWelcome to the TMP102 I2C temperature sensor test!\r\n\r\n");
		tipo = 1;
	}
	else if (data == '2')
	{
		tipo = 0;
		USART_Transmit("\r\nWelcome to the MCP4725 I2C DAC test!\r\n\r\n");
	}
}

ISR(USART_UDRE_vect)
{
	if (Send_Linked_list(&UDR0))
	{
		reset_list(head_t, 't');
		//UDR0 = '\n';
		//disable transmission and UDR0 empty interrupt
		UCSR0B &= ~((1<<TXEN0)|(1<<UDRIE0));
	}
}

/* Resumen I2C
 * Usa dos pines: SCL que es el clock y SDA data
 * 
 * Primero se envía un bit de inicio, luego la dirección del dispositivo con el que se quiere comunicar
 * Después el bit que indica si se quiere escribir o si se quiere leer información: 0 para escritura, 1 para lectura
 * 
 * Una vez completado esto, el slave envía un bit de acknowledge (reconocimiento): 0 es que se estableció la comunicación
 * 1 si no se reconoció el slave.
 * 
 */
