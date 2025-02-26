#ifndef FCU_ROTARY_EVENT_HANDLER_H
#define FCU_ROTARY_EVENT_HANDLER_H

#include "Arduino.h"

#include "event/rotary_event.hpp"
#include "can_bus/can_bus.hpp"

class RotaryEventHandler : public RotaryEvent 
{
public:
    explicit RotaryEventHandler(CanBus *pCanBus, const e_event &incrEvent, const e_event &decrEvent);
    virtual ~RotaryEventHandler() = default;
    
    void onMove(const RotaryEvent::e_direction &direction) override;

private:
    CanBus *m_pCanBus;

    e_event m_incrEvent;
    e_event m_decrEvent;
};

#endif