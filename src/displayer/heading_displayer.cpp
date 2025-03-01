#include "heading_displayer.hpp"

/**
 * @brief Construction de l'afficheur pour l'écran OLED du cap
 * 
 * @param pScreen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param nIndexDisplay L'index de l'écran sur le multiplexer I2C
 */
HeadingDisplayer::HeadingDisplayer(Adafruit_SSD1306 *pScreen, const int8_t &nIndexDisplay): Displayer (pScreen, nIndexDisplay)
{

}


void HeadingDisplayer::setFrame(const FrameFcuDisplay &frame)
{
    if(m_bIsTrackMode != frame.isTrack())
    {
        m_bIsTrackMode = frame.isTrack();
        m_bMutation = true;
    }

    if(m_bIsLatNavigation != frame.isLat())
    {
        m_bIsLatNavigation = frame.isLat();
        m_bMutation = true;
    }

    if(m_nHeading != frame.getHeading())
    {
        m_nHeading = frame.getHeading();
        m_bMutation = true;
    }

    if(m_bIsHeadingDash != frame.isHeadingDashed())
    {
        m_bIsHeadingDash = frame.isHeadingDashed();
        m_bMutation = true;
    }

    if(m_bIsHeadingDot != frame.isHeadingDot())
    {
        m_bIsHeadingDot = frame.isHeadingDot();
        m_bMutation = true;
    }
}

bool HeadingDisplayer::checkMutation()
{
    if(m_bMutation)
    {
        m_bMutation = false;
        return true;
    }

    return false;
}


void HeadingDisplayer::display()
{
    if(m_bIsTrackMode) 
    {
        printTrackIndicator();
        
    } 
    else
    {
        printHeadingIndicator();
    }

    if(m_bIsLatNavigation) 
    {
        printLatIndicator();
    }

    String sHeadingDisplay;
    if(m_bIsHeadingDash) 
    {
        sHeadingDisplay = "---";
    } 
    else
    {
        sHeadingDisplay = leftPad(m_nHeading, 3);
    }

    if(m_bIsHeadingDot) 
    {
        sHeadingDisplay += "*";
    }

    // HDG digit
    printDigit(sHeadingDisplay);
}

void HeadingDisplayer::displayTestLight()
{
    printHeadingIndicator();
    printTrackIndicator();
    printLatIndicator();
    printDigit(F("888*"));
}

void HeadingDisplayer::printHeadingIndicator()
{
    m_pScreen->setCursor(X_OFFSET + 4, Y_OFFSET + 16);
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->print(F("HDG"));
}

void HeadingDisplayer::printTrackIndicator()
{
    m_pScreen->setCursor(X_OFFSET + 48, Y_OFFSET + 16);
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->print(F("TRK"));
}

void HeadingDisplayer::printLatIndicator()
{
    m_pScreen->setCursor(X_OFFSET + 92, Y_OFFSET + 16);
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->print(F("LAT"));
}

void HeadingDisplayer::printDigit(const String &sValue)
{
    m_pScreen->setCursor(X_OFFSET + 31, Y_OFFSET + 45);
    m_pScreen->setFont(&DSEG7_Classic_Mini_Bold_25);
    m_pScreen->print(sValue);
}