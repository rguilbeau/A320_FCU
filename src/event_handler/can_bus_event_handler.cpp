#include "can_bus_event_handler.hpp"

CanBusEventHandler::CanBusEventHandler(
    Light *pAp1,
    Light *pAp2,
    Light *pAthr,
    Light *pLoc,
    Light *pExped,
    Light *pAppr,
    Backlight *pIndicatorsDim,
    Backlight *pButtonDim,
    Backlight *pPanelDim
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

            m_pAp1->on(m_glareshieldIndicatorFrame.getAp1());
            m_pAp2->on(m_glareshieldIndicatorFrame.getAp2());
            m_pAthr->on(m_glareshieldIndicatorFrame.getAutoThrottle());
            m_pLoc->on(m_glareshieldIndicatorFrame.getLoc());
            m_pExped->on(m_glareshieldIndicatorFrame.getExped());
            m_pAppr->on(m_glareshieldIndicatorFrame.getApproch()); 
        }
    }


    else if(frame.getId() == e_frameId::BRIGTNESS_PANEL)
    {
        FrameBrightnessPanel brightnessPanelFrame(frame);

        if(brightnessPanelFrame != m_brightnessPanelFrame)
        {
            m_brightnessPanelFrame = brightnessPanelFrame;

            m_pPanelDim->set(m_brightnessPanelFrame.getGlarshield());
            m_pButtonDim->set(m_brightnessPanelFrame.getButton());
            m_pIndicatorsDim->set(m_brightnessPanelFrame.getLightButton());

            bool bIsTestLight = m_brightnessPanelFrame.isTestLight();
            m_pAp1->setTestLight(bIsTestLight);
            m_pAp2->setTestLight(bIsTestLight);
            m_pAthr->setTestLight(bIsTestLight);
            m_pLoc->setTestLight(bIsTestLight);
            m_pExped->setTestLight(bIsTestLight);
            m_pAppr->setTestLight(bIsTestLight); 
        }
    }

    else if(frame.getId() == e_frameId::POWER)
    {
        FramePower framePower(frame);
        
        if(m_framePower != framePower)
        {
            m_framePower = framePower;

            bool bIsPowered = m_framePower.isFcuPowered();

            m_pAp1->setPower(bIsPowered);
            m_pAp2->setPower(bIsPowered);
            m_pAthr->setPower(bIsPowered);
            m_pLoc->setPower(bIsPowered);
            m_pExped->setPower(bIsPowered);
            m_pAppr->setPower(bIsPowered); 

            m_pPanelDim->setPower(bIsPowered);
            m_pButtonDim->setPower(bIsPowered);
            m_pIndicatorsDim->setPower(bIsPowered);
        }
    }
}