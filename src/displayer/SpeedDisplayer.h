#ifndef FCU_SPEED_DISPLAYER_H
#define FCU_SPEED_DISPLAYER_H

#include "Displayer.h"

class SpeedDisplayer : public Displayer {

    public:
        SpeedDisplayer(Adafruit_SSD1306 *screen, short indexDisplay, short x_offset, short y_offset);

        void display(FcuDisplayFrame *frame);
        bool checkMutation(FcuDisplayFrame *frame);

    private:
        bool _isMachSpeed; 
        unsigned short _speed; 
        bool _isSpeedHidden;
        bool _isSpeedForced;
};

#endif