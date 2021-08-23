// MCP2517/8 receive a CAN frame with interrupt

// Modified By Soldered for use with https://solde.red/333012

#include "CANBus-SOLDERED.h"


// Change pins according to your setup
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;

CANBus CAN(SPI_CS_PIN); // Set CS pin

// Global variables for the CAN frame and interrupt flag
unsigned char flagRecv = 0;
unsigned char len = 0;
unsigned char buf[8];
char str[20];

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), CAN_ISR, FALLING); // start interrupt
    while (CAN_OK != CAN.begin(CAN_125KBPS))
    { // init can bus : baudrate = 125k
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
    Serial.println("CAN init ok!");
}

// Should be as fast as possible, otherwise might crash
void CAN_ISR()
{
    flagRecv = 1;
}

void loop()
{
    if (flagRecv)
    {
        // check if get data

        flagRecv = 0;              // clear flag
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
