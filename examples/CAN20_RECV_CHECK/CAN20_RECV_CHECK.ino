// MCP2517/8 receive a frame under CAN2.0

// Modified By Soldered for use with https://solde.red/333012

#include "CANBus-SOLDERED.h"

// Change pins accordingly
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;

CANBus CAN(SPI_CS_PIN); // Set CS pin

void setup()
{
    // Initialize USB
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_125KBPS))
    { // init can bus : baudrate = 125k
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
    Serial.println("CAN init ok!");
}


void loop()
{
    // Allocate buffer
    unsigned char len = 0;
    unsigned char buf[8];

    if (CAN_MSGAVAIL == CAN.checkReceive())
    { // check if data coming

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
