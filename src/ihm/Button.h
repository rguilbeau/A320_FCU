#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"
#include "ihm/IhmInterface.h"
#include "pin/InputInterface.h"
#include "ButtonEvent.h"

class Button : public IhmInterface {

    public:
        Button(InputInterface *input);
        Button(InputInterface *input, ButtonEvent *event);

        void loop() override;

    private:
        InputInterface *_input;
        ButtonEvent *_event;
        bool _lastState;
};

#endif