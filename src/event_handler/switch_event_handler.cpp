#include "switch_event_handler.hpp"
#include "setup.h"

SwitchEventHandler::SwitchEventHandler(CanBus *pCanBus, const e_event &event)
{
    m_pCanBus = pCanBus;
    m_event = event;
}

void SwitchEventHandler::onChange(const bool &bIsOn)
{
    FrameEvent e(m_event, bIsOn ? 1 : 0);
    m_pCanBus->send(e);
}

void SwitchEventHandler::onPing(const bool &bIsOn)
{
    FrameEvent e(m_event, bIsOn ? 1 : 0);
    m_pCanBus->send(e);
}