#ifndef FCU_DISPLAY_FRAME_RECEIVE_HANDLER_H
#define FCU_DISPLAY_FRAME_RECEIVE_HANDLER_H

#include "setup.h"
#include "event/can_bus_frame_event.hpp"

#include "displayer/speed_displayer.hpp"
#include "displayer/heading_displayer.hpp"
#include "displayer/nav_mode_displayer.hpp"
#include "displayer/altitude_displayer.hpp"
#include "displayer/vertical_displayer.hpp"

#include "frames/frame_fcu_display.hpp"
#include "frames/frame_brightness_panel.hpp"

class CanBusEventHandler: public CanBusFrameEvent {

public:
    CanBusEventHandler(
        SpeedDisplayer *pSpeedDisplayer, 
        HeadingDisplayer *pHeadingDisplayer, 
        NavModeDisplayer *pNavModeDisplayer, 
        AltitudeDisplayer *pAltitudeDisplayer, 
        VerticalDisplayer *pVerticalDisplayer
    );

    void frameReceived(const Frame &frame) override;

private:
    FrameBrightnessPanel m_brightnessPanelFrame;
    FrameFcuDisplay m_fcuDisplayFrame;

    SpeedDisplayer *m_pSpeedDisplayer;
    HeadingDisplayer *m_pHeadingDisplayer; 
    NavModeDisplayer *m_pNavModeDisplayer;
    AltitudeDisplayer *m_pAltitudeDisplayer;
    VerticalDisplayer *m_pVerticalDisplayer;
};

#endif