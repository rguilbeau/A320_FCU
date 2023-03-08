#ifndef FCU_ROTARY_H
#define FCU_ROTARY_H

#include "Arduino.h"
#include "pin/InputInterface.h"
#include "ihm/IhmInterface.h"
#include "RotaryEvent.h"

#define R_CW_FINAL 0x1
#define R_CW_BEGIN 0x2
#define R_CW_NEXT 0x3
#define R_CCW_BEGIN 0x4
#define R_CCW_FINAL 0x5
#define R_CCW_NEXT 0x6
#define R_START 0x0
#define R_DIR_CW 0x10
#define R_DIR_CCW 0x20

class Rotary : public IhmInterface {

    public:
        Rotary(InputInterface *inputA, InputInterface *inputB);
        Rotary(InputInterface *inputA, InputInterface *inputB, RotaryEvent *event);
        void loop() override;

    private:
        InputInterface *_inputA;
        InputInterface *_inputB;
        RotaryEvent *_event;
        unsigned char _lastState;
        static const unsigned char _tableState[7][4]; 
};


#endif