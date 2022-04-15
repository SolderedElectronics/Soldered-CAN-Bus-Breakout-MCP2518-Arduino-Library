/**
 **************************************************

   @file        OBDII-PIDs.ino
   @brief       Input a PID, then you will get reponse
                from vehicle, the input should be end with '\n'
                    Query
                        send id: 0x7df
                        dta: 0x02, 0x01, PID_CODE, 0, 0, 0, 0, 0

                    Response
                        From id: 0x7E9 or 0x7EA or 0x7EB
                        dta: len, 0x41, PID_CODE, byte0, byte1(option), byte2(option), byte3(option), byte4(option)


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

// Change according to your setup
const int SPI_CS_PIN = 10;

// pin for CANBed FD
// const int SPI_CS_PIN = 17;
// const int CAN_INT_PIN = 7;

CANBus CAN(SPI_CS_PIN); // Set CS pin

#define PID_ENGIN_PRM     0x0C // Engine RPM
#define PID_VEHICLE_SPEED 0x0D // Vehicle speed
#define PID_COOLANT_TEMP  0x05 // Engine coolant temperature

#define CAN_ID_PID 0x7DF

unsigned char PID_INPUT;
unsigned char getPid = 0;

void set_mask_filt()
{
  /*
      set mask, set both the mask to 0x3ff
  */
  CAN.init_Mask(0, 0, 0x7FC); // Set masks for IDs 
  CAN.init_Mask(1, 0, 0x7FC); // Set masks for IDs 

  /*
      set filter, we can receive id from 0x04 ~ 0x09
  */
  CAN.init_Filt(0, 0, 0x7E8); // Set filters and masks for IDs
  CAN.init_Filt(1, 0, 0x7E8); // Set filters and masks for IDs

  CAN.init_Filt(2, 0, 0x7E8); // Set filters and masks for IDs
  CAN.init_Filt(3, 0, 0x7E8); // Set filters and masks for IDs
  CAN.init_Filt(4, 0, 0x7E8); // Set filters and masks for IDs
  CAN.init_Filt(5, 0, 0x7E8); // Set filters and masks for IDs

  // Those are OBD II data and they are just copied here, if you want to
  // know more about those, you should search on the internet, informations
  // about OBD II is hard to find because it is only used in automotive
  // systems. You can find library for OBD here: https://github.com/sandeepmistry/arduino-OBD2
}

void sendPid(unsigned char __pid)
{
  unsigned char tmp[8] = {0x02, 0x01, __pid, 0, 0, 0, 0, 0}; // Make buffer with formatted data to send
  Serial.print("SEND PID: 0x"); 
  Serial.println(__pid, HEX); // Print data to send on Serial monitor
  CAN.sendMsgBuf(CAN_ID_PID, 0, 8, tmp);// Send data in CAN network
  // First parameter - which ID to set in frame (ID of transmitter)
  // Second parameter - Frame size (0 - Normal frame, 1 - Extended frame)
  // Third parameter - Length of buffer in bytes
  // Fourth parameter - Buffer which contains data to send
}

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
  set_mask_filt(); // Call function to set masks and filters
}


void loop()
{
  taskCanRecv(); // Call function to check if data is incoming from CAN network
  taskDbg(); // Call function to make data for sendin in CAN network

  if (getPid) // GET A PID
  {
    getPid = 0;
    sendPid(PID_INPUT);
    PID_INPUT = 0;
  }
}

void taskCanRecv()
{
  unsigned char len = 0; // Variable to store length of incoming data
  unsigned char buf[8];  // Buffer to store incoming data

  if (CAN_MSGAVAIL == CAN.checkReceive()) // Check if data coming
  {

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

void taskDbg()
{
  while (Serial.available()) //While data is incoming from Serial communication
  {
    char c = Serial.read(); // Read one char
      // Next part of code appends char on beggining of array (PID command array)
      // and is converted to hexadecimal form which can easily be converted in binary.
    if (c >= '0' && c <= '9') // If number from 0 to 9 is received
    {
      PID_INPUT *= 0x10; // Multiply by ten in hexadecimal (or simply said shift left by one number)
      PID_INPUT += c - '0'; // Add last received number on first place in array
    }
    else if (c >= 'A' && c <= 'F') // If hexadecimal value from A to F is received
    {
      PID_INPUT *= 0x10; // Multiply by ten in hexadecimal (or simply said shift left by one number)
      PID_INPUT += 10 + c - 'A'; // Add last received number on first place in array
    }
    else if (c >= 'a' && c <= 'f') // If hexadecimal value from a to f is received
    {
      PID_INPUT *= 0x10; // Multiply by ten in hexadecimal (or simply said shift left by one number)
      PID_INPUT += 10 + c - 'a'; // Add last received number on first place in array
    }
    else if (c == '\n') // Data collecting stops when newline symbol is received
    { // END
      getPid = 1;
    }
  }
}
// END FILE
