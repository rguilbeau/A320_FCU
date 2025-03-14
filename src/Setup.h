// #define DEBUG

#ifdef DEBUG
    #define SERIAL_BEGIN(x) Serial.begin(x);
    #define SERIAL_PRINTLN(x) Serial.println(x);
    #define SERIAL_PRINT(x) Serial.print(x);
#else
    #define SERIAL_BEGIN(x)
    #define SERIAL_PRINTLN(x)
    #define SERIAL_PRINT(x)
#endif


#define MCP1_ADDR 0x21
#define MCP2_ADDR 0x20

#define PIN_CAN_BUS_CS 10

#define PIN_BACKLIGHT_PANEL 6
#define PIN_BACKLIGHT_BUTTON 5
#define PIN_BACKLIGHT_INDICATOR 3

#define PIN_SPD_MACH 2
#define PIN_FPA_VS 3
#define PIN_MATRIC_ALT 1

#define PIN_AP1 15
#define PIN_AP1_INDICATOR 4

#define PIN_AP2 14
#define PIN_AP2_INDICATOR 5

#define PIN_ATHR 13
#define PIN_ATHR_INDICATOR 6

#define PIN_EXPED 12
#define PIN_EXPED_INDICATOR 7

#define PIN_APPR 11
#define PIN_APPR_INDICATOR 8

#define PIN_LOC 10
#define PIN_LOC_INDICATOR 9

#define PIN_SPD_ROTARY_A 12
#define PIN_SPD_ROTARY_B 13
#define PIN_SPD_PUSH 15
#define PIN_SPD_PULL 14

#define PIN_HDG_ROTARY_A 8
#define PIN_HDG_ROTARY_B 9
#define PIN_HDG_PUSH 10
#define PIN_HDG_PULL 11

#define PIN_ALT_ROTARY_A 4
#define PIN_ALT_ROTARY_B 5
#define PIN_ALT_PUSH 6
#define PIN_ALT_PULL 7
#define PIN_ALT_SWITCH 0

#define PIN_VS_ROTARY_A 0
#define PIN_VS_ROTARY_B 1
#define PIN_VS_PUSH 2
#define PIN_VS_PULL 3