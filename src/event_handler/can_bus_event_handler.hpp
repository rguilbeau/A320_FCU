#ifndef FCU_CAN_BUS_FRAME_RECEIVE_HANDLER_H
#define FCU_CAN_BUS_FRAME_RECEIVE_HANDLER_H

#include "Arduino.h"

#include "event/can_bus_frame_event.hpp"
#include "ihm/light.hpp"
#include "ihm/backlight.hpp"

#include "frames/frame_brightness_panel.hpp"
#include "frames/frame_glareshield_indicator.hpp"
#include "frames/frame_power.hpp"

class CanBusEventHandler: public CanBusFrameEvent 
{

public:
    CanBusEventHandler(
        Light *pAp1,
        Light *pAp2,
        Light *pAthr,
        Light *pLoc,
        Light *pExped,
        Light *pAppr,
        Backlight *pIndicatorsDim,
        Backlight *pButtonDim,
        Backlight *pPanelDim
    );

    void frameReceived(const Frame &frame) override;

private:
    Light *m_pAp1;
    Light *m_pAp2;
    Light *m_pAthr;
    Light *m_pLoc;
    Light *m_pExped;
    Light *m_pAppr;

    Backlight *m_pIndicatorsDim;
    Backlight *m_pButtonDim;
    Backlight *m_pPanelDim;

    FrameBrightnessPanel m_brightnessPanelFrame;
    FrameGlareshieldIndicator m_glareshieldIndicatorFrame;
    FramePower m_framePower;
};

#endif