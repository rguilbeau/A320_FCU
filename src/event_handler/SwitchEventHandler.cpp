#include "SwitchEventHandler.h"
#include "Setup.h"

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
        SERIAL_PRINTLN("isOn " + String(_idEvent));
        frame.setData(1, 1);
    } else {
        SERIAL_PRINTLN("isOff " + String(_idEvent));
        frame.setData(1, 0);
    }
    
    _canBus->send(&frame);
}