#include "StdAfx.h"
#include "Transmitter.h"

const CString Transmitter::ON_READY = _T("OnReady");
	
const CString Transmitter::ON_DATA = _T("OnData");

Transmitter::Transmitter(void)
{
}

Transmitter::~Transmitter(void)
{
}

void Transmitter::sendData(LPCTSTR lpszPath, BYTE* lpData, size_t size)
{
	BYTE Buff[256];
	DWORD dwResult = 0;
	HANDLE hPipe = NULL;
	HANDLE hOnData = NULL;
	HANDLE hOnReady = CreateEvent( NULL, FALSE, FALSE, ON_READY );
	BOOL isConnect = FALSE;

	hPipe = CreateNamedPipe(lpszPath, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(Buff), sizeof(Buff), 1000, NULL);
		
	if( hPipe != INVALID_HANDLE_VALUE ){
		SetEvent(hOnReady);
		isConnect = ConnectNamedPipe(hPipe, NULL);
	}

	if( isConnect ){
		memcpy(Buff, lpData, size);
		WriteFile(hPipe, Buff, sizeof(Buff), &dwResult, NULL);
		CloseHandle(hPipe);
		
		if( hOnData == NULL )
			hOnData = CreateEvent( NULL, FALSE, FALSE, ON_DATA );
			
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
	_beginthread( Transmitter::reciveData, 0, static_cast<void*>(this) );
}

void Transmitter::reciveData(void* transmitter)
{
	Transmitter* tr = static_cast<Transmitter*>(transmitter);
	HANDLE hOnData = NULL;
	HANDLE hOnReady = NULL;
	HANDLE hPipe = NULL;
	BYTE buff[256];
	
	while(hOnReady == NULL){
		Sleep(1);	//	CPUƒŠƒ\[ƒX‚ÌÁ”ï‚ð—}‚¦‚é
		hOnReady = OpenEvent( EVENT_ALL_ACCESS, FALSE, ON_READY);
	}

	while( tr->doesReciveData() ){
		WaitForSingleObject(hOnReady, INFINITE);
		hPipe = CreateFile(tr->path(), GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		
		if( hPipe != INVALID_HANDLE_VALUE ){
			DWORD dwResult = 0;
			
			while( hOnData == NULL ){
				hOnData = OpenEvent(EVENT_ALL_ACCESS,FALSE, ON_DATA);
			}

			WaitForSingleObject(hOnData, INFINITE);

			ReadFile(hPipe, buff, sizeof(buff), &dwResult, NULL);
			tr->setReciveData(buff, dwResult);

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
