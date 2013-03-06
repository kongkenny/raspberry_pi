#! /usr/bin/python

import serial
import io
import signal
import sys

serialport = serial.Serial("/dev/ttyAMA0", 9600, timeout=1);

def signal_handler(signal, frame) :
    if (serialport.isOpen()) :
        serialport.close();
        sys.exit(0);

signal.signal(signal.SIGINT, signal_handler);

if (serialport.isOpen()) :
    while (True) :
        # response = serialport.readline(size=None, eol='\n');
        response  = serialport.read(size=1);
        print response;

