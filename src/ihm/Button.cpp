#include "Button.h"


Button::Button(InputInterface *input)
{
    _input = input;
    _event = nullptr;
    _lastState = false;
}

Button::Button(InputInterface *input, ButtonEvent *event)
{
    _input = input;
    _event = event;
    _lastState = false;
}

void Button::loop()
{
    bool value = _input->read();
    _lastState = value;

    if(value && !_lastState && _event != nullptr) {
        _event->onClick();
    } 
}