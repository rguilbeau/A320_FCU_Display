#include "VerticalDisplayer.h"

/**
 * @brief Construction de l'afficheur pour l'écran OLED de la vitesse vertical
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 */
VerticalDisplayer::VerticalDisplayer(
    Adafruit_SSD1306 *screen, 
    short indexDisplay
): Displayer (
    screen, 
    indexDisplay
) {

}

/**
 * @brief Vérification si la frame passée en paramètre contient des valeurs différents de celles déjà affichées sur l'écran
 * 
 * @param frame La frame
 * @return true Des modifications sont présentes, un rafraichissement de l'écran est requis
 * @return false Aucune modification, le rafraichissement de l'écran n'est pas nécéssaire
 */
bool VerticalDisplayer::checkMutation(FcuDisplayFrame *frame)
{
    return
        _isFpa != frame->isFpa ||
        _verticalSpeed != frame->verticalSpeed ||
        _isVerticalSpeedPositive != frame->isVerticalSpeedPositive ||
        _isVerticalSpeedDash != frame->isVerticalSpeedDash;
}

void VerticalDisplayer::displayTest()
{
    selectScreen(); 
    _screen->clearDisplay();
    
    printFixedIndicator();
    printVsSpeedIndicator();
    printFpaIndicator();
    printDigit(F("+8888"));
    
    _screen->display(); 
}

/**
 * @brief Rafraichissement l'écran avec les données de la frame
 * 
 * @param frame La nouvelle frame
 */
void VerticalDisplayer::display(FcuDisplayFrame *frame)
{
    _isFpa = frame->isFpa;
    _verticalSpeed = frame->verticalSpeed;
    _isVerticalSpeedPositive = frame->isVerticalSpeedPositive;
    _isVerticalSpeedDash = frame->isVerticalSpeedDash;

    selectScreen(); 
    _screen->clearDisplay();
    
    printFixedIndicator();

    if(_isFpa) {
        printFpaIndicator();
    } else {
       printVsSpeedIndicator();
    }

    String verticalSpeedDisplay;
    
    if(_isVerticalSpeedDash) {
        verticalSpeedDisplay = "-----";
    } else {
        if(_isFpa) {
            verticalSpeedDisplay = String(_verticalSpeed);
            verticalSpeedDisplay = verticalSpeedDisplay.substring(0, verticalSpeedDisplay.length() - 1) + " ";
        } else {
            // -5 parce que float 1600.00
            verticalSpeedDisplay = leftPad(_verticalSpeed, 4);
            verticalSpeedDisplay = verticalSpeedDisplay.substring(0, verticalSpeedDisplay.length() - 2) + "oo";
        }

        if(_isVerticalSpeedPositive) {
            verticalSpeedDisplay = "+" + verticalSpeedDisplay;
        } else {
            verticalSpeedDisplay = "-" + verticalSpeedDisplay; 
        }
    }

    printDigit(verticalSpeedDisplay);
        
    _screen->display();    
}

void VerticalDisplayer::printFixedIndicator()
{
    // CH
    _screen->setCursor(X_OFFSET + 0, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("CH"));

    // ARROW RIGHT
    _screen->fillRect(X_OFFSET + 28, Y_OFFSET + 10, 24, 3, SSD1306_WHITE);
    _screen->fillRect(X_OFFSET + 49, Y_OFFSET + 12, 3, 3, SSD1306_WHITE);
}

void VerticalDisplayer::printVsSpeedIndicator()
{
    _screen->setCursor(X_OFFSET + 60, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("V/S"));  
}

void VerticalDisplayer::printFpaIndicator()
{
    _screen->setCursor(X_OFFSET + 88, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("FPA"));
}

void VerticalDisplayer::printDigit(String digit)
{
    // V/S digit
    _screen->setCursor(X_OFFSET + 21, Y_OFFSET + 45);
    _screen->setFont(&DSEG7_Classic_Mini_Bold_25);
    _screen->print(digit);
}
