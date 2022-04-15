/**
 **************************************************

   @file        CAN20_SEND_INT.ino
   @brief       Example for sending frame through CAN
                communication using CAN 2.0 protocol

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

// Change according to your setup
const int SPI_CS_PIN = 10;

CANBus CAN(SPI_CS_PIN); // Set CS pin

void setup()
{
  Serial.begin(115200); //Begin serial communication with PC

  while (CAN_OK != CAN.begin(CAN_125KBPS))  // Initialize CAN BUS with baud rate of 125 kbps
    // This should be in while loop because MCP2518
    // needs some time to initialize and start function
    // properly.
  {
    Serial.println("CAN init fail, retry..."); // Print information message
    delay(100);
  }
  Serial.println("CAN init ok!");
}

unsigned char stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7}; // Buffer which stores data to send

void loop()
{

  CAN.sendMsgBuf(0x01, 0, 8, stmp); // Send data in CAN network
  // First parameter - which ID to set in frame (ID of transmitter)
  // Second parameter - Frame size (0 - Normal frame, 1 - Extended frame)
  // Third parameter - Length of buffer in bytes
  // Fourth parameter - Buffer which contains data to send
  delay(10); // Wait a bit for CAN module to send data
  CAN.sendMsgBuf(0x04, 0, 8, stmp); // Send same data again
  delay(500); // Wait a bit not to overfill network
  Serial.println("CAN BUS sendMsgBuf ok!"); // Print message
}

// END FILE
