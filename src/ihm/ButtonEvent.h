#ifndef FCU_BUTTON_EVENT_H
#define FCU_BUTTON_EVENT_H

#include "Arduino.h"

class ButtonEvent {

    public:
        virtual void onClick() = 0;

};

#endif