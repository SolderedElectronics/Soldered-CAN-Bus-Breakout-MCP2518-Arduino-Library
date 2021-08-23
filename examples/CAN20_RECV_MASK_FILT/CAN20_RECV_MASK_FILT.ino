// MCP2517/8 receive a CAN2.0 frame with Mask and Filter setting

// Modified By Soldered for use with https://solde.red/333012

#include "CANBus-SOLDERED.h"

// Change according to your setup
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;

CANBus CAN(SPI_CS_PIN); // Set CS pin

// Global CAN buffer and interrupt flag
unsigned char flagRecv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];

void setup()
{
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

    int filtn = 0;     // 0~31, 32 mask and filter
    int ext = 0;       // 0: standard frame, 1: ext frame
    int filter = 0x04; // filter
    int mask = 0x7ff;  // mask

    CAN.init_Filt_Mask(filtn, ext, 0x04, 0x7ff);

    pinMode(13, OUTPUT);
}


void loop()
{
    if (CAN_MSGAVAIL == CAN.checkReceive())
    {
        CAN.readMsgBuf(&len, buf); // You should call readMsgBuff before getCanId
        unsigned long id = CAN.getCanId();

        Serial.print("Get Data From id: ");
        Serial.println(id);
        Serial.print("Len = ");
        Serial.println(len);
        // PRINT DATA
        for (int i = 0; i < len; i++)
        {
            Serial.print(buf[i]);
            Serial.print("\t");
        }
        Serial.println();
    }
}


// END FILE