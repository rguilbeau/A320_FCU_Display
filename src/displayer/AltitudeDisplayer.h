#ifndef FCU_ALTITUDE_DISPLAYER_H
#define FCU_ALTITUDE_DISPLAYER_H

#include "Displayer.h"

class AltitudeDisplayer : public Displayer {

    public:
        AltitudeDisplayer(Adafruit_SSD1306 *screen, short indexDisplay);

        void display(FcuDisplayFrame *frame);
        void displayTest();

        bool checkMutation(FcuDisplayFrame *frame);
        
    private:
        
        void printFixedIndicator();
        void printDigit(String altitude);

        bool _isAltitudeHidden;
        bool _isAltitudeForced;
        int _altitude;
};

#endif