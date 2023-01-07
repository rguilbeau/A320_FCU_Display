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
 */
Displayer::Displayer(
    Adafruit_SSD1306 *screen, 
    short indexDisplay
) {
    _screen = screen;
    _indexDisplay = indexDisplay;
}

/**
 * @brief Afifiche "init display" sur l'écran
 * 
 */
void Displayer::begin()
{
    selectScreen();
    _screen->begin(SSD1306_EXTERNALVCC, SCREEN_ADDRESS);
    
    _screen->setContrast(100);
    
    _screen->setTextColor(SSD1306_WHITE);

    _screen->clearDisplay();
    _screen->setRotation(2);
    _screen->setCursor(X_OFFSET + 15, Y_OFFSET + 16);
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
 * @brief Changement de contraste (rétroéclairage) de l'écran
 * 
 * @param value 
 */
void Displayer::setContrast(short value)
{
    selectScreen();
    _screen->setContrast(value);
}

/**
 * @brief Séléctione un écran sur le multiplexeur I2C
 * 
 */
void Displayer::selectScreen()
{
    if(Displayer::_selectedScreen != _indexDisplay) {
        Wire.beginTransmission(0x70);  // TCA9548A address
        Wire.write(1 << _indexDisplay);
        Wire.endTransmission();
        Displayer::_selectedScreen = _indexDisplay;
    }
}