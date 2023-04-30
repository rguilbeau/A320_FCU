#include "CanBusEventHandler.h"

CanBusEventHandler::CanBusEventHandler(
    Light *ap1,
    Light *ap2,
    Light *athr,
    Light *loc,
    Light *exped,
    Light *appr,
    PwmInterface *indicatorsDim,
    PwmInterface *buttonDim,
    PwmInterface *panelDim
) {
    _ap1 = ap1;
    _ap2 = ap2;
    _athr = athr;
    _loc = loc;
    _exped = exped;
    _appr = appr;
    _indicatorsDim = indicatorsDim;
    _buttonDim = buttonDim;
    _panelDim = panelDim;
}

void CanBusEventHandler::frameReceived(Frame *frame)
{
    switch (frame->getId()) {
        case GlareshieldIndicatorsFrame::ID :
            _glareshieldIndicatorsFrame.decode(frame);
            
            _ap1->on(_glareshieldIndicatorsFrame.ap1);
            _ap2->on(_glareshieldIndicatorsFrame.ap2);
            _athr->on(_glareshieldIndicatorsFrame.athr);
            _loc->on(_glareshieldIndicatorsFrame.loc);
            _exped->on(_glareshieldIndicatorsFrame.exped);
            _appr->on(_glareshieldIndicatorsFrame.appr); 
            break;
        
        case BrightnessPanelFrame::ID :
            _brightnessPanelFrame.decode(frame);

            _panelDim->write(_brightnessPanelFrame.glareshieldPanel);
            _buttonDim->write(_brightnessPanelFrame.buttons);
            _indicatorsDim->write(_brightnessPanelFrame.indicators);
            break;
    }
}