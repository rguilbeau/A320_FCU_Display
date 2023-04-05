#ifndef FCU_LIGHT_INDICTORS_FRAME
#define FCU_LIGHT_INDICTORS_FRAME

#include "Arduino.h"
#include "can.h"

class LightIndicatorsFrame {

    public:

        LightIndicatorsFrame();

        void decode(struct can_frame *frame);

        static void binaryConvert(int decimal, bool binaryArray[]); 

        bool isTestLight;
};

#endif