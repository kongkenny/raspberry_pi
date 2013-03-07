node-I2C
========

This is a library made as a wrapper around ioctl to controll I2C ports in 
embedded linux.  It has been tested with the raspberry Pi and an BMP085 chip
only.


Usage
-----

rom nodejs script include with
    var i2c = require('./path/to/module/rI2C')
or place module in an appropriate node_modules directory.

Functions:

    i2c._initI2C_(addr)
	take address addr of the device. It initialize the device.

    i2c.readU8(reg)
	read an unsigned 8-bits value from register reg.

    i2c.readS8(reg)
	read a signed 8-bits value from register reg.

    i2c.readU16(reg)
	read an unsigned 16-bits value from register reg.

    i2c.readS16(reg)
	read an signed 16-bits value from register reg.

    i2c.write8(reg, data)
    	write an 8-bits value data to register reg.

See code comments for more details.


Build Instructions
------------------

### Dependencies
* npm -- This comes with newer versions of node 
* node-gyp -- this tool automates building node modules (requires a system compiler)

    npm install -g node-gyp

* wiringPi -- this is a handy library for different kind of wiring protocol. (https://projects.drogon.net/raspberry-pi/)

### to build you must first configure
    node-gyp configure
### and finally build
    node-gyp build

the addon is now in /build/Release/*.node
to use the addon move rI2C.node to either the global node_modules directory or
place it in a your a folder called node_modules with in your project directory



