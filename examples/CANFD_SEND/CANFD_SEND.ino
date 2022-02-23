/**
 **************************************************
 *
 * @file        CANFD_RECV_INT.ino
 * @brief       Example for sending frame through CAN
 *              communication using CAN FD protocol
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

// Change according to your setup
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;

// pin for CANBed FD
// const int SPI_CS_PIN = 17;
// const int CAN_INT_PIN = 7;

CANBus CAN(SPI_CS_PIN); // Set CS pin

unsigned char stmp[MAX_DATA_SIZE] = {0};


void setup()
{
    Serial.begin(115200); //Begin serial communication with PC
    while (!Serial)
    {
    }

    CAN.setMode(CAN_NORMAL_MODE);

    // init can bus : arbitration bitrate = 125k, data bitrate = 500k
    while (0 != CAN.begin(CAN_125K_500K))
    {
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
    Serial.println("CAN init ok!");

    byte mode = CAN.getMode();
    Serial.print("CAN mode = ");
    Serial.println(mode);

    for (int i = 0; i < MAX_DATA_SIZE; i++)
    {
        stmp[i] = i;
    }
}


void loop()
{
    // send data:  id = 0x00, standrad frame, data len = 64, stmp: data buf
    CAN.sendMsgBuf(0x01, 0, CANFD::len2dlc(MAX_DATA_SIZE), stmp);
    delay(10);
    CAN.sendMsgBuf(0x04, 0, CANFD::len2dlc(MAX_DATA_SIZE), stmp);
    delay(500); // send data per 100ms
    Serial.println("CAN BUS sendMsgBuf ok!");
}

// END FILE
