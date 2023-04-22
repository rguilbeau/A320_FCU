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

const int ihmSize = 13;
IhmInterface *ihm[ihmSize];


void setup() {
  SERIAL_BEGIN(9600);
  SERIAL_PRINTLN(F("Setup..."));

  Wire.begin();

  mcp1.begin(MCP1_ADDR);
  mcp2.begin(MCP2_ADDR);
  
  canBus.begin();

  // SPD
  ihm[0] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_SPD_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_SPD_ROTARY_B), new RotaryEventHandler(&canBus, 0x1));
  ihm[1] = new Button(new McpExpanderInputPullup(&mcp1, PIN_SPD_PUSH), new ButtonEventHandler(&canBus, 0x3));
  ihm[2] = new Button(new McpExpanderInputPullup(&mcp1, PIN_SPD_PULL), new ButtonEventHandler(&canBus, 0x4));
  
  // HDG
  ihm[3] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_HDG_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_HDG_ROTARY_B), new RotaryEventHandler(&canBus, 0x2));
  ihm[4] = new Button(new McpExpanderInputPullup(&mcp1, PIN_HDG_PUSH), new ButtonEventHandler(&canBus, 0x5));
  ihm[5] = new Button(new McpExpanderInputPullup(&mcp1, PIN_HDG_PULL), new ButtonEventHandler(&canBus, 0x6));

  // ALT
  ihm[6] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_ALT_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_ALT_ROTARY_B), new RotaryEventHandler(&canBus, 0x3));
  ihm[7] = new Button(new McpExpanderInputPullup(&mcp1, PIN_ALT_PUSH), new ButtonEventHandler(&canBus, 0x7));
  ihm[8] = new Button(new McpExpanderInputPullup(&mcp1, PIN_ALT_PULL), new ButtonEventHandler(&canBus, 0x8));
  ihm[9] = new Switch(new McpExpanderInputPullup(&mcp2, PIN_ALT_SWITCH), new SwitchEventHandler(&canBus, 0x9));
  
  // VS
  ihm[10] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_VS_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_VS_ROTARY_B), new RotaryEventHandler(&canBus, 0x4));
  ihm[11] = new Button(new McpExpanderInputPullup(&mcp1, PIN_VS_PUSH), new ButtonEventHandler(&canBus, 0xa));
  ihm[12] = new Button(new McpExpanderInputPullup(&mcp1, PIN_VS_PULL),  new ButtonEventHandler(&canBus, 0xb));

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