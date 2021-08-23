/*  MCP2517/8 send a can fd frame

    can-fd baud rate:

    CAN_125K_500K
    CAN_250K_500K
    CAN_250K_750K
    CAN_250K_1M
    CAN_250K_1M5
    CAN_250K_2M
    CAN_250K_3M
    CAN_250K_4M
    CAN_500K_1M
    CAN_500K_2M
    CAN_500K_3M
    CAN_500K_4M
    CAN_1000K_4M

    Modified By Soldered for use with https://solde.red/333012
*/

#include "CANBus-SOLDERED.h"
#include <SPI.h>

#define MAX_DATA_SIZE 64

// pin for CAN-FD Shield
const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;

// pin for CANBed FD
// const int SPI_CS_PIN = 17;
// const int CAN_INT_PIN = 7;

CANBus CAN(SPI_CS_PIN); // Set CS pin

unsigned char stmp[MAX_DATA_SIZE] = {0};


void setup()
{
    Serial.begin(115200);
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
