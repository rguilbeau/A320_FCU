#include "RotaryEventHandler.h"
#include "Setup.h"

RotaryEventHandler::RotaryEventHandler(CanBus *canBus, unsigned char idEvent)
{
    _idEvent = idEvent;
    _canBus = canBus;
}

void RotaryEventHandler::onMove(RotaryEventDirection direction)
{
    Frame frame(0x0, 2);
    frame.setData(0, _idEvent);
    
    if(direction == RotaryEventDirection::INCR) {
        SERIAL_PRINTLN("Rotary incr " + String(_idEvent));
        frame.setData(1, 1);
    } else {
        SERIAL_PRINTLN("Rotary decr " + String(_idEvent));
        frame.setData(1, 0);
    }
    _canBus->send(&frame);
}