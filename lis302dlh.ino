
//June 6 2012
//This program is given to you without any warranty.
//The author disclaims copyright to this source code.

#include <Wire.h>
#include <stdint.h>
#include "lis302dlh.h"

#define ACCEL_ADDR  I2C_ADDRESS_0

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  delay(100);
  Serial.println(lis320dlh_detect(ACCEL_ADDR) ? "LIS302DLH not found :-(" :  "LIS302DLH found :-)");
  lis320dlh_basic_setup(ACCEL_ADDR);
  lis320dlh_print_config(ACCEL_ADDR);
}

void loop()
{
  delay(500);
  
  int16_t x, y, z;
  uint8_t st_reg;
  int rc = lis320dlh_read_all(ACCEL_ADDR, &x, &y, &z, &st_reg);
  Serial.print("x= ");
  Serial.print(x);
  Serial.print(", y= ");
  Serial.print(y);
  Serial.print(", z= ");
  Serial.print(z);
  Serial.println("");
  
}

int lis320dlh_detect(uint8_t i2c_addr)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write((uint8_t)WHO_AM_I);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)i2c_addr, (uint8_t)1);
  if (Wire.available())
  { 
    uint8_t hello = Wire.read();
    return hello != WHO_AM_I_VALUE;
  }
  return -1;
}

#define ALL_AXES_READY ((uint8_t)((1 << ZOR) | (1 << YOR) | (1 << XOR)))

int lis320dlh_read_all(uint8_t i2c_addr, int16_t* x, int16_t* y, int16_t* z, uint8_t* st_reg_out)
{
  uint8_t st_reg;
  do
  {
    Wire.beginTransmission(i2c_addr);
    Wire.write((uint8_t)STATUS_REG);
    Wire.endTransmission();
    Wire.requestFrom(i2c_addr, (uint8_t)1);
    st_reg = Wire.read();
  } while (Wire.available() && ((st_reg & ALL_AXES_READY) == ALL_AXES_READY));//TODO timeout

  if ( st_reg_out != NULL )
  {
    *st_reg_out = st_reg;
  }

  Wire.beginTransmission(i2c_addr);
  Wire.write((uint8_t)(0x28 | AUTO_INCREMENT));
  Wire.endTransmission();
  Wire.requestFrom(i2c_addr, (uint8_t)6);

  uint8_t mem[6];
  for (int i = 0; (i < 6) && Wire.available(); i++)
  {
    mem[i] = Wire.read();
//    Serial.print("0x");
//    Serial.print(mem[i], HEX);
//    Serial.print(", ");
  }
//  Serial.println("");
  *x = ((int16_t*)mem)[0];
  *y = ((int16_t*)mem)[1];
  *z = ((int16_t*)mem)[2];
  return 0;
}

int lis320dlh_basic_setup(uint8_t i2c_addr)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write((uint8_t)(CTRL_REG1 | AUTO_INCREMENT));
  Wire.write((uint8_t)((1 << PM0_BIT) | (1 << Zen_BIT) | (1 << Yen_BIT) | (1 << Xen_BIT)));//all axes on, full data rate
  Wire.write((uint8_t)0);//reg 2
  Wire.write((uint8_t)0);//reg 3
  Wire.write((uint8_t)(1 << BDU));//block data update
  Wire.endTransmission();
  return 0;
}

int lis320dlh_print_config(uint8_t i2c_addr)
{
  Wire.beginTransmission(i2c_addr);
  Wire.write((uint8_t)(CTRL_REG1 | AUTO_INCREMENT));//auto increment
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)i2c_addr, (uint8_t)5);
  Serial.print("LIS302DLH CTRL_REG1-5: ");
  for (int i = 0; (i < 5) && Wire.available(); i++)
  {
    uint8_t r = Wire.read();
    Serial.print("0x");
    Serial.print(r, HEX);
    Serial.print(", ");
  }
  Serial.println("");
  return 0;
}


