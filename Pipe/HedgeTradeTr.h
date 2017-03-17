#pragma once
#include "transmitter.h"
class HedgeTradeTr :
	public Transmitter
{
public:
	HedgeTradeTr(void);
	virtual ~HedgeTradeTr(void);

protected:
	void setReciveData(BYTE* data, DWORD size) override;

	enum HedgeTrade : int{
		NONE,
		CLOSE_LONG,
		CLOSE_SHORT
	};
	
private:
	HedgeTrade m_hedgeTrade;
};
