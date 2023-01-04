#ifndef FCU_HEADING_DISPLAYER_H
#define FCU_HEADING_DISPLAYER_H

#include "Displayer.h"

class HeadingDisplayer : public Displayer {

    public:
        HeadingDisplayer(Adafruit_SSD1306 *screen, short indexDisplay, short x_offset, short y_offset);

        void display(FcuDisplayFrame *frame);
        bool checkMutation(FcuDisplayFrame *frame);

    private:
        bool _isTrackMode;
        bool _isLatNavigation;
        bool _isHeadingHidden;
        bool _isHeadingForced;
        unsigned short _heading;

};

#endif