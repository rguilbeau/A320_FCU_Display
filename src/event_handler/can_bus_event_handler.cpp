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
    m_bForceRefreshDisplay = true;
}

void CanBusEventHandler::frameReceived(const Frame &frame)
{
    SERIAL_PRINTLN("frame " + String(frame->getId()));
    

    if(frame.getId() == e_frameId::FCU_DISPLAY) 
    {
        FrameFcuDisplay fcuDisplayframe(frame);

        if(m_fcuDisplayFrame != fcuDisplayframe)
        {
            m_fcuDisplayFrame = fcuDisplayframe;

            if(m_brightnessPanelFrame.getGlarshield() != 0 && !m_brightnessPanelFrame.isTestLight())
            {
                display();
            }
        }
    }

    else if(frame.getId() == e_frameId::BRIGTNESS_PANEL)
    {
        FrameBrightnessPanel brightnessPanelFrame(frame);

        if(m_brightnessPanelFrame != brightnessPanelFrame)
        {
            m_brightnessPanelFrame = brightnessPanelFrame;

            setContrast(m_brightnessPanelFrame.getDisplayGlareshield());
        }
        
        if(m_brightnessPanelFrame.getDisplayGlareshield() == 0) 
        {
            displayNone();
        }
        else if(m_brightnessPanelFrame.isTestLight()) 
        {
            setTestLightIndicators();
        } 
        else 
        {
            display();
        }
    }
}

void CanBusEventHandler::setContrast(const uint8_t &nContrast)
{
    m_pSpeedDisplayer->setContrast(nContrast);
    m_pHeadingDisplayer->setContrast(nContrast);
    m_pNavModeDisplayer->setContrast(nContrast);
    m_pAltitudeDisplayer->setContrast(nContrast);
    m_pVerticalDisplayer->setContrast(nContrast);
}

void CanBusEventHandler::displayNone()
{
    m_pSpeedDisplayer->displayNone();
    m_pHeadingDisplayer->displayNone();
    m_pNavModeDisplayer->displayNone();
    m_pAltitudeDisplayer->displayNone();
    m_pVerticalDisplayer->displayNone();
    m_bForceRefreshDisplay = true;
}

void CanBusEventHandler::setTestLightIndicators()
{
    m_pSpeedDisplayer->displayTest();
    m_pHeadingDisplayer->displayTest();
    m_pNavModeDisplayer->displayTest();
    m_pAltitudeDisplayer->displayTest();
    m_pVerticalDisplayer->displayTest();
    m_bForceRefreshDisplay = true;
}

void CanBusEventHandler::display()
{
    if(m_pSpeedDisplayer->checkMutation(m_fcuDisplayFrame) || m_bForceRefreshDisplay) 
    {
        m_pSpeedDisplayer->display(m_fcuDisplayFrame);
    }

    if(m_pHeadingDisplayer->checkMutation(m_fcuDisplayFrame) || m_bForceRefreshDisplay)
    {
        m_pHeadingDisplayer->display(m_fcuDisplayFrame);
    }

    if(m_pNavModeDisplayer->checkMutation(m_fcuDisplayFrame) || m_bForceRefreshDisplay)
    {
        m_pNavModeDisplayer->display(m_fcuDisplayFrame);
    }

    if(m_pAltitudeDisplayer->checkMutation(m_fcuDisplayFrame) || m_bForceRefreshDisplay)
    {
        m_pAltitudeDisplayer->display(m_fcuDisplayFrame);
    }

    if(m_pVerticalDisplayer->checkMutation(m_fcuDisplayFrame) || m_bForceRefreshDisplay)
    {
        m_pVerticalDisplayer->display(m_fcuDisplayFrame);
    }

    m_bForceRefreshDisplay = false;
}