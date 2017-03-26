#include "StdAfx.h"
#include "TransmitterService.h"
#include "MainTradeTr.h"
#include "HedgeTradeTr.h"
#include "TradeDataManager.h"

CString TransmitterService::PathSpread = _T("\\\\.\\pipe\\Spread");
CString TransmitterService::PathTrade = _T("\\\\.\\pipe\\Trade");

TransmitterService::TransmitterService(void)
{
}

TransmitterService::~TransmitterService(void)
{
}

TransmitterService& TransmitterService::instance()
{
	static TransmitterService Singleton;

	return Singleton;
}

void TransmitterService::beginMainTrade()
{
	stop();

	try{
		m_trans.reset(new MainTradeTr());
		m_trans->beginReciveData(PathSpread);
		m_trans->beginSendData(PathTrade);
	}
	catch(std::bad_alloc& e){
		// TODO ログ出力
	}
	catch(...){
		// TODO ログ出力
	}
}

void TransmitterService::beginHedgeTrade()
{
	stop();

	try{
		m_trans.reset(new HedgeTradeTr());
		m_trans->beginReciveData(PathTrade);
		m_trans->beginSendData(PathSpread);
	}
	catch(std::bad_alloc& e){
		// TODO ログ出力
	}
	catch(...){
		// TODO ログ出力
	}
}

void TransmitterService::stop()
{
	if(m_trans){
		m_trans->setDoesReciveData(false);
		m_trans->setDoesSendData(false);	
		m_trans.reset(nullptr);
	}
}

void TransmitterService::addSpread(double spread)
{
	TradeData data;
	const BYTE* dataPtr = static_cast<BYTE*>(static_cast<void*>(&spread));
	
	data.set(dataPtr, sizeof(double));
	TradeDataManager::instance().addData(data);
}

void TransmitterService::addTrade(Trade trade)
{
	TradeData data;
	const BYTE* dataPtr = static_cast<BYTE*>(static_cast<void*>(&trade));
	
	data.set(dataPtr, sizeof(Trade));
	TradeDataManager::instance().addData(data);
}
