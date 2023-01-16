#ifndef FCU_SPEED_DISPLAYER_H
#define FCU_SPEED_DISPLAYER_H

#include "Displayer.h"

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
        bool _isSpeedHidden;
        bool _isSpeedForced;
};

#endif