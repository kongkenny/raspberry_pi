#! /usr/bin/python

import smbus

class I2C :

    def __init__(self, address, bus = smbus.SMBus(1), debug = False) :
        self.address = address;
        self.bus = bus;
        self.debug = debug;

    def readU8(self, reg) : # read an unsigned byte value
        return self.bus.read_byte_data(self.address, reg);

    def readS8(self, reg) : # read a signed byte value
        result = self.readU8(reg);
        if (result > 127) :
            return result - 256;
        else :
            return result;
            
    def readU16(self, reg) : # read an unsigned 16-bit value
        hi_byte = self.readU8(reg);
        result = (hi_byte << 8) + self.readU8(reg + 1);
        return result;
    
    def readS16(self, reg) : # read a signed 16-bit value
        hi_byte = self.readU8(reg);
        if (hi_byte > 127) :
            hi_byte -= 256;
        result = (hi_byte << 8) + self.readU8(reg + 1);
        return result;

    def write8(self, cmd, val) :
        self.bus.write_byte_data(self.address, cmd, val);

    def writeList(self, reg, list) :
        self.bus.write_i2c_block_data(self.address, reg, list);
