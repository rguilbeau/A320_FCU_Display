#include "vertical_displayer.hpp"

/**
 * @brief Construction de l'afficheur pour l'écran OLED de la vitesse vertical
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 */
VerticalDisplayer::VerticalDisplayer(Adafruit_SSD1306 *pScreen, const int8_t &nIndexDisplay): Displayer (pScreen, nIndexDisplay)
{

}

/**
 * @brief Vérification si la frame passée en paramètre contient des valeurs différents de celles déjà affichées sur l'écran
 * 
 * @param frame La frame
 * @return true Des modifications sont présentes, un rafraichissement de l'écran est requis
 * @return false Aucune modification, le rafraichissement de l'écran n'est pas nécéssaire
 */
bool VerticalDisplayer::checkMutation(const FrameFcuDisplay &frame)
{
    bool bSameVerticalSpeed;

    if(frame.isFpa())
    {
        bSameVerticalSpeed = m_nVerticalSpeed != frame.getFpa();
    }
    else
    {
        bSameVerticalSpeed = m_nVerticalSpeed != frame.getVerticalSpeed();
    }

    return
        !bSameVerticalSpeed ||
        m_bIsFpa != frame.isFpa() ||
        m_bIsVerticalSpeedDash != frame.isVerticalSpeedDashed();
}

void VerticalDisplayer::displayTest()
{
    selectScreen(); 
    m_pScreen->clearDisplay();
    
    printFixedIndicator();
    printVsSpeedIndicator();
    printFpaIndicator();
    printDigit(F("+8888"));
    
    m_pScreen->display(); 
}

/**
 * @brief Rafraichissement l'écran avec les données de la frame
 * 
 * @param frame La nouvelle frame
 */
void VerticalDisplayer::display(const FrameFcuDisplay &frame)
{
    m_bIsFpa = frame.isFpa();
    m_bIsVerticalSpeedDash = frame.isVerticalSpeedDashed(),

    selectScreen(); 
    m_pScreen->clearDisplay();
    
    printFixedIndicator();

    if(m_bIsFpa) 
    {
        printFpaIndicator();
    } 
    else 
    {
       printVsSpeedIndicator();
    }

    String verticalSpeedDisplay;
    
    if(m_bIsVerticalSpeedDash) 
    {
        verticalSpeedDisplay = "-----";
    } else 
    {
        if(m_bIsFpa) 
        {   
            m_nVerticalSpeed = frame.getFpa();

            verticalSpeedDisplay = String(static_cast<double>(abs(m_nVerticalSpeed)) / 10);
            verticalSpeedDisplay = verticalSpeedDisplay.substring(0, verticalSpeedDisplay.length() - 1) + " ";
        } else {
            m_nVerticalSpeed = frame.getVerticalSpeed();

            // -5 parce que float 1600.00
            verticalSpeedDisplay = leftPad(abs(m_nVerticalSpeed), 4);
            verticalSpeedDisplay = verticalSpeedDisplay.substring(0, verticalSpeedDisplay.length() - 2) + "oo";
        }

        if(m_nVerticalSpeed >= 0) 
        {
            verticalSpeedDisplay = "+" + verticalSpeedDisplay;
        } 
        else 
        {
            verticalSpeedDisplay = "-" + verticalSpeedDisplay; 
        }
    }

    printDigit(verticalSpeedDisplay);
        
    m_pScreen->display();    
}

void VerticalDisplayer::printFixedIndicator()
{
    // CH
    m_pScreen->setCursor(X_OFFSET + 0, Y_OFFSET + 16);
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->print(F("CH"));

    // ARROW RIGHT
    m_pScreen->fillRect(X_OFFSET + 28, Y_OFFSET + 10, 24, 3, SSD1306_WHITE);
    m_pScreen->fillRect(X_OFFSET + 49, Y_OFFSET + 12, 3, 3, SSD1306_WHITE);
}

void VerticalDisplayer::printVsSpeedIndicator()
{
    m_pScreen->setCursor(X_OFFSET + 60, Y_OFFSET + 16);
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->print(F("V/S"));  
}

void VerticalDisplayer::printFpaIndicator()
{
    m_pScreen->setCursor(X_OFFSET + 88, Y_OFFSET + 16);
    m_pScreen->setFont(&Nimbus_Sans_L_Bold_16);
    m_pScreen->print(F("FPA"));
}

void VerticalDisplayer::printDigit(const String &sValue)
{
    // V/S digit
    m_pScreen->setCursor(X_OFFSET + 21, Y_OFFSET + 45);
    m_pScreen->setFont(&DSEG7_Classic_Mini_Bold_25);
    m_pScreen->print(sValue);
}
