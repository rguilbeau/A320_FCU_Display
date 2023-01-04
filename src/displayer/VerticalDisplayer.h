#ifndef FCU_VERTICAL_DISPLAYER_H
#define FCU_VERTICAL_DISPLAYER_H

#include "Displayer.h"

class VerticalDisplayer : public Displayer {

    public:
        VerticalDisplayer(Adafruit_SSD1306 *screen, short indexDisplay, short x_offset, short y_offset);

        void display(FcuDisplayFrame *frame);
        bool checkMutation(FcuDisplayFrame *frame);

    private:
        bool _isFpa;
        float _verticalSpeed;
        bool _isVerticalSpeedNegative;
        bool _isVerticalSpeedHidden;
};

#endif