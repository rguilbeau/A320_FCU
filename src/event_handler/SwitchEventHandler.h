#ifndef FCU_SWITCH_EVENT_HANDLER_H
#define FCU_SWITCH_EVENT_HANDLER_H

#include "Arduino.h"
#include "ihm/SwitchEvent.h"

class SwitchEventHandler : public SwitchEvent {

    public:
        SwitchEventHandler(unsigned char idEvent);

        void onChange(bool isOn) override;

    private:
        unsigned char _idEvent;
};

#endif