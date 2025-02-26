#include "speed_displayer.hpp"

/**
 * @brief Construction de l'afficheur pour l'écran OLED de la vitesse
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 */
SpeedDisplayer::SpeedDisplayer(Adafruit_SSD1306 *pScreen, const int8_t &nIndexDisplay) : Displayer(pScreen, nIndexDisplay)
{
    
}

/**
 * @brief Vérification si la frame passée en paramètre contient des valeurs différents de celles déjà affichées sur l'écran
 * 
 * @param frame La frame
 * @return true Des modifications sont présentes, un rafraichissement de l'écran est requis
 * @return false Aucune modification, le rafraichissement de l'écran n'est pas nécéssaire
 */
bool SpeedDisplayer::checkMutation(const FrameFcuDisplay &frame) 
{
    bool bSameSpeed;

    if(frame.isMach())
    {
        bSameSpeed = m_nSpeed == frame.getMachSpeed();
    }
    else
    {
        bSameSpeed = m_nSpeed == frame.getKnotSpeed();
    }

    return
        !bSameSpeed || 
        m_bIsMachSpeed != frame.isMach() ||
        m_bIsSpeedDash != frame.isSpeedDashed() ||
        m_bIsSpeedDot != frame.isSpeedDot();
}

void SpeedDisplayer::displayTest()
{
    selectScreen();
    m_pScreen->clearDisplay();
    printSpeedIndicator();
    printMachIndicator();
    printDigit(F("888*"));
    m_pScreen->display();
}

/**
 * @brief Rafraichissement l'écran avec les données de la frame
 * 
 * @param frame La nouvelle frame
 */
void SpeedDisplayer::display(const FrameFcuDisplay &frame)
{
    m_bIsMachSpeed = frame.isMach();
    m_bIsSpeedDash = frame.isSpeedDashed();
    m_bIsSpeedDot = frame.isSpeedDot();
    
    selectScreen();

    m_pScreen->clearDisplay();
    String sSpeedDisplay = "";

    if(m_bIsMachSpeed) 
    {
        m_nSpeed = frame.getMachSpeed();

        printMachIndicator();
        sSpeedDisplay = String(static_cast<double>(m_nSpeed) / 100);
    } 
    else 
    {
        m_nSpeed = frame.getKnotSpeed();
        printSpeedIndicator();
        sSpeedDisplay = leftPad(m_nSpeed, 3);
    }

    if(m_bIsSpeedDash) 
    {
        sSpeedDisplay = "---";
    }

    if(m_bIsSpeedDot) 
    {
        sSpeedDisplay += "*";
    }

    printDigit(sSpeedDisplay);
    m_pScreen->display();
}

void SpeedDisplayer::printSpeedIndicator()
{
    m_pScreen->setCursor(X_OFFSET + 4, Y_OFFSET + 16);
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->print(F("SPD"));
}

void SpeedDisplayer::printMachIndicator()
{
    m_pScreen->setCursor(X_OFFSET + 46, Y_OFFSET + 16);
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->print(F("MACH"));
}

void SpeedDisplayer::printDigit(const String &sValue)
{
    m_pScreen->setCursor(X_OFFSET + 31, Y_OFFSET + 45);
    m_pScreen->setFont(&DSEG7_Classic_Mini_Bold_25);
    m_pScreen->print(sValue);
}