



/*
   This sketch will looks for button presses to turn on/off the
   iMac G3 CRT circuitry and send the init sequence to the IVAD board.
   if you are planning to just send the init sequence on startup, you can 
   uncomment "initIvadBoard();"  in setup()
*/

#include <Wire.h>



//define solid state relay and power button pins
int solid_state_relay_Pin = 7;

//int powerButtonPin = 3;
int powerButtonPin = 13;

//define state variables
int externalCircuitState = LOW;
int buttonState = LOW;


//counters
int buttonPressedTime = 0;


void setup() {

  //define pin direction
  pinMode(solid_state_relay_Pin, OUTPUT);
  pinMode(powerButtonPin, INPUT);



  Wire.begin();
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
  Wire.beginTransmission(address);
  Wire.write(message);
  Wire.endTransmission();

}//end method

void writeToIvad(int address, int message1, int message2) {
  Wire.beginTransmission(address);
  Wire.write(message1);
  Wire.write(message2);
  Wire.endTransmission();

}//end method

void  readFromIvad(int address, int bytes) {
  char buf[bytes + 1];
  int bytesRead = 0;
  Wire.requestFrom(address, bytes);
  while (Wire.available())
  {
    char c = Wire.read();
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
