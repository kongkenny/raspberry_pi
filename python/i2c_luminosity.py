#! /usr/bin/python

from I2C import I2C
import signal
import sys
import smbus
import time

# TSL2561

DEBUG = 0;

# address options
address_low = 0x29;
address_float = 0x39;
address_high = 0x49;

COMMAND_BIT = 0x80;
CLEAR_BIT = 0x40;
WORD_BIT = 0x20;
BLOCK_BIT = 0x10;

CONTROL_POWER_ON = 0x03;
CONTROL_POWER_OFF = 0X00;

# Registers
REGISTER_CONTROL = 0x00;
REGISTER_TIMING = 0x01;
REGISTER_THRESHOLDL_LOW = 0x02;
REGISTER_THRESHOLDL_HIGH = 0x03;
REGISTER_THRESHOLDH_LOW = 0x04;
REGISTER_THRESHOLDH_HIGH = 0x05
REGISTER_INTERRUPT = 0x06;
REGISTER_CRC = 0x08;
REGISTER_ID = 0x0A;
REGISTER_CHAN0_LOW = 0x0C;
REGISTER_CHAN0_HIGH = 0x0D;
REGISTER_CHAN1_LOW = 0x0E;
REGISTER_CHAN1_HIGH = 0x0F;

# Integration Time
INTEGRATIONTIME_13MS = 0x00;
INTEGRATIONTIME_101MS = 0x01;
INTEGRATIONTIME_402MS = 0x02;
integration = INTEGRATIONTIME_13MS;

# Gain
GAIN_0X = 0x00;
GAIN_16X = 0x10;
gain = GAIN_16X;

# channel
channel_visible = 2; # channel 0 - channel 1
channel_infrared = 1; # channel 1
channel_fullspectrum = 0; # channel 0

i2c = I2C(address_float);

def signal_handler(signal, frame) :
    sys.exit(0);

signal.signal(signal.SIGINT, signal_handler);

def enable() :
    i2c.write8(COMMAND_BIT | REGISTER_CONTROL, CONTROL_POWER_ON);

def disable() :
    i2c.write8(COMMAND_BIT | REGISTER_CONTROL, CONTROL_POWER_OFF);

def setTiming(timing) :
    enable();

    integration = timing;
    i2c.write8(COMMAND_BIT | REGISTER_TIMING, integration | gain);

    disable();

def setGain(gain) :
    enable();

    i2c.write8(COMMAND_BIT | REGISTER_TIMING, integration | gain);
    
    disable();

def getFullLuminosity() :
    luminosity = 0;

    enable();

    delay = {
        INTEGRATIONTIME_13MS : 0.014,
        INTEGRATIONTIME_101MS : 0.102,
        }.get(integration, 0.403);
    time.sleep(delay);

    luminosity = i2c.readU16(COMMAND_BIT | WORD_BIT | REGISTER_CHAN1_LOW);
    luminosity <<= 16;
    luminosity |= i2c.readU16(COMMAND_BIT | WORD_BIT | REGISTER_CHAN0_LOW);

    disable();

    return luminosity;
    
def getLuminosity(channel) :
    luminosity = getFullLuminosity();

    if (channel == 0) :
        return luminosity & 0xFFFF;
    elif (channel == 1) :
        return luminosity >> 16;
    elif (channel == 2) :
        return (luminosity & 0xFFFF) - (luminosity >> 16);

    return -1; # unknown channel

setTiming(INTEGRATIONTIME_13MS);
setGain(GAIN_16X);


while True :
    print getLuminosity(channel_visible), ":", getLuminosity(channel_infrared);
    time.sleep(1);
