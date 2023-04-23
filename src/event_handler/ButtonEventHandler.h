#ifndef FCU_BUTTON_EVENT_HANDLER_H
#define FCU_BUTTON_EVENT_HANDLER_H

#include "Arduino.h"
#include "A320_Core/event/ButtonEvent.h"
#include "A320_Core/can_bus/CanBus.h"

class ButtonEventHandler: public ButtonEvent {

    public:
        ButtonEventHandler(CanBus *canBus, unsigned short idEvent);

        void onClick() override;

    private:
        CanBus *_canBus;
        unsigned short _idEvent;
};

#endif