#ifndef FCU_HEADING_MODE_DISPLAYER_H
#define FCU_HEADING_MODE_DISPLAYER_H

#include "Displayer.h"

class HeadingModeDisplayer : public Displayer {

    public:
        HeadingModeDisplayer(Adafruit_SSD1306 *screen, short indexDisplay, short x_offset, short y_offset);

        void display(FcuDisplayFrame *frame);
        bool checkMutation(FcuDisplayFrame *frame);

    private:
        bool _isTrackMode;
};

#endif