#include <avr/io.h>

#include "I2C_implement_me.h"


// Inicialización de I2c
void I2C_init()
{
	
	TWBR = 12;								               	// 400 kHz at 16MHz crystal and no prescaler
                                            // TWBR = ((FCPU/SCL)-16)/(2*PRESCALER)
	TWSR &= ~((1 << TWPS1) | (1 << TWPS0));		// Pág 231: PRESCALER = 1
	TWDR = 0xFF;							              	// sending only ones equals an idle high SDA line
	TWCR = (1<<TWEN);					            		// Activa el TWI, cuando se escribe en 1, los PC4 y PC5 se
                                            // conectan a el SCL y el SDA
}


// Send a start condition
void i2cSendStart()
{                                              // Pág 230
	TWCR |= (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); // TWINT: Espera a que se reciba la respuesta del slave
                                               // TWSTA: Genera la START condition cuando el bus está libre
                                               // TWEN: Activa el TWI, cuando se escribe en 1, los PC4 y PC5 se
                                               // conectan a el SCL y el SDA
}


// Send a stop condition
void i2cSendStop()
{
	TWCR |= (1<<TWINT) | (1<<TWSTO) | (1<<TWEN); // TWINT: Espera a que se reciba la respuesta del slave
                                               // TWSTO: Genera la STOP condition cuando el bus está libre
                                               // TWEN: Activa el TWI, cuando se escribe en 1, los PC4 y PC5 se
                                               // conectan a el SCL y el SDA
}


// Waits for the previous operation to finish
void i2cWaitForComplete()
{
	while (!(TWCR & (1<<TWINT)));
}


// Transmits one byte over the bus to a slave
// (Can be either an address or a value.)
void i2cSendByte(unsigned char data)
{
	TWDR = data;
	TWCR = (1<<TWINT) | (1<<TWEN);
}


// Receives one byte from a slave
// (Always a value; master has no address.)
// Send an ACK if you expect more data, NAK if not.
void i2cReceiveByte(bool sendAnACK)
{
	if (sendAnACK) TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
	else TWCR = (1<<TWINT)|(1<<TWEN);
}


// After receiving a byte, fetch this byte from the TWDR register
// (if you are interested in it).
// It is possible to *not* call this function after a call to
// i2cReceiveByte() if you are not interested in the actual value.
unsigned char i2cGetReceivedByte(void)
{
	return TWDR;
}

/* Temperature read function */

//Read a tmp102 sensor on a given temp_number or channel
int16_t tmp102Read(void)
{

	uint8_t msb, lsb;
	int16_t temp;


	i2cSendStart();						       	// send start condition
	i2cWaitForComplete();

	i2cSendByte(TMP102_WRITE); 				// send WRITE address of TMP102
	i2cWaitForComplete();
	i2cSendByte(0x00); 					      // set TMP102 pointer register to 0 (read temperature)
	i2cWaitForComplete();
  i2cSendStop();
  
	i2cSendStart();					      		// send repeated start condition
	i2cWaitForComplete();

	i2cSendByte(TMP102_READ);			  	// send READ address of TMP102
	i2cWaitForComplete();
	i2cReceiveByte(true);				    	// receives one byte from the bus and ACKs it
	i2cWaitForComplete();
	msb = i2cGetReceivedByte(); 			// reads the MSB (it is a 12 bit value!)
	i2cWaitForComplete();
	i2cReceiveByte(false);					  // receives one byte from the bus and NAKs it (last one)
	i2cWaitForComplete();
	lsb = i2cGetReceivedByte();				// reads the LSB
	i2cWaitForComplete();

	i2cSendStop();						      	// send stop condition
	TWCR = 0;								          // stop everything


	// Convert the number to an 8-bit degree Celsius value
	temp = (msb<<8) | lsb;					// combine those two values into one 16 bit value
	temp >>= 4; 							      // the values are left justified; fix that by shifting 4 right

	// The 12 bit value has 0.0625�C precision, which is too much for what we want (and the sensor is anyways only about 0.5�C precise)
	// 0.0625 is 1/16 -> Dividing by 16 leaves I2C precision for the output. 
	temp /= 16;

	return(temp);
}
