#include "SwitchEventHandler.h"

SwitchEventHandler::SwitchEventHandler(unsigned char idEvent)
{
    _idEvent = idEvent;
}

void SwitchEventHandler::onChange(bool isOn)
{
    if(isOn) {
        // do stuff
    } else {
        // do stuff
    }
}