#! /usr/bin/python

from I2C import I2C
import signal
import sys
import smbus
import time

# BMP085

DEBUG = 1;

# addresses
address = 0x77;
data_address = 0xF6;

# calibration data registers
CAL_AC1 = 0xAA;
CAL_AC2 = 0xAC;
CAL_AC3 = 0xAE;
CAL_AC4 = 0xB0;
CAL_AC5 = 0xB2;
CAL_AC6 = 0xB4;
CAL_B1 = 0xB6;
CAL_B2 = 0xB8;
CAL_MB = 0xBA;
CAL_MC = 0xBC;
CAL_MD = 0xBE;

# control commands
control = 0xF4;
read_temp_cmd = 0x2E;
read_pressure_cmd = 0x34;

# mode
mode_ultra_low_power = 0;
mode_standard = 1;
mode_high_res = 2;
mode_ultra_high_res = 3;
mode = mode_ultra_high_res;

over_sampling = mode_ultra_high_res;

i2c = I2C(address);

def signal_handler(signal, frame) :
    sys.exit(0);

signal.signal(signal.SIGINT, signal_handler);

ac1 = i2c.readS16(CAL_AC1);
ac2 = i2c.readS16(CAL_AC2);
ac3 = i2c.readS16(CAL_AC3);
ac4 = i2c.readU16(CAL_AC4);
ac5 = i2c.readU16(CAL_AC5);
ac6 = i2c.readU16(CAL_AC6);

b1 = i2c.readS16(CAL_B1);
b2 = i2c.readS16(CAL_B2);

mb = i2c.readS16(CAL_MB);
mc = i2c.readS16(CAL_MC);
md = i2c.readS16(CAL_MD);

if DEBUG :
    print "AC1: ", ac1;
    print "AC2: ", ac2;
    print "AC3: ", ac3;
    print "AC4: ", ac4;
    print "AC5: ", ac5;
    print "AC6: ", ac6;
    print "B1: ", b1;
    print "B2: ", b2;
    print "MB: ", mb;
    print "MC: ", mc;
    print "MD: ", md;

def read_raw_temp() :
    i2c.write8(control, read_temp_cmd);
    time.sleep(0.005);

    return i2c.readU16(data_address);

def read_temp() :
    UT = read_raw_temp();

    X1 = ((UT - ac6) * ac5) >> 15;
    X2 = (mc << 11) / (X1 + md);
    B5 = X1 + X2;
    temp = ((B5 + 8) >> 4) / 10.0;

    return temp;

def read_raw_pressure() :
    i2c.write8(control, read_pressure_cmd + (mode << 6));
    if (mode == mode_ultra_low_power) :
        time.sleep(0.005);
    elif (mode == mode_high_res) :
        time.sleep(0.014);
    elif (mode == mode_ultra_high_res) :
        time.sleep(0.026);
    else :
        time.sleep(0.008);

    msb = i2c.readU8(data_address);
    lsb = i2c.readU8(data_address + 1);
    xlsb = i2c.readU8(data_address + 2);
    raw = ((msb << 16) + (lsb << 8) + xlsb) >> (8 - mode);

    return raw;

def read_pressure() :
    pressure = 0;

    UT = read_raw_temp();
    UP = read_raw_pressure();

    # True temperature calculation
    X1 = ((UT - ac6) * ac5) >> 15;
    X2 = (mc << 11) / (X1 + md);
    B5 = X1 + X2;

    # pressure calculation
    B6 = B5 - 4000;
    X1 = (b2 * (B6 * B6) >> 12) >> 11;
    X2 = (ac2 * B6) >> 11;
    X3 = X1 + X2;
    B3 = (((ac1 * 4 + X3) << mode) + 2) / 4;

    X1 = (ac3 * B6) >> 13;
    X2 = (b1 * ((B6 * B6) >> 12)) >> 16;
    X3 = ((X1 + X2) + 2) >> 2;
    B4 = (ac4 * (X3 + 32768)) >> 15;
    B7 = (UP - B3) * (50000 >> mode);

    if (B7 < 0x80000000) :
        pressure = (B7 * 2) / B4;
    else :
        pressure = (B7 / B4) * 2;

    X1 = (pressure >> 8) * (pressure >> 8);
    X1 = (X1 * 3038) >> 16;
    X2 = (-7375 * pressure) >> 16;

    pressure = pressure + ((X1 + X2 + 3791) >> 4);

    return pressure;

def read_altitude(sea_level_pressure=101325) :
    altitude = 0.0;

    pressure = float(read_pressure());
    altitude = 44330.0 * (1.0 - pow(pressure / sea_level_pressure, 0.1903));

    return altitude;

while True :
    print read_raw_temp(), " :", read_temp(), "C :", read_pressure(), "Pa :", read_altitude(), "m";
    time.sleep(1);
