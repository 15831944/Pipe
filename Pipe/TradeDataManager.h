#pragma once

#include <queue>
#include "TradeData.h"

class TradeDataManager
{
public:
	typedef std::queue<TradeData> dataContainer;

	static TradeDataManager& instance();

	void addData(const TradeData& data);

	void moveData(dataContainer& data);

private:
	TradeDataManager(void);
	virtual ~TradeDataManager(void);

	dataContainer m_conData;
};

