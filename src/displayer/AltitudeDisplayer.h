#ifndef FCU_ALTITUDE_DISPLAYER_H
#define FCU_ALTITUDE_DISPLAYER_H

#include "Setup.h"
#include "A320_Displayer/Displayer.h"
#include "A320_Core/can_bus/frame/glareshield/FcuDisplayFrame.h"

class AltitudeDisplayer : public Displayer {

    public:
        AltitudeDisplayer(Adafruit_SSD1306 *screen, short indexDisplay);

        void display(FcuDisplayFrame *frame);
        void displayTest();

        bool checkMutation(FcuDisplayFrame *frame);
        
    private:
        
        void printFixedIndicator();
        void printDigit(String altitude);

        bool _isAltitudeDash;
        bool _isAltitudeDot;
        int _altitude;
};

#endif