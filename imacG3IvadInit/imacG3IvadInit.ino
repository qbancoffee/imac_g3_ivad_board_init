
//Rocky Hill


/*
   This sketch waits for button presses to turn on/off the iMac G3 CRT
   circuitry and send the init sequence to the IVAD board.
   if you are planning to just send the init sequence on startup, you
   can uncomment "initIvadBoard();"  in setup(). It uses software i2c
   lines.

   it also sends edid information when requested via i2c on port 0x50.
   The Edid information is for an iMac G3 DV and it sends the three
   supported modes.

   1024x768 @ 75 Hz
   800x600 @ 95 Hz
   640x480 @ 117 Hz

   In order for this program to work, the i2c transmit buffer length
   constants must be changed in two files. The Wire library has two
   buffers it uses for i2c transmissions

   "BUFFER_LENGTH" in
   "arduino_install_folder/hardware/arduino/avr/libraries/Wire/src/Wire.h"

   and

   "TWI_BUFFER_LENGTH" in
   "arduino_install_folder/hardware/arduino/avr/libraries/Wire/src/utility/twi.h"

   Both of these must be changed from 32 to 128 to be able to transmit
   the edid byte array in one shot.

   To test this program, you can directly wire SDA(pin 12),SCL(pin 15)
   and GND(pin 6) pins from your computers VGA portbdirectly into the
   corresponding pins on the arduino.


*/


/*
  Uses SoftwareWire from the arduino libraries. install with library
  manager or from https://github.com/Testato/SoftwareWire
*/

#include "ivad.h"
#include <SoftwareWire.h>
#include <Wire.h>

byte data = -1;


//starting indices for byte arrays that hold the monitor property values.
byte verticalPositionValueIndex = 59;
byte contrastValueIndex = 72;
byte horizontalPositionValueIndex = 83;
byte heightValueIndex = 94;
byte widthValueIndex = 127;
byte brightnessValueIndex = 10;
byte parallelogramValueIndex = 66;
byte keystoneValueIndex = 25;
byte rotationValueIndex = 9;
byte pincushionValueIndex = 83;


//define solid state relay and power button pins
byte solid_state_relay_Pin = 7;

byte powerButtonPin = 3;
//int powerButtonPin = 13;

//define state variables
byte externalCircuitState = LOW;
byte buttonState = LOW;


//counters
byte buttonPressedTime = 0;

//The init sequence is sent on a software i2c bus.
// sda is on 4 and scl is on 5
SoftwareWire softWire( 4, 5);



void handleSerial() {
  /*
     a = move left
     s = move right
     w = move up
     z = move down

     d = skinnier
     f = fatter
     r = taller
     c = shorter

     g = contrast down
     h = contrast up

     j = brightness down
     k = brightness up


  */


  if (Serial.available() > 0) {
    char incoming = Serial.read();

    switch (incoming) {
      case 'a'://move left
        moveHorizontal(-1);
        break;
      case 's'://move right
        moveHorizontal(+1);
        break;
      case 'w'://move up
        moveVertical(+1);
        break;
      case 'z'://move down
        moveVertical(-1);
        break;
      case 'd'://make skinnier
        changeWidth(-1);
        break;
      case 'f'://make fatter
        changeWidth(+1);
        break;
      case 'r'://make taller
        changeHeight(+1);
        break;
      case 'c'://make shorter
        changeHeight(-1);
        break;
      case 'g'://decrease contrast
        changeContrast(-1);
        break;
      case 'h'://increase contrast
        changeContrast(+1);
        break;
      case 'j'://decrease brightness
        changeBrightness(-1);
        break;
      case 'k'://increase brightness
        changeBrightness(+1);
        break;
      case 'x'://tilt paralellogram left
        changeParallelogram(-1);
        break;
      case 'v'://tilt paralellogram right
        changeParallelogram(+1);
        break;
      case 'b'://keystone pinch top
        changeKeystone(-1);
        break;
      case 'n'://keystone pinch bottom
        changeKeystone(+1);
        break;
      case 't'://rotate left
        changeRotation(-1);
        break;
      case 'y'://rotate right
        changeRotation(+1);
        break;
      case 'u'://pincushion pull corners out
        changePincushion(-1);
        break;
      case 'i'://pincushion pull corners in
        changePincushion(+1);
        break;
      case 'p':
        printCurrentSettings();
        break;
      case 'o'://power off
        if ( externalCircuitState == HIGH ) {
          externalCircuitOff();
        }//end if
        break;
    }
  }
}

void printCurrentSettings() {
  Serial.println("----------------------------");

  Serial.print("heightValueIndex: ");
  Serial.println(heightValueIndex);

  Serial.print("widthValueIndex: ");
  Serial.println(widthValueIndex);

  Serial.println("");

  Serial.print("verticalPositionValueIndex: ");
  Serial.println(verticalPositionValueIndex);

  Serial.print("horizontalPositionValueIndex: ");
  Serial.println(horizontalPositionValueIndex);

  Serial.println("");

  Serial.print("rotationValueIndex: ");
  Serial.println(rotationValueIndex);

  Serial.print("parallelogramValueIndex: ");
  Serial.println(parallelogramValueIndex);

  Serial.print("keystoneValueIndex: ");
  Serial.println(keystoneValueIndex);

  Serial.print("pincushionValueIndex: ");
  Serial.println(pincushionValueIndex);

  Serial.println("");

  Serial.print("contrastValueIndex: ");
  Serial.println(contrastValueIndex);

  Serial.print("brightnessValueIndex: ");
  Serial.println(brightnessValueIndex);

  Serial.println("----------------------------");
}

void writeToIvad(byte address, byte message) {
  softWire.beginTransmission(address);
  softWire.write(message);
  softWire.endTransmission();

}//end method

void writeToIvad(byte address, byte message1, byte message2) {
  softWire.beginTransmission(address);
  softWire.write(message1);
  softWire.write(message2);
  softWire.endTransmission();

}//end method

void  readFromIvad(byte address, byte bytes) {
  char buf[bytes + 1];
  byte bytesRead = 0;
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
   //Provied by Rocky Hill
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
   
   
// init sequence 2 provided by sparpet.
//https://forums.macrumors.com/threads/imac-g3-mod-video-connector.1712095/post-25819428   
/**
  writeToIvad( 0x46, 0x13,0x00);
  readFromIvad(0x46, 1);
  writeToIvad( 0x46, 0x09, 0x00);
  writeToIvad( 0x53, 0x33);
  readFromIvad(0x53, 1);
  writeToIvad( 0x46, 0x13,0x0B);
  writeToIvad( 0x46, 0x00,0x00);
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
  writeToIvad( 0x46, 0x01, 0x98);
  writeToIvad( 0x46, 0x02, 0x88);
  writeToIvad( 0x46, 0x03, 0x88);
  writeToIvad( 0x46, 0x04, 0x97);
  writeToIvad( 0x46, 0x05, 0x78);
  writeToIvad( 0x46, 0x06, 0x80);
  writeToIvad( 0x46, 0x07, 0xB0);
  writeToIvad( 0x46, 0x08, 0xEF);
  writeToIvad( 0x46, 0x09, 0x49);
  writeToIvad( 0x46, 0x0A, 0x9E);
  writeToIvad( 0x46, 0x0B, 0x93);
  writeToIvad( 0x46, 0x0C, 0xCA);
  writeToIvad( 0x46, 0x0D, 0x09);
  writeToIvad( 0x46, 0x0E, 0xC0);
  writeToIvad( 0x46, 0x0F, 0xC1);
  writeToIvad( 0x46, 0x10, 0x40);
  writeToIvad( 0x46, 0x11, 0x09);
  writeToIvad( 0x46, 0x12, 0x7D);
  writeToIvad( 0x46, 0x00, 0xFF);
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
  writeToIvad( PROPERTY, 0x13, 0x00);
  readFromIvad(PROPERTY, 1);
  writeToIvad( PROPERTY, VERTICAL_POS, 0x00);
  writeToIvad( 0x53, 0x33);
  readFromIvad(0x53, 1);
  writeToIvad( PROPERTY, 0x13, 0x0B);
  writeToIvad( PROPERTY, CONTRAST, 0x00); //setting contrast to 0x00 seems to turn something on.
  //writeToIvad( PROPERTY, HEIGHT, 0xE4);
  //writeToIvad( PROPERTY, ROTATION, 0xC9);
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

  writeToIvad( PROPERTY, 0x04, 0x80);//red x-30
  writeToIvad( PROPERTY, 0x05, 0xB0);// green x
  writeToIvad( PROPERTY, 0x06, 0x78); //blue x-38
  writeToIvad( PROPERTY, HORIZONTAL_POS, HORIZONTAL_POS_VAL[horizontalPositionValueIndex]); //horizontal position
  writeToIvad( PROPERTY, HEIGHT, HEIGHT_VAL[heightValueIndex]);
  writeToIvad( PROPERTY, VERTICAL_POS, VERTICAL_POS_VAL[verticalPositionValueIndex]);
  writeToIvad( PROPERTY, 0x0A, 0x9E);
  writeToIvad( PROPERTY, KEYSTONE, KEYSTONE_VAL[keystoneValueIndex]);
  writeToIvad( PROPERTY, PINCUSHION, PINCUSHION_VAL[pincushionValueIndex]);
  writeToIvad( PROPERTY, WIDTH, WIDTH_VAL[widthValueIndex]);
  writeToIvad( PROPERTY, 0x0E, 0xC0);
  writeToIvad( PROPERTY, PARALLELOGRAM, PARALLELOGRAM_VAL[parallelogramValueIndex]);
  writeToIvad( PROPERTY, 0x10, 0x40); // brightness
  writeToIvad( PROPERTY, BRIGHTNESS, BRIGHTNESS_VAL[brightnessValueIndex]);
  writeToIvad( PROPERTY, ROTATION, ROTATION_VAL[rotationValueIndex]); // rotation
  writeToIvad( PROPERTY, CONTRAST, CONTRAST_VAL[contrastValueIndex]);





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


void receiveData(byte byteCount) {


  while (Wire.available()) {
    data = Wire.read();
  }
}


//the following methods change picture properties

void moveHorizontal(int off) {
  horizontalPositionValueIndex += off;
  limitIndex(horizontalPositionValueIndex, sizeof(HORIZONTAL_POS_VAL));
  byte value = HORIZONTAL_POS_VAL[horizontalPositionValueIndex];
  writeToIvad(PROPERTY, HORIZONTAL_POS, value);
}//end moveHorizontal

void moveVertical(int off) {
  verticalPositionValueIndex += off;
  limitIndex(verticalPositionValueIndex, sizeof(VERTICAL_POS_VAL));
  byte value = VERTICAL_POS_VAL[verticalPositionValueIndex];
  writeToIvad(PROPERTY, VERTICAL_POS, value);
}//end move vertical

void changeWidth(int off) {
  widthValueIndex += off;
  limitIndex(widthValueIndex, sizeof(WIDTH_VAL));
  byte value = WIDTH_VAL[widthValueIndex];
  writeToIvad(PROPERTY, WIDTH, value);
}//end changeWidth

void changeHeight(int off) {
  heightValueIndex += off;
  limitIndex(heightValueIndex, sizeof(HEIGHT_VAL));
  byte value = HEIGHT_VAL[heightValueIndex];
  writeToIvad(PROPERTY, HEIGHT, value);
}//end changeHeight

void changeContrast(int off) {
  contrastValueIndex += off;
  limitIndex(contrastValueIndex, sizeof(CONTRAST_VAL));
  byte value = CONTRAST_VAL[contrastValueIndex];
  writeToIvad(PROPERTY, CONTRAST, value);
}//end changeContrast

void changeBrightness(int off) {
  brightnessValueIndex += off;
  limitIndex(brightnessValueIndex, sizeof(BRIGHTNESS_VAL));
  byte value = BRIGHTNESS_VAL[brightnessValueIndex];
  writeToIvad(PROPERTY, BRIGHTNESS, value);
}//end changeBrightness

void changeParallelogram(int off) {
  parallelogramValueIndex += off;
  limitIndex(parallelogramValueIndex, sizeof(PARALLELOGRAM_VAL));
  byte value = PARALLELOGRAM_VAL[parallelogramValueIndex];
  writeToIvad(PROPERTY, PARALLELOGRAM, value);
}

void changeKeystone(int off) {
  keystoneValueIndex += off;
  limitIndex(keystoneValueIndex, sizeof(KEYSTONE_VAL));
  byte value = KEYSTONE_VAL[keystoneValueIndex];
  writeToIvad(PROPERTY, KEYSTONE, value);
}

void changeRotation(int off) {
  rotationValueIndex += off;
  limitIndex(rotationValueIndex, sizeof(ROTATION_VAL));
  byte value = ROTATION_VAL[rotationValueIndex];
  writeToIvad(PROPERTY, ROTATION, value);
}

void changePincushion(int off) {
  pincushionValueIndex += off;
  limitIndex(pincushionValueIndex, sizeof(PINCUSHION_VAL));
  byte value = PINCUSHION_VAL[pincushionValueIndex];
  writeToIvad(PROPERTY, PINCUSHION, value);
}

void limitIndex(byte &index, byte array_size) {
  byte maximum = ((array_size / sizeof(byte)) - 1);

  if (index < 0) index = 0;
  if (index > maximum) index = maximum;
}


void setup() {

  //define pin direction
  pinMode(solid_state_relay_Pin, OUTPUT);
  pinMode(powerButtonPin, INPUT);
  pinMode(14, INPUT);//this pin is on the J5 connector for general use.
  pinMode(15, INPUT);//this pin is on the J5 connector for general use.

  Wire.begin(0x50); //join as slave and wait for EDID requests
  softWire.begin();// join as master and send init sequence
  Serial.begin(9600);//use built in serial

  Wire.onRequest(requestEvent); //event handler for requests from master
  Wire.onReceive(receiveData); // event handler when receiving from  master
  // turn it all off
  externalCircuitOff();

  //initIvadBoard();


}//end setup

byte x = 0;
/*
   This loops looks for button presses, turns the circuit on or off, and
   listens for characters on the serial port to make screen adjustments.
*/
void loop() {
  buttonState = digitalRead(powerButtonPin);

  if ( externalCircuitState == HIGH ) {
    handleSerial();
  }//end if


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




}//end loop
