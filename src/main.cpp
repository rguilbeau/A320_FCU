#include "setup.h"

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <mcp2515.h>
#include "frame_id.h"

#include "can_bus/can_bus.hpp"

#include "event.h"

#include "ihm/ihm_interface.hpp"
#include "ihm/light.hpp"
#include "ihm/button.hpp"
#include "ihm/rotary.hpp"
#include "ihm/switch.hpp"

#include "mcp_expander/mcp_expander.hpp"
#include "output/mcp_expander_output.hpp"
#include "output/arduino_pwm.hpp"

#include "input/mcp_expander_input_pullup.hpp"

#include "event_handler/can_bus_event_handler.hpp"
#include "event_handler/button_event_handler.hpp"
#include "event_handler/rotary_event_handler.hpp"
#include "event_handler/switch_event_handler.hpp"

const uint16_t numberFilters = 3;
const uint32_t filters[numberFilters] = {
  e_frameId::GLARESHIELD_INDICATOR,
  e_frameId::BRIGTNESS_PANEL
};

McpExpander mcp1;
McpExpander mcp2;

CanBus *canBus = nullptr;

const int ihmSize = 22;
IhmInterface *ihm[ihmSize];

void setup() 
{
  SERIAL_BEGIN(9600);
  SERIAL_PRINTLN(F("Setup..."));

  Wire.begin();
  mcp1.begin(MCP1_ADDR);
  mcp2.begin(MCP2_ADDR);
  
  canBus = new CanBus(
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

  canBus->begin(filters, numberFilters);

  //---------------------------------------------------------------------------------------------
  //                                        SPD
  //---------------------------------------------------------------------------------------------
  ihm[0] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_SPD_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_SPD_ROTARY_B), 
            new RotaryEventHandler(canBus, e_event::FCU_SPEED_INCR, e_event::FCU_SPEED_INCR));

  ihm[1] = new Button(new McpExpanderInputPullup(&mcp1, PIN_SPD_PUSH),
            new ButtonEventHandler(canBus, e_event::FCU_SPEED_PUSH));

  ihm[2] = new Button(new McpExpanderInputPullup(&mcp1, PIN_SPD_PULL), 
            new ButtonEventHandler(canBus, e_event::FCU_SPEED_PULL));
  

  //---------------------------------------------------------------------------------------------
  //                                        HDG
  //---------------------------------------------------------------------------------------------
  ihm[3] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_HDG_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_HDG_ROTARY_B), 
            new RotaryEventHandler(canBus, e_event::FCU_HEADING_INCR, e_event::FCU_HEADING_DECR));

  ihm[4] = new Button(new McpExpanderInputPullup(&mcp1, PIN_HDG_PUSH), 
            new ButtonEventHandler(canBus, e_event::FCU_HEADING_PUSH));

  ihm[5] = new Button(new McpExpanderInputPullup(&mcp1, PIN_HDG_PULL), 
            new ButtonEventHandler(canBus, e_event::FCU_HEADING_PULL));


  //---------------------------------------------------------------------------------------------
  //                                        ALT
  //---------------------------------------------------------------------------------------------
  ihm[6] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_ALT_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_ALT_ROTARY_B), 
            new RotaryEventHandler(canBus, e_event::FCU_ALTITUDE_INCR, e_event::FCU_ALTITUDE_DECR));

  ihm[7] = new Button(new McpExpanderInputPullup(&mcp1, PIN_ALT_PUSH), 
            new ButtonEventHandler(canBus, e_event::FCU_ALTITUDE_PUSH));

  ihm[8] = new Button(new McpExpanderInputPullup(&mcp1, PIN_ALT_PULL), 
            new ButtonEventHandler(canBus, e_event::FCU_ALTITUDE_PULL));

  ihm[9] = new Switch(new McpExpanderInputPullup(&mcp2, PIN_ALT_SWITCH), 
            new SwitchEventHandler(canBus, e_event::FCU_ALTITUDE_ALT),
            new Ping(1000));
  
  
  //---------------------------------------------------------------------------------------------
  //                                        V/S
  //---------------------------------------------------------------------------------------------
  ihm[10] = new Rotary(new McpExpanderInputPullup(&mcp1, PIN_VS_ROTARY_A), new McpExpanderInputPullup(&mcp1, PIN_VS_ROTARY_B), 
              new RotaryEventHandler(canBus, e_event::FCU_VS_INCR, e_event::FCU_VS_DECR));

  ihm[11] = new Button(new McpExpanderInputPullup(&mcp1, PIN_VS_PUSH), 
              new ButtonEventHandler(canBus, e_event::FCU_VS_PUSH));

  ihm[12] = new Button(new McpExpanderInputPullup(&mcp1, PIN_VS_PULL),  
              new ButtonEventHandler(canBus, e_event::FCU_VS_PULL));

  
  //---------------------------------------------------------------------------------------------
  //                                    Toggle Buttons
  //---------------------------------------------------------------------------------------------
  ihm[13] = new Button(new McpExpanderInputPullup(&mcp2, PIN_SPD_MACH), 
              new ButtonEventHandler(canBus, e_event::FCU_SPEED_MACH));

  ihm[14] = new Button(new McpExpanderInputPullup(&mcp2, PIN_FPA_VS), 
              new ButtonEventHandler(canBus, e_event::FCU_HEADING_TRACK));

  ihm[15] = new Button(new McpExpanderInputPullup(&mcp2, PIN_MATRIC_ALT), 
              new ButtonEventHandler(canBus, e_event::FCU_METRIC_ALT));


  //---------------------------------------------------------------------------------------------
  //                                  AP1, AP2, ATHR
  //---------------------------------------------------------------------------------------------
  ihm[16] = new Button(new McpExpanderInputPullup(&mcp2, PIN_AP1), 
              new ButtonEventHandler(canBus, e_event::FCU_AP1));

  ihm[17] = new Button(new McpExpanderInputPullup(&mcp2, PIN_AP2), 
              new ButtonEventHandler(canBus, e_event::FCU_AP2));

  ihm[18] = new Button(new McpExpanderInputPullup(&mcp2, PIN_ATHR), 
              new ButtonEventHandler(canBus, e_event::FCU_ATHR));
  

  //---------------------------------------------------------------------------------------------
  //                                  APPR, LOC, EXPED
  //---------------------------------------------------------------------------------------------
  ihm[19] = new Button(new McpExpanderInputPullup(&mcp2, PIN_LOC), 
              new ButtonEventHandler(canBus, e_event::FCU_LOC));

  ihm[20] = new Button(new McpExpanderInputPullup(&mcp2, PIN_APPR), 
              new ButtonEventHandler(canBus, e_event::FCU_APPR));

  ihm[21] = new Button(new McpExpanderInputPullup(&mcp2, PIN_EXPED), 
              new ButtonEventHandler(canBus, e_event::FCU_EXPED));

  SERIAL_PRINTLN("End of setup");
}

void loop() 
{
  canBus->loop();
  
  // Lecture des broches des mcp23017
  mcp1.loop();
  mcp2.loop();

  // Recherche d'évenement sur les IHM
  for(int i = 0; i < ihmSize; i++) 
  {
    ihm[i]->loop();
  }
}