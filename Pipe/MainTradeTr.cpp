#include "StdAfx.h"
#include "MainTradeTr.h"
#include "stUtility.h"

MainTradeTr::MainTradeTr(void)
	: m_hedgeAccountSpread(0.0)
{
}

MainTradeTr::~MainTradeTr(void)
{
}

void MainTradeTr::setReciveData(BYTE* data, DWORD size){
	if(sizeof(double) == size){
		TCHAR szBuff[128];

		m_hedgeAccountSpread = *(reinterpret_cast<double*>(data));
		_stprintf(szBuff, _T("Spread=%.5lf\n"), m_hedgeAccountSpread);
		stUtility::writeLog( _T("MainTradeTr::setReciveData %s\n"), szBuff );

		OutputDebugString(szBuff);
	}
}

const CString& MainTradeTr::onReadyReciveEventName() const
{
	return ON_READY_SPREAD;
}

const CString& MainTradeTr::onReciveEventName() const
{
	return ON_DATA_SPREAD;	
}

const CString& MainTradeTr::onReadySendEventName() const
{
	return ON_READY_TRADE;
}
	
const CString& MainTradeTr::onSendEventName() const
{
	return ON_DATA_TRADE;
}
