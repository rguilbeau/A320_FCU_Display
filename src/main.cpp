#include "setup.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "can_bus/can_bus.hpp"
#include "event_handler/can_bus_event_handler.hpp"

#include "displayer/speed_displayer.hpp"
#include "displayer/heading_displayer.hpp"
#include "displayer/nav_mode_displayer.hpp"
#include "displayer/altitude_displayer.hpp"
#include "displayer/vertical_displayer.hpp"

const uint16_t numberFilters = 3;
const uint32_t filters[numberFilters] = 
{
  e_frameId::FCU_DISPLAY,
  e_frameId::BRIGTNESS_PANEL,
  e_frameId::POWER
};

// Initialisation des objets des afficheurs
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
SpeedDisplayer speedDisplayer(&display, OLED_SPEED_INDEX);
HeadingDisplayer headingDisplayer(&display, OLED_HEADING_INDEX);
NavModeDisplayer navModeDisplayer(&display, OLED_NAV_MODE_INDEX);
AltitudeDisplayer altitudeDisplayer(&display, OLED_ALTITUDE_INDEX);
VerticalDisplayer verticalDisplayer(&display, OLED_VERTICAL_INDEX);

uint8_t nDisplayerSize = 5;
Displayer *displayers[] = {&speedDisplayer, &headingDisplayer, &navModeDisplayer, &altitudeDisplayer, &verticalDisplayer};

CanBus canbus(
  PIN_CANBUS_CS_SPI, 
  new CanBusEventHandler(
    &speedDisplayer,
    &headingDisplayer,
    &navModeDisplayer,
    &altitudeDisplayer,
    &verticalDisplayer
  )
);

/**
 * @brief Initialisation des écrans et du CAN Bus
 * 
 */
void setup() 
{
  SERIAL_BEGIN(9600);

  SERIAL_PRINTLN(F("Starting..."));

  Wire.begin();
  Wire.setClock(400000); // I2C fast mode

  speedDisplayer.begin(SCREEN_ADDRESS);
  headingDisplayer.begin(SCREEN_ADDRESS);
  navModeDisplayer.begin(SCREEN_ADDRESS);
  altitudeDisplayer.begin(SCREEN_ADDRESS);
  verticalDisplayer.begin(SCREEN_ADDRESS);

  canbus.begin(filters, numberFilters);
  delay(3000);

  SERIAL_PRINTLN(F("Started !"));
}

/**
 * @brief Attente et traitement des messages du CAN Bus
 * 
 */
void loop() 
{
  for(uint8_t nIndexDisplayer = 0; nIndexDisplayer < nDisplayerSize; nIndexDisplayer++)
  {
    canbus.loop(); // call can loop between each display update, can avoid lost messages
    displayers[nIndexDisplayer]->loop();
  }
}