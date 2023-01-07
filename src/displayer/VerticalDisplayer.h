#ifndef FCU_VERTICAL_DISPLAYER_H
#define FCU_VERTICAL_DISPLAYER_H

#include "Displayer.h"

class VerticalDisplayer : public Displayer {

    public:
        VerticalDisplayer(Adafruit_SSD1306 *screen, short indexDisplay);

        void display(FcuDisplayFrame *frame);
        bool checkMutation(FcuDisplayFrame *frame);

    private:
        bool _isFpa;
        float _verticalSpeed;
        bool _isVerticalSpeedPositive;
        bool _isVerticalSpeedHidden;
};

#endif