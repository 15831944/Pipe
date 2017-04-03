#include "StdAfx.h"
#include "HedgeTradeTr.h"
#include "stUtility.h"


HedgeTradeTr::HedgeTradeTr(void)
	: m_hedgeTrade(HedgeTrade::NONE)
{
}

HedgeTradeTr::~HedgeTradeTr(void)
{
}

void HedgeTradeTr::setReciveData(BYTE* data, DWORD size)
{
	if(sizeof(HedgeTrade) == size){
		TCHAR szBuff[128];

		m_hedgeTrade = *(reinterpret_cast<HedgeTrade*>(data));
		_stprintf(szBuff, _T("Trade=%d\n"), (int)m_hedgeTrade);
		stUtility::writeLog( _T("HedgeTradeTr::setReciveData %s\n"), szBuff );
		OutputDebugString(szBuff);
	}
}

const CString& HedgeTradeTr::onReadyReciveEventName() const
{
	return ON_READY_TRADE;
}

const CString& HedgeTradeTr::onReciveEventName() const
{
	return ON_DATA_TRADE;
}

const CString& HedgeTradeTr::onReadySendEventName() const
{
	return ON_READY_SPREAD;
}
	
const CString& HedgeTradeTr::onSendEventName() const
{
	return ON_DATA_SPREAD;
}
