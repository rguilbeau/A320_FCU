#ifndef FCU_MCP_H
#define FCU_MCP_H

#include "Setup.h"
#include "Arduino.h"
#include "Adafruit_MCP23X17.h"

class Mcp {

    public:
        Mcp();

        void begin(uint8_t i2c_addr);
        void loop();
        unsigned char getValue(uint8_t pin);

    private:
        Adafruit_MCP23X17 *_mcp;
        uint16_t _allValues;
};

#endif