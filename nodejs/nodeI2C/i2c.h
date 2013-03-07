#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <wiringPiI2C.h>
#include <sys/ioctl.h>


//#define DEBUG = 0;

/*
 * Inititial the I2C with specific address
 * 
 * @param addr the address of the I2C device
 * @return the file descriptor of where you can access the device
 */
int _initI2C_(uint16_t addr);

/*
 * Read an unsigned 8-bits integer
 * 
 * @param reg the register where the data is stored
 * @return the value that stored in addr
 */
uint8_t readU8(uint16_t reg);

/*
 * Read a signed 8-bits integer
 *
 * @param reg the register where the data is stored
 * @return the value that stored in addr
 */
int8_t readS8(uint16_t reg);

/*
 * Read an unsigned 16-bits integer
 *
 * @param reg the register where the data is stored
 * @return the value that stored in addr
 */
uint16_t readU16(uint16_t reg);

/*
 * Read a signed 16-bits integer
 *
 * @param reg the register where the data is stored
 * @return the value that stored in addr
 */
int16_t readS16(uint16_t reg);

/*
 * Write an 8-bits data to address addr
 *
 * @param reg the register to write to
 * @param data the data to be written
 * @return 
 */
int write8(int reg, int data);
