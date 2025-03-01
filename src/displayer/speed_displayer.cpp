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


void SpeedDisplayer::setFrame(const FrameFcuDisplay &frame)
{
    if(frame.isMach())
    {
        if(m_nSpeed != frame.getMachSpeed())
        {
            m_nSpeed = frame.getMachSpeed();
            m_bMutation = true;
        }
    }
    else
    {
        if(m_nSpeed != frame.getKnotSpeed())
        {
            m_nSpeed = frame.getKnotSpeed();
            m_bMutation = true;
        }
    }

    if(m_bIsMachSpeed != frame.isMach())
    {
        m_bIsMachSpeed = frame.isMach();
        m_bMutation = true;
    }

    if(m_bIsSpeedDash != frame.isSpeedDashed())
    {
        m_bIsSpeedDash = frame.isSpeedDashed();
        m_bMutation = true;
    }

    if(m_bIsSpeedDot != frame.isSpeedDot())
    {
        m_bIsSpeedDot = frame.isSpeedDot();
        m_bMutation = true;
    }
}

bool SpeedDisplayer::checkMutation()
{
    if(m_bMutation)
    {
        m_bMutation = false;
        return true;
    }

    return false;
}

void SpeedDisplayer::display()
{
    String sSpeedDisplay = "";

    if(m_bIsMachSpeed) 
    {
        printMachIndicator();
        sSpeedDisplay = String(static_cast<double>(m_nSpeed) / 100);
    } 
    else 
    {
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
}
    
void SpeedDisplayer::displayTestLight()
{
    printSpeedIndicator();
    printMachIndicator();
    printDigit(F("888*"));
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