#include "Lab10_Info.h"
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
   Init_GPIO();

       milliS_timer_0();

   linked_list_init();
   USART_Init(BAUD);

   // External Interrupt Enable
   PCMSK0 |= (1 << PCINT7);  // Activate change interrupt PB7
   PCICR  |= (1<<PCIE0);     // Pin Change Interrupt Enable 0

   sei();

   int mantiene_junto_el_aluminio = 0;
   bouncing = 0;
   tiempo = 0;

	while(1)
	{
		if (bouncing == 0)
		{
			if (ALUM_but_pressed)
			{
				if (mantiene_junto_el_aluminio == 0) cambiar_led(0);
				bouncing = 1;
				mantiene_junto_el_aluminio = 1;
			}
			else mantiene_junto_el_aluminio = 0;
		}
   else millis_50_timer_1();
	}

}



ISR(TIMER0_COMPA_vect) // TimerCounter0 Compare Match A
{
	contador++;
	tiempo++;
	if (contador == 1000)
	{
		contador = 0;
		PORTD ^= (1 << PORTD6);
	}
}


// Debouncing
ISR(TIMER1_COMPA_vect) // Timer/Counter1 Compare Match A
{
	contador_2++;
	if (contador_2 == 3)
	{
		contador_2 = 0;
		bouncing = 0;
	}
}


// Interrupción relacionada al botón de la avr
ISR(PCINT0_vect) // Pin Change Interrupt Request 0
{
	if (AVR_but_pressed)
	{
		cambiar_led(1);
		tiempo = 0;
	}
	else
	{
		int2str(tiempo);
		USART_Transmit("Se soltó el Boton. Duración: ");
		USART_Transmit(str_num);
		USART_Transmit(" ms.\r\n");
	}
}


//
 ISR(USART_UDRE_vect) // USART Data Register Empty
 {
 	if (Transmit_Linked_list(&UDR0))
 	{
 		 reset_list(head_t);
 		UCSR0B &= ~((1<<TXEN0)|(1<<UDRIE0));
 	}
 }
