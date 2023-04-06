#include "SpeedDisplayer.h"

/**
 * @brief Construction de l'afficheur pour l'écran OLED de la vitesse
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 */
SpeedDisplayer::SpeedDisplayer(
    Adafruit_SSD1306 *screen, 
    short indexDisplay
) : Displayer(
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
bool SpeedDisplayer::checkMutation(FcuDisplayFrame *frame) 
{
    return 
        _isMachSpeed != frame->isMachSpeed ||
        _speed != frame->speed ||
        _isSpeedDash != frame->isSpeedDash ||
        _isSpeedDot != frame->isSpeedDot;
}

void SpeedDisplayer::displayTest()
{
    selectScreen();
    _screen->clearDisplay();
    printSpeedIndicator();
    printMachIndicator();
    printDigit(F("888*"));
    _screen->display();
}

/**
 * @brief Rafraichissement l'écran avec les données de la frame
 * 
 * @param frame La nouvelle frame
 */
void SpeedDisplayer::display(FcuDisplayFrame *frame)
{
    _isMachSpeed = frame->isMachSpeed;
    _speed = frame->speed;
    _isSpeedDash = frame->isSpeedDash;
    _isSpeedDot = frame->isSpeedDot;

    selectScreen();

    _screen->clearDisplay();
    String speedDisplay = "";

    if(_isMachSpeed) {
        printMachIndicator();
        speedDisplay = String(_speed);
    } else {
        printSpeedIndicator();
        speedDisplay = leftPad((int)_speed, 3);
    }

    if(_isSpeedDash) {
        speedDisplay = "---";
    }

    if(_isSpeedDot) {
        speedDisplay += "*";
    }

    printDigit(speedDisplay);
    _screen->display();
}

void SpeedDisplayer::printSpeedIndicator()
{
    _screen->setCursor(X_OFFSET + 4, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("SPD"));
}

void SpeedDisplayer::printMachIndicator()
{
    _screen->setCursor(X_OFFSET + 46, Y_OFFSET + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("MACH"));
}

void SpeedDisplayer::printDigit(String digit)
{
    _screen->setCursor(X_OFFSET + 31, Y_OFFSET + 45);
    _screen->setFont(&DSEG7_Classic_Mini_Bold_25);
    _screen->print(digit);
}