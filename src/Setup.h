#define DEBUG

#ifdef DEBUG
    #define SERIAL_BEGIN(x) Serial.begin(x);
    #define SERIAL_PRINTLN(x) Serial.println(x);
    #define SERIAL_PRINT(x) Serial.print(x);
#else
    #define SERIAL_BEGIN(x)
    #define SERIAL_PRINTLN(x)
    #define SERIAL_PRINT(x)
#endif


#define MCP1_ADDR 0x20
#define MCP2_ADDR 0x21

#define PIN_CAN_BUS_CS 10

#define PIN_BACKLIGHT_PANEL 0
#define PIN_BACKLIGHT_BUTTON 0
#define PIN_BACKLIGHT_INDICATOR 0

#define PIN_SPD_MACH 0
#define MCP_SPD_MACH 1

#define PIN_FPA_VS 0
#define MCP_FPA_VS 1

#define PIN_MATRIC_ALT 0
#define MCP_SPD_MACH 1

#define PIN_AP1 0
#define PIN_AP1_INDICATOR 0
#define MCP_AP1 1
#define MCP_AP1_INDICATOR 1

#define PIN_AP2 0
#define PIN_AP2_INDICATOR 0
#define MCP_AP2 1
#define MCP_AP2_INDICATOR 1

#define PIN_ATHR 0
#define PIN_ATHR_INDICATOR 0
#define MCP_ATHR 1
#define MCP_ATHR_INDICATOR 1

#define PIN_LOC 0
#define PIN_LOC_INDICATOR 0
#define MCP_LOC 1
#define MCP_LOC_INDICATOR 1

#define PIN_EXPED 0
#define PIN_EXPED_INDICATOR 0
#define MCP_EXPED 1
#define MCP_EXPED_INDICATOR 1

#define PIN_APPR 0
#define PIN_APPR_INDICATOR 0
#define MCP_APPR 1
#define MCP_APPR_INDICATOR 1

#define PIN_SPD_ROTARY_A 0
#define PIN_SPD_ROTARY_B 0
#define PIN_SPD_PUSH 0
#define PIN_SPD_PULL 0
#define MCP_SPD_ROTARY 0
#define MCP_SPD_PUSH 0
#define MCP_SDP_PULL 0

#define PIN_HDG_ROTARY_A 0
#define PIN_HDG_ROTARY_B 0
#define PIN_HDG_PUSH 0
#define PIN_HDG_PULL 0
#define MCP_HDG_ROTARY 0
#define MCP_HDG_PUSH 0
#define MCP_HDG_PULL 0

#define PIN_ALT_ROTARY_A 0
#define PIN_ALT_ROTARY_B 0
#define PIN_ALT_PUSH 0
#define PIN_ALT_PULL 0
#define PIN_ALT_SWITCH 0
#define MCP_ALT_ROTARY 0
#define MCP_ALT_PUSH 0
#define MCP_ALT_PULL 0
#define MCP_ALT_SWITCH 1

#define PIN_VS_ROTARY_A 0
#define PIN_VS_ROTARY_B 0
#define PIN_VS_PUSH 0
#define PIN_VS_PULL 0
#define MCP_VS_ROTARY 0
#define MCP_VS_PUSH 0
#define MCP_VS_PULL 0