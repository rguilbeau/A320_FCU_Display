#ifndef FCU_DISPLAY_FRAME_RECEIVE_HANDLER_H
#define FCU_DISPLAY_FRAME_RECEIVE_HANDLER_H

#include "Setup.h"
#include "A320_Core/event/CanBusFrameEvent.h"

#include "A320_Core/can_bus/frame/brightness/BrightnessSevenSegmentsFrame.h"
#include "A320_Core/can_bus/frame/glareshield/FcuDisplayFrame.h"

#include "displayer/SpeedDisplayer.h"
#include "displayer/HeadingDisplayer.h"
#include "displayer/NavModeDisplayer.h"
#include "displayer/AltitudeDisplayer.h"
#include "displayer/VerticalDisplayer.h"

class CanBusEventHandler: public CanBusFrameEvent {

public:
    CanBusEventHandler(
        SpeedDisplayer *speedDisplayer, 
        HeadingDisplayer *headingDisplayer, 
        NavModeDisplayer *navModeDisplayer, 
        AltitudeDisplayer *altitudeDisplayer, 
        VerticalDisplayer *verticalDisplayer
    );

    void frameReceived(Frame *frame) override;

private:
    BrightnessSevenSegmentsFrame _brightnessSevenSegmentsFrame;
    FcuDisplayFrame _fcuDisplayFrame;

    SpeedDisplayer *_speedDisplayer;
    HeadingDisplayer *_headingDisplayer; 
    NavModeDisplayer *_navModeDisplayer;
    AltitudeDisplayer *_altitudeDisplayer;
    VerticalDisplayer *_verticalDisplayer;

    bool _forceRefreshDisplay;

    void setContrast(unsigned char contrast);
    void displayNone();
    void setTestLightIndicators();
    void display();
};

#endif