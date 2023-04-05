//#define DEBUG

#ifdef DEBUG
    #define SERIAL_BEGIN(x) Serial.begin(x);
    #define SERIAL_PRINTLN(x) Serial.println (x)
#else
    #define SERIAL_BEGIN(x)
    #define SERIAL_PRINTLN(x)
#endif

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
#define X_OFFSET 0
#define Y_OFFSET 6

#define PIN_CANBUS_CS_SPI D8

#define OLED_SPEED_INDEX 3
#define OLED_HEADING_INDEX 4
#define OLED_NAV_MODE_INDEX 5
#define OLED_ALTITUDE_INDEX 6
#define OLED_VERTICAL_INDEX 7

#define FRAME_ID_FCU_DISPLAY 0x101
#define FRAME_ID_LIGHT_INDICATORS 0x201
#define FRAME_ID_BRIGHTNESS 0x001