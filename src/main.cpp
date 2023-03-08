#include "Setup.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <mcp2515.h>

#include "mcp/Mcp.h"
#include "pin/McpInput.h"
#include "pin/McpInputPullup.h"

#include "ihm/IhmInterface.h"
#include "ihm/Rotary.h"
#include "ihm/Button.h"
#include "ihm/Switch.h"

#include "event_handler/RotaryEventHandler.h"
#include "event_handler/ButtonEventHandler.h"
#include "event_handler/SwitchEventHandler.h"


MCP2515 mcp2515(PIN_CAN_BUS_CS);

struct can_frame frame;

Mcp mcp1;
Mcp mcp2;

const int ihmSize = 22;
IhmInterface *ihm[ihmSize] = {
  // SPD
  new Rotary(new McpInput(&mcp1, PIN_SPD_ROTARY_A), new McpInput(&mcp1, PIN_SPD_ROTARY_B), new RotaryEventHandler(0x1)),
  new Button(new McpInputPullup(&mcp1, PIN_SPD_PUSH), new ButtonEventHandler(0x3)),
  new Button(new McpInputPullup(&mcp1, PIN_SPD_PULL), new ButtonEventHandler(0x4)),
  
  // HDG
  new Rotary(new McpInput(&mcp1, PIN_HDG_ROTARY_A), new McpInput(&mcp1, PIN_HDG_ROTARY_B), new RotaryEventHandler(0x2)),
  new Button(new McpInputPullup(&mcp1, PIN_HDG_PUSH), new ButtonEventHandler(0x5)),
  new Button(new McpInputPullup(&mcp1, PIN_HDG_PULL), new ButtonEventHandler(0x6)),

  // ALT
  new Rotary(new McpInput(&mcp1, PIN_ALT_ROTARY_A), new McpInput(&mcp1, PIN_ALT_ROTARY_B), new RotaryEventHandler(0x3)),
  new Button(new McpInputPullup(&mcp1, PIN_ALT_PUSH), new ButtonEventHandler(0x7)),
  new Button(new McpInputPullup(&mcp1, PIN_ALT_PULL), new ButtonEventHandler(0x8)),
  new Switch(new McpInputPullup(&mcp1, PIN_ALT_SWITCH), new SwitchEventHandler(0x9)),

  // V/S
  new Rotary(new McpInput(&mcp1, PIN_VS_ROTARY_A), new McpInput(&mcp1, PIN_VS_ROTARY_B), new RotaryEventHandler(0x4)),
  new Button(new McpInputPullup(&mcp1, PIN_VS_PUSH), new ButtonEventHandler(0xa)),
  new Button(new McpInputPullup(&mcp1, PIN_VS_PULL),  new ButtonEventHandler(0xb)),

  // Toggle button
  new Button(new McpInputPullup(&mcp1, PIN_SPD_MACH), new ButtonEventHandler(0xc)),
  new Button(new McpInputPullup(&mcp1, PIN_FPA_VS), new ButtonEventHandler(0xd)),
  new Button(new McpInputPullup(&mcp1, PIN_MATRIC_ALT), new ButtonEventHandler(0xe)),

  // AP
  new Button(new McpInputPullup(&mcp1, PIN_AP1), new ButtonEventHandler(0xf)),
  new Button(new McpInputPullup(&mcp1, PIN_AP2), new ButtonEventHandler(0x0a)),
  new Button(new McpInputPullup(&mcp1, PIN_ATHR), new ButtonEventHandler(0x0b)),

  // Apporch
  new Button(new McpInputPullup(&mcp1, PIN_LOC), new ButtonEventHandler(0xac)),
  new Button(new McpInputPullup(&mcp1, PIN_APPR), new ButtonEventHandler(0x0d)),
  new Button(new McpInputPullup(&mcp1, PIN_EXPED), new ButtonEventHandler(0x0e)),
};


void setup() {
  SERIAL_BEGIN(9600);
  SERIAL_PRINTLN(F("Setup..."));

  Wire.begin();
  mcp1.begin(MCP1_ADDR);
  mcp2.begin(MCP2_ADDR);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  SERIAL_PRINTLN("End of setup");
}

void loop() {
  mcp1.loop();

  for(int i = 0; i < ihmSize; i++) {
    ihm[i]->loop();
  }
}