#include "altitude_displayer.hpp"

/**
 * @brief Construction de l'afficheur pour l'écran OLED de l'altitude
 * 
 * @param pScreen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param nIndexDisplay L'index de l'écran sur le multiplexer I2C
 */
AltitudeDisplayer::AltitudeDisplayer(Adafruit_SSD1306 *pScreen, const int8_t &nIndexDisplay): Displayer (pScreen, nIndexDisplay)
{

}

void AltitudeDisplayer::setFrame(const FrameFcuDisplay &frame)
{
    if(m_bIsAltitudeDot != frame.isAltitudeDot())
    {
        m_bIsAltitudeDot = frame.isAltitudeDot();
        m_bMutation = true;
    }

    if(m_nAltitude != frame.getAltitude())
    {
        m_nAltitude = frame.getAltitude();
        m_bMutation = true;
    }
}

bool AltitudeDisplayer::checkMutation()
{
    if(m_bMutation)
    {
        m_bMutation = false;
        return true;
    }

    return false;
}

void AltitudeDisplayer::display()
{
    printFixedIndicator();

    String sAltitudeDisplay = leftPad(m_nAltitude, 5);

    if(m_bIsAltitudeDot)
    {
        sAltitudeDisplay += "*";
    }

    printDigit(sAltitudeDisplay);
}

void AltitudeDisplayer::displayTestLight()
{
    printFixedIndicator();
    printDigit(F("88888*"));
}

void AltitudeDisplayer::printFixedIndicator()
{
    //ALT
    m_pScreen->setCursor(X_OFFSET + 24, Y_OFFSET + 16);
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->print(F("ALT"));

    // ARROW LEFT
    m_pScreen->fillRect(X_OFFSET + 65, Y_OFFSET + 10, 24, 3, SSD1306_WHITE);
    m_pScreen->fillRect(X_OFFSET + 65, Y_OFFSET + 12, 3, 4, SSD1306_WHITE);

    //LVL
    m_pScreen->setCursor(X_OFFSET + 93, Y_OFFSET + 16);
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->print(F("LVL"));
}

void AltitudeDisplayer::printDigit(const String &sValue)
{
    // ALT digit
    m_pScreen->setCursor(X_OFFSET + 0, Y_OFFSET + 45);
    m_pScreen->setFont(&DSEG7_Classic_Mini_Bold_25);
    m_pScreen->print(sValue);
}