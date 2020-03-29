
//Rocky Hill


/*
   This sketch waits for button presses to turn on/off the
   iMac G3 CRT circuitry and send the init sequence to the IVAD board.
   if you are planning to just send the init sequence on startup, you can 
   uncomment "initIvadBoard();"  in setup().
   It uses software i2c lines.
  
  it also sends edid information when requested via i2c on port 0x50.
  The Edid information is for an iMac G3 DV and it sends the three supported modes.   
  
  1024x768 @ 75 Hz
   800x600 @ 95 Hz
   640x480 @ 117 Hz
  
   In order for this program to work, the i2c transmit buffer length constants must be changed in
   two files. The Wire library has two buffers it uses for i2c transmissions

   "BUFFER_LENGTH" in
   "arduino_install_folder/hardware/arduino/avr/libraries/Wire/src/Wire.h" and

   "TWI_BUFFER_LENGTH" in
   "arduino_install_folder/hardware/arduino/avr/libraries/Wire/src/utility/twi.h"

   Both of these must be changed from 32 to 128 to be able to transmit the edid byte array in
   one shot.

   To test this program, you can directly wire SDA(pin 12),SCL(pin 15) and GND(pin 6) pins from your computers VGA port
   directly into the corresponding pins on the arduino.


*/


/*
Uses SoftwareWire from the arduino libraries. install with library manager or from https://github.com/Testato/SoftwareWire
*/
#include <SoftwareWire.h>   
#include <Wire.h>

byte data = -1;


//this is the EDID information that is sent to the computer that requests it.
const byte edid[128] =
{

  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x06, 0x10, 0x74, 0x61,
  0xed, 0x5f, 0x84, 0x00, 0x06, 0x1e, 0x01, 0x03, 0x6d, 0x1a, 0x14, 0x78,
  0xea, 0x5e, 0xc0, 0xa4, 0x59, 0x4a, 0x98, 0x25, 0x20, 0x50, 0x54, 0x00,
  0x00, 0x00, 0x61, 0x4f, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xc3, 0x1e, 0x00, 0x30, 0x41, 0x00,
  0x34, 0x30, 0x14, 0x60, 0xd3, 0x00, 0x0a, 0xc8, 0x10, 0x00, 0x00, 0x1e,
  0x5f, 0x18, 0x20, 0xf0, 0x30, 0x58, 0x2c, 0x20, 0x15, 0x50, 0x93, 0x00,
  0xd0, 0x9c, 0x00, 0x00, 0x00, 0x18, 0x7d, 0x13, 0x80, 0xc0, 0x20, 0xe0,
  0x22, 0x10, 0x11, 0x40, 0x13, 0x00, 0xa6, 0x7d, 0x00, 0x00, 0x00, 0x18,
  0x00, 0x00, 0x00, 0xfd, 0x00, 0x3b, 0x3d, 0x3a, 0x3d, 0x08, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x19
};

//define solid state relay and power button pins
int solid_state_relay_Pin = 7;

int powerButtonPin = 3;
//int powerButtonPin = 13;

//define state variables
int externalCircuitState = LOW;
int buttonState = LOW;


//counters
int buttonPressedTime = 0;

//The init sequence is sent on a software i2c bus.
// sda is on 4 and scl is on 5
SoftwareWire softWire( 4, 5);


void setup() {

  //define pin direction
  pinMode(solid_state_relay_Pin, OUTPUT);
  pinMode(powerButtonPin, INPUT);
  pinMode(14, INPUT);//this pin is on the J5 connector for general use.
  pinMode(15, INPUT);//this pin is on the J5 connector for general use.



  Wire.begin(0x50); //join as slave and wait for EDID requests
  softWire.begin();// join as master and send init sequence
  
  Wire.onRequest(requestEvent); //event handler for requests from master
  Wire.onReceive(receiveData); // event handler when receiving from  master
  // turn it all off
  externalCircuitOff();

  //initIvadBoard();

}

byte x = 0;
/*
   This loops looks for button presses and turns the circuit on or off.
*/
void loop() {
  buttonState = digitalRead(powerButtonPin);


  if (buttonState == LOW )
  {
    if (buttonPressedTime <= 10) {
      buttonPressedTime++;
    }//end if



  }
  else
  {
    //buttonPressedTime = 0;

  }
  delay(10);

  //turn everything off if button is pressed for 10 ms
  if (buttonPressedTime >= 1 && externalCircuitState == HIGH && buttonState == HIGH) {
    externalCircuitOff();
    buttonPressedTime = 0;

  }

  //turn everything on if button is pressed for 10 ms
  if (buttonPressedTime >= 1 && externalCircuitState == LOW  && buttonState == HIGH) {
    externalCircuitOn();
    delay(500);
    initIvadBoard();
    buttonPressedTime = 0;

  }




}


void writeToIvad(int address, int message) {
  softWire.beginTransmission(address);
  softWire.write(message);
  softWire.endTransmission();

}//end method

void writeToIvad(int address, int message1, int message2) {
  softWire.beginTransmission(address);
  softWire.write(message1);
  softWire.write(message2);
  softWire.endTransmission();

}//end method

void  readFromIvad(int address, int bytes) {
  char buf[bytes + 1];
  int bytesRead = 0;
  softWire.requestFrom(address, bytes);
  while (softWire.available())
  {
    char c = softWire.read();
    buf[bytesRead++] = c;
  }
  buf[bytesRead] = '\0';

}//end method


void initIvadBoard() {

  //Init sequence 1
  /**
    writeToIvad( 0x46,0x13,0x00);
    readFromIvad(0x46,1);
    writeToIvad( 0x46,0x09,0x00);
    writeToIvad( 0x53,0x33);
    readFromIvad(0x53,1);
    //delay(900);
    writeToIvad( 0x46,0x13,0x0A);
    writeToIvad( 0x46,0x00,0x00);
    writeToIvad( 0x46,0x08,0xE4);
    writeToIvad( 0x46,0x12,0xC9);
    //delay(8000);
    writeToIvad( 0x53,0x00);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x0A);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x14);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x1E);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x28);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x32);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x3C);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x46);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x50);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x5A);
    readFromIvad(0x53,10);
    writeToIvad( 0x46,0x01,0x93);
    writeToIvad( 0x46,0x02,0x93);
    writeToIvad( 0x46,0x03,0x8F);
    writeToIvad( 0x46,0x04,0x9A);
    writeToIvad( 0x46,0x05,0x7B);
    writeToIvad( 0x46,0x06,0x7B);
    writeToIvad( 0x46,0x07,0xB0);
    writeToIvad( 0x46,0x08,0xDC);
    writeToIvad( 0x46,0x09,0x49);
    writeToIvad( 0x46,0x0A,0x92);
    writeToIvad( 0x46,0x0B,0xA2);
    writeToIvad( 0x46,0x0C,0xDF);
    writeToIvad( 0x46,0x0D,0x20);
    writeToIvad( 0x46,0x0E,0xC2);
    writeToIvad( 0x46,0x0F,0xD2);
    writeToIvad( 0x46,0x10,0x40);
    writeToIvad( 0x46,0x11,0x09);
    writeToIvad( 0x46,0x12,0x27);
    writeToIvad( 0x46,0x00,0xFA);
    writeToIvad( 0x53,0x00);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x0A);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x14);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x1E);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x28);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x32);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x3C);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x46);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x50);
    readFromIvad(0x53,10);
    writeToIvad( 0x53,0x5A);
    readFromIvad(0x53,2);
    writeToIvad( 0x46,0x01,0x93);
    writeToIvad( 0x46,0x02,0x93);
    writeToIvad( 0x46,0x03,0x8F);
    writeToIvad( 0x46,0x04,0x9A);
    writeToIvad( 0x46,0x05,0x7B);
    writeToIvad( 0x46,0x06,0x7B);
    writeToIvad( 0x46,0x07,0xB0);
    writeToIvad( 0x46,0x08,0xDC);
    writeToIvad( 0x46,0x09,0x49);
    writeToIvad( 0x46,0x0A,0x92);
    writeToIvad( 0x46,0x0B,0xA2);
    writeToIvad( 0x46,0x0C,0xDF);
    writeToIvad( 0x46,0x0D,0x20);
    writeToIvad( 0x46,0x0E,0xC2);
    writeToIvad( 0x46,0x0F,0xD2);
    writeToIvad( 0x46,0x10,0x40);
    writeToIvad( 0x46,0x11,0x09);
    writeToIvad( 0x46,0x12,0x27);
    writeToIvad( 0x46,0x00,0xFA);
    writeToIvad( 0x46, 0x04, 0x80);//red x-30
    writeToIvad( 0x46, 0x05, 0xB0);// green x
    writeToIvad( 0x46, 0x06, 0x78); //blue x-38
    writeToIvad( 0x46, 0x10, 0x40); // brightness

    **/


  //init sequence 2 <---this is the one that works well with my iMac G3
  writeToIvad( 0x46, 0x13, 0x00);
  readFromIvad(0x46, 1);
  writeToIvad( 0x46, 0x09, 0x00);
  writeToIvad( 0x53, 0x33);
  readFromIvad(0x53, 1);
  writeToIvad( 0x46, 0x13, 0x0B);
  writeToIvad( 0x46, 0x00, 0x00);
  writeToIvad( 0x46, 0x08, 0xE4);
  writeToIvad( 0x46, 0x12, 0xC9);
  writeToIvad( 0x53, 0x00);
  readFromIvad(0x53, 10);
  writeToIvad( 0x53, 0x0A);
  readFromIvad(0x53, 10);
  writeToIvad( 0x53, 0x14);
  readFromIvad(0x53, 10);
  writeToIvad( 0x53, 0x1E);
  readFromIvad(0x53, 10);
  writeToIvad( 0x53, 0x28);
  readFromIvad(0x53, 10);
  writeToIvad( 0x53, 0x32);
  readFromIvad(0x53, 10);
  writeToIvad( 0x53, 0x3C);
  readFromIvad(0x53, 10);
  writeToIvad( 0x53, 0x46);
  readFromIvad(0x53, 10);
  writeToIvad( 0x53, 0x50);
  readFromIvad(0x53, 10);
  writeToIvad( 0x53, 0x5A);
  readFromIvad(0x53, 2);
  //writeToIvad( 0x46, 0x01, 0x98);//red
  //writeToIvad( 0x46, 0x02, 0x88);//green
  //writeToIvad( 0x46, 0x03, 0x88);//blue

  writeToIvad( 0x46, 0x04, 0x80);//red x-30
  writeToIvad( 0x46, 0x05, 0xB0);// green x
  writeToIvad( 0x46, 0x06, 0x78); //blue x-38

  writeToIvad( 0x46, 0x07, 0xB1); //horizontal position
  writeToIvad( 0x46, 0x08, 0xF8); //vertical size
  writeToIvad( 0x46, 0x09, 0x49);
  writeToIvad( 0x46, 0x0A, 0x9E);
  writeToIvad( 0x46, 0x0B, 0x93);
  writeToIvad( 0x46, 0x0C, 0xCA);
  writeToIvad( 0x46, 0x0D, 0x18); // horizontal size
  writeToIvad( 0x46, 0x0E, 0xC0);
  writeToIvad( 0x46, 0x0F, 0xC1);
  writeToIvad( 0x46, 0x10, 0x40); // brightness
  writeToIvad( 0x46, 0x11, 0x09);
  writeToIvad( 0x46, 0x12, 0xE0); // rotation
  writeToIvad( 0x46, 0x00, 0xF0);





}


void solid_state_relayOn() {
  digitalWrite(solid_state_relay_Pin, HIGH);

}

void solid_state_relayOff() {
  digitalWrite(solid_state_relay_Pin, LOW);

}




//these are probably too much but they are here in case I would lke to add more stuff to turn on and off
void externalCircuitOn() {
  solid_state_relayOn();
  externalCircuitState = HIGH;

}
void externalCircuitOff() {
  solid_state_relayOff();
  externalCircuitState = LOW;

}



// function that executes whenever data is requested by master
// this function is registered as an event.
void requestEvent() {
  //delay(500);
  Wire.write(edid, 128);



}//end method
// function that executes whenever data is received by the slave


void receiveData(int byteCount) {


  while (Wire.available()) {
    data = Wire.read();
  }
}
