#ifndef FCU_NAV_MODE_DISPLAYER_H
#define FCU_NAV_MODE_DISPLAYER_H

#include "setup.h"
#include "displayer.hpp"
#include "frames/frame_fcu_display.hpp"

class NavModeDisplayer : public Displayer 
{
public:
    explicit NavModeDisplayer(Adafruit_SSD1306 *pScreen, const int8_t &nIndexDisplay);
    virtual ~NavModeDisplayer() = default;

    void setFrame(const FrameFcuDisplay &frame);

    bool checkMutation() override;
    void display() override;
    void displayTestLight() override;

private:
    void printTrackIndicator();
    void printHeadingIndicator();
    void printFpaIndicator();
    void printVsIndicator();

    bool m_bIsTrackMode;
    bool m_bIsFpa;

    bool m_bMutation = true;
};

#endif