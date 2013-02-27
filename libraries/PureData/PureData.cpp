/*
  PureData.cpp - PureData library
  Copyright (C) 2011 Lourens Rozema
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#include "Arduino.h"
#include "HardwareSerial.h"
#include "PureData.h"

extern "C" {
# include <string.h>
# include <stdlib.h>
}

PureDataClass::PureDataClass() {
	// prepare floating-point value pointer
	inputBufferValuePtr = (uint8_t *)&inputBufferValue;
}

void PureDataClass::begin(void) {
  begin(115200);
}

void PureDataClass::begin(long speed) {
#if defined(__AVR_ATmega128__)
  Serial.begin((uint32_t)speed);
#else
  Serial.begin(speed);
#endif
}

void PureDataClass::processInput() {
	if(!inputBufferEmpty()) return;

  const int inputData = Serial.read(); // this is 'int' to handle -1 when no data

	if(inputData < 0) return;

	switch(inputBufferState) {
	 	// also wait for a start-byte in this case (so we won't hang on unhandled tags!)
		case(3):
			// TODO: implement double buffering? if execution of the loop takes more then
			// one byte-time and PureData sends two tags directly after each other we could
			// miss it!

		// wait for start byte
		case(0):
		{
			if(inputData != 0xAA) break;

			inputBufferTagIdx = 0;
			inputBufferValuePtrIdx = 0;

			inputBufferState = 1;
			break;
		}
		// wait for reception of tag to complete
		case(1):
		{
			if(inputData != 0x00) {
				// always keep room for a null-terminator
				if(inputBufferTagIdx < (sizeof(inputBufferTag)-1)) {
					inputBufferTag[inputBufferTagIdx++] = inputData;
				}
				break;
			}

			// close string
			inputBufferTag[inputBufferTagIdx++] = '\0';
			inputBufferState = 2;
			break;
		}
		// wait for the floating-point value to complete
		case(2):
		{
			if(inputBufferValuePtrIdx < sizeof(inputBufferValue)) {
				inputBufferValuePtr[inputBufferValuePtrIdx++] = inputData;
			}

			if(inputBufferValuePtrIdx < sizeof(inputBufferValue)) break;

			inputBufferState = 3;
			break;
		}
	}
}

void PureDataClass::send(const char * const tag, const float value) {
	// write start byte
	Serial.write((uint8_t)0xAA);

	// write string tag + null terminator
	Serial.write(tag);
	Serial.write((uint8_t)'\0');

	// write floating-point value
	Serial.write((const uint8_t * const)&value, sizeof(value));
}

uint8_t PureDataClass::receive(const char * const tag, float * const value) {
	// always process input data
	processInput();

	// nothing to receive when no data in input buffer
	if(inputBufferEmpty()) return(0);

	// check if requested tag matches the one currently in the input buffer
	if(strcmp(inputBufferTag, tag) != 0) return(0);

	// it matched, so return that value and mark the buffer empty again
	*value = inputBufferValue;
	inputBufferState = 0;
	return(1);
}

// make one instance for the user to use
PureDataClass PureData;

