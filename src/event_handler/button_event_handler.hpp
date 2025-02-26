#ifndef FCU_BUTTON_EVENT_HANDLER_H
#define FCU_BUTTON_EVENT_HANDLER_H

#include "Arduino.h"
#include "event/button_event.hpp"
#include "can_bus/can_bus.hpp"

class ButtonEventHandler: public ButtonEvent 
{
public:
    explicit ButtonEventHandler(CanBus *pCanBus, const e_event &event);
    virtual ~ButtonEventHandler() = default;

    void onClick() override;

private:
    CanBus *m_pCanBus;
    e_event m_event;
};

#endif