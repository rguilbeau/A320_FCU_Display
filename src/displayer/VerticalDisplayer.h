#ifndef FCU_VERTICAL_DISPLAYER_H
#define FCU_VERTICAL_DISPLAYER_H

#include "Setup.h"
#include "A320_Displayer/Displayer.h"
#include "A320_Core/can_bus/frame/glareshield/FcuDisplayFrame.h"

class VerticalDisplayer : public Displayer {

    public:
        VerticalDisplayer(Adafruit_SSD1306 *screen, short indexDisplay);

        void display(FcuDisplayFrame *frame);
        void displayTest();

        bool checkMutation(FcuDisplayFrame *frame);

    private:

        void printFixedIndicator();
        void printVsSpeedIndicator();
        void printFpaIndicator();
        void printDigit(String digit);

        bool _isFpa;
        float _verticalSpeed;
        bool _isVerticalSpeedPositive;
        bool _isVerticalSpeedDash;
};

#endif