/**
 **************************************************
 *
 * @file        CANBus-SOLDERED.h
 * @brief       CAN Bus Breakout code
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Zvonimir Haramustek for soldered.com
 ***************************************************/

#ifndef __CAN_BUS_SOLDERED__
#define __CAN_BUS_SOLDERED__

#include "Arduino.h"
#include "libs/Longan_CANFD/src/mcp2518fd_can.h"

class CANBus : public mcp2518fd
{
  public:
    CANBus(int _pin) : mcp2518fd(_pin)
    {
    }
};

#endif
