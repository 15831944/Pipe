#include "StdAfx.h"
#include "TradeDataManager.h"


TradeDataManager::TradeDataManager(void)
{
}


TradeDataManager::~TradeDataManager(void)
{
}

TradeDataManager& TradeDataManager::instance()
{
	static TradeDataManager Singleton;

	return Singleton;
}

void TradeDataManager::addData(const TradeData& data)
{
	// TODO ロック
	m_conData.push(data);
}

void TradeDataManager::moveData(dataContainer& data)
{
	// TODO ロック
	while( !m_conData.empty() ){
		data.push( m_conData.front() );
		m_conData.pop();	
	}
}
