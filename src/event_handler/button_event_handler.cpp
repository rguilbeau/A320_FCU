#include "button_event_handler.hpp"
#include "setup.h"

ButtonEventHandler::ButtonEventHandler(CanBus *pCanBus, const e_event &event)
{
    m_pCanBus = pCanBus;
    m_event = event;
}

void ButtonEventHandler::onClick()
{
    SERIAL_PRINTLN("onClick " + String(_idEvent));
    
    FrameEvent e(m_event);
    m_pCanBus->send(e);
}