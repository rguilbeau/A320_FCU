#ifndef FCU_BUTTON_EVENT_HANDLER_H
#define FCU_BUTTON_EVENT_HANDLER_H

#include "Arduino.h"
#include "core/event/ButtonEvent.h"
#include "core/can_bus/CanBus.h"

class ButtonEventHandler: public ButtonEvent {

    public:
        ButtonEventHandler(CanBus *canBus, unsigned short idEvent);

        void onClick() override;

    private:
        CanBus *_canBus;
        unsigned short _idEvent;
};

#endif