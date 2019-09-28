#ifndef I2C_H
#define I2C_H

#include "pic_specific.h"

void init_i2c(void);
void i2c_start(void);
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data);
unsigned char i2c_read(void);

//----------------------------------------------------

void i2c_fail(unsigned char status);
void write_external_eeprom(unsigned char address, unsigned char data);
unsigned char read_external_eeprom(unsigned char);

#endif
