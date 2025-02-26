#ifndef FCU_VERTICAL_DISPLAYER_H
#define FCU_VERTICAL_DISPLAYER_H

#include "setup.h"
#include "displayer.hpp"
#include "frames/frame_fcu_display.hpp"

class VerticalDisplayer : public Displayer 
{
public:
    explicit VerticalDisplayer(Adafruit_SSD1306 *pScreen, const int8_t &nIndexDisplay);
    virtual ~VerticalDisplayer() = default;

    void display(const FrameFcuDisplay &frame);
    void displayTest();

    bool checkMutation(const FrameFcuDisplay &frame);

private:
    void printFixedIndicator();
    void printVsSpeedIndicator();
    void printFpaIndicator();
    void printDigit(const String &nValue);

    bool m_bIsFpa;
    int16_t m_nVerticalSpeed;
    bool m_bIsVerticalSpeedDash;
};

#endif