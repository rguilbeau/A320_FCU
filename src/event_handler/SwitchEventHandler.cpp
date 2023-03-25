#include "SwitchEventHandler.h"

SwitchEventHandler::SwitchEventHandler(CanBus *canBus, unsigned char idEvent)
{
    _idEvent = idEvent;
    _canBus = canBus;
}

void SwitchEventHandler::onChange(bool isOn)
{
    Frame frame(0x0, 2);
    frame.setData(0, _idEvent);

    if(isOn) {
        frame.setData(1, 1);
    } else {
        frame.setData(1, 0);
    }
    
    _canBus->send(&frame);
}