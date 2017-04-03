#include "StdAfx.h"
#include "Transmitter.h"
#include "stUtility.h"
#include "TradeDataManager.h"

const CString Transmitter::ON_READY_SPREAD = _T("OnReadySpread");
	
const CString Transmitter::ON_DATA_SPREAD = _T("OnDataSpread");

const CString Transmitter::ON_READY_TRADE = _T("OnReadyTrade");
	
const CString Transmitter::ON_DATA_TRADE = _T("OnDataTrade");


Transmitter::Transmitter(void)
	: m_doesReciveData(false)
	, m_doesSendData(false)
	, m_path()
	, m_sendPath()
	, m_testPath()
{
}

Transmitter::~Transmitter(void)
{
}

void Transmitter::sendData(LPCTSTR lpszPath, const BYTE* lpData, size_t size)
{
	CString debug;
	BYTE Buff[256];
	DWORD dwResult = 0;
	HANDLE hPipe = NULL;
	HANDLE hOnData = NULL;
	/*
	debug.Format(_T("Transmitter::sendData before CreateEvent onReadySendEventName=%s\n"), onReadySendEventName());
	OutputDebugString(debug);
	*/

	HANDLE hOnReady = CreateEvent( NULL, FALSE, FALSE, onReadySendEventName() );
	BOOL isConnect = FALSE;

	stUtility::writeLog( _T("Transmitter::sendData CreateEvent onReadySendEventName=%s hOnReady=%d\n"), onReadySendEventName(), (int)hOnReady);

	hPipe = CreateNamedPipe(lpszPath, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(Buff), sizeof(Buff), 10000, NULL);

	stUtility::writeLog( _T("Transmitter::sendData CreateNamedPipe lpszPath=%s hPipe=%d\n"), lpszPath, (int)hPipe);
		
	if( hPipe != INVALID_HANDLE_VALUE ){
		OutputDebugString("Transmitter::sendData before SetEvent hOnReady\n");
		SetEvent(hOnReady);
		isConnect = ConnectNamedPipe(hPipe, NULL);
	}

	if( isConnect ){
		memcpy(Buff, lpData, size);
		WriteFile(hPipe, Buff, sizeof(Buff), &dwResult, NULL);
		CloseHandle(hPipe);
		
		if( hOnData == NULL ){
			hOnData = CreateEvent( NULL, FALSE, FALSE, onSendEventName() );
			stUtility::writeLog( _T("Transmitter::sendData CreateEvent onSendEventName()=%s hOnData=%d data=%d\n"), onSendEventName(), (int)hOnData, *((int*)lpData) );
		}
		
		OutputDebugString("Transmitter::sendData before SetEvent hOnData\n");
		SetEvent(hOnData);
	}
	else{
		OutputDebugString("Error CreateNamedPipe\n");
	}

	CloseHandle(hOnReady);
	CloseHandle(hOnData);
}

void Transmitter::beginReciveData(LPCTSTR lpszPath)
{
	setPath(lpszPath);
	setDoesReciveData(true);
	_beginthread( Transmitter::reciveDataProc, 0, static_cast<void*>(this) );
}

void Transmitter::reciveDataProc(void* transmitter)
{
	Transmitter* tr = static_cast<Transmitter*>(transmitter);
	HANDLE hOnData = NULL;
	HANDLE hOnReady = NULL;
	HANDLE hPipe = NULL;
	BYTE buff[256];
	
	while(hOnReady == NULL){
		Sleep(1);	//	CPUリソースの消費を抑える
		hOnReady = OpenEvent( EVENT_ALL_ACCESS, FALSE, tr->onReadyReciveEventName() );
		OutputDebugString("Transmitter::reciveData after OpenEvent hOnReady\n");
	}

	while( tr->doesReciveData() ){
		WaitForSingleObject(hOnReady, INFINITE);
		hPipe = CreateFile(tr->path(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		stUtility::writeLog( _T("Transmitter::reciveData CreateFile path()=%s hPipe=%d\n"), tr->path(), hPipe);
		
		if( hPipe != INVALID_HANDLE_VALUE ){
			DWORD dwResult = 0;
			
			while( hOnData == NULL ){
				hOnData = OpenEvent(EVENT_ALL_ACCESS,FALSE, tr->onReciveEventName() );
			}

			stUtility::writeLog( _T("Transmitter::reciveData OpenEvent onReciveEventName()=%s hOnData=%d\n"), tr->onReciveEventName(), hOnData);

			WaitForSingleObject(hOnData, INFINITE);

			ReadFile(hPipe, buff, sizeof(buff), &dwResult, NULL);
			tr->setReciveData(buff, dwResult);
			OutputDebugString("Transmitter::reciveData after setReciveData\n");

			CloseHandle(hPipe);
			ResetEvent(hOnData);
			ResetEvent(hOnReady);
		}
		else{
			OutputDebugString("Error CreateFile\n");
			Sleep(1);
		}
	}

	CloseHandle(hOnReady);
	CloseHandle(hOnData);
}

void Transmitter::beginSendData(LPCTSTR lpszPath)
{
	setSendPath(lpszPath);
	setDoesSendData(true);
	_beginthread( Transmitter::sendDataProc, 0, static_cast<void*>(this) );
}

void Transmitter::sendDataProc(void* transmitter)
{
	Transmitter* tr = static_cast<Transmitter*>(transmitter);
	TradeDataManager::dataContainer conData;

	while( tr->doesSendData() ){
		TradeDataManager::instance().moveData(conData);

		while( !conData.empty() ){
			const auto& data = conData.front();

			tr->sendData( tr->sendPath(), data.get(), data.size() );
			//	TODO ログ出力
			conData.pop();
		}
		
		::Sleep(1);
	}
}

void Transmitter::beginTestSendData(LPCTSTR lpszPath)
{
	setTestPath(lpszPath);
	_beginthread( Transmitter::testSendData, 0, static_cast<void*>(this) );
}

void Transmitter::testSendData(void* transmitter)
{
	int trade[] = {1, 2};
	static int cnt = 0;
	Transmitter* tr = static_cast<Transmitter*>(transmitter);
	BYTE buff[32];

	while(true){
		memcpy( buff, &trade[cnt%2], sizeof(int) );

		tr->sendData( tr->testPath(), buff, sizeof(int) );
		::Sleep(2000);
		cnt++;
	}
}
