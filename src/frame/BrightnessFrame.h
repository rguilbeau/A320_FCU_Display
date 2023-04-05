#ifndef FCU_BRIGHTNESS_FRAME
#define FCU_BRIGHTNESS_FRAME

#include "Arduino.h"
#include "can.h"

class BrightnessFrame {

    public:

        BrightnessFrame();

        void decode(struct can_frame *frame);

        static void binaryConvert(int decimal, bool binaryArray[]); 

        short fcuDisplayContrast;
};

#endif