/**
 **************************************************

   @file        CANFD_RECV_INT.ino
   @brief       Example for receiving frame through CAN
                communication using CAN FD protocol and
                interrupt

                Product used is www.solde.red/333020

                Modified By Soldered

   @authors     Longan Labs
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

unsigned char flagRecv = 0;// Flag which indicates if chip received data
unsigned char len = 0; // Length of data
unsigned char buf[MAX_DATA_SIZE]; // Buffer to store data

void setup()
{
  Serial.begin(115200); //Begin serial communication with PC

  while (0 != CAN.begin(CAN_125K_500K))// Initialize CAN BUS with baud rate of 125 kbps and arbitration rate of 500k
    // This should be in while loop because MCP2518
    // needs some time to initialize and start function
    // properly.
  {
    Serial.println("CAN init fail, retry..."); // Print information message
    delay(100);
  }
  Serial.println("CAN init ok!");

  attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), CAN_ISR, FALLING); // Set interrupt on pin CAN_INT_PIN
  // and call ISR CAN_ISR, fire interrupt on falling edge
}

// Should be as fast as possible, otherwise might crash
void CAN_ISR()
{
  flagRecv = 1; // If data is received, interrupt will fire, and this flag will be set to 1
}

void loop()
{

  if (flagRecv)
  {

    flagRecv = 0;              // Clear flag
    CAN.readMsgBuf(&len, buf);  // You should call readMsgBuff before getCanId
    // This function saves incoming data into buffer buf
    // It saves len number of bytes
    unsigned long id = CAN.getCanId(); // Get ID of transmitter
    Serial.print("Get Data From id: "); // Print ifnormatio message
    Serial.println(id); // Print ID of transmitter
    Serial.print("Len = ");
    Serial.println(len);// Print length of the data
    for (int i = 0; i < len; i++)
    {
      Serial.print(buf[i]); // Print array with received data
      Serial.print("\t"); // Print tabulator to format printing
    }
    Serial.println(); // Print new line at the end
  }
}

// END FILE
