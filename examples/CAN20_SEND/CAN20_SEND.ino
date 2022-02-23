/**
 **************************************************
 *
 * @file        CAN20_SEND_INT.ino
 * @brief       Example for sending frame through CAN
 *              communication using CAN 2.0 protocol
 *
 *              Product used is www.solde.red/333020
 * 
 *              Modified By Soldered
 * 
 * @authors     Longan Labs
 ***************************************************/

//Connecting diagram
//Breakout      Arduino
//|-------------|
//NCS-----------10
//SDI-----------MOSI(11 on Dasduino Core)
//SDO-----------MISO(12 on Dasduino Core)
//SCK-----------SCK(13 on Dasduino Core)
//GND-----------GND
//VCC-----------5V
//CLKO----------NOT CONNECTED
//INT-----------2
//INT0----------NOT CONNECTED
//INT1----------NOT CONNECTED

#include "CANBus-SOLDERED.h"

// Change according to your setup
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;

CANBus CAN(SPI_CS_PIN); // Set CS pin

void setup()
{
    // Initialize USB
    Serial.begin(115200); //Begin serial communication with PC
    while (!Serial)
    {
    };

    while (CAN_OK != CAN.begin(CAN_125KBPS))
    { // init can bus : baudrate = 125k
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
    Serial.println("CAN init ok!");
}

unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};

void loop()
{

    CAN.sendMsgBuf(0x01, 0, 8, stmp);
    delay(10);
    CAN.sendMsgBuf(0x04, 0, 8, stmp);
    delay(500); // send data per 100ms
    Serial.println("CAN BUS sendMsgBuf ok!");
}

// END FILE
