#ifndef FCU_CAN_BUS_FRAME_RECEIVE_HANDLER_H
#define FCU_CAN_BUS_FRAME_RECEIVE_HANDLER_H

#include "Arduino.h"
#include "core/event/CanBusFrameEvent.h"
#include "core/output/PwmInterface.h"
#include "core/output/OutputInterface.h"
#include "core/ihm/Light.h"
#include "core/can_bus/frame/brightness/BrightnessFrame.h"
#include "core/can_bus/frame/glareshield/GlareshieldIndicatorsFrame.h" 

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