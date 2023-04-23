#ifndef FCU_ROTARY_EVENT_HANDLER_H
#define FCU_ROTARY_EVENT_HANDLER_H

#include "Arduino.h"
#include "core/event/RotaryEvent.h"
#include "core/can_bus/CanBus.h"

class RotaryEventHandler : public RotaryEvent {

public:
    RotaryEventHandler(CanBus *canBus, unsigned short idEvent);

    void onMove(RotaryEventDirection direction) override;

private:
    CanBus *_canBus;
    unsigned short _idEvent;
};

#endif