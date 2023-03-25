#include "RotaryEventHandler.h"

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
        frame.setData(1, 1);
    } else {
        frame.setData(1, 0);
    }
    _canBus->send(&frame);
}