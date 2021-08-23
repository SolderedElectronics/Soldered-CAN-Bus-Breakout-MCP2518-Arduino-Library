// MCP2517/8 send a CAN frame

// Modified By Soldered for use with https://solde.red/333012

#include "CANBus-SOLDERED.h"

// Change according to your setup
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;

CANBus CAN(SPI_CS_PIN); // Set CS pin

void setup()
{
    // Initialize USB
    Serial.begin(115200);
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
