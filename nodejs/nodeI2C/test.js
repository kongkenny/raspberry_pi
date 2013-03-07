#! /usr/local/bin/node

var ri2c = require('./build/Release/rI2C');

var DEBUG = 1;

//BMP085

// addresses
var ADDRESS = 0x77;
var DATA_ADDRESS = 0xF6;

// control commands
var CONTROL = 0xF4;
var READ_TEMP_CMD = 0x2E;
var READ_PRESSURE_CMD = 0x34;

// calibration data registers
var CAL_AC1 = 0xAA;
var CAL_AC2 = 0xAC;
var CAL_AC3 = 0xAE;
var CAL_AC4 = 0xB0;
var CAL_AC5 = 0xB2;
var CAL_AC6 = 0xB4;
var CAL_B1 = 0xB6;
var CAL_B2 = 0xB8;
var CAL_MB = 0xBA;
var CAL_MC = 0xBC;
var CAL_MD = 0xBE;

var fd, ac1, ac2, ac3, ac4, ac5, ac6, b1, b2, mb, mc, md;

function setup() {
    fd = ri2c.setupI2C(ADDRESS);

    ac1 = ri2c.readS16(CAL_AC1);
    ac2 = ri2c.readS16(CAL_AC2);
    ac3 = ri2c.readS16(CAL_AC3);
    ac4 = ri2c.readU16(CAL_AC4);
    ac5 = ri2c.readU16(CAL_AC5);
    ac6 = ri2c.readU16(CAL_AC6);
    b1 = ri2c.readS16(CAL_B1);
    b2 = ri2c.readS16(CAL_B2);
    mb = ri2c.readS16(CAL_MB);
    mc = ri2c.readS16(CAL_MC);
    md = ri2c.readS16(CAL_MD);
    
    if (DEBUG == 1) {
	console.log("ac1: " + ac1);
	console.log("ac2: " + ac2);
	console.log("ac3: " + ac3);
	console.log("ac4: " + ac4);
	console.log("ac5: " + ac5);
	console.log("ac6: " + ac6);
	console.log("b1: " + b1);
	console.log("b2: " + b2);
	console.log("mb: " + mb);
	console.log("mc: " + mc);
	console.log("md: " + md);
    }
}

function readTemperature() {
    var raw;

    ri2c.write8(CONTROL, READ_TEMP_CMD);
    setTimeout(function() {
	raw = ri2c.readU16(DATA_ADDRESS);
	console.log(raw + " : " + convertTemperature(raw).toFixed(3));
    }, 5);

    return raw;
}

function convertTemperature(UT) {
    var X1, X2, B5, temp;

    //UT = readRawTemperature();
    X1 = ((UT - ac6) * ac5) >>> 15;
    X2 = (mc << 11) / (X1 + md);
    B5 = X1 + X2;
    temp = ((B5 + 8) >>> 4) / 10.0;

    return temp;
}

setup();
readTemperature();
//console.log(readRawTemperature() + " : " + readTemperature());
