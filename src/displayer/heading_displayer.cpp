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

/**
 * @brief Vérification si la frame passée en paramètre contient des valeurs différents de celles déjà affichées sur l'écran
 * 
 * @param frame La frame
 * @return true Des modifications sont présentes, un rafraichissement de l'écran est requis
 * @return false Aucune modification, le rafraichissement de l'écran n'est pas nécéssaire
 */
bool HeadingDisplayer::checkMutation(const FrameFcuDisplay &frame)
{
    return 
        m_bIsTrackMode != frame.isTrack() ||
        m_bIsLatNavigation != frame.isLat() ||
        m_nHeading != frame.getHeading() ||
        m_bIsHeadingDash != frame.isHeadingDashed() ||
        m_bIsHeadingDot != frame.isHeadingDot();
}

void HeadingDisplayer::displayTest()
{
    selectScreen();
    m_pScreen->clearDisplay();
    printHeadingIndicator();
    printTrackIndicator();
    printLatIndicator();
    printDigit(F("888*"));
    m_pScreen->display();
}

/**
 * @brief Rafraichissement l'écran avec les données de la frame
 * 
 * @param frame La nouvelle frame
 */
void HeadingDisplayer::display(const FrameFcuDisplay &frame)
{
    m_bIsTrackMode = frame.isTrack();
    m_bIsLatNavigation = frame.isLat();
    m_nHeading = frame.getHeading();
    m_bIsHeadingDash = frame.isHeadingDashed();
    m_bIsHeadingDot = frame.isHeadingDot();

    selectScreen();
    m_pScreen->clearDisplay();
    
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

    m_pScreen->display();    
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