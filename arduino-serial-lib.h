//
// arduino-serial-lib -- simple library for reading/writing serial ports
//
// 2006-2013, Tod E. Kurt, http://todbot.com/blog/
//


#ifndef __ARDUINO_SERIAL_LIB_H__
#define __ARDUINO_SERIAL_LIB_H__

#include <stdint.h>   // Standard types 

int serialport_init(const char* serialport, int baud);
int serialport_flush(int fd);

#endif
