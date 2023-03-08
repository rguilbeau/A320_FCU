#ifndef FCU_INPUT_H
#define FCU_INPUT_H

#include "Arduino.h"

class InputInterface
{
    public:
        virtual bool read() = 0;
};

#endif