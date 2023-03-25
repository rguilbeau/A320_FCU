#ifndef FCU_SWITCH_EVENT_HANDLER_H
#define FCU_SWITCH_EVENT_HANDLER_H

#include "Arduino.h"
#include "core/event/SwitchEvent.h"
#include "core/can_bus/CanBus.h"

class SwitchEventHandler : public SwitchEvent {

    public:
        SwitchEventHandler(CanBus *canBus, unsigned char idEvent);

        void onChange(bool isOn) override;

    private:
        CanBus *_canBus;
        unsigned char _idEvent;
};

#endif