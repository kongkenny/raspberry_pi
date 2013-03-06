#include "i2c.h"

int fd;

int _initI2C_(uint16_t addr) {
  fd = wiringPiI2CSetup(addr);

  return fd;
}

uint8_t readU8(uint16_t addr) {
  return (uint8_t)wiringPiI2CReadReg8(fd, addr);
}

int8_t readS8(uint16_t addr) {
  int8_t result = readU8(addr);
  if (result > 127)
    return result - 256;
  else
    return result;
}

uint16_t readU16(uint16_t addr) {
  uint8_t hi_byte = readU8(addr);
  uint16_t result = (hi_byte << 8) + readU8(addr + 1);
  return result;
}

int16_t readS16(uint16_t addr) {
  uint8_t hi_byte = readU8(addr);
  if (hi_byte > 127)
    hi_byte -= 256;
  int16_t result = (hi_byte << 8) + readU8(addr + 1);
  return result;
}

int write8(int addr, int data) {
  return wiringPiI2CWriteReg8(fd, addr, data);
}
