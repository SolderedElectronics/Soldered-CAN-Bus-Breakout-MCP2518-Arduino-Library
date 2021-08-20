/**
 **************************************************
 *
 * @file        easyC.cpp
 * @brief       Basic funtions for easyC
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     @ soldered.com
 ***************************************************/

#include "easyC.h"

namespace EASYC_SOLDERED_LIBS
{

/**
 * @brief       Main constructor for easyC version
 *
 */
EasyC::EasyC()
{
    native = 0;
}

/**
 * @brief       Initializes sensors on native or easyC on default address
 */
void EasyC::begin()
{
    if (native)
        initializeNative();
    else
        begin(defaultAddress);

    beginDone = 1;
}

/**
 * @brief                  Initializes sensors on supplied i2c address
 *
 * @param uint8_t _address Custom easyC sensor address
 */
void EasyC::begin(uint8_t _address)
{
    address = _address;

    Wire.begin();

    beginDone = 1;
}

/**
 * @brief                   Private function to send over i2c and then read n bytes
 *
 * @param char regAddr      Address of register to access data from
 * @param char a            Array to put data in
 * @param size_t n          Size of data to read
 *
 * @return int              0 if read successfuly, error code from endTransmission if not
 */
int EasyC::readRegister(char regAddr, char a[], size_t n)
{
    if (sendAddress(regAddr))
        return err;

    if (readData(a, n))
        return err;

    return 0;
}

/**
 * @brief                Private function to send a single byte to sensor
 *
 * @param  char regAddr  Address of register to access later
 *
 * @return int           Standard endTransmission error codes
 */
int EasyC::sendAddress(char regAddr)
{
    Wire.beginTransmission(address);
    Wire.write(regAddr);

    return err = Wire.endTransmission();
}

/**
 * @brief           Private function to read n bytes over i2c
 *
 * @param  char a[] Array to read data to
 * @param  int n    Number of bytes to read
 *
 * @return int      Error code, always 0
 */
int EasyC::readData(char a[], int n)
{
    Wire.requestFrom(address, n);
    Wire.readBytes(a, n);

    return 0;
}

/**
 * @brief           Private function to write n bytes over i2c
 *
 * @param char a[]  Array to read data from
 * @param int n     Number of bytes to read
 *
 * @return int       Standard endTransmission error codes
 */
int EasyC::sendData(const uint8_t *a, int n)
{
    Wire.beginTransmission(address);
    Wire.write(a, n);

    return err = Wire.endTransmission();
}

} // namespace EASYC_SOLDERED_LIBS
