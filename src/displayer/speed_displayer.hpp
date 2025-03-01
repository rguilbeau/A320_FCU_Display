#ifndef FCU_SPEED_DISPLAYER_H
#define FCU_SPEED_DISPLAYER_H

#include "setup.h"
#include "displayer.hpp"
#include "frames/frame_fcu_display.hpp"

class SpeedDisplayer : public Displayer 
{
public:
    explicit SpeedDisplayer(Adafruit_SSD1306 *pScreen, const int8_t &nIndexDisplay);
    virtual ~SpeedDisplayer() = default;

    void setFrame(const FrameFcuDisplay &frame);

    bool checkMutation() override;
    void display() override;
    void displayTestLight() override; 

private:

    void printSpeedIndicator();
    void printMachIndicator();
    void printDigit(const String &sValue);

    bool m_bIsMachSpeed; 
    uint16_t m_nSpeed; 
    bool m_bIsSpeedDash;
    bool m_bIsSpeedDot;

    bool m_bMutation = true;
};

#endif