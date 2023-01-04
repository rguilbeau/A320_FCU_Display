#include "Displayer.h"

/**
 * @brief L'écran actuellement séléctionnée sur le multiplexeur I2C
 * 
 */
short Displayer::_selectedScreen = -1;

/**
 * @brief Construction de l'afficheur pour un écran OLED
 * 
 * @param screen Le driver Adafruit_SSD1306 pour le pilotage de l'écran
 * @param indexDisplay L'index de l'écran sur le multiplexer I2C
 * @param x_offset L'offset x des curseurs
 * @param y_offset L'offset y des les curseurs
 */
Displayer::Displayer(
    Adafruit_SSD1306 *screen, 
    short indexDisplay, 
    short x_offset, 
    short y_offset
) {
    _screen = screen;
    _indexDisplay = indexDisplay;
    _x_offset = x_offset;
    _y_offset = y_offset;

    selectScreen();
    _screen->begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
    _screen->setTextColor(SSD1306_WHITE);
    _screen->clearDisplay();
    _screen->display();
}

/**
 * @brief Afifiche "init display" sur l'écran
 * 
 */
void Displayer::displayInit()
{
    selectScreen();
    _screen->clearDisplay();
    _screen->setCursor(_x_offset + 30, _y_offset + 16);
    _screen->setFont(&Nimbus_Sans_L_Bold_16);
    _screen->print(F("init display"));
    _screen->display();
}

/**
 * @brief Ajoute les "leading zero"
 * 
 * @param value La valeurs à laquelle ajouter les "leading zero"
 * @param size Le nombre de charactère total de la chaine de caractère voulu
 * @return String Le chaine de caractère avec les "leading zero"
 */
String Displayer::leftPad(int value, int size)
{
    char buff[size + 1];
    String format = "%." + String(size) + "u";
    sprintf(buff, format.c_str(), value);
    return String(buff);
}

/**
 * @brief Séléctione un écran sur le multiplexeur I2C
 * 
 */
void Displayer::selectScreen()
{
    if(Displayer::_selectedScreen != _indexDisplay) {
        // switch i2c
        Displayer::_selectedScreen = _indexDisplay;
    }
}