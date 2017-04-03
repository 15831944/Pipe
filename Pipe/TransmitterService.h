#pragma once

#include <memory>
#include "Transmitter.h"

class TransmitterService
{
public:
	enum Trade : short{
		NONE,
		LONG,
		SHORT
	};

	static TransmitterService& instance();

	void beginMainTrade();

	void beginHedgeTrade();

	void addSpread(double spread);

	void addTrade(Trade trade);

private:
	TransmitterService(void);
	virtual ~TransmitterService(void);

	void stop();

private:
	typedef std::unique_ptr<Transmitter> transPtr;

	transPtr m_trans;

	static CString PathSpread;

	static CString PathTrade;
};
