#include "USART_implement_me.h"

int main(void)
{
	// Initialise the serial communication interface
	struct USART_configuration config_57600_8N1 = {57600, 8, 0, 1};
	USART_Init(config_57600_8N1);
	ADC_Init();

	//int_t control

	_delay_ms(50);
	while (1)
	{
		ADCvalue=(float) ADC_Read()*1.1;
		int8_t tmp = calcular_temp(ADCvalue);
		USART_Transmit_char(tmp);
	}
}
