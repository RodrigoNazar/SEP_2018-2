
#include <msp430.h>

#include "USART.h"

// Sólo se configura el trasmisor (sólo comunicación al pc)
void USART_Init( void )
{

    P4SEL |= BIT4; // P4.4/UCA1TXD: Transmisor de data en el modo USCI_A1 UART
                   // Este pin escribe información en P4.4/UCA1TXD
                   // Luego, se activa TXD y la data llega a EZFET_UARTRXD.
                   // (Página 55 de slau533) Donde EZFET es el usb de la tarjeta.


    
    UCA1CTL1 |= UCSWRST; // Resetea la USCI: Universal serial communication interface y la deja listo para operar
                         // Es un software reset enable: 
                         // 0b = Disabled. USCI reset released for operation.
                         // 1b = Enabled. USCI logic held in reset state.
                         // Página 24 documento uart
                         
    UCA1CTL1 |= UCSSEL_2; // Seleciona el clock a utilizar.
                          // En este caso se selecciona el SMCLK. Un clock interno de 1MHz.
                          // En las opciones también está el ACLK y UCAxCLK. ACLK es un clock de baja
                          // frecuencia (32kHz tipicamente). UCAxCLK es un clock externo.
    
    UCA1BR0 = 18; // UCAxBR0 es el baund rate control 0. Es un registro de 7 bits que realiza un preescalado
                  // del clock para tener el baund rate correcto Notemos que 1M/18 aprox 57600

    
    UCA1MCTL = BIT1; // Registro de 8 bits de control de modulación.
                     // El bit que seteamos es el primero del campo UCBRSx
                     // Lo que hace es determinar el patron de modulación
    
    UCA1CTL1 &= ~UCSWRST; // Reinicio del sistema
}

void USART_Transmit_char(uint8_t data)
{   
    while(UCA1STAT & UCBUSY);  // UCA1STAT es registro de 8 bits, donde el primero es UCBUSY
                               // Si UCBUSY es 1 USCI está transmitiendo
                               // Si es 0, USCI está inactivo

    
    UCA1TXBUF = data;  // UCAxRXBUF: Registro de recepción del buffer.
                       // Este registro carga la información que se debe transmitir
                       // Pag 27 del documento uart
}
