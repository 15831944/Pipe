#include "StdAfx.h"
#include "HedgeTradeTr.h"


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
		OutputDebugString(szBuff);
	}
}
