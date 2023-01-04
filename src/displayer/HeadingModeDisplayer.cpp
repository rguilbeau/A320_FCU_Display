#include "HeadingModeDisplayer.h"

/**
 * @brief Construction de l'afficheur pour l'écran OLED du mode du cap (headinfg/track)
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 * @param x_offset L'offset x des curseurs
 * @param y_offset L'offset y des les curseurs
 */
HeadingModeDisplayer::HeadingModeDisplayer(
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
bool HeadingModeDisplayer::checkMutation(FcuDisplayFrame *frame)
{
    return _isTrackMode != frame->isTrackMode;
}

/**
 * @brief Rafraichissement l'écran avec les données de la frame
 * 
 * @param frame La nouvelle frame
 */
void HeadingModeDisplayer::display(FcuDisplayFrame *frame)
{
    _isTrackMode = frame->isTrackMode;

    selectScreen(); 
    _screen->clearDisplay();
    
    if(_isTrackMode) {
        _screen->setCursor(_x_offset + 92, _y_offset + 45);
        _screen->setFont(&Nimbus_Sans_L_Bold_16);
        _screen->print(F("TRK")); 
    } else {
        _screen->setCursor(_x_offset + 90, _y_offset + 30);
        _screen->setFont(&Nimbus_Sans_L_Bold_16);
        _screen->print(F("HDG"));  
    }
    
    _screen->display();    
}