#include "Mcp.h"

Mcp::Mcp()
{
    _mcp = new Adafruit_MCP23X17();
}

void Mcp::begin(uint8_t i2c_addr)
{
    SERIAL_PRINT(F("Connect to mcp1"));
    while(!_mcp->begin_I2C(i2c_addr)) {
        SERIAL_PRINT(F("."));
    }
    SERIAL_PRINTLN(F("."));
}

void Mcp::loop()
{
    _allValues = _mcp->readGPIOAB();
}

unsigned char Mcp::getValue(uint8_t pin)
{
    return bitRead(_allValues, pin);
}