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
SpeedDisplayer speedDisplayer(&display, OLED_SPEED_INDEX);
HeadingDisplayer headingDisplayer(&display, OLED_HEADING_INDEX);
NavModeDisplayer navModeDisplayer(&display, OLED_NAV_MODE_INDEX);
AltitudeDisplayer altitudeDisplayer(&display, OLED_ALTITUDE_INDEX);
VerticalDisplayer verticalDisplayer(&display, OLED_VERTICAL_INDEX);

// Flag pour forcer la 1ère mise à jour
bool firstInit = true;
bool isLightTestMode = false;
bool isPowerOff = true;

/**
 * @brief Initialisation des écrans et du CAN Bus
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
 * @brief Attente et traitement des messages du CAN Bus
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
    
    /**
     *  Gestion du rétroéclairage des écrans
     */
    if(frame.can_id == 0x65) {
      short contrast = (short)frame.data[1];
      if(contrast > 100) {
        contrast = 100;
      }
      speedDisplayer.setContrast(contrast);
      headingDisplayer.setContrast(contrast);
      navModeDisplayer.setContrast(contrast);
      altitudeDisplayer.setContrast(contrast);
      verticalDisplayer.setContrast(contrast);

      bool testLight[] = {0,0,0,0,0,0,0,0};
      FcuDisplayFrame::binaryConvert(frame.data[0], testLight);

      if(testLight[0]) {
        isLightTestMode = true;
      } else {
        isLightTestMode = false;
        firstInit = true;
      }
    }


    else if(frame.can_id == 0x12C) {
      bool electBus[] = {0,0,0,0,0,0,0,0};
      FcuDisplayFrame::binaryConvert(frame.data[0], electBus);

      if(electBus[0]) {
        isPowerOff = false;
        firstInit = true;
      } else {
        isPowerOff = true;
      }
    }


    /**
     * Mise à jour des écrans avec les informations
     * de la frame
     */
    else if(frame.can_id == 0x64) {
      fcuDisplayFrame.decode(&frame);
    }

    if(isPowerOff){
      speedDisplayer.displayNone();
      headingDisplayer.displayNone();
      navModeDisplayer.displayNone();
      altitudeDisplayer.displayNone();
      verticalDisplayer.displayNone();
    } else if(isLightTestMode) {
      speedDisplayer.displayTest();
      headingDisplayer.displayTest();
      navModeDisplayer.displayTest();
      altitudeDisplayer.displayTest();
      verticalDisplayer.displayTest();
    } else {
      if(speedDisplayer.checkMutation(&fcuDisplayFrame) || firstInit) {
        speedDisplayer.display(&fcuDisplayFrame);
      }

      if(headingDisplayer.checkMutation(&fcuDisplayFrame) || firstInit) {
        headingDisplayer.display(&fcuDisplayFrame);
      }

      if(navModeDisplayer.checkMutation(&fcuDisplayFrame) || firstInit) {
        navModeDisplayer.display(&fcuDisplayFrame);
      }

      if(altitudeDisplayer.checkMutation(&fcuDisplayFrame) || firstInit) {
        altitudeDisplayer.display(&fcuDisplayFrame);
      }

      if(verticalDisplayer.checkMutation(&fcuDisplayFrame) || firstInit) {
        verticalDisplayer.display(&fcuDisplayFrame);
      }
      
      firstInit = false;
    }    
  }
}