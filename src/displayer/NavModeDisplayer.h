#ifndef FCU_NAV_MODE_DISPLAYER_H
#define FCU_NAV_MODE_DISPLAYER_H

#include "Setup.h"
#include "core/displayer/Displayer.h"
#include "frame/FcuDisplayFrame.h"

class NavModeDisplayer : public Displayer {

    public:
        NavModeDisplayer(Adafruit_SSD1306 *screen, short indexDisplay);

        void display(FcuDisplayFrame *frame);
        void displayTest();

        bool checkMutation(FcuDisplayFrame *frame);

    private:
        void printTrackIndicator();
        void printHeadingIndicator();
        void printFpaIndicator();
        void printVsIndicator();

        bool _isTrackMode;
        bool _isFpa;
};

#endif