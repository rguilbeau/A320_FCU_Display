#ifndef FCU_DISPLAY_FRAME
#define FCU_DISPLAY_FRAME

#include "Arduino.h"
#include "can.h"

class FcuDisplayFrame {

    public:

        FcuDisplayFrame();

        void decode(struct can_frame *frame);
        bool isMachSpeed;
        bool isTrackMode;
        bool isLatNavigation;
        bool isFpa;
        bool isSpeedForced;
        bool isHeadingForced;
        bool isAltitudeForced;
        bool isVerticalSpeedPositive;
    
        float speed;
        unsigned short heading;

        int altitude;

        float verticalSpeed;
        bool isSpeedHidden;
        bool isHeadingHidden;
        bool isAltitudeHidden;
        bool isVerticalSpeedHidden;

    private:
        static void binaryConvert(int decimal, bool binaryArray[]);

};

#endif