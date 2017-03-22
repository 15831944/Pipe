#pragma once
#include "transmitter.h"
class HedgeTradeTr :
	public Transmitter
{
public:
	HedgeTradeTr(void);
	virtual ~HedgeTradeTr(void);

protected:
	const CString& onReadyReciveEventName() const override;

	const CString& onReciveEventName() const override;

	const CString& onReadySendEventName() const override;
	
	const CString& onSendEventName() const override;
	
	void setReciveData(BYTE* data, DWORD size) override;

	enum HedgeTrade : int{
		NONE,
		CLOSE_LONG,
		CLOSE_SHORT
	};
	
private:
	HedgeTrade m_hedgeTrade;
};
