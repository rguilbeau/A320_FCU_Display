#ifndef FCU_DISPLAYER_H
#define FCU_DISPLAYER_H

#include "Arduino.h"
#include "Adafruit_SSD1306.h"
#include "fonts/Nimbus_Sans_L_Bold_16.h"
#include "fonts/DSEG7_Classic_Mini_Bold_25.h"
#include "frame/FcuDisplayFrame.h"
#include "Setup.h"

class Displayer
{

    public:
        void displayInit();

    protected:
        Displayer(Adafruit_SSD1306 *screen, short indexDisplay, short x_offset, short y_offset);

        Adafruit_SSD1306 *_screen;

        short _indexDisplay;
        short _x_offset;
        short _y_offset;

        String leftPad(int value, int size);
        void selectScreen();
        
    private:
        static short  _selectedScreen;
};

#endif