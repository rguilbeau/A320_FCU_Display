#include "Setup.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <mcp2515.h>

#include "displayer/SpeedDisplayer.h"
#include "displayer/HeadingDisplayer.h"
#include "displayer/NavModeDisplayer.h"
#include "displayer/AltitudeDisplayer.h"
#include "displayer/VerticalDisplayer.h"

#include "frame/FcuDisplayFrame.h"

// Initialisation des objets du CAN Bus
MCP2515 mcp2515(PIN_CANBUS_CS_SPI);
struct can_frame frame;
FcuDisplayFrame fcuDisplayFrame;

// Initialisation des objets des afficheurs
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

SpeedDisplayer speedDisplayer(&display, 7);
HeadingDisplayer headingDisplayer(&display, 6);
NavModeDisplayer navModeDisplayer(&display, 5);
AltitudeDisplayer altitudeDisplayer(&display, 4);
VerticalDisplayer verticalDisplayer(&display, 3);

/**
 * @brief Initialisation du CAN Bus et des afficheurs
 * 
 */
void setup() {
  SERIAL_BEGIN(9600);

  SERIAL_PRINTLN(F("Starting..."));

  Wire.begin();
  speedDisplayer.begin();
  headingDisplayer.begin();
  navModeDisplayer.begin();
  altitudeDisplayer.begin();
  verticalDisplayer.begin();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  delay(5000);
  SERIAL_PRINTLN(F("Started !"));
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
    Serial.println(frame.can_id);
    
    fcuDisplayFrame.decode(&frame);
    
    if(speedDisplayer.checkMutation(&fcuDisplayFrame)) {
      speedDisplayer.display(&fcuDisplayFrame);
    }
    
    if(headingDisplayer.checkMutation(&fcuDisplayFrame)) {
      headingDisplayer.display(&fcuDisplayFrame);
    }

    if(navModeDisplayer.checkMutation(&fcuDisplayFrame)) {
      navModeDisplayer.display(&fcuDisplayFrame);
    }

    if(altitudeDisplayer.checkMutation(&fcuDisplayFrame)) {
      altitudeDisplayer.display(&fcuDisplayFrame);
    }

    if(verticalDisplayer.checkMutation(&fcuDisplayFrame)) {
      verticalDisplayer.display(&fcuDisplayFrame);
    }
  }
}