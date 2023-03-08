#include "RotaryEventHandler.h"

RotaryEventHandler::RotaryEventHandler(unsigned char idEvent)
{
    _idEvent = idEvent;
}

void RotaryEventHandler::onMove(RotaryEventDirection direction)
{
    if(direction == RotaryEventDirection::INCR) {
        // do stuff
    } else {
        // do stuff
    }
}