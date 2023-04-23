#ifndef FCU_ROTARY_EVENT_HANDLER_H
#define FCU_ROTARY_EVENT_HANDLER_H

#include "Arduino.h"
#include "A320_Core/event/RotaryEvent.h"
#include "A320_Core/can_bus/CanBus.h"

class RotaryEventHandler : public RotaryEvent {

public:
    RotaryEventHandler(CanBus *canBus, unsigned short idEvent);

    void onMove(RotaryEventDirection direction) override;

private:
    CanBus *_canBus;
    unsigned short _idEvent;
};

#endif