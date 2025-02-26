#ifndef FCU_HEADING_DISPLAYER_H
#define FCU_HEADING_DISPLAYER_H

#include "setup.h"
#include "displayer.hpp"
#include "frames/frame_fcu_display.hpp"

class HeadingDisplayer : public Displayer 
{
public:
    explicit HeadingDisplayer(Adafruit_SSD1306 *pScreen, const int8_t &nIndexDisplay);
    virtual ~HeadingDisplayer() = default;

    void display(const FrameFcuDisplay &frame);
    void displayTest();

    bool checkMutation(const FrameFcuDisplay &frame);

private:

    void printHeadingIndicator();
    void printTrackIndicator();
    void printLatIndicator();
    void printDigit(const String &sValue);

    bool m_bIsTrackMode;
    bool m_bIsLatNavigation;
    bool m_bIsHeadingDash;
    bool m_bIsHeadingDot;
    uint16_t m_nHeading;
};

#endif