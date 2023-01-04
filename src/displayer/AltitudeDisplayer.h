#ifndef FCU_ALTITUDE_DISPLAYER_H
#define FCU_ALTITUDE_DISPLAYER_H

#include "Displayer.h"

class AltitudeDisplayer : public Displayer {

    public:
        AltitudeDisplayer(Adafruit_SSD1306 *screen, short indexDisplay, short x_offset, short y_offset);

        void display(FcuDisplayFrame *frame);
        bool checkMutation(FcuDisplayFrame *frame);
        
    private:
        
        bool _isAltitudeHidden;
        bool _isAltitudeForced;
        int _altitude;
};

#endif