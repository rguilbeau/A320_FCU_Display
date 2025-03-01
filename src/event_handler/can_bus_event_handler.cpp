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

        uint8_t nContrast = brightnessPanelFrame.getDisplayGlareshield();
        m_pSpeedDisplayer->setContrast(nContrast);
        m_pHeadingDisplayer->setContrast(nContrast);
        m_pNavModeDisplayer->setContrast(nContrast);
        m_pAltitudeDisplayer->setContrast(nContrast);
        m_pVerticalDisplayer->setContrast(nContrast);
        
        bool bIsTestLight = brightnessPanelFrame.isTestLight();
        m_pSpeedDisplayer->setTestLight(bIsTestLight);
        m_pHeadingDisplayer->setTestLight(bIsTestLight);
        m_pNavModeDisplayer->setTestLight(bIsTestLight);
        m_pAltitudeDisplayer->setTestLight(bIsTestLight);
        m_pVerticalDisplayer->setTestLight(bIsTestLight);
    }

    else if(frame.getId() == e_frameId::POWER)
    {
        FramePower powerFrame(frame);

        bool bIsPowered = powerFrame.isFcuDisplayPowered();
        m_pSpeedDisplayer->setPowerOn(bIsPowered);
        m_pHeadingDisplayer->setPowerOn(bIsPowered); 
        m_pNavModeDisplayer->setPowerOn(bIsPowered); 
        m_pAltitudeDisplayer->setPowerOn(bIsPowered); 
        m_pVerticalDisplayer->setPowerOn(bIsPowered);
    }
}