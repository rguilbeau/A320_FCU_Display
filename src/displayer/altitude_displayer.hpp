#ifndef FCU_ALTITUDE_DISPLAYER_H
#define FCU_ALTITUDE_DISPLAYER_H

#include "setup.h"
#include "displayer.hpp"
#include "frames/frame_fcu_display.hpp"
#include "frames/frame_brightness_panel.hpp"

class AltitudeDisplayer : public Displayer 
{
public:
    explicit AltitudeDisplayer(Adafruit_SSD1306 *pScreen, const int8_t &nIndexDisplay);
    virtual ~AltitudeDisplayer() = default;

    void setFrame(const FrameFcuDisplay &frame);

    bool checkMutation() override;
    void display() override;
    void displayTestLight() override;
    
private:
    void printFixedIndicator();
    void printDigit(const String &sValue);

    bool m_bMutation = true;
    bool m_bIsAltitudeDot;
    uint16_t m_nAltitude;
};

#endif