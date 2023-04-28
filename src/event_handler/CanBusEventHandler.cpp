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
        
        case BrightnessFrame::ID :
            _brightnessFrame.decode(frame);
            break;
    }    

    if(_glareshieldIndicatorsFrame.isPowerOn && _brightnessFrame.testLight) {
        // Test des témoins actif
        _ap1->force(true);
        _ap2->force(true);
        _athr->force(true);
        _loc->force(true);
        _exped->force(true);
        _appr->force(true);
        _panelDim->write(_brightnessFrame.glareshieldPanel);
    } else if(!_glareshieldIndicatorsFrame.isPowerOn) {
        _ap1->force(false);
        _ap2->force(false);
        _athr->force(false);
        _loc->force(false);
        _exped->force(false);
        _appr->force(false);
        _panelDim->write(0x0);
    } else {
        _ap1->disableForce();
        _ap2->disableForce();
        _athr->disableForce();
        _loc->disableForce();
        _exped->disableForce();
        _appr->disableForce();
        _panelDim->write(_brightnessFrame.glareshieldPanel);
    }

    _buttonDim->write(_brightnessFrame.buttons);
    _indicatorsDim->write(_brightnessFrame.indicators);
}