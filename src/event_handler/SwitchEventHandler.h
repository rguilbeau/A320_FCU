#ifndef FCU_SWITCH_EVENT_HANDLER_H
#define FCU_SWITCH_EVENT_HANDLER_H

#include "Arduino.h"
#include "A320_Core/event/SwitchEvent.h"
#include "A320_Core/can_bus/CanBus.h"

class SwitchEventHandler : public SwitchEvent {

    public:
        SwitchEventHandler(CanBus *canBus, unsigned short idEvent);

        void onChange(bool isOn) override;
        void onPing(bool isOn) override;

    private:
        CanBus *_canBus;
        unsigned short _idEvent;
};

#endif