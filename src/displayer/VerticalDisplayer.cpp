#include "VerticalDisplayer.h"

/**
 * @brief Construction de l'afficheur pour l'écran OLED de la vitesse vertical
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 * @param x_offset L'offset x des curseurs
 * @param y_offset L'offset y des les curseurs
 */
VerticalDisplayer::VerticalDisplayer(
    Adafruit_SSD1306 *screen, 
    short indexDisplay, 
    short x_offset, 
    short y_offset
): Displayer (
    screen, 
    indexDisplay, 
    x_offset, 
    y_offset
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
        _isVerticalSpeedNegative != frame->isVerticalSpeedNegative ||
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
    _isVerticalSpeedNegative = frame->isVerticalSpeedNegative;
    _isVerticalSpeedHidden = frame->isVerticalSpeedHidden;

    selectScreen(); 
    _screen->clearDisplay();
    
    // CH
    _screen->setCursor(_x_offset + 4, _y_offset + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("CH"));

    // ARROW RIGHT
    _screen->fillRect(_x_offset + 32, _y_offset + 10, 24, 2, SSD1306_WHITE);
    _screen->fillRect(_x_offset + 54, _y_offset + 12, 2, 3, SSD1306_WHITE);

    // V/S
    _screen->setCursor(_x_offset + 64, _y_offset + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("V/S"));  

    if(_isFpa) {
        _screen->setCursor(_x_offset + 93, _y_offset + 16);
        _screen->setFont(&Nimbus_Sans_L_Bold_16);
        _screen->print(F("FPA"));
    }

    String verticalSpeedDisplay = String(_verticalSpeed);
    
    if(_isVerticalSpeedNegative) {
        verticalSpeedDisplay = "-" + verticalSpeedDisplay;
    } else {
        verticalSpeedDisplay = "+" + verticalSpeedDisplay; 
    }

    if(_isFpa) {
        verticalSpeedDisplay = " " + verticalSpeedDisplay.substring(0, verticalSpeedDisplay.length() - 1) + " ";
    } else {
        verticalSpeedDisplay = verticalSpeedDisplay.substring(0, verticalSpeedDisplay.length() - 2) + "o";
    }

    // V/S digit
    _screen->setCursor(_x_offset + 25, _y_offset + 45);
    _screen->setFont(&DSEG7_Classic_Mini_Bold_25);
    _screen->print(verticalSpeedDisplay);
        
    _screen->display();    
}