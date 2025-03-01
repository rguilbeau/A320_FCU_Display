#include "nav_mode_displayer.hpp"

/**
 * @brief Construction de l'afficheur pour l'écran OLED du mode du cap (headinfg/track)
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 */
NavModeDisplayer::NavModeDisplayer(Adafruit_SSD1306 *pScreen, const int8_t &nIndexDisplay): Displayer (pScreen, nIndexDisplay)
{

}


void NavModeDisplayer::setFrame(const FrameFcuDisplay &frame)
{
    if(m_bIsTrackMode != frame.isTrack())
    {
        m_bIsTrackMode = frame.isTrack();
        m_bMutation = true;
    }

    if(m_bIsTrackMode != frame.isTrack())
    {
        m_bIsTrackMode = frame.isTrack();
        m_bMutation = true;
    }
}

bool NavModeDisplayer::checkMutation()
{
    if(m_bMutation)
    {
        m_bMutation = false;
        return true;
    }

    return false;
}
    
void NavModeDisplayer::display()
{
    if(m_bIsTrackMode)
    {
        printTrackIndicator();
    } 
    else 
    {
        printHeadingIndicator();
    }

    if(m_bIsFpa) 
    {
        printFpaIndicator();
    } 
    else 
    {
        printVsIndicator();
    }
}
    
void NavModeDisplayer::displayTestLight()
{
    printTrackIndicator();
    printHeadingIndicator();
    printFpaIndicator();
    printVsIndicator();
}

void NavModeDisplayer::printTrackIndicator()
{
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->setCursor(X_OFFSET + 17, Y_OFFSET + 45);
    m_pScreen->print(F("TRK")); 
}

void NavModeDisplayer::printHeadingIndicator()
{
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->setCursor(X_OFFSET + 15, Y_OFFSET + 30);
    m_pScreen->print(F("HDG"));  
}

void NavModeDisplayer::printFpaIndicator()
{
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->setCursor(X_OFFSET + 75, Y_OFFSET + 45);
    m_pScreen->print(F("FPA")); 
}

void NavModeDisplayer::printVsIndicator()
{
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->setCursor(X_OFFSET + 75, Y_OFFSET + 30);
    m_pScreen->print(F("V/S"));  
}