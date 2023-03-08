#include "Switch.h"

Switch::Switch(InputInterface *input)
{
    _input = input;
    _lastValue = false;
    _event = nullptr;
}

Switch::Switch(InputInterface *input, SwitchEvent *event)
{
    _input = input;
    _lastValue = false;
    _event = event;
}

void Switch::loop()
{
    bool value = _input->read();
    
    if(_lastValue != value && _event != nullptr) {
        _event->onChange(value);
    }
}