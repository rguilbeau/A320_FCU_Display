#ifndef FCU_NAV_MODE_DISPLAYER_H
#define FCU_NAV_MODE_DISPLAYER_H

#include "Displayer.h"

class NavModeDisplayer : public Displayer {

    public:
        NavModeDisplayer(Adafruit_SSD1306 *screen, short indexDisplay);

        void display(FcuDisplayFrame *frame);
        bool checkMutation(FcuDisplayFrame *frame);

    private:
        bool _isTrackMode;
        bool _isFpa;
};

#endif