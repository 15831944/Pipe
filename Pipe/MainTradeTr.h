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

private:
	//	ヘッジアカウントスプレッド
	double m_hedgeAccountSpread;

};

