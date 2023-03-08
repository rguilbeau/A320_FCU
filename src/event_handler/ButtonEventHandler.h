#ifndef FCU_BUTTON_EVENT_HANDLER_H
#define FCU_BUTTON_EVENT_HANDLER_H

#include "Arduino.h"
#include "ihm/ButtonEvent.h"

class ButtonEventHandler: public ButtonEvent {

    public:
        ButtonEventHandler(unsigned char idEvent);

        void onClick() override;

    private:
        unsigned char _idEvent;
};

#endif