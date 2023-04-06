#ifndef FCU_DISPLAY_FRAME
#define FCU_DISPLAY_FRAME

#include "Arduino.h"
#include "can.h"

class FcuDisplayFrame {

    public:

        FcuDisplayFrame();

        void decode(struct can_frame *frame);

        static void binaryConvert(int decimal, bool binaryArray[]);

        bool isMachSpeed;
        bool isTrackMode;
        bool isLatNavigation;
        bool isFpa;
        bool isSpeedDot;
        bool isHeadingDot;
        bool isAltitudeDot;
        bool isVerticalSpeedPositive;
        bool isPowerOn;
    
        float speed;
        unsigned short heading;

        int altitude;

        float verticalSpeed;
        bool isSpeedDash;
        bool isHeadingDash;
        bool isAltitudeDash;
        bool isVerticalSpeedDash;        

};

#endif