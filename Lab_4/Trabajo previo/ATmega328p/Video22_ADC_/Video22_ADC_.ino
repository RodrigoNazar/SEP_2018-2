#include <avr/io.h>
#include <avr/interrupt.h>

////// El programa lee un voltaje solamente

//////////////////////////////////////////////                   PRIMERA PARTE PARA LEER

// Especificaciónes del ADC:
// 10-bit resolution
// 76.9kSPS
// 0 - Vcc input voltage

// Diagrama de bloques del ADC página 306
// Tres cosas claves para la lógica del ADC
// - El ADC multiplexor select (ADMUX)se enfoca en seleccionar el voltaje de referencia
// del ADC. Vcc, un voltaje interno de 1.1V o un voltaje externo.
// Luego el multiplexor escogerá el canal de ADC a utilizar: ADC del 0 al 7
// - Hay un registro de control de status, que está relacionado al clock del ADC
// - Finalmente hay un registro de resultado de la medición

// Cosas interesantes a tener en cuenta:
// - Cuando nos fijamos del preescalado y conversión del clock, lo que es importante
// es que para tener una máxima resolución de la medición necesitamos un clock que tenga
// una frecuencia entre 50 kHz a 200 kHz.
// - El voltaje de referencia indica el rango de conversión del ADC
// Según Glen, si queremos obtener el rango más amplio debemos fijar Vref en Vcc.
// - Lo que lee el ADC es ADC = Vin*1024/Vref. El 1024 es si usamos la mayor resolución. Pág 315


#define LED_ON        PORTB |= (1<<PORTB5);
#define LED_OFF       PORTB &= ~(1<<PORTB5);
#define LED_TOGGLE    PINB |= (1<<PORTB5);



//////////////////////////////////////////////                   SEGUNDA PARTE PARA LEER

// Parte 2 de programación 
ISR(ADC_vect){ // Librerías -> <avr/interrupt.h>: Interrupts -> Buscamos ADC -> ADC_vect (el vector de interrupcion del ADC)

  LED_TOGGLE
  
}


// Parte 1 de programación
void ADC_init(void){
  // Set up del mux
  ADMUX |= (1<<REFS0) | (1<<MUX0); // Voltaje de referencia pag 317. REFS0 = 1 para voltaje de ref sea Vcc 
                                   // ADC input channel (ADC1). Buscando ADC1, notamos que está conectado al pin PC1
                                   // MUX0 = 1 es para seleccionar el ADC1

  // Set up del registro de control de status, para el reloj
  ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE) | (1<<ADIE) | (1<<ADPS0) | (1<<ADPS1) | (1<<ADPS2);  
                                   // Página 249.
                                   // ADEN: Writing this bit to one enables the ADC.
                                   // ADSC: write this bit to one to start each conversion.
                                   // ADATE: When this bit is written to one, Auto Triggering of the ADC is enabled.
                                   // ADIF: This bit is set when an ADC conversion completes and the Data Registers are updated. NO LO QUEREMOS
                                   // ADIE: the ADC Conversion Complete Interrupt is activated.
                                   // ADPS0, ADPS1 y ADPS2 Aparecen en la tabla 25-5 (pág 250)
                                   // Necesitabamos una frecuencia entre 50 kHz a 200 kHz para tener buena resolución. Como alimentamos el AVR
                                   // Con 5V, CPU_Freq es de 16MHz y notamos que 16M/128 = 125k :). Con ADPS0, ADPS1 y ADPS2 en 1, el divisor de clk es 128.

  // Setup de las interrupciones
  sei(); // Ver la segunda parte de programación
} 


int main(void){


  ADC_init();





  while(1){

    
  }
}

