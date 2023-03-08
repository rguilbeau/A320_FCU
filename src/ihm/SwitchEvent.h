#ifndef FCU_SWITCH_EVENT_H
#define FCU_SWITCH_EVENT_H

class SwitchEvent {

public:
    virtual void onChange(bool isOn) = 0;
};

#endif