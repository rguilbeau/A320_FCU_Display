#include "AltitudeDisplayer.h"

/**
 * @brief Construction de l'afficheur pour l'écran OLED de l'altitude
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 */
AltitudeDisplayer::AltitudeDisplayer(
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
bool AltitudeDisplayer::checkMutation(FcuDisplayFrame *frame)
{
    return 
        _isAltitudeHidden != frame->isAltitudeHidden ||
        _isAltitudeForced != frame->isAltitudeForced ||
        _altitude != frame->altitude;
}

/**
 * @brief Rafraichissement l'écran avec les données de la frame
 * 
 * @param frame La nouvelle frame
 */
void AltitudeDisplayer::display(FcuDisplayFrame *frame)
{
    _isAltitudeHidden = frame->isAltitudeHidden;
    _isAltitudeForced = frame->isAltitudeForced;
    _altitude = frame->altitude;

    selectScreen(); 
    _screen->clearDisplay();
    
    //ALT
    _screen->setCursor(X_OFFSET + 24, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("ALT"));

    // ARROW LEFT
    _screen->fillRect(X_OFFSET + 65, Y_OFFSET + 10, 24, 2, SSD1306_WHITE);
    _screen->fillRect(X_OFFSET + 65, Y_OFFSET + 12, 2, 3, SSD1306_WHITE);

    //LVL
    _screen->setCursor(X_OFFSET + 93, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("LVL"));

    String altitudeDisplay;
    if(_isAltitudeHidden) {
        altitudeDisplay = "-----";
    } else {
        altitudeDisplay = leftPad(_altitude, 5);
    }

    if(!_isAltitudeForced) {
        altitudeDisplay += "*";
    }

    // ALT digit
    _screen->setCursor(X_OFFSET + 0, Y_OFFSET + 45);
    _screen->setFont(&DSEG7_Classic_Mini_Bold_25);
    _screen->print(altitudeDisplay);
        
    _screen->display();    
}