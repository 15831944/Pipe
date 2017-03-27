#include "StdAfx.h"
#include "Lock.h"
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
	Lock lock(m_cs);

	m_conData.push(data);
}

void TradeDataManager::moveData(dataContainer& data)
{
	if( m_conData.empty() )
		return;

	Lock lock(m_cs);
	
	while( !m_conData.empty() ){
		data.push( m_conData.front() );
		m_conData.pop();	
	}
}
