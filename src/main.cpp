#include "Setup.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <mcp2515.h>

#include "core/event/ButtonEvent.h"

#include "core/mcp_expander/McpExpander.h"
#include "core/input/McpExpanderInput.h"
#include "core/input/McpExpanderInputPullup.h"

#include "core/ihm/IhmInterface.h"
#include "core/ihm/Rotary.h"
#include "core/ihm/Button.h"
#include "core/ihm/Switch.h"

#include "core/output/ArduinoPwm.h"
#include "core/output/McpExpanderOutput.h"

#include "event_handler/RotaryEventHandler.h"
#include "event_handler/ButtonEventHandler.h"
#include "event_handler/SwitchEventHandler.h"
#include "event_handler/CanBusEventHandler.h"

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

const int ihmSize = 22;
IhmInterface *ihm[ihmSize] = {
  // SPD
  new Rotary(new McpExpanderInput(&mcp1, PIN_SPD_ROTARY_A), new McpExpanderInput(&mcp1, PIN_SPD_ROTARY_B), new RotaryEventHandler(&canBus, 0x1)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_SPD_PUSH), new ButtonEventHandler(&canBus, 0x3)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_SPD_PULL), new ButtonEventHandler(&canBus, 0x4)),
  
  // HDG
  new Rotary(new McpExpanderInput(&mcp1, PIN_HDG_ROTARY_A), new McpExpanderInput(&mcp1, PIN_HDG_ROTARY_B), new RotaryEventHandler(&canBus, 0x2)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_HDG_PUSH), new ButtonEventHandler(&canBus, 0x5)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_HDG_PULL), new ButtonEventHandler(&canBus, 0x6)),

  // ALT
  new Rotary(new McpExpanderInput(&mcp1, PIN_ALT_ROTARY_A), new McpExpanderInput(&mcp1, PIN_ALT_ROTARY_B), new RotaryEventHandler(&canBus, 0x3)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_ALT_PUSH), new ButtonEventHandler(&canBus, 0x7)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_ALT_PULL), new ButtonEventHandler(&canBus, 0x8)),
  new Switch(new McpExpanderInputPullup(&mcp1, PIN_ALT_SWITCH), new SwitchEventHandler(&canBus, 0x9)),

  // V/S
  new Rotary(new McpExpanderInput(&mcp1, PIN_VS_ROTARY_A), new McpExpanderInput(&mcp1, PIN_VS_ROTARY_B), new RotaryEventHandler(&canBus, 0x4)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_VS_PUSH), new ButtonEventHandler(&canBus, 0xa)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_VS_PULL),  new ButtonEventHandler(&canBus, 0xb)),

  // Toggle button
  new Button(new McpExpanderInputPullup(&mcp1, PIN_SPD_MACH), new ButtonEventHandler(&canBus, 0xc)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_FPA_VS), new ButtonEventHandler(&canBus, 0xd)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_MATRIC_ALT), new ButtonEventHandler(&canBus, 0xe)),

  // AP
  new Button(new McpExpanderInputPullup(&mcp1, PIN_AP1), new ButtonEventHandler(&canBus, 0xf)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_AP2), new ButtonEventHandler(&canBus, 0x0a)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_ATHR), new ButtonEventHandler(&canBus, 0x0b)),

  // Apporch
  new Button(new McpExpanderInputPullup(&mcp1, PIN_LOC), new ButtonEventHandler(&canBus, 0xac)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_APPR), new ButtonEventHandler(&canBus, 0x0d)),
  new Button(new McpExpanderInputPullup(&mcp1, PIN_EXPED), new ButtonEventHandler(&canBus, 0x0e)),
};


void setup() {
  SERIAL_BEGIN(9600);
  SERIAL_PRINTLN(F("Setup..."));

  Wire.begin();
  mcp1.begin(MCP1_ADDR);
  mcp2.begin(MCP2_ADDR);
  
  canBus.begin();

  SERIAL_PRINTLN("End of setup");
}

void loop() {
  // Lecture des broches des mcp23017
  mcp1.loop();
  mcp2.loop();

  // Recherche d'évenement sur les IHM
  bool eventTriggered = false;
  for(int i = 0; i < ihmSize; i++) {
    bool event = ihm[i]->loop();
    eventTriggered = eventTriggered || event;
  }

  if(!eventTriggered) {
    // Pas de loop pour le canbus si un évenement a été triggé
    // pour laisser la priorité sur les boutons et rotary encodeur
    canBus.loop();
  }
}