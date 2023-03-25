#ifndef FCU_ROTARY_EVENT_HANDLER_H
#define FCU_ROTARY_EVENT_HANDLER_H

#include "Arduino.h"
#include "core/event/RotaryEvent.h"
#include "core/can_bus/CanBus.h"

class RotaryEventHandler : public RotaryEvent {

public:
    RotaryEventHandler(CanBus *canBus, unsigned char idEvent);

    void onMove(RotaryEventDirection direction) override;

private:
    CanBus *_canBus;
    unsigned char _idEvent;
};

#endif