#include "ButtonEventHandler.h"
#include "Setup.h"

ButtonEventHandler::ButtonEventHandler(CanBus *canBus, unsigned short idEvent)
{
    _idEvent = idEvent;
    _canBus = canBus;
}

void ButtonEventHandler::onClick()
{
    SERIAL_PRINTLN("onClick " + String(_idEvent));
    _canBus->sendEvent(_idEvent, 0, false);
}