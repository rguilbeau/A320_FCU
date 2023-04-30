#include "SwitchEventHandler.h"
#include "Setup.h"

SwitchEventHandler::SwitchEventHandler(CanBus *canBus, unsigned short idEvent)
{
    _idEvent = idEvent;
    _canBus = canBus;
}

void SwitchEventHandler::onChange(bool isOn)
{
    _canBus->sendEvent(_idEvent, isOn ? 1 : 0);
}

void SwitchEventHandler::onPing(bool isOn)
{
    _canBus->sendEvent(_idEvent, isOn ? 1 : 0);
}