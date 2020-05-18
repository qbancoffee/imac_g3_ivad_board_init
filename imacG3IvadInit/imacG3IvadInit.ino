
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
#include "imacG3IvadInit.h"
#include <EEPROMWearLevel.h>
#include <SoftwareWire.h>
#include <Wire.h>


//starting monitor property values.
byte verticalPositionValueIndex = 0x4d;//77
byte contrastValueIndex = 0xfe;
byte horizontalPositionValueIndex = 0xb0;//176
byte heightValueIndex = 0xf0;//240
byte widthValueIndex = 0x19;//25
byte brightnessValueIndex = 0x0a;
byte parallelogramValueIndex = 0xc6;//198
byte keystoneValueIndex = 0x9b;//155
byte rotationValueIndex = 0x42;//66
byte pincushionValueIndex = 0xcb;//203

byte SERIAL_BUFFER[SERIAL_BUFFER_MAX_SIZE];
byte SERIAL_BUFFER_DATA_SIZE;
byte CURRENT_CONFIG[CONFIG_EEPROM_SLOTS];
byte FIRST_RUN = 0x79;

byte data = -1;

//define solid state relay and power button pins
byte solid_state_relay_Pin = 7;

byte powerButtonPin = 3;
//int powerButtonPin = 13;

//define state variables
byte externalCircuitState = LOW;
byte buttonState = LOW;

//vsync pin
byte vsyncPin = 8;


//vsync power off countdown in seconds
byte vsync_off_time = 5;

//counters
byte buttonPressedTime = 0;
byte vsyncDetect = 0;
unsigned long currentTime = 0;
unsigned long startTime = 0;
unsigned long elapsedTime = 0;

//The init sequence is sent on a software i2c bus.
// sda is on 4 and scl is on 5
SoftwareWire softWire( 4, 5);




void setup() {

  //define pin direction
  pinMode(solid_state_relay_Pin, OUTPUT);
  pinMode(powerButtonPin, INPUT);
  pinMode(vsyncPin, INPUT);//this pin is on the J5 connector for general use PB0.
  pinMode(9, INPUT);//this pin is on the J5 connector for general use PB1.

  EEPROMwl.begin(CONFIG_EEPROM_VERSION, CONFIG_EEPROM_SLOTS + 1);
  Wire.begin(0x50); //join as slave and wait for EDID requests
  softWire.begin();// join as master and send init sequence
  Serial.begin(115200);//use built in serial
  Serial.setTimeout(1000);

  Wire.onRequest(requestEvent); //event handler for requests from master
  Wire.onReceive(receiveData); // event handler when receiving from  master
  // turn it all off
  externalCircuitOff();

  //check to see if it's the 1st time running after burning firmware
  FIRST_RUN = EEPROMwl.read(CONFIG_EEPROM_SLOTS);
  if (FIRST_RUN != 0x79 ) {
    EEPROMwl.update(CONFIG_EEPROM_SLOTS, 0x79);
    settings_reset_default();
    settings_store();
    settings_load();
    ivad_write_settings();
  }//end if


  //externalCircuitOn();


}//end setup

//byte x = 0;
/*
   This loops looks for button presses, turns the circuit on or off, and
   listens for characters on the serial port to make screen adjustments.
*/
void loop() {

  buttonState = digitalRead(powerButtonPin);

  // do stuff only when the CRT is on
  if ( externalCircuitState == HIGH ) {

    currentTime = millis();
    elapsedTime = currentTime - startTime;


    serial_processing();


    //increment vsyncDetect everytime vsync is detected
    if (pulseIn(vsyncPin, HIGH, 10000) > 0) {

      if (vsyncDetect < vsync_off_time) {
        vsyncDetect++;
      }//end if
      startTime = currentTime = millis();
    }//end if


    //decrement vsyncDetect whenever one second elapses
    if (elapsedTime >= 1000 && vsyncDetect > 0) {
      vsyncDetect--;
      startTime = currentTime = millis();
    }

    //do stuff whn vsyncDetect is 0
    if (vsyncDetect <= 0) {
      startTime = 0;
      currentTime = 0;
      // externalCircuitOff();


    }

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

  //turn everything off if button is pressed for 10 ms
  if (buttonPressedTime > 0 && externalCircuitState == HIGH && buttonState == HIGH) {
    externalCircuitOff();
    buttonPressedTime = 0;

  }

  //turn everything on if button is pressed for 10 ms
  if (buttonPressedTime > 0 && externalCircuitState == LOW  && buttonState == HIGH) {
    externalCircuitOn();
    buttonPressedTime = 0;
    startTime = millis();
    currentTime = millis();
    vsyncDetect = vsync_off_time;

  }




}//end loop



void handleSerial(char incoming) {
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


  //if (Serial.available() > 0) {
  // char incoming = Serial.read();

  int index = -1;
  bool increment = true;
  switch (incoming) {
    case 'a'://move left
      //moveHorizontal(+1);
      index = IVAD_SETTING_HORIZONTAL_POS;
      break;
    case 's'://move right
      //moveHorizontal(-1);
      index = IVAD_SETTING_HORIZONTAL_POS;
      increment = false;
      break;
    case 'w'://move up
      //moveVertical(-1);
      index = IVAD_SETTING_VERTICAL_POS;
      increment = false;
      break;
    case 'z'://move down
      //moveVertical(+1);
      index = IVAD_SETTING_VERTICAL_POS;
      break;
    case 'd'://make skinnier
      //changeWidth(+1);
      index = IVAD_SETTING_WIDTH;
      break;
    case 'f'://make fatter
      //changeWidth(-1);
      index = IVAD_SETTING_WIDTH;
      increment = false;
      break;
    case 'r'://make taller
      //changeHeight(+1);
      index = IVAD_SETTING_HEIGHT;
      break;
    case 'c'://make shorter
      //changeHeight(-1);
      index = IVAD_SETTING_HEIGHT;
      increment = false;
      break;
    case 'g'://decrease contrast
      //changeContrast(-1);
      index = IVAD_SETTING_CONTRAST;
      increment = false;
      break;
    case 'h'://increase contrast
      //changeContrast(+1);
      index = IVAD_SETTING_CONTRAST;
      break;
    case 'j'://decrease brightness
      //changeBrightness(-1);
      index = IVAD_SETTING_BRIGHTNESS;
      increment = false;
      break;
    case 'k'://increase brightness
      // changeBrightness(+1);
      index = IVAD_SETTING_BRIGHTNESS;
      break;
    case 'x'://tilt paralellogram left
      //changeParallelogram(+1);
      index = IVAD_SETTING_PARALLELOGRAM;
      break;
    case 'v'://tilt paralellogram right
      //changeParallelogram(-1);
      index = IVAD_SETTING_PARALLELOGRAM;
      increment = false;
      break;
    case 'b'://keystone pinch top
      //changeKeystone(-1);
      index = IVAD_SETTING_KEYSTONE;
      increment = false;
      break;
    case 'n'://keystone pinch bottom
      //changeKeystone(+1);
      index = IVAD_SETTING_KEYSTONE;
      break;
    case 't'://rotate left
      //changeRotation(+1);
      index = IVAD_SETTING_ROTATION;
      break;
    case 'y'://rotate right
      //changeRotation(-1);
      index = IVAD_SETTING_ROTATION;
      increment = false;
      break;
    case 'u'://pincushion pull corners out
      //changePincushion(-1);
      index = IVAD_SETTING_PINCUSHION;
      increment = false;
      break;
    case 'i'://pincushion pull corners in
      //changePincushion(+1);
      index = IVAD_SETTING_PINCUSHION;
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
  //}

  if (index > -1) {
    int val = CURRENT_CONFIG[index];
    if (increment) {
      val++;
    }
    else
    {
      val--;
    }

    ivad_change_setting(index, val);
  }//end if


}//end handleSerial

void printCurrentSettings() {
  Serial.println(F("----------------------------"));

  Serial.print(F("heightValueIndex: "));
  Serial.println(heightValueIndex, HEX);

  Serial.print(F("widthValueIndex: "));
  Serial.println(widthValueIndex, HEX);

  Serial.println("");

  Serial.print(F("verticalPositionValueIndex: "));
  Serial.println(verticalPositionValueIndex, HEX);

  Serial.print(F("horizontalPositionValueIndex: "));
  Serial.println(horizontalPositionValueIndex, HEX);

  Serial.println(F(""));

  Serial.print(F("rotationValueIndex: "));
  Serial.println(rotationValueIndex, HEX);

  Serial.print(F("parallelogramValueIndex: "));
  Serial.println(parallelogramValueIndex, HEX);

  Serial.print(F("keystoneValueIndex: "));
  Serial.println(keystoneValueIndex, HEX);

  Serial.print(F("pincushionValueIndex: "));
  Serial.println(pincushionValueIndex, HEX);

  Serial.println("");

  Serial.print(F("contrastValueIndex: "));
  Serial.println(contrastValueIndex, HEX);

  Serial.print(F("brightnessValueIndex: "));
  Serial.println(brightnessValueIndex, HEX);

  Serial.println(F("----------------------------"));

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

  //init sequence 2 <---this is the one that works well with my iMac G3, Rocky Hill
  writeToIvad( IVAD_REGISTER_PROPERTY, 0x13, 0x00);
  readFromIvad(IVAD_REGISTER_PROPERTY, 1);
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_VERTICAL_POS, 0x00);
  writeToIvad( 0x53, 0x33);
  readFromIvad(0x53, 1);
  writeToIvad( IVAD_REGISTER_PROPERTY, 0x13, 0x0B);
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_CONTRAST, 0x00); //setting contrast to 0x00 seems to turn something on.
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_HEIGHT, 0xE4);
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_ROTATION, 0xC9);
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
  writeToIvad( IVAD_REGISTER_PROPERTY, 0x04, 0x80);//red x-30
  writeToIvad( IVAD_REGISTER_PROPERTY, 0x05, 0xB0);// green x
  writeToIvad( IVAD_REGISTER_PROPERTY, 0x06, 0x78); //blue x-38
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_HORIZONTAL_POS, horizontalPositionValueIndex); //horizontal position
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_HEIGHT, heightValueIndex);
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_VERTICAL_POS, verticalPositionValueIndex);
  writeToIvad( IVAD_REGISTER_PROPERTY, 0x0A, 0x9E);
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_KEYSTONE, keystoneValueIndex);
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_PINCUSHION, pincushionValueIndex);
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_WIDTH, widthValueIndex);
  writeToIvad( IVAD_REGISTER_PROPERTY, 0x0E, 0xC0);
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_PARALLELOGRAM, parallelogramValueIndex);
  writeToIvad( IVAD_REGISTER_PROPERTY, 0x10, 0x40); // brightness
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_BRIGHTNESS, brightnessValueIndex);
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_ROTATION, rotationValueIndex); // rotation
  writeToIvad( IVAD_REGISTER_PROPERTY, IVAD_SETTING_CONTRAST, contrastValueIndex);





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
  delay(500);
  initIvadBoard();
  settings_load();
  ivad_write_settings();
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


/*
  This is my implementation of oshimai's communications protocol.
  Clearly I borrowed heavily from his sketch and I purposely
  kept the same variable names to make it easier to port any
  changes he might make to his sletch. There are parts I didn't
  bother to port, verifying the checksum for example because of
  time constraints. I might implement the rest in the future.

*/
void serial_processing()
{

  byte b ;

  if (Serial.available()) {

    do
    {
      b = Serial.read();
      SERIAL_BUFFER[SERIAL_BUFFER_DATA_SIZE++] = b;
    }
    while (Serial.available() &&  b != SERIAL_EOL_MARKER);


    //call other serial handler
    if (SERIAL_BUFFER_DATA_SIZE != 9)
    {
      if (SERIAL_BUFFER[0] != 0x07) {
        SERIAL_BUFFER_DATA_SIZE = 0;
        handleSerial((char)b);
      }
      return;

    }


    SERIAL_BUFFER_DATA_SIZE = 0;

    byte id = SERIAL_BUFFER[1];
    byte cmd = SERIAL_BUFFER[2];
    byte valA = SERIAL_BUFFER[3];
    byte valB = SERIAL_BUFFER[4];

    switch (cmd)
    {

      case 0x01: // Get EEPROM Version
        {
          byte ret[8] { 0x06, id, 0x01, CONFIG_EEPROM_VERSION, 0x03, 0xFF, 0x04, SERIAL_EOL_MARKER };
          ret[5] = checksum(ret, 5);
          Serial.write(ret, 8);
        }
        break;

      case 0x02: // Dump SRAM Config
        {
          byte ret[7 + CONFIG_EEPROM_SLOTS];
          ret[0] = 0x06;
          ret[1] = SERIAL_BUFFER[1];
          ret[2] = CONFIG_EEPROM_SLOTS;

          for (int i = 0; i < CONFIG_EEPROM_SLOTS; i++)
            ret[3 + i] = CURRENT_CONFIG[i];

          ret[2 + CONFIG_EEPROM_SLOTS + 1] = 0x03;
          ret[2 + CONFIG_EEPROM_SLOTS + 2] = checksum(ret, 2 + CONFIG_EEPROM_SLOTS + 1 + 1);
          ret[2 + CONFIG_EEPROM_SLOTS + 3] = 0x04;
          ret[2 + CONFIG_EEPROM_SLOTS + 4] = SERIAL_EOL_MARKER;
          Serial.write(ret, 7 + CONFIG_EEPROM_SLOTS);
        }
        break;

      case 0x03: // IVAD Change Setting
        {
          ivad_change_setting(valA, valB);
          byte ret[7] { 0x06, id, 0x00, 0x03, 0xFF, 0x04, SERIAL_EOL_MARKER };
          ret[4] = checksum(ret, 4);
          Serial.write(ret, 7);
        }
        break;

      case 0x04: // IVAD Reset from EEPROM
        {
          settings_load();
          byte ret[7] { 0x06, id, 0x00, 0x03, 0xFF, 0x04, SERIAL_EOL_MARKER };
          ret[4] = checksum(ret, 4);
          Serial.write(ret, 7);
        }
        break;

      case 0x05: // EEPROM Reset to Default
        {
          settings_reset_default();
          settings_store();
          settings_load();
          ivad_write_settings();
          byte ret[7] { 0x06, id, 0x00, 0x03, 0xFF, 0x04, SERIAL_EOL_MARKER };
          ret[4] = checksum(ret, 4);
          Serial.write(ret, 7);
        }
        break;

      case 0x06: // Write SRAM to EEPROM
        {
          settings_store();
          byte ret[7] { 0x06, id, 0x00, 0x03, 0xFF, 0x04, SERIAL_EOL_MARKER };
          ret[4] = checksum(ret, 4);
          Serial.write(ret, 7);
        }
    }//end switch

    SERIAL_BUFFER[1] = 0xFF;

  }

}//end if









//===================================



byte checksum(const byte arr[], const int len)
{
  int sum = 1; // Checksum may never be 0.

  for (int i = 0; i < len; i++)
    sum += arr[i];

  byte ret = 256 - (sum % 256);

  return ret;
}




int ivad_change_setting(const int ivad_setting,  const byte value)
{

  CURRENT_CONFIG[ivad_setting] = value;

  if (CURRENT_CONFIG[ivad_setting] < VIDEO_CONFIG_MIN[ivad_setting]) CURRENT_CONFIG[ivad_setting] = VIDEO_CONFIG_MIN[ivad_setting];
  if (CURRENT_CONFIG[ivad_setting] > VIDEO_CONFIG_MAX[ivad_setting]) CURRENT_CONFIG[ivad_setting] = VIDEO_CONFIG_MAX[ivad_setting];

  writeToIvad(IVAD_REGISTER_PROPERTY, ivad_setting, CURRENT_CONFIG[ivad_setting]);
  CURRENT_CONFIG[CONFIG_OFFSET_CHECKSUM] = checksum(CURRENT_CONFIG, CONFIG_EEPROM_SLOTS - 1);

  return 0;
}



/*
  This function loads the monitor property values from the EEPROM
  into variables.
*/
void settings_load()
{
  // Set something so a checksum mismatch can trigger if there's nothing in the EEPROM.

  for (byte eeprom_memory_offset = 0 ; eeprom_memory_offset < CONFIG_EEPROM_SLOTS ; eeprom_memory_offset++) {
    CURRENT_CONFIG[eeprom_memory_offset] = EEPROMwl.read(eeprom_memory_offset);
  }//end for

  byte loaded_checksum = CURRENT_CONFIG[CONFIG_OFFSET_CHECKSUM];
  byte expected_checksum = checksum(CURRENT_CONFIG, CONFIG_EEPROM_SLOTS - 1);

  if (loaded_checksum != expected_checksum)
  {
    //settings_reset_default();
    settings_store();


  }


}

void ivad_write_settings()
{

  for (int IVAD_SETTING = 0 ; IVAD_SETTING < IVAD_SETTING_END ;  IVAD_SETTING ++ )
  {
    writeToIvad(IVAD_REGISTER_PROPERTY, IVAD_SETTING, CURRENT_CONFIG[IVAD_SETTING]);
  }

}



void settings_store()
{

  //compute current config checksum and store it.
  byte current_config_checksum = checksum(CURRENT_CONFIG, CONFIG_EEPROM_SLOTS - 1);

  CURRENT_CONFIG[CONFIG_OFFSET_CHECKSUM] = current_config_checksum;

  for (byte eeprom_memory_offset = 0 ; eeprom_memory_offset < CONFIG_EEPROM_SLOTS ; eeprom_memory_offset++) {
    EEPROMwl.update(eeprom_memory_offset, CURRENT_CONFIG[eeprom_memory_offset]);
  }//end for


}


void settings_reset_default()
{

  //compute current config checksum and store it.
  byte current_config_checksum = checksum(CURRENT_CONFIG, CONFIG_EEPROM_SLOTS - 1);

  CURRENT_CONFIG[CONFIG_OFFSET_CHECKSUM] = current_config_checksum;

  for (byte eeprom_memory_offset = 0 ; eeprom_memory_offset < CONFIG_EEPROM_SLOTS ; eeprom_memory_offset++) {
    CURRENT_CONFIG[eeprom_memory_offset] = VIDEO_CONFIG_DEFAULT[eeprom_memory_offset];
  }//end for



}
