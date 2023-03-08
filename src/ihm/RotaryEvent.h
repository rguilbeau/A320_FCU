#ifndef FCU_ROTARY_EVENT_H
#define FCU_ROTARY_EVENT_H

enum RotaryEventDirection {INCR, DECR, NONE};

class RotaryEvent {

    public:
        virtual void onMove(RotaryEventDirection direction) = 0;

};

#endif