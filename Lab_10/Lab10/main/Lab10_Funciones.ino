#include "Lab10_Info.h"



// INICIALIZACIÓN DE LOS PINES
void Init_GPIO(void)
{
	// LEDS
	DDRD  |= (1 << DDD0) | (1 << DDD2) | (1 << DDD3) | (1 << DDD4) | (1 << DDD5) | (1 << DDD6);

	// BOTÓNES
	DDRB &=  ~((1 << DDB3) | (1 << DDB7));
	// PULLUP
    PORTB |= (1 << PORTB3) | (1 << PORTB7);

	// DEFINICIÓN POR DEFECTO DE LOS LEDS
	PORTD &= ~((1 << PORTD2) | (1 << PORTD3) | (1 << PORTD4) | (1 << PORTD5));

	PORTD |=  (1 << PORTD0) | (1 << PORTD6);

	numero_led = 1;
}



// TIMER DEL BLINK DE CADA 1 SEGUNDO
void milliS_timer_0(void)
{
	// Timer/Counter Control Register A
	TCCR0A |= (1 << WGM01) ;			   // CTC mode
	TCCR0B |= (1 << CS00) | (1 << CS01) ;  // Preescalado de 64
										   // F_CPU / Preescalado / Frecuencia
	OCR0A = 250;						   // 16M / 64 / 1000 (tiene que ser número entero)
	TIMSK0 |= (1 << OCIE0A); // Activa la interrupción cuando el timer overflows (bit TOV0)
}



// TIMER 2
void millis_50_timer_1(void)
{
	// Timer/Counter1 Control Register B
	TCCR1B |= (1 << WGM12);			  	   // CTC mode
	TCCR1B |= (1 << CS10) | (1 << CS11) ;  // Preescalado de 64

	OCR1A = 12500;
	TIMSK1 |= (1 << OCIE1A);	// Activa la interrupción cuando el timer overflows (bit TOV0)
}



// CAMBIA EL LED
void cambiar_led(int dir)  // dir=1: sube | dir=0: baja
{
	if (numero_led == 1)
	{
		if (dir)
		{
			PORTD ^= (1 << PORTD0) | (1 << PORTD2);
			numero_led++;
		}
		else
		{
			PORTD ^= (1 << PORTD0) | (1 << PORTD5);
			numero_led = 5;
		}
	}
	else if (numero_led == 2)
	{
		if (dir)
		{
			PORTD ^= (1 << PORTD2) | (1 << PORTD3);
			numero_led++;
		}
		else
		{
			PORTD ^= (1 << PORTD2) | (1 << PORTD0);
			numero_led--;
		}
	}
	else if (numero_led == 3)
	{
		if (dir)
		{
			PORTD ^= (1 << PORTD3) | (1 << PORTD4);
			numero_led++;
		}
		else
		{
			PORTD ^= (1 << PORTD3) | (1 << PORTD2);
			numero_led--;
		}
	}
	else if (numero_led == 4)
	{
		if (dir)
		{
			PORTD ^= (1 << PORTD4) | (1 << PORTD5);
			numero_led++;
		}
		else
		{
			PORTD ^= (1 << PORTD4) | (1 << PORTD3);
			numero_led--;
		}
	}
	else if (numero_led == 5)
	{
		if (dir)
		{
			PORTD ^= (1 << PORTD5) | (1 << PORTD0);
			numero_led = 1;
		}
		else
		{
			PORTD ^= (1 << PORTD5) | (1 << PORTD4);
			numero_led--;
		}
	}
}
