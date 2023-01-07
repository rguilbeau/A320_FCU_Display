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
        _isVerticalSpeedHidden != frame->isVerticalSpeedHidden;
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
    _isVerticalSpeedHidden = frame->isVerticalSpeedHidden;

    selectScreen(); 
    _screen->clearDisplay();
    
    // CH
    _screen->setCursor(X_OFFSET + 4, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("CH"));

    // ARROW RIGHT
    _screen->fillRect(X_OFFSET + 32, Y_OFFSET + 10, 24, 2, SSD1306_WHITE);
    _screen->fillRect(X_OFFSET + 54, Y_OFFSET + 12, 2, 3, SSD1306_WHITE);

    if(_isFpa) {
        _screen->setCursor(X_OFFSET + 93, Y_OFFSET + 16);
        _screen->setFont(&Nimbus_Sans_L_Bold_16);
        _screen->print(F("FPA"));
    } else {
        _screen->setCursor(X_OFFSET + 64, Y_OFFSET + 16);
        _screen->setFont(&Nimbus_Sans_L_Bold_16);
        _screen->print(F("V/S"));  
    }

    
    String verticalSpeedDisplay;;
    
    if(_isVerticalSpeedHidden) {
        verticalSpeedDisplay = "-----";
    } else {
        verticalSpeedDisplay = String(_verticalSpeed);

        if(_isVerticalSpeedPositive) {
            verticalSpeedDisplay = "+" + verticalSpeedDisplay;
        } else {
            verticalSpeedDisplay = "-" + verticalSpeedDisplay; 
        }

        if(_isFpa) {
            verticalSpeedDisplay = " " + verticalSpeedDisplay.substring(0, verticalSpeedDisplay.length() - 1) + " ";
        } else {
            // -5 parce que float 1600.00
            verticalSpeedDisplay = verticalSpeedDisplay.substring(0, verticalSpeedDisplay.length() - 5) + "oo";
        }
    }

    // V/S digit
    _screen->setCursor(X_OFFSET + 25, Y_OFFSET + 45);
    _screen->setFont(&DSEG7_Classic_Mini_Bold_25);
    _screen->print(verticalSpeedDisplay);
        
    _screen->display();    
}