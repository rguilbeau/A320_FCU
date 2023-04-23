#ifndef FCU_CAN_BUS_FRAME_RECEIVE_HANDLER_H
#define FCU_CAN_BUS_FRAME_RECEIVE_HANDLER_H

#include "Arduino.h"
#include "A320_Core/event/CanBusFrameEvent.h"
#include "A320_Core/output/PwmInterface.h"
#include "A320_Core/output/OutputInterface.h"
#include "A320_Core/ihm/Light.h"
#include "A320_Core/can_bus/frame/brightness/BrightnessFrame.h"
#include "A320_Core/can_bus/frame/glareshield/GlareshieldIndicatorsFrame.h" 

class CanBusEventHandler: public CanBusFrameEvent {

public:
    CanBusEventHandler(
        Light *ap1,
        Light *ap2,
        Light *athr,
        Light *loc,
        Light *exped,
        Light *appr,
        PwmInterface *indicatorsDim,
        PwmInterface *buttonDim,
        PwmInterface *panelDim
    );

    void frameReceived(Frame *frame) override;

private:
    Light *_ap1;
    Light *_ap2;
    Light *_athr;
    Light *_loc;
    Light *_exped;
    Light *_appr;
    PwmInterface *_indicatorsDim;
    PwmInterface *_buttonDim;
    PwmInterface *_panelDim;

    BrightnessFrame _brightnessFrame;
    GlareshieldIndicatorsFrame _glareshieldIndicatorsFrame;
};

#endif