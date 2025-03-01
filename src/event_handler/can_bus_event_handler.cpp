#include "can_bus_event_handler.hpp"

CanBusEventHandler::CanBusEventHandler(
    Light *pAp1,
    Light *pAp2,
    Light *pAthr,
    Light *pLoc,
    Light *pExped,
    Light *pAppr,
    PwmInterface *pIndicatorsDim,
    PwmInterface *pButtonDim,
    PwmInterface *pPanelDim
) {
    m_pAp1 = pAp1;
    m_pAp2 = pAp2;
    m_pAthr = pAthr;
    m_pLoc = pLoc;
    m_pExped = pExped;
    m_pAppr = pAppr;
    m_pIndicatorsDim = pIndicatorsDim;
    m_pButtonDim = pButtonDim;
    m_pPanelDim = pPanelDim;
}

void CanBusEventHandler::frameReceived(const Frame &frame)
{
    if(frame.getId() == e_frameId::GLARESHIELD_INDICATOR)
    {
        FrameGlareshieldIndicator glareshieldIndicatorFrame(frame);

        if(glareshieldIndicatorFrame != m_glareshieldIndicatorFrame)
        {
            m_glareshieldIndicatorFrame = glareshieldIndicatorFrame;
            setLights();
        }
    }


    else if(frame.getId() == e_frameId::BRIGTNESS_PANEL)
    {
        FrameBrightnessPanel brightnessPanelFrame(frame);

        if(brightnessPanelFrame != m_brightnessPanelFrame)
        {
            m_brightnessPanelFrame = brightnessPanelFrame;

            m_pPanelDim->write(m_brightnessPanelFrame.getGlarshield());
            m_pButtonDim->write(m_brightnessPanelFrame.getButton());
            m_pIndicatorsDim->write(m_brightnessPanelFrame.getLightButton());

            m_bIsTestLight = m_brightnessPanelFrame.isTestLight();

            setLights();
        }
    }
}

void CanBusEventHandler::setLights()
{
    m_pAp1->on(m_glareshieldIndicatorFrame.getAp1() || m_bIsTestLight);
    m_pAp2->on(m_glareshieldIndicatorFrame.getAp2() || m_bIsTestLight);
    m_pAthr->on(m_glareshieldIndicatorFrame.getAutoThrottle() || m_bIsTestLight);
    m_pLoc->on(m_glareshieldIndicatorFrame.getLoc() || m_bIsTestLight);
    m_pExped->on(m_glareshieldIndicatorFrame.getExped() || m_bIsTestLight);
    m_pAppr->on(m_glareshieldIndicatorFrame.getApproch() || m_bIsTestLight); 
}