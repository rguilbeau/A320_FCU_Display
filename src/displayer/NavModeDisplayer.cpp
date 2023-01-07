#include "NavModeDisplayer.h"

/**
 * @brief Construction de l'afficheur pour l'écran OLED du mode du cap (headinfg/track)
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 */
NavModeDisplayer::NavModeDisplayer(
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
bool NavModeDisplayer::checkMutation(FcuDisplayFrame *frame)
{
    return 
        _isTrackMode != frame->isTrackMode ||
        _isFpa != frame->isFpa;
}

/**
 * @brief Rafraichissement l'écran avec les données de la frame
 * 
 * @param frame La nouvelle frame
 */
void NavModeDisplayer::display(FcuDisplayFrame *frame)
{
    _isTrackMode = frame->isTrackMode;
    _isFpa = frame->isFpa;

    selectScreen(); 
    _screen->clearDisplay();
    

    _screen->setFont(&Nimbus_Sans_L_Bold_16);


    if(_isTrackMode) {
        _screen->setCursor(X_OFFSET + 15, Y_OFFSET + 45);
        _screen->print(F("TRK")); 
    } else {
        _screen->setCursor(X_OFFSET + 15, Y_OFFSET + 30);
        _screen->print(F("HDG"));  
    }

    if(_isFpa) {
        _screen->setCursor(X_OFFSET + 75, Y_OFFSET + 45);
        _screen->print(F("FPA")); 
    } else {
        _screen->setCursor(X_OFFSET + 75, Y_OFFSET + 30);
        _screen->print(F("V/S"));  
    }
    
    _screen->display();    
}