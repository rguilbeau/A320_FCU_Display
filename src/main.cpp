
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
#include "frame/LightIndicatorsFrame.h"
#include "frame/BrightnessFrame.h"

// Initialisation des objets du CAN Bus
MCP2515 mcp2515(PIN_CANBUS_CS_SPI);
struct can_frame frame;

// Les frames
FcuDisplayFrame fcuDisplayFrame;
LightIndicatorsFrame lightIndicatorsFrame;
BrightnessFrame brightnessFrame;

// Initialisation des objets des afficheurs
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SpeedDisplayer speedDisplayer(&display, OLED_SPEED_INDEX);
HeadingDisplayer headingDisplayer(&display, OLED_HEADING_INDEX);
NavModeDisplayer navModeDisplayer(&display, OLED_NAV_MODE_INDEX);
AltitudeDisplayer altitudeDisplayer(&display, OLED_ALTITUDE_INDEX);
VerticalDisplayer verticalDisplayer(&display, OLED_VERTICAL_INDEX);

// Flag pour forcer la mise à jour des écrans
// A true pour le 1er tours de loop
bool forceDisplayUpdate = true;

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
    SERIAL_PRINTLN("ID:" + String(frame.can_id));    
    
    // Décodage de la frame pour la gestion du mode test des lumières
    if(frame.can_id == FRAME_ID_LIGHT_INDICATORS) {
      lightIndicatorsFrame.decode(&frame);

      if(!lightIndicatorsFrame.isTestLight) {
        forceDisplayUpdate = true;
      }
    }

    // Décodage de la frame du rétro-éclairage
    else if(frame.can_id == FRAME_ID_BRIGHTNESS) {
      brightnessFrame.decode(&frame);
      speedDisplayer.setContrast(brightnessFrame.fcuDisplayContrast);
      headingDisplayer.setContrast(brightnessFrame.fcuDisplayContrast);
      navModeDisplayer.setContrast(brightnessFrame.fcuDisplayContrast);
      altitudeDisplayer.setContrast(brightnessFrame.fcuDisplayContrast);
      verticalDisplayer.setContrast(brightnessFrame.fcuDisplayContrast);
    }

    // Décodage de la frame FCU Display
    else if(frame.can_id == FRAME_ID_FCU_DISPLAY) {
      fcuDisplayFrame.decode(&frame);

      if(!fcuDisplayFrame.isPowerOn) {
        forceDisplayUpdate = true;
      }
    }

    // Mise à jour des écrans
    if(!fcuDisplayFrame.isPowerOn){
      speedDisplayer.displayNone();
      headingDisplayer.displayNone();
      navModeDisplayer.displayNone();
      altitudeDisplayer.displayNone();
      verticalDisplayer.displayNone();
    } else if(lightIndicatorsFrame.isTestLight) {
      speedDisplayer.displayTest();
      headingDisplayer.displayTest();
      navModeDisplayer.displayTest();
      altitudeDisplayer.displayTest();
      verticalDisplayer.displayTest();
    } else {
      if(speedDisplayer.checkMutation(&fcuDisplayFrame) || forceDisplayUpdate) {
        speedDisplayer.display(&fcuDisplayFrame);
      }

      if(headingDisplayer.checkMutation(&fcuDisplayFrame) || forceDisplayUpdate) {
        headingDisplayer.display(&fcuDisplayFrame);
      }

      if(navModeDisplayer.checkMutation(&fcuDisplayFrame) || forceDisplayUpdate) {
        navModeDisplayer.display(&fcuDisplayFrame);
      }

      if(altitudeDisplayer.checkMutation(&fcuDisplayFrame) || forceDisplayUpdate) {
        altitudeDisplayer.display(&fcuDisplayFrame);
      }

      if(verticalDisplayer.checkMutation(&fcuDisplayFrame) || forceDisplayUpdate) {
        verticalDisplayer.display(&fcuDisplayFrame);
      }
      
      forceDisplayUpdate = false;
    }    
  }
}