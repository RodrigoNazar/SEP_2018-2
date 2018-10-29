
#ifndef _I2C_IMPLEMENT_ME_H_
#define _I2C_IMPLEMENT_ME_H_

// MCU Clock Speed - needed for delay.h
#define F_CPU	16000000UL

// Direcciones de escritura y lectura del sensor de temperatura
// Página 11
#define TMP102_READ	 	0x91
#define TMP102_WRITE 	0x90

// Direcciones de escritura y lectura del DAC
// Página 24
#define MCP4725_WRITE	0xC0
#define MCP4725_READ	0xC1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>

int tipo = 3;
int16_t temperature = 0;
uint16_t lookup = 0;        // variable for navigating through the tables
uint8_t msb_out;
uint8_t lsb_out;
uint16_t dato;

uint16_t obtener_dato(uint16_t index);

void send_data(uint8_t msb_data, uint8_t lsb_data);

void I2C_init();

// Send a start condition
void i2cSendStart();

// Send a stop condition
void i2cSendStop();

// Waits for the previous operation to finish
void i2cWaitForComplete();

// Transmits one byte over the bus to a slave
// (Can be either an address or a value.)
void i2cSendByte(unsigned char data);

// Receives one byte from a slave
// (Always a value; master has no address.)
// Send an ACK if you expect more data, NAK if not.
void i2cReceiveByte(bool sendAnACK);

// After receiving a byte, fetch this byte from the TWDR register
// (if you are interested in it).
// It is possible to *not* call this function after a call to
// i2cReceiveByte() if you are not interested in the actual value.
unsigned char i2cGetReceivedByte(void);

int16_t tmp102Read(void);

#endif // _I2C_IMPLEMENT_ME_H_
