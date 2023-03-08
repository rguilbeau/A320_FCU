#include "McpInputPullup.h"

McpInputPullup::McpInputPullup(Mcp *mcp, uint8_t pin)
{
    _pin = pin;
    _mcp = mcp;
}

bool McpInputPullup::read()
{
    bool value = _mcp->getValue(_pin);
    // inversion à cause du pullup
    return !value;
}