
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

int monitorAddress = 0x46;

int settingParallelogram = 0x0f;
int settingKeystone = 0x0b;
int settingRotation = 0x12;
int settingPincushion = 0x0c;


int verticalPositionSetting = 0x09;
const int verticalPositionValues[19] = {
  // Low to High
  0x7e, 0x7c, 0x79, 0x75, 0x70, 0x6a, 0x63, 0x5b, 0x52, 0x49, 0x40, 0x37, 0x2e, 0x25, 0x1c, 0x13, 0x0a, 0x01, 0x00
};
int verticalPositionValueIndex = 9;

int contrastSetting = 0x00;
const int contrastValues[73] = {
  0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 
  0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 
  0xdb, 0xdc, 0xdd, 0xde, 0xdf, 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 
  0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfc, 0xfd, 0xff
};
int contrastValueIndex = 72;

int horizontalPositionSetting = 0x07;
const int horizontalPositionValues[19] = {
  0xfe, 0xfc, 0xf9, 0xf5, 0xf0, 0xea, 0xe3, 0xdb, 0xd2, 0xc9, 0xc0, 0xb7, 0xae, 0xa5, 0x9c, 0x93, 0x8a, 0x81, 0x80
};
int horizontalPositionValueIndex = 11;

int heightSetting = 0x08;
const int heightValues[19] = {
  // short to tall
  0x81, 0x83, 0x10, 0x8a, 0x8f, 0x95, 0x9c, 0xa4, 0xad, 0xb6, 0xbf, 0xc8, 0x1a, 0xda, 0xe3, 0xec, 0xf5, 0xfe, 0xff
};
int heightValueIndex = 14;

int widthSetting = 0x0d;
const int widthValues[19] = {
  // thinnest to thickest 
  0x7e, 0x7c, 0x79, 0x75, 0x70, 0x6a, 0x63, 0x5b, 0x52, 0x49, 0x40, 0x37, 0x2e, 0x25, 0x1c, 0x13, 0x0a, 0x01, 0x00
};
int widthValueIndex = 18;

int brightnessSetting = 0x11;
int brightnessValues[10] = {
  // Dim to Bright
  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a
};
int brightnessValueIndex = 9;

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


void handleSerial() {
  /*
   * a = move left
   * s = move right
   * w = move up
   * z = move down
   * 
   * d = skinnier
   * f = fatter
   * r = taller
   * c = shorter
   * 
   * g = contrast down
   * h = contrast up
   * 
   * j = brightness down
   * k = brightness up
   * 
   * 
   */

  
  while(Serial.available() > 0) {
    char incoming = Serial.read();

    switch(incoming) {
      case 'a':
        moveLeft();
        break;
      case 's':
        moveRight();
        break;
      case 'w':
        moveUp();
        break;
      case 'z':
        moveDown();
        break;

      case 'd':
        decreaseWidth();
        break;
      case 'f':
        increaseWidth();
        break;
      case 'r':
        increaseHeight();
        break;
      case 'c':
        decreaseHeight();
        break;

      case 'g':
        decreaseContrast();
        break;
      case 'h':
        increaseContrast();
        break;

      case 'j':
         decreaseBrightness();
         break;
      case 'k':
         increaseBrightness();
         break;
    }
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


// This initsequence was provided by "anotherelise"
// https://forums.macrumors.com/threads/imac-g3-mod-video-connector.1712095/post-28346679
/**
     writeToIvad( 0x46,0x13,0x00);
    writeToIvad(0x46,0x13,0x00);
    readFromIvad(0x46,1);
    writeToIvad(0x46,0x09,0x00);
    writeToIvad(0x53,0x33);
    readFromIvad(0x53,1);
    writeToIvad(0x46,0x13,0x0b);
    writeToIvad(0x46,0x00,0x00);
    writeToIvad(0x46,0x08,0xe4);
    writeToIvad(0x46,0x12,0xc9);
    writeToIvad(0x53,0x00);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x0a);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x14);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x1e);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x28);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x32);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x3c);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x46);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x50);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x5a);
    readFromIvad(0x53,10);
    writeToIvad(0x46,0x01,0x82);
    writeToIvad(0x46,0x02,0x82);
    writeToIvad(0x46,0x03,0x82);
    writeToIvad(0x46,0x04,0xa0);
    writeToIvad(0x46,0x05,0xa0);
    writeToIvad(0x46,0x06,0xa0);
    writeToIvad(0x46,0x07,0xad);
    writeToIvad(0x46,0x08,0xe4);
    writeToIvad(0x46,0x09,0x3d);
    writeToIvad(0x46,0x0a,0x9e);
    writeToIvad(0x46,0x0b,0xb4);
    writeToIvad(0x46,0x0c,0xc4);
    writeToIvad(0x46,0x0d,0x27);
    writeToIvad(0x46,0x0e,0xbf);
    writeToIvad(0x46,0x0f,0xc0);
    writeToIvad(0x46,0x10,0x40);
    writeToIvad(0x46,0x11,0x0a);
    writeToIvad(0x46,0x12,0x5b);
    writeToIvad(0x46,0x00,0xff);
    writeToIvad(0x53,0x00);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x10);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x20);
    readFromIvad(0x53,10);
    writeToIvad(0x53,0x30);
    readFromIvad(0x53,10);
    writeToIvad(0x46,0x11,0x05);
    writeToIvad(0x46,0x00,0xff);
    writeToIvad(0x46,0x00,0x00);
    writeToIvad(0x46,0x07,0xb1);
    writeToIvad(0x46,0x0d,0x10);
    writeToIvad(0x46,0x0c,0xc7);
    writeToIvad(0x46,0x09,0x4a);
    writeToIvad(0x46,0x08,0xea);
    writeToIvad(0x46,0x0f,0xc0);
    writeToIvad(0x46,0x0b,0xae);
    writeToIvad(0x46,0x12,0x5b);
    writeToIvad(0x46,0x00,0xff);
    writeToIvad(0x46,0x11,0x05);
    writeToIvad(0x46,0x00,0xff);
    writeToIvad(0x46,0x10,0x40);
    writeToIvad(0x46,0x06,0xa0);
    writeToIvad(0x46,0x05,0xa0);
    writeToIvad(0x46,0x04,0xa0);
    writeToIvad(0x46,0x03,0x82);
    writeToIvad(0x46,0x02,0x82);
    writeToIvad(0x46,0x01,0x82);
    writeToIvad(0x46,0x11,0x05);
    writeToIvad(0x46,0x00,0xff);
    writeToIvad(0x46,0x11,0x05);
    writeToIvad(0x46,0x00,0xff);
    writeToIvad(0x46,0x10,0x40);
    writeToIvad(0x46,0x06,0xa0);
    writeToIvad(0x46,0x05,0xa0);
    writeToIvad(0x46,0x04,0xa0);
    writeToIvad(0x46,0x03,0x82);
    writeToIvad(0x46,0x02,0x82);
    writeToIvad(0x46,0x01,0x82);
    writeToIvad(0x46,0x11,0x05);
    writeToIvad(0x46,0x00,0xff);
 */



  //init sequence 2 <---this is the one that works well with my iMac G3, Rocky Hill
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
  //writeToIvad( 0x46, 0x08, 0xF8); //vertical size
  writeToIvad( 0x46,0x08,0xDC);
  writeToIvad( 0x46, 0x09, 0x49);
  writeToIvad( 0x46, 0x0A, 0x9E);
  writeToIvad( 0x46, 0x0B, 0x93);
  writeToIvad( 0x46, 0x0C, 0xCA);
  //writeToIvad( 0x46, 0x0D, 0x18); // horizontal size
  writeToIvad( 0x46, 0x0D,0x20);
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


void moveLeft() {
  horizontalPositionValueIndex--;
  setHorizontalPosition();
}
void moveRight() {
  horizontalPositionValueIndex++;
  setHorizontalPosition();
}

void moveUp() {
  verticalPositionValueIndex++;
  setVerticalPosition();
}
void moveDown() {
  verticalPositionValueIndex--;
  setVerticalPosition();
}

void increaseWidth() {
  widthValueIndex++;
  setWidth();
}
void decreaseWidth() {
  widthValueIndex--;
  setWidth();
}

void increaseHeight() {
  heightValueIndex++;
  
  setHeight();
}
void decreaseHeight() {
  heightValueIndex--;
  
  setHeight();
}

void decreaseContrast() {
  contrastValueIndex--;
  setContrast();
}
void increaseContrast() {
  contrastValueIndex++;

  setContrast();
}

void decreaseBrightness() {
  brightnessValueIndex--;
  
  setBrightness();
}
void increaseBrightness() {
  brightnessValueIndex++;
  
  setBrightness();
}


void setVerticalPosition(int value) {
  writeToIvad(monitorAddress, verticalPositionSetting, value);
}
void setVerticalPosition() {
  limitIndex(verticalPositionValueIndex, sizeof(verticalPositionValues));
  int value = verticalPositionValues[verticalPositionValueIndex];

  setVerticalPosition(value);
}

void setHorizontalPosition(int value) {
  writeToIvad(monitorAddress, horizontalPositionSetting, value);
}
void setHorizontalPosition() {
  limitIndex(horizontalPositionValueIndex, sizeof(horizontalPositionValues));
  int value = horizontalPositionValues[horizontalPositionValueIndex];

  setHorizontalPosition(value);
}

void setHeight(int value) {
  writeToIvad(monitorAddress, heightSetting, value);
}
void setHeight() {
  limitIndex(heightValueIndex, sizeof(heightValues));
  int value = heightValues[heightValueIndex];

  setHeight(value);
}

void setWidth(int value) {
  writeToIvad(monitorAddress, widthSetting, value);
}
void setWidth() {
  limitIndex(widthValueIndex, sizeof(widthValues));
  int value = widthValues[widthValueIndex];
  
  setWidth(value);
}

void setContrast(int value) {
  writeToIvad(monitorAddress, contrastSetting, value);
}
void setContrast() {
  limitIndex(contrastValueIndex, sizeof(contrastValues));
  int value = contrastValues[contrastValueIndex];
  
  setContrast(value);
}

void setBrightness(int value) {
  writeToIvad(monitorAddress, brightnessSetting, value);
  writeToIvad(monitorAddress, brightnessSetting, value);
}
void setBrightness() {
  limitIndex(brightnessValueIndex, sizeof(brightnessValues));
  int value = brightnessValues[brightnessValueIndex];
  
  setBrightness(value);
}

void limitIndex(int &index, int array_size) {
  int maximum = ((array_size / sizeof(int)) - 1);
  
  if(index < 0) index = 0;
  if(index > maximum) index = maximum;
}


void setParallelogram(int value) {
  /*
   * Left
   * 0xfe
   * 0xfd
   * 0xfb
   * 0xf8
   * 0xf4
   * 0xef
   * 0xe9
   * 0xe2
   * 0xda
   * 0xd1
   * 0xc8
   * 0xbf
   * 0xb6
   * 0xad
   * 0xa4
   * 0x9b
   * 0x92
   * 0x89
   * 0x80
   * Right
   */
  writeToIvad(monitorAddress, settingParallelogram, value);
}
void setKeystone(int value) {
  /*
   * Thin top
   * 0x81
   * 0x83
   * 0x86
   * 0x8a
   * 0x8f
   * 0x95
   * 0x9c
   * 0xa4
   * 0xad
   * 0xb6
   * 0xbf
   * 0xc8
   * 0xd1
   * 0xda
   * 0xe3
   * 0xec
   * 0xf5
   * 0xfe
   * 0xff
   * Thin Bottom
   */
  writeToIvad(monitorAddress, settingKeystone, value);
}
void setRotation(int value) {
  /*
   * Left
   * 0x7e
   * 0x7c
   * 0x79
   * 0x75
   * 0x70
   * 0x8d
   * 0x63
   * 0x5b
   * 0x52
   * 0x49
   * 0x40
   * 0x37
   * 0x2e
   * 0x25
   * 0x1c
   * 0x13
   * 0x0a
   * 0x01
   * 0x00
   * Right
   */
  writeToIvad(monitorAddress, settingRotation, value);
}
void setPincushion(int value) {
  /*
   * Concave
   * 0x81
   * 0x83
   * 0x86
   * 0x8a
   * 0x8f
   * 0x95
   * 0x9c
   * 0xa4
   * 0xad
   * 0xb6
   * 0xbf
   * 0xc8
   * 0xd1
   * 0xda
   * 0xe3
   * 0xec
   * 0xf5
   * 0xfe
   * 0xff
   * Convex
   */
  writeToIvad(monitorAddress, settingPincushion, value);
}
