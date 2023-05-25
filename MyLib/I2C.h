#ifndef I2C
#define I2C 
/* I2C Status Bits in the TWSR Register */
#define I2C_START         0x08 // start has been sent
#define I2C_REPEAT_START     0x10 // repeated start
#define I2C_MT_SLA_W_ACK  0x18 // Master transmit ( slave address + Write request ) to slave + Ack received from slave
#define I2C_MT_SLA_R_ACK  0x40 // Master transmit ( slave address + Read request ) to slave + Ack received from slave
#define I2C_MT_DATA_ACK   0x28 // Master transmit data and ACK has been received from Slave.
#define I2C_MR_DATA_ACK   0x50 // Master received data and send ACK to slave
#define I2C_MR_DATA_NACK  0x58 // Master received data but doesn't send ACK to slave
void I2C_Init(uint8_t TWDR_Value)
{
	
	TWSR =0x00;
	TWDR = TWDR_Value;
	TWAR =0b00000010;
	TWCR =(1<<TWEN);
}
void I2C_Start()
{
	TWCR = (1<<TWEN) |(1<<TWINT) | (1<<TWSTA);
	while(!(TWCR &(1<<TWINT)));
}
void I2C_Stop()
{
  TWCR = (1<<TWEN) |(1<<TWINT) | (1<<TWSTO);
}
void I2C_Write(uint8_t data)
{
	TWDR = data;
	TWCR = (1<<TWEN) |(1<<TWINT);
	while(!(TWCR &(1<<TWINT)));
}
uint8_t I2C_Read_With_ACK()
{
	TWCR = (1<<TWEN) |(1<<TWINT) |(1<<TWEA);
	while(!(TWCR &(1<<TWINT)));
	return TWDR;
}

uint8_t I2C_Read_With_NACK()
{
	TWCR = (1<<TWEN) |(1<<TWINT);
	while(!(TWCR &(1<<TWINT)));
	return TWDR;
}
uint8_t Check_Status()
{
	uint8_t Status;
	Status = TWSR & 0xF8;
	return Status;
}


#endif