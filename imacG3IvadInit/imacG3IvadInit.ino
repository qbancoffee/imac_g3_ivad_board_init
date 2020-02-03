



#include <Wire.h>

//define relay and power button pins
int relay1OnPin = 7;
int relay1OffPin = 6;
int relay2OnPin = 5;
int relay2OffPin = 4;
int powerButtonPin = 3;


//define state variables
int externalCircuitState = LOW;
int buttonState = LOW;

//counters
int buttonPressedTime = 0;


void setup() {

  //define pin direction
  pinMode(relay1OnPin, OUTPUT);
  pinMode(relay1OffPin, OUTPUT);
  pinMode(relay2OnPin, OUTPUT);
  pinMode(relay2OffPin, OUTPUT);
  pinMode(powerButtonPin, INPUT);

  Wire.begin(); // join i2c bus (address optional for master)
  // turn off raspberry pi, audio board and CRT
  externalCircuitOff();
  delay(4000);
  initIvadBoard();
}

byte x = 0;

void loop() {
  buttonState = digitalRead(powerButtonPin);


  if (buttonState == LOW)
  {
    buttonPressedTime++;
    //  Serial.println("HIGH");

  }
  else
  {
    buttonPressedTime = 0;

  }
  delay(1000);

  //turn everything off if button is pressed for 3 seconds
  if (buttonPressedTime >= 3 && externalCircuitState == HIGH) {
    externalCircuitOff();
    buttonPressedTime = 0;

  }

  //turn everything on if button is pressed for 1 second
  if (buttonPressedTime >= 2 && externalCircuitState == LOW) {
    externalCircuitOn();
    delay(5000);
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
  //return buf;


}//end method


void initIvadBoard() {




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


void relay1On() {
  digitalWrite(relay1OnPin, HIGH);
  delay(2000);
  digitalWrite(relay1OnPin, LOW);

}

void relay1Off() {
  digitalWrite(relay1OffPin, HIGH);
  delay(200);
  digitalWrite(relay1OffPin, LOW);

}

void relay2On() {
  digitalWrite(relay2OnPin, HIGH);
  delay(200);
  digitalWrite(relay2OnPin, LOW);

}

void relay2Off() {
  digitalWrite(relay2OffPin, LOW);
  delay(2000);
  digitalWrite(relay2OffPin, HIGH);

}


void externalCircuitOn() {
  relay1On();
  //relay2On();
  externalCircuitState = HIGH;

}
void externalCircuitOff() {
  //relay1Off();
  relay2Off();
  externalCircuitState = LOW;

}
