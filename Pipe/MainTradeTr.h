#pragma once
#include "transmitter.h"
class MainTradeTr :
	public Transmitter
{
public:
	MainTradeTr(void);
	virtual ~MainTradeTr(void);

	double hedgeAccountSpread() const{
		return m_hedgeAccountSpread;
	}

protected:
	void setReciveData(BYTE* data, DWORD size) override;

	const CString& onReadyReciveEventName() const override;

	const CString& onReciveEventName() const override;

	const CString& onReadySendEventName() const override;
	
	const CString& onSendEventName() const override;

private:
	//	�w�b�W�A�J�E���g�X�v���b�h
	double m_hedgeAccountSpread;

};

