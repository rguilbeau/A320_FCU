#include "rotary_event_handler.hpp"
#include "setup.h"

RotaryEventHandler::RotaryEventHandler(CanBus *pCanBus, const e_event &incrEvent, const e_event &decrEvent)
{
    m_pCanBus = pCanBus;
    m_incrEvent = incrEvent;
    m_decrEvent = decrEvent;
}

void RotaryEventHandler::onMove(const RotaryEvent::e_direction &direction)
{   
    if(direction == RotaryEvent::e_direction::INCR) 
    {
        SERIAL_PRINTLN("Rotary incr " + String(_idEvent));

        FrameEvent e(m_incrEvent);
        m_pCanBus->send(e);
    } 
    else 
    {
        SERIAL_PRINTLN("Rotary decr " + String(_idEvent));

        FrameEvent e(m_decrEvent);
        m_pCanBus->send(e);
    }
}