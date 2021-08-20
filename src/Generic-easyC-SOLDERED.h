/**
 **************************************************
 *
 * @file        Generic-easyC-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/

#ifndef __SENSOR__
#define __SENSOR__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.h"

class Sensor : public EASYC_SOLDERED_LIBS::EasyC
{
  public:
    Sensor(int _pin);

  protected:
    void initializeNative();

  private:
    int pin;
};

#endif
