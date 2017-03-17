#include "StdAfx.h"
#include "MainTradeTr.h"


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
		OutputDebugString(szBuff);
	}
}
