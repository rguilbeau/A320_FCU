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
        case 0x65:
            // Etat des témoins
            _ap1->on(frame->getBinary(0, 0));
            _ap2->on(frame->getBinary(0, 1));
            _athr->on(frame->getBinary(0, 2));
            _loc->on(frame->getBinary(0, 3));
            _exped->on(frame->getBinary(0, 4));
            _appr->on(frame->getBinary(0, 5));
            _buttonDim->write(frame->getData(2));
            _panelDim->write(frame->getData(3));
            break;
        
        case 0xC8:
            if(frame->getBinary(0, 0)) {
                // Test des témoins actif
                _ap1->force(true);
                _ap2->force(true);
                _athr->force(true);
                _loc->force(true);
                _exped->force(true);
                _appr->force(true);
            } else {
                // Test des témoins inactif
                _ap1->disableForce();
                _ap2->disableForce();
                _athr->disableForce();
                _loc->disableForce();
                _exped->disableForce();
                _appr->disableForce();
            }
            break;

        case 0x12C:
            if(frame->getBinary(0, 0)) {
                // Bus AC 1 actif
                _ap1->disableForce();
                _ap2->disableForce();
                _athr->disableForce();
                _loc->disableForce();
                _exped->disableForce();
                _appr->disableForce();
            } else {
                // Bus AC 1 inactif
                _ap1->force(false);
                _ap2->force(false);
                _athr->force(false);
                _loc->force(false);
                _exped->force(false);
                _appr->force(false);
            }
            break;
    
    default:
        break;
    }    
}