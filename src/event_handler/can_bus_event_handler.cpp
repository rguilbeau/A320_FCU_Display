#include "can_bus_event_handler.hpp"

CanBusEventHandler::CanBusEventHandler(        
    SpeedDisplayer *pSpeedDisplayer, 
    HeadingDisplayer *pHeadingDisplayer, 
    NavModeDisplayer *pNavModeDisplayer, 
    AltitudeDisplayer *pAltitudeDisplayer, 
    VerticalDisplayer *pVerticalDisplayer
) {
    m_pSpeedDisplayer = pSpeedDisplayer;
    m_pHeadingDisplayer = pHeadingDisplayer; 
    m_pNavModeDisplayer = pNavModeDisplayer; 
    m_pAltitudeDisplayer = pAltitudeDisplayer; 
    m_pVerticalDisplayer = pVerticalDisplayer;

    m_pSpeedDisplayer->setContrast(255);
    m_pHeadingDisplayer->setContrast(255);
    m_pNavModeDisplayer->setContrast(255);
    m_pAltitudeDisplayer->setContrast(255);
    m_pVerticalDisplayer->setContrast(255);
}

void CanBusEventHandler::frameReceived(const Frame &frame)
{
    //SERIAL_PRINTLN("frame " + String(frame.getId()));
    
    if(frame.getId() == e_frameId::FCU_DISPLAY) 
    {
        FrameFcuDisplay fcuDisplayframe(frame);

        m_pSpeedDisplayer->setFrame(fcuDisplayframe);
        m_pHeadingDisplayer->setFrame(fcuDisplayframe); 
        m_pNavModeDisplayer->setFrame(fcuDisplayframe); 
        m_pAltitudeDisplayer->setFrame(fcuDisplayframe); 
        m_pVerticalDisplayer->setFrame(fcuDisplayframe);
    }

    else if(frame.getId() == e_frameId::BRIGTNESS_PANEL)
    {
        FrameBrightnessPanel brightnessPanelFrame(frame);

        m_pSpeedDisplayer->setContrast(brightnessPanelFrame.getDisplayGlareshield());
        m_pSpeedDisplayer->setTestLight(brightnessPanelFrame.isTestLight());

        m_pHeadingDisplayer->setContrast(brightnessPanelFrame.getDisplayGlareshield());
        m_pHeadingDisplayer->setTestLight(brightnessPanelFrame.isTestLight());

        m_pNavModeDisplayer->setContrast(brightnessPanelFrame.getDisplayGlareshield());
        m_pNavModeDisplayer->setTestLight(brightnessPanelFrame.isTestLight());

        m_pAltitudeDisplayer->setContrast(brightnessPanelFrame.getDisplayGlareshield());
        m_pAltitudeDisplayer->setTestLight(brightnessPanelFrame.isTestLight());

        m_pVerticalDisplayer->setContrast(brightnessPanelFrame.getDisplayGlareshield());
        m_pVerticalDisplayer->setTestLight(brightnessPanelFrame.isTestLight());
    }
}