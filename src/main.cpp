#include "Setup.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <mcp2515.h>

#include "A320_Core/event/ButtonEvent.h"

#include "A320_Core/mcp_expander/McpExpander.h"
#include "A320_Core/input/McpExpanderInput.h"
#include "A320_Core/input/McpExpanderInputPullup.h"

#include "A320_Core/ihm/IhmInterface.h"
#include "A320_Core/ihm/Rotary.h"
#include "A320_Core/ihm/Button.h"
#include "A320_Core/ihm/Switch.h"

#include "A320_Core/output/ArduinoPwm.h"
#include "A320_Core/output/McpExpanderOutput.h"

#include "event_handler/RotaryEventHandler.h"
#include "event_handler/ButtonEventHandler.h"
#include "event_handler/SwitchEventHandler.h"
#include "event_handler/CanBusEventHandler.h"

const unsigned int numberFilters = 2;
const unsigned long filters[numberFilters] = {
  BrightnessFrame::ID, 
  GlareshieldIndicatorsFrame::ID
};

McpExpander mcp1;
McpExpander mcp2;

CanBus canBus(
  PIN_CAN_BUS_CS, 
  new CanBusEventHandler(
    new Light(new McpExpanderOutput(&mcp2, PIN_AP1_INDICATOR)),
    new Light(new McpExpanderOutput(&mcp2, PIN_AP2_INDICATOR)),
    new Light(new McpExpanderOutput(&mcp2, PIN_ATHR_INDICATOR)),
    new Light(new McpExpanderOutput(&mcp2, PIN_LOC_INDICATOR)),
    new Light(new McpExpanderOutput(&mcp2, PIN_EXPED_INDICATOR)),
    new Light(new McpExpanderOutput(&mcp2, PIN_APPR_INDICATOR)),
    new ArduinoPwm(PIN_BACKLIGHT_INDICATOR),
    new ArduinoPwm(PIN_BACKLIGHT_BUTTON),
    new ArduinoPwm(PIN_BACKLIGHT_PANEL)
  )
);

const int ihmSize = 13;
IhmInterface *ihm[ihmSize];

void setup() {
  SERIAL_BEGIN(9600);
  SERIAL_PRINTLN(F("Setup..."));

  Wire.begin();
 // ArduinoPwmTest toto(PIN_BACKLIGHT_INDICATOR);
  mcp1.begin(MCP1_ADDR);
  mcp2.begin(MCP2_ADDR);
  
  canBus.begin(filters, numberFilters);

  // SPD 
  ihm[0] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_SPD_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_SPD_ROTARY_B), new RotaryEventHandler(&canBus, EVENT_FCU_SPD_BUG));
  ihm[1] = new Button(new McpExpanderInputPullup(&mcp1, PIN_SPD_PUSH), new ButtonEventHandler(&canBus, EVENT_FCU_SPD_PUSH));
  ihm[2] = new Button(new McpExpanderInputPullup(&mcp1, PIN_SPD_PULL), new ButtonEventHandler(&canBus, EVENT_FCU_SPD_PULL));
  
  // HDG
  ihm[3] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_HDG_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_HDG_ROTARY_B), new RotaryEventHandler(&canBus, EVENT_FCU_HDG_BUG));
  ihm[4] = new Button(new McpExpanderInputPullup(&mcp1, PIN_HDG_PUSH), new ButtonEventHandler(&canBus, EVENT_FCU_HDG_PUSH));
  ihm[5] = new Button(new McpExpanderInputPullup(&mcp1, PIN_HDG_PULL), new ButtonEventHandler(&canBus, EVENT_FCU_HDG_PULL));

  // ALT
  ihm[6] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_ALT_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_ALT_ROTARY_B), new RotaryEventHandler(&canBus, EVENT_FCU_ALT_BUG));
  ihm[7] = new Button(new McpExpanderInputPullup(&mcp1, PIN_ALT_PUSH), new ButtonEventHandler(&canBus, EVENT_FCU_ALT_PUSH));
  ihm[8] = new Button(new McpExpanderInputPullup(&mcp1, PIN_ALT_PULL), new ButtonEventHandler(&canBus, EVENT_FCU_ALT_PULL));
  ihm[9] = new Switch(new McpExpanderInputPullup(&mcp2, PIN_ALT_SWITCH), new SwitchEventHandler(&canBus, EVENT_FCU_ALT_STEP));
  
  // VS
  ihm[10] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_VS_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_VS_ROTARY_B), new RotaryEventHandler(&canBus, EVENT_FCU_VS_BUG));
  ihm[11] = new Button(new McpExpanderInputPullup(&mcp1, PIN_VS_PUSH), new ButtonEventHandler(&canBus, EVENT_FCU_VS_PUSH));
  ihm[12] = new Button(new McpExpanderInputPullup(&mcp1, PIN_VS_PULL),  new ButtonEventHandler(&canBus, EVENT_FCU_VS_PULL));

  /*// Toggle buttons
  ihm[13] = new Button(new McpExpanderInputPullup(&mcp2, PIN_SPD_MACH), new ButtonEventHandler(&canBus, 0xc));
  ihm[14] = new Button(new McpExpanderInputPullup(&mcp2, PIN_FPA_VS), new ButtonEventHandler(&canBus, 0xd));
  ihm[15] = new Button(new McpExpanderInputPullup(&mcp2, PIN_MATRIC_ALT), new ButtonEventHandler(&canBus, 0xe));
  
  // AP1, AP2, ATHR
  ihm[16] = new Button(new McpExpanderInputPullup(&mcp2, PIN_AP1), new ButtonEventHandler(&canBus, 0xf));
  ihm[17] = new Button(new McpExpanderInputPullup(&mcp2, PIN_AP2), new ButtonEventHandler(&canBus, 0x0a));
  ihm[18] = new Button(new McpExpanderInputPullup(&mcp2, PIN_ATHR), new ButtonEventHandler(&canBus, 0x0b));
  
  // APPR, LOC, EXPED
  ihm[19] = new Button(new McpExpanderInputPullup(&mcp2, PIN_LOC), new ButtonEventHandler(&canBus, 0xac));
  ihm[20] = new Button(new McpExpanderInputPullup(&mcp2, PIN_APPR), new ButtonEventHandler(&canBus, 0x0d));
  ihm[21] = new Button(new McpExpanderInputPullup(&mcp2, PIN_EXPED), new ButtonEventHandler(&canBus, 0x0e));*/

  SERIAL_PRINTLN("End of setup");
}

void loop() {
 // Lecture des broches des mcp23017
  mcp1.loop();
  mcp2.loop();

  // Recherche d'évenement sur les IHM
  for(int i = 0; i < ihmSize; i++) {
    ihm[i]->loop();
  }
  
  canBus.loop();
}