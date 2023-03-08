#ifndef FCU_MCP_INPUT_H
#define FCU_MCP_INPUT_H

#include "Arduino.h"
#include "pin/InputInterface.h"
#include "mcp/Mcp.h"

class McpInput : public InputInterface {

    public:
        McpInput(Mcp *mcp, uint8_t pin);
        bool read() override;

    private:
        Mcp *_mcp;
        uint16_t _pin;
};

#endif