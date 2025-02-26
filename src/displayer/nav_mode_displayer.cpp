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

/**
 * @brief Vérification si la frame passée en paramètre contient des valeurs différents de celles déjà affichées sur l'écran
 * 
 * @param frame La frame
 * @return true Des modifications sont présentes, un rafraichissement de l'écran est requis
 * @return false Aucune modification, le rafraichissement de l'écran n'est pas nécéssaire
 */
bool NavModeDisplayer::checkMutation(const FrameFcuDisplay &frame)
{
    return 
        m_bIsTrackMode != frame.isTrack() ||
        m_bIsFpa != frame.isFpa();
}

void NavModeDisplayer::displayTest()
{
    selectScreen();
    m_pScreen->clearDisplay();
    printTrackIndicator();
    printHeadingIndicator();
    printFpaIndicator();
    printVsIndicator();
    m_pScreen->display();
}

/**
 * @brief Rafraichissement l'écran avec les données de la frame
 * 
 * @param frame La nouvelle frame
 */
void NavModeDisplayer::display(const FrameFcuDisplay &frame)
{
    m_bIsTrackMode = frame.isTrack();
    m_bIsFpa = frame.isFpa();

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

    if(m_bIsFpa) 
    {
        printFpaIndicator();
    } 
    else 
    {
        printVsIndicator();
    }
    
    m_pScreen->display();    
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