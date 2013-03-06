#define BUILDING_NODE_EXTENSION
#include <node.h>

#include<fcntl.h>
//#include<stdio.h> //for debug only
#include<string>
extern "C" {
#include "i2c.h"
}

using namespace v8;

/*
  function name: setupI2C
  inputs:
  args[0]: address 
  returns:
  undefined
*/
Handle<Value> setupI2C(const Arguments& args) {
  HandleScope scope;

  //Check inputs
  if (args.Length() < 1) {
    ThrowException(Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }

  if (!args[0]->IsNumber()) {
    ThrowException(Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  //unpack args
  int address = args[0]->Int32Value();

  if (!_initI2C_(address)) {
    ThrowException(Exception::Error(String::New("unable to configure I2C")));
    return scope.Close(Undefined());
  }

  return scope.Close(Undefined());
}



/*
  function name: readU8
  inputs:
  args[0]: register to read
  returns:
  value read.
*/
Handle<Value> readU8(const Arguments& args) {
  HandleScope scope;

  //Check inputs
  if (args.Length() < 1) {
    ThrowException(
		   Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }
  if (!args[0]->IsNumber()) {
    ThrowException(
		   Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  //unwrap inputs
  int reg = args[0]->Int32Value();
  int val;
  ///////////////////ACTUAL WORK///////////////////  

  val = readU8(reg);
  /*if ((readU8(reg))) {
    ThrowException(Exception::Error(String::New("I2C read failed.")));
    return scope.Close(Undefined());
    }*/

  //////////////////PACK UP OUTPUTS/////////////////////
  Local<Integer> value = Integer::New(val);
			
  return scope.Close(value);
}



/*
  function name: readS8
  inputs:
  args[0]: register to read
  returns:
  value read.
*/
Handle<Value> readS8(const Arguments& args) {
  HandleScope scope;

  //Check inputs
  if (args.Length() < 1) {
    ThrowException(
		   Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }
  if (!args[0]->IsNumber()) {
    ThrowException(
		   Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  //unwrap inputs
  int reg = args[0]->Int32Value();
  int val;
  ///////////////////ACTUAL WORK///////////////////  

  val = readS8(reg);
  /*if ((readU8(reg))) {
    ThrowException(Exception::Error(String::New("I2C read failed.")));
    return scope.Close(Undefined());
    }*/

  //////////////////PACK UP OUTPUTS/////////////////////
  Local<Integer> value = Integer::New(val);
			
  return scope.Close(value);
}



/*
  function name: readU16
  inputs:
  args[0]: register to read
  returns:
  value read.
*/
Handle<Value> readU16(const Arguments& args) {
  HandleScope scope;

  //Check inputs
  if (args.Length() < 1) {
    ThrowException(
		   Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }
  if (!args[0]->IsNumber()) {
    ThrowException(
		   Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  //unwrap inputs
  int reg = args[0]->Int32Value();
  int val;
  ///////////////////ACTUAL WORK///////////////////  

  val = readU16(reg);
  /*if ((readU8(reg))) {
    ThrowException(Exception::Error(String::New("I2C read failed.")));
    return scope.Close(Undefined());
    }*/

  //////////////////PACK UP OUTPUTS/////////////////////
  Local<Integer> value = Integer::New(val);
			
  return scope.Close(value);
}



/*
  function name: readS16
  inputs:
  args[0]: register to read
  returns:
  value read.
*/
Handle<Value> readS16(const Arguments& args) {
  HandleScope scope;

  //Check inputs
  if (args.Length() < 1) {
    ThrowException(
		   Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }
  if (!args[0]->IsNumber()) {
    ThrowException(
		   Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  //unwrap inputs
  int reg = args[0]->Int32Value();
  int val;
  ///////////////////ACTUAL WORK///////////////////  

  val = readS16(reg);
  /*if ((readU8(reg))) {
    ThrowException(Exception::Error(String::New("I2C read failed.")));
    return scope.Close(Undefined());
    }*/

  //////////////////PACK UP OUTPUTS/////////////////////
  Local<Integer> value = Integer::New(val);
			
  return scope.Close(value);
}



/*
  function name: write8
  inputs:
  args[0]: register to write to
  args[1]: value to be written
  returns:
  undefined
*/
Handle<Value> write8(const Arguments& args) {
  HandleScope scope;

  //Check inputs
  if (args.Length() < 2) {
    ThrowException(
		   Exception::TypeError(String::New("Wrong number of arguments")));
    return scope.Close(Undefined());
  }
  if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
    ThrowException(
		   Exception::TypeError(String::New("Wrong arguments")));
    return scope.Close(Undefined());
  }

  //unwrap inputs
  int reg = args[0]->Int32Value();
  int val = args[1]->Int32Value();
  ///////////////////ACTUAL WORK///////////////////  

  write8(reg, val);
  /*if ((readU8(reg))) {
    ThrowException(Exception::Error(String::New("I2C read failed.")));
    return scope.Close(Undefined());
    }*/

  //////////////////PACK UP OUTPUTS/////////////////////
  Local<Integer> value = Integer::New(val);
			
  return scope.Close(Undefined());
}



void Init(Handle<Object> target) {
  target->Set(String::NewSymbol("readU8"),
	      FunctionTemplate::New(readU8)->GetFunction());
  target->Set(String::NewSymbol("readS8"),
	      FunctionTemplate::New(readS8)->GetFunction());
  target->Set(String::NewSymbol("readU16"),
	      FunctionTemplate::New(readU16)->GetFunction());
  target->Set(String::NewSymbol("readS16"),
	      FunctionTemplate::New(readS16)->GetFunction());
  target->Set(String::NewSymbol("write8"),
	      FunctionTemplate::New(write8)->GetFunction());
  target->Set(String::NewSymbol("setupI2C"),
	      FunctionTemplate::New(setupI2C)->GetFunction());
}

NODE_MODULE(rI2C, Init)

