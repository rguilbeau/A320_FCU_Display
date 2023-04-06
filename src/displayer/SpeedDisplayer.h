#ifndef FCU_SPEED_DISPLAYER_H
#define FCU_SPEED_DISPLAYER_H

#include "Setup.h"
#include "core/displayer/Displayer.h"
#include "core/can_bus/frame/glareshield/FcuDisplayFrame.h"

class SpeedDisplayer : public Displayer {

    public:
        SpeedDisplayer(Adafruit_SSD1306 *screen, short indexDisplay);

        void display(FcuDisplayFrame *frame);
        void displayTest();

        bool checkMutation(FcuDisplayFrame *frame);

    private:

        void printSpeedIndicator();
        void printMachIndicator();
        void printDigit(String digit);

        bool _isMachSpeed; 
        float _speed; 
        bool _isSpeedDash;
        bool _isSpeedDot;
};

#endif