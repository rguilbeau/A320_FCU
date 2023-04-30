#include "RotaryEventHandler.h"
#include "Setup.h"

RotaryEventHandler::RotaryEventHandler(CanBus *canBus, unsigned short idEvent)
{
    _idEvent = idEvent;
    _canBus = canBus;
}

void RotaryEventHandler::onMove(RotaryEventDirection direction)
{   
    if(direction == RotaryEventDirection::INCR) {
        SERIAL_PRINTLN("Rotary incr " + String(_idEvent));
        _canBus->sendEvent(_idEvent, 1, false);
    } else {
        SERIAL_PRINTLN("Rotary decr " + String(_idEvent));
        _canBus->sendEvent(_idEvent, 0, false);
    }
}