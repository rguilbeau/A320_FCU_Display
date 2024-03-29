#ifndef FCU_HEADING_DISPLAYER_H
#define FCU_HEADING_DISPLAYER_H

#include "Setup.h"
#include "A320_Displayer/Displayer.h"
#include "A320_Core/can_bus/frame/glareshield/FcuDisplayFrame.h"

class HeadingDisplayer : public Displayer {

    public:
        HeadingDisplayer(Adafruit_SSD1306 *screen, short indexDisplay);

        void display(FcuDisplayFrame *frame);
        void displayTest();

        bool checkMutation(FcuDisplayFrame *frame);

    private:

        void printHeadingIndicator();
        void printTrackIndicator();
        void printLatIndicator();
        void printDigit(String digit);

        bool _isTrackMode;
        bool _isLatNavigation;
        bool _isHeadingDash;
        bool _isHeadingDot;
        unsigned short _heading;

};

#endif