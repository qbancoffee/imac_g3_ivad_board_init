//properties register address
byte IVAD_REGISTER_PROPERTY = 0x46;
byte IVAD_REGISTER_UNKNOWN  = 0x53;

/*register offsets for the different properties
There are some unknown ones but we know the values
to send. The values range from 0x00 to 0x12 and keeping
them in order on an enum they can also be used as indices
cleaning up code.
*/


enum IVAD_REGISTER_OFFSET : const byte
{
                                   //   OFFSET  MIN  -  MAX
                                   //   ===================
  IVAD_SETTING_CONTRAST,           // = 0x00    0XB5 - 0XFF
  IVAD_SETTING_RED_DRIVE,          // = 0x01    0X00 - 0XFF
  IVAD_SETTING_GREEN_DRIVE,        // = 0x02    0X00 - 0XFF
  IVAD_SETTING_BLUE_DRIVE,         // = 0x03    0X00 - 0XFF
  IVAD_SETTING_RED_CUTOFF,         // = 0x04    0X00 - 0XFF
  IVAD_SETTING_GREEN_CUTOFF,   // = 0x05    0X00 - 0XFF
  IVAD_SETTING_BLUE_CUTOFF,    // = 0x06    0X00 - 0XFF
  IVAD_SETTING_HORIZONTAL_POS,     // = 0x07    0X80 - 0XFF
  IVAD_SETTING_HEIGHT,             // = 0x08    0X80 - 0XFF
  IVAD_SETTING_VERTICAL_POS,       // = 0x09    0X00 - 0X7F
  IVAD_SETTING_S_CORRECTION,       // = 0x0A    0X80 - 0XFF
  IVAD_SETTING_KEYSTONE,           // = 0x0B    0X80 - 0XFF
  IVAD_SETTING_PINCUSHION,         // = 0x0C    0X80 - 0XFF
  IVAD_SETTING_WIDTH,              // = 0x0D    0X00 - 0X7F
  IVAD_SETTING_PINCUSHION_BALANCE, // = 0x0E    0X80 - 0XFF
  IVAD_SETTING_PARALLELOGRAM,      // = 0x0F    0X80 - 0XFF
  IVAD_SETTING_RESERVED6,          // = 0x10
  IVAD_SETTING_BRIGHTNESS,         // = 0x11    0X00 - 0X0A
  IVAD_SETTING_ROTATION,           // = 0x12    0X00 - 0X7F
  IVAD_SETTING_END                 // always last
};



const byte VIDEO_CONFIG_DEFAULT[] =
{
  0xFE, //CONTRAST
  0x93, //RED_DRIVE
  0x93, //GREEN_DRIVE
  0x8F, //BLUE_DRIVE
  0x80, //RED_CUTOFF
  0xB0, //GREEN_CUTOFF
  0x78, //BLUE_CUTOFF
  0xB0, //HORIZONTAL_POS
  0xF0, //HEIGHT
  0x4D, //VERTICAL_POS
  0x9A, //S_CORRECTION
  0x9B, //KEYSTONE
  0xCB, //PINCUSHION
  0x19, //WIDTH
  0x7B, //PINCUSHION_BALANCE
  0xC6, //PARALLELOGRAM
  0x7B, //RESERVED6
  0x0A, //BRIGHTNESS
  0x42, //ROTATION
};

const byte VIDEO_CONFIG_MIN[] =
{
  0xB5, //CONTRAST
  0x00, //RED_DRIVE
  0x00, //GREEN_DRIVE
  0x00, //BLUE_DRIVE
  0x00, //RED_RED_CUTOFF
  0x00, //GREEN_RED_CUTOFF
  0x00, //BLUE_RED_CUTOFF
  0x80, //HORIZONTAL_POS
  0x80, //HEIGHT
  0x00, //VERTICAL_POS
  0x80, //S_CORRECTION
  0x80, //KEYSTONE
  0x80, //PINCUSHION
  0x00, //WIDTH
  0x80, //PINCUSHION_BALANCE
  0x80, //PARALLELOGRAM
  0x7B, //RESERVED6
  0x00, //BRIGHTNESS
  0x00  //ROTATION
};


const byte VIDEO_CONFIG_MAX[] =
{
  0xFF, //CONTRAST
  0xFF, //RED_DRIVE
  0xFF, //GREEN_DRIVE
  0xFF, //BLUE_DRIVE
  0xFF, //RED_RED_CUTOFF
  0xFF, //GREEN_RED_CUTOFF
  0xFF, //BLUE_RED_CUTOFF
  0xFF, //HORIZONTAL_POS
  0xFF, //HEIGHT
  0x7F, //VERTICAL_POS
  0xFF, //S_CORRECTION
  0xFF, //KEYSTONE
  0xFF, //PINCUSHION
  0x7F, //WIDTH
  0xFF, //PINCUSHION_BALANCE
  0xFF, //PARALLELOGRAM
  0x7B, //RESERVED6
  0x0A, //BRIGHTNESS
  0x7F  //ROTATION
};
