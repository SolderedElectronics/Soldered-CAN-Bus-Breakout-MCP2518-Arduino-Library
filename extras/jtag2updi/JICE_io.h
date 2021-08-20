/*
 * stk_io.h
 *
 * Created: 18-11-2017 14:55:53
 *  Author: JMR_2
 */

#ifndef JICE_IO_H_
#define JICE_IO_H_

#include "JTAG2.h"
#include <stdint.h>

namespace JICE_io
{
// Function prototypes
uint8_t put(char c);
uint8_t get(void);
void init(void);
void flush(void);
void set_baud(JTAG2::baud_rate rate);
} // namespace JICE_io

#endif /* JICE_IO_H_ */