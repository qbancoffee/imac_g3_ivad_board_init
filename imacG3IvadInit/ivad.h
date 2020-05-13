
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

  IVAD_SETTING_CONTRAST,      // = 0x00
  IVAD_SETTING_RESERVED1,     // = 0x01
  IVAD_SETTING_RESERVED2,     // = 0x02
  IVAD_SETTING_RESERVED3,     // = 0x03
  IVAD_SETTING_RED,           // = 0x04
  IVAD_SETTING_GREEN,         // = 0x05
  IVAD_SETTING_BLUE,          // = 0x06
  IVAD_SETTING_HORIZONTAL_POS,// = 0x07
  IVAD_SETTING_HEIGHT,        // = 0x08
  IVAD_SETTING_VERTICAL_POS,  // = 0x09
  IVAD_SETTING_RESERVED4,     // = 0x0A
  IVAD_SETTING_KEYSTONE,      // = 0x0B
  IVAD_SETTING_PINCUSHION,    // = 0x0C
  IVAD_SETTING_WIDTH,         // = 0x0D
  IVAD_SETTING_RESERVED5,     // = 0x0E
  IVAD_SETTING_PARALLELOGRAM, // = 0x0F
  IVAD_SETTING_RESERVED6,     // = 0x10
  IVAD_SETTING_BRIGHTNESS,    // = 0x11
  IVAD_SETTING_ROTATION,      // = 0x12
  IVAD_SETTING_END            // always last
};



const byte VIDEO_CONFIG_DEFAULT[] =
{
  0xFE, //CONTRAST
  0x93, //RESERVED1
  0x93, //RESERVED2
  0x8F, //RESERVED3
  0x80, //RED
  0xB0, //GREEN
  0x78, //BLUE
  0xB0, //HORIZONTAL_POS
  0xF0, //HEIGHT
  0x4D, //VERTICAL_POS
  0x9A, //RESERVED4
  0x9B, //KEYSTONE
  0xCB, //PINCUSHION
  0x19, //WIDTH
  0x7B, //RESERVED5
  0xC6, //PARALLELOGRAM
  0x7B, //RESERVED6
  0x0A, //BRIGHTNESS
  0x42, //ROTATION
};

const byte VIDEO_CONFIG_MIN[] =
{
  0xB5, //CONTRAST
  0x93, //RESERVED1
  0x93, //RESERVED2
  0x8F, //RESERVED3
  0x00, //RED
  0x00, //GREEN
  0x00, //BLUE
  0x80, //HORIZONTAL_POS
  0x80, //HEIGHT
  0x01, //VERTICAL_POS
  0x9A, //RESERVED4
  0x80, //KEYSTONE
  0x80, //PINCUSHION
  0x01, //WIDTH
  0x7B, //RESERVED5
  0x80, //PARALLELOGRAM
  0x7B, //RESERVED6
  0x00, //BRIGHTNESS
  0x01  //ROTATION
};


const byte VIDEO_CONFIG_MAX[] =
{
  0xFF, //CONTRAST
  0x93, //RESERVED1
  0x93, //RESERVED2
  0x8F, //RESERVED3
  0xFF, //RED
  0xFF, //GREEN
  0xFF, //BLUE
  0xFE, //HORIZONTAL_POS
  0xFE, //HEIGHT
  0x7F, //VERTICAL_POS
  0x9A, //RESERVED4
  0xFE, //KEYSTONE
  0xFE, //PINCUSHION
  0x7F, //WIDTH
  0x7B, //RESERVED5
  0xFE, //PARALLELOGRAM
  0x7B, //RESERVED6
  0x32, //BRIGHTNESS
  0x7F  //ROTATION
};
