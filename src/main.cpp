#include "Setup.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <mcp2515.h>

#include "displayer/SpeedDisplayer.h"
#include "displayer/HeadingDisplayer.h"
#include "displayer/HeadingModeDisplayer.h"
#include "displayer/VerticalModeDisplayer.h"
#include "displayer/AltitudeDisplayer.h"
#include "displayer/VerticalDisplayer.h"

#include "frame/FcuDisplayFrame.h"

// Initialisation des objets du CAN Bus
MCP2515 mcp2515(PIN_CANBUS_CS_SPI);
struct can_frame frame;
FcuDisplayFrame fcuDisplayFrame;

// Initialisation des objets des afficheurs
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SpeedDisplayer speedDisplayer(&display, 0, X_OFFSET, Y_OFFSET);
HeadingDisplayer headingDisplayer(&display, 1, X_OFFSET, Y_OFFSET);
HeadingModeDisplayer headingModeDisplayer(&display, 1, X_OFFSET, Y_OFFSET);
VerticalModeDisplayer verticalModeDisplayer(&display, 1, X_OFFSET, Y_OFFSET);
AltitudeDisplayer altitudeDisplayer(&display, 1, X_OFFSET, Y_OFFSET);
VerticalDisplayer verticalDisplayer(&display, 1, X_OFFSET, Y_OFFSET);

/**
 * @brief Initialisation du CAN Bus et des afficheurs
 * 
 */
void setup() {
  SERIAL_BEGIN(9600);

  SERIAL_PRINTLN("Starting...");
  speedDisplayer.displayInit();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  delay(5000);
  SERIAL_PRINTLN("Started !");
}

/**
 * @brief Récéption des messages du CAN Bus et rafraichissement des afficheurs
 * 
 */
void loop() {

  // Récétion des messages du CAN Bus
  MCP2515::ERROR error = mcp2515.readMessage(&frame);

  if(error != MCP2515::ERROR_OK && error != MCP2515::ERROR_NOMSG) {
    // ERROR_OK        = 0
    // ERROR_FAIL      = 1
    // ERROR_ALLTXBUSY = 2
    // ERROR_FAILINIT  = 3
    // ERROR_FAILTX    = 4
    // ERROR_NOMSG     = 5
    SERIAL_PRINTLN("Can bus message failed. errno:" + String(error));
  } else if (error == MCP2515::ERROR_OK) {
    
    fcuDisplayFrame.decode(&frame);
    
    if(speedDisplayer.checkMutation(&fcuDisplayFrame)) {
      speedDisplayer.display(&fcuDisplayFrame);
    }
    
    if(headingDisplayer.checkMutation(&fcuDisplayFrame)) {
      headingDisplayer.display(&fcuDisplayFrame);
    }

    if(headingModeDisplayer.checkMutation(&fcuDisplayFrame)) {
      headingModeDisplayer.display(&fcuDisplayFrame);
    }

    if(verticalModeDisplayer.checkMutation(&fcuDisplayFrame)) {
      verticalModeDisplayer.display(&fcuDisplayFrame);
    }

    if(altitudeDisplayer.checkMutation(&fcuDisplayFrame)) {
      altitudeDisplayer.display(&fcuDisplayFrame);
    }

    if(verticalDisplayer.checkMutation(&fcuDisplayFrame)) {
      verticalDisplayer.display(&fcuDisplayFrame);
    }
  }
}