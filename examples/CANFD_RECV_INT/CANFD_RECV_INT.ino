/**
 **************************************************
 *
 * @file        CANFD_RECV_INT.ino
 * @brief       Example for receiving frame through CAN
 *              communication using CAN FD protocol and 
 *              interrupt
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
#include <SPI.h>

#define MAX_DATA_SIZE 64

// pin for CAN-FD Shield
// const int SPI_CS_PIN = 9;
// const int CAN_INT_PIN = 2;

// Change according to your setup
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;

CANBus CAN(SPI_CS_PIN); // Set CS pin

unsigned char flagRecv = 0;
unsigned char len = 0;
unsigned char buf[MAX_DATA_SIZE];

void setup()
{
    Serial.begin(115200); //Begin serial communication with PC
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), CAN_ISR, FALLING); // start interrupt
    CAN.setMode(CAN_NORMAL_MODE);

    // init can bus : arbitration bitrate = 125k, data bitrate = 500k
    while (0 != CAN.begin(CAN_125K_500K))
    {
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
    Serial.println("CAN init ok!");
}

void CAN_ISR()
{
    flagRecv = 1;
}

void loop()
{

    if (flagRecv)
    {

        flagRecv = 0; // check if get data

        CAN.readMsgBuf(&len, buf); // You should call readMsgBuff before getCanId
        unsigned long id = CAN.getCanId();

        Serial.print("Get Data From id: ");
        Serial.println(id);
        Serial.print("Len = ");
        Serial.println(len);
        // print the data
        for (int i = 0; i < len; i++)
        {
            Serial.print(buf[i]);
            Serial.print("\t");
        }
        Serial.println();
    }
}

// END FILE
