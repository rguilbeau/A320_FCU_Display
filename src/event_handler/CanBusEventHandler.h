#ifndef FCU_DISPLAY_FRAME_RECEIVE_HANDLER_H
#define FCU_DISPLAY_FRAME_RECEIVE_HANDLER_H

#include "Setup.h"
#include "core/event/CanBusFrameEvent.h"

#include "core/can_bus/frame/brightness/BrightnessFrame.h"
#include "core/can_bus/frame/glareshield/FcuDisplayFrame.h"
#include "core/can_bus/frame/overhead/LightIndicatorsFrame.h"

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
    BrightnessFrame _brightnessFrame;
    LightIndicatorsFrame _lightIndicatorsFrame;
    FcuDisplayFrame _fcuDisplayFrame;

    SpeedDisplayer *_speedDisplayer;
    HeadingDisplayer *_headingDisplayer; 
    NavModeDisplayer *_navModeDisplayer;
    AltitudeDisplayer *_altitudeDisplayer;
    VerticalDisplayer *_verticalDisplayer;

    bool _forceRefreshDisplay;

    void setContrast();
    void setTestLightIndicators();
    void setPowerOff();
    void display();
};

#endif