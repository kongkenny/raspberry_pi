#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPiI2C.h>
//#include <linux/i2c-dev.h>
#include <sys/ioctl.h>


//#define DEBUG = 0;

void _initI2C_(int *fd, uint16_t addr);

uint8_t readU8(int fd, uint16_t reg);
int8_t readS8(int fd, uint16_t reg);
uint16_t readU16(int fd, uint16_t reg);
int16_t readS16(int fd, uint16_t reg);
int write8(int fd, int reg, int data);
