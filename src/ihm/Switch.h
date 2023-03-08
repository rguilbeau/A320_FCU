#ifndef FCU_SWITCH_H
#define FCU_SWITCH_H

#include "Arduino.h"
#include "pin/InputInterface.h"
#include "ihm/IhmInterface.h"
#include "SwitchEvent.h"

class Switch : public IhmInterface {

    public:
        Switch(InputInterface *input);
        Switch(InputInterface *input, SwitchEvent *event);

        void loop() override;

    private:
        InputInterface *_input;
        SwitchEvent *_event;
        bool _lastValue;
};

#endif