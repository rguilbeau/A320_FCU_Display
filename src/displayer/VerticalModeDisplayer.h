#ifndef FCU_VERTICAL_MODE_DISPLAYER_H
#define FCU_VERTICAL_MODE_DISPLAYER_H

#include "Displayer.h"

class VerticalModeDisplayer : public Displayer {

    public:
        VerticalModeDisplayer(Adafruit_SSD1306 *screen, short indexDisplay, short x_offset, short y_offset);

        void display(FcuDisplayFrame *frame);
        bool checkMutation(FcuDisplayFrame *frame);

    private:
        bool _isFpa;
};

#endif