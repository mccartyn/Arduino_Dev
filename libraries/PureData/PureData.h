/*
  PureData.h - PureData library
  Copyright (C) 2011 Lourens Rozema
 
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  See file LICENSE.txt for further informations on licensing terms.
*/

#ifndef PureData_h
#define PureData_h

#include <Arduino.h>
#include <inttypes.h>

extern "C" {
}

class PureDataClass
{
public:
	PureDataClass();

/* Arduino constructors */
  void begin();
  void begin(long);

/* serial receive handling */
  void processInput();

	void send(const char * const, const float);
	uint8_t receive(const char * const, float * const);

private:
	char inputBufferTag[32];
	float inputBufferValue;

	uint8_t inputBufferState;
	uint8_t inputBufferTagIdx;
	uint8_t *inputBufferValuePtr;
	uint8_t inputBufferValuePtrIdx;

	inline uint8_t inputBufferEmpty() {
		return(inputBufferState < 3);
	}
};

extern PureDataClass PureData;

#endif /* PureData_h */

