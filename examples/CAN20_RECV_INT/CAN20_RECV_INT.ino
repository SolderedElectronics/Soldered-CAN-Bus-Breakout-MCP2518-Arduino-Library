/**
 **************************************************

   @file        CAN20_RECV_INT.ino
   @brief       Example for receiving data through CAN
                communication using CAN 2.0 protocol
                and interrupt

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


// Change pins according to your setup
const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2; //INT pin

CANBus CAN(SPI_CS_PIN); // Set CS pin

// Global variables for the CAN frame and interrupt flag
unsigned char flagRecv = 0; // Flag which indicates if chip received data
unsigned char len = 0; // Length of data
unsigned char buf[8]; // Buffer to store data

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
  if (flagRecv)// Check if flag is 1
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
