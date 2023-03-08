#include "McpInput.h"

McpInput::McpInput(Mcp *mcp, uint8_t pin)
{
    _pin = pin;
    _mcp = mcp;
}

bool McpInput::read()
{
    return _mcp->getValue(_pin);
}