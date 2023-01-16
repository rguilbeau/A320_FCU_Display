#include "HeadingDisplayer.h"

/**
 * @brief Construction de l'afficheur pour l'écran OLED du cap
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 */
HeadingDisplayer::HeadingDisplayer(
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
bool HeadingDisplayer::checkMutation(FcuDisplayFrame *frame)
{
    return 
        _isTrackMode != frame->isTrackMode ||
        _isLatNavigation !=  frame->isLatNavigation ||
        _heading != frame->heading ||
        _isHeadingHidden != frame->isHeadingHidden ||
        _isHeadingForced != frame->isHeadingForced;
}

void HeadingDisplayer::displayTest()
{
    selectScreen();
    _screen->clearDisplay();
    printHeadingIndicator();
    printTrackIndicator();
    printLatIndicator();
    printDigit(F("888*"));
    _screen->display();
}

/**
 * @brief Rafraichissement l'écran avec les données de la frame
 * 
 * @param frame La nouvelle frame
 */
void HeadingDisplayer::display(FcuDisplayFrame *frame)
{
    _isTrackMode = frame->isTrackMode;
    _isLatNavigation = frame->isLatNavigation;
    _heading = frame->heading;
    _isHeadingHidden = frame->isHeadingHidden;
    _isHeadingForced = frame->isHeadingForced;

    selectScreen();
    _screen->clearDisplay();
    
    if(_isTrackMode) {
        printTrackIndicator();
        
    } else {
        printHeadingIndicator();
    }

    if(_isLatNavigation) {
        printLatIndicator();
    }

    String headingDisplay;
    if(_isHeadingHidden) {
        headingDisplay = "---";
    } else {
        headingDisplay = leftPad(_heading, 3);
    }

    if(!_isHeadingForced) {
        headingDisplay += "*";
    }

    // HDG digit
    printDigit(headingDisplay);

    _screen->display();    
}

void HeadingDisplayer::printHeadingIndicator()
{
    _screen->setCursor(X_OFFSET + 4, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("HDG"));
}

void HeadingDisplayer::printTrackIndicator()
{
    _screen->setCursor(X_OFFSET + 48, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("TRK"));
}

void HeadingDisplayer::printLatIndicator()
{
    _screen->setCursor(X_OFFSET + 92, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("LAT"));
}

void HeadingDisplayer::printDigit(String digit)
{
    _screen->setCursor(X_OFFSET + 31, Y_OFFSET + 45);
    _screen->setFont(&DSEG7_Classic_Mini_Bold_25);
    _screen->print(digit);
}