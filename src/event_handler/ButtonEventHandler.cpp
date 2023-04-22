#include "ButtonEventHandler.h"
#include "Setup.h"

ButtonEventHandler::ButtonEventHandler(CanBus *canBus, unsigned char idEvent)
{
    _idEvent = idEvent;
    _canBus = canBus;
}

void ButtonEventHandler::onClick()
{
    SERIAL_PRINTLN("onClick " + String(_idEvent));
    Frame frame(0x0, 2);
    frame.setData(0, _idEvent);
    frame.setData(1, 1);
    _canBus->send(&frame);    
}