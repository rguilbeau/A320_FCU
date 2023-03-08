#ifndef FCU_ROTARY_EVENT_HANDLER_H
#define FCU_ROTARY_EVENT_HANDLER_H

#include "Arduino.h"
#include "ihm/RotaryEvent.h"

class RotaryEventHandler : public RotaryEvent {

public:
    RotaryEventHandler(unsigned char idEvent);

    void onMove(RotaryEventDirection direction) override;

private:
    unsigned char _idEvent;
};

#endif