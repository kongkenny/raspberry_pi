#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include "i2c.h"

// BMP085

#define DEBUG 1

// addresses
#define ADDRESS 0x77
#define DATA_ADDRESS 0xF6

// calibration data registers
#define CAL_AC1 0xAA
#define CAL_AC2 0xAC
#define CAL_AC3 0xAE
#define CAL_AC4 0xB0
#define CAL_AC5 0xB2
#define CAL_AC6 0xB4
#define CAL_B1 0xB6
#define CAL_B2 0xB8
#define CAL_MB 0xBA
#define CAL_MC 0xBC
#define CAL_MD 0xBE

// control commands
#define CONTROL 0xF4
#define READ_TEMP_CMD 0x2E
#define READ_PRESSURE_CMD 0x34

// mode
#define MODE_ULTRA_LOW_POWER 0
#define MODE_STANDARD 1
#define MODE_HIGH_RES 2
#define MODE_ULTRA_HIGH_RES 3

uint8_t mode = MODE_ULTRA_HIGH_RES;
uint8_t over_sampling = MODE_ULTRA_HIGH_RES;

int fd;

int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
uint16_t ac4, ac5, ac6;

void readTemperature(float *temperature);
int32_t readPressure(void);
float readAltitude(void);
uint16_t readRawTemperature(void);
uint32_t readRawPressure(void);

void setup(void) {
  _initI2C_(&fd, ADDRESS);

#if DEBUG == 1
  printf("fd = %d\n", fd);
  printf("0x%X (this output must be 0x55, something is wrong otherwise.)\n", readU8(fd, 0xD0));
#endif

  ac1 = readS16(fd, CAL_AC1);
  ac2 = readS16(fd, CAL_AC2);
  ac3 = readS16(fd, CAL_AC3);
  ac4 = readU16(fd, CAL_AC4);
  ac5 = readU16(fd, CAL_AC5);
  ac6 = readU16(fd, CAL_AC6);
  b1 = readS16(fd, CAL_B1);
  b2 = readS16(fd, CAL_B2);
  mb = readS16(fd, CAL_MB);
  mc = readS16(fd, CAL_MC);
  md = readS16(fd, CAL_MD);

#if DEBUG == 1
  printf("ac1 = %d\n", ac1);
  printf("ac2 = %d\n", ac2);
  printf("ac3 = %d\n", ac3);
  printf("ac4 = %d\n", ac4);
  printf("ac5 = %d\n", ac5);
  printf("ac6 = %d\n", ac6);
  printf("b1 = %d\n", b1);
  printf("b2 = %d\n", b2);
  printf("mb = %d\n", mb);
  printf("mc = %d\n", mc);
  printf("md = %d\n", md);
#endif
}

uint16_t readRawTemperature(void) {
  write8(fd, CONTROL, READ_TEMP_CMD);
  usleep(5000);
  return readU16(fd, DATA_ADDRESS);
}

void readTemperature(float *temperature) {
  int32_t UT, X1, X2, B5;

  UT = readRawTemperature();

  X1 = (UT - (int32_t)ac6) * (int32_t)ac5 / pow(2, 15);
  X2 = ((int32_t)mc * pow(2, 11)) / (X1 + (int32_t)md);
  B5 = X1 + X2;
  *temperature = (B5 + 8) / pow(2, 4);
  *temperature /= 10.0;
}

int main() {
  float temperature;

  setup();

  readTemperature(&temperature);
  if (fd) {
    printf("%d : %f\n", readRawTemperature(), temperature);
  }

  return 0;
}
