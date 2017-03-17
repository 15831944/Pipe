#include "StdAfx.h"
#include <iostream>
#include <process.h>
#include "Transmission.h"

bool Transmission::EndTransmission = false;

Transmission::Transmission(void)
{
}

Transmission::~Transmission(void)
{
}
/*
void Transmission::execute(const char* lpszSendPath, const char* lpszReciveParh)
{
	EndTransmission = false;
	while(!EndTransmission){

	}
}
*/

void Transmission::execute(const char* lpszPath)
{
	EndTransmission = false;
	
	_beginthread( Transmission::sendData, 0, (void*)lpszPath);
	_beginthread( Transmission::reciveData, 0, (void*)lpszPath);

}

void Transmission::sendData(void* lpszPath)
{
	BYTE Buff[256];
	DWORD Result;
	HANDLE Pipe = NULL;
	//HANDLE hEvent = CreateEvent(NULL,FALSE,FALSE,"EVENT");
	HANDLE hEvent = NULL;
	HANDLE hOnReadyEvent = CreateEvent(NULL,FALSE,FALSE,"EVENT_READY");
	
	//Pipe = CreateNamedPipe((const char*)lpszPath, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(Buff), sizeof(Buff), 1000, NULL);

	for( int n = 1; !EndTransmission; n++ ){
		Pipe = CreateNamedPipe((const char*)lpszPath, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(Buff), sizeof(Buff), 1000, NULL);
		BOOL isConnect = FALSE;
		
		if( Pipe != INVALID_HANDLE_VALUE ){
			SetEvent(hOnReadyEvent);
			isConnect = ConnectNamedPipe(Pipe, NULL);
		}

		if( isConnect ){
			char debugString[256];
			double spread[] = { 0.0025, 0.0024, 0.0023 };

			memcpy(Buff, &spread[n%3], sizeof(double));
			WriteFile(Pipe, Buff, sizeof(Buff), &Result, NULL);
			//FlushFileBuffers(Pipe);
			//DisconnectNamedPipe(Pipe);
			CloseHandle(Pipe);
			std::cout << "sendData \"" << spread[n%3] << '\"' << std::endl;
			sprintf(debugString, "sendData=%lf\n", spread[n%3] );
			OutputDebugString(debugString);
			
			if( hEvent == NULL )
				hEvent = CreateEvent(NULL,FALSE,FALSE,"EVENT");
			
			SetEvent(hEvent);
		}
		else{
			std::cout << "Error CreateNamedPipe" << std::endl;
			OutputDebugString("Error CreateNamedPipe\n");
			Sleep(1);
			continue;
		}

		//OutputDebugString("notify event before\n");
		//SetEvent(hEvent);
		Sleep(1000);
	}
	//CloseHandle(Pipe);
	CloseHandle(hOnReadyEvent);
	CloseHandle(hEvent);

	/*
	BYTE Buff[256];
	DWORD Result;
	HANDLE Pipe = NULL;

	for( int n = 1; !EndTransmission; n++ ){
		Pipe = CreateNamedPipe((const char*)lpszPath, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, sizeof(Buff), sizeof(Buff), 1000, NULL);
						
		if( Pipe != INVALID_HANDLE_VALUE ){
			ConnectNamedPipe(Pipe, NULL);
			char debugString[256];
			double spread[] = { 0.0025, 0.0024, 0.0023 };

			memcpy(Buff, &spread[n%3], sizeof(double));			
			WriteFile(Pipe, Buff, sizeof(Buff), &Result, NULL);
			FlushFileBuffers(Pipe);
			DisconnectNamedPipe(Pipe);
			CloseHandle(Pipe);
			std::cout << "sendData \"" << spread[n%3] << '\"' << std::endl;
			sprintf(debugString, "sendData=%lf\n", spread[n%3] );
			OutputDebugString(debugString);
		}
		else{
			std::cout << "Error CreateNamedPipe" << std::endl;
			OutputDebugString("Error CreateNamedPipe\n");
			Sleep(1);
			continue;
		}
	
		Sleep(1000);
	}
	*/
	/*
	char Buff[256];
	DWORD Result;

	for( int n = 1; !EndTransmission; n++ ){
		auto Pipe = CreateNamedPipe((const char*)lpszPath, PIPE_ACCESS_OUTBOUND, PIPE_TYPE_MESSAGE, 1, sizeof(Buff), sizeof(Buff), 1000, NULL);
						
		if( Pipe != INVALID_HANDLE_VALUE ){
			ConnectNamedPipe(Pipe, NULL);
			char debugString[256];

			//"TEST"‚Æ‚¢‚¤•¶Žš—ñ‚ð‘—M
			sprintf(Buff, "TEST=%d", n);
			WriteFile(Pipe, Buff, sizeof(Buff), &Result, NULL);
			CloseHandle(Pipe);
			std::cout << "sendData \"" << Buff << '\"' << std::endl;
			sprintf(debugString, "sendData=%s\n", Buff);
			OutputDebugString(debugString);
		}
		else{
			std::cout << "Error CreateNamedPipe" << std::endl;
			OutputDebugString("Error CreateNamedPipe\n");
			Sleep(1);
			continue;
		}
	
		Sleep(1000);
	}
	*/
}

void Transmission::reciveData(void* lpszPath)
{
	HANDLE hEvent = NULL;
	HANDLE hOnReadyEvent = NULL;
	HANDLE Pipe = NULL;
	BYTE Buff[256];
	DWORD Result;
	int debug = 0;

	while(hOnReadyEvent == NULL ){
		hOnReadyEvent = OpenEvent(EVENT_ALL_ACCESS,FALSE,"EVENT_READY");
		debug++;
	}

	//while(hEvent == NULL ){
	//	hEvent = OpenEvent(EVENT_ALL_ACCESS,FALSE,"EVENT");
	//}

	while( !EndTransmission ){
		WaitForSingleObject(hOnReadyEvent, INFINITE);
		Pipe = CreateFile((const char*)lpszPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		
		if( Pipe != INVALID_HANDLE_VALUE ){
			char debugString[256];
			double spread = 0.0;
			
			while(hEvent == NULL )
				hEvent = OpenEvent(EVENT_ALL_ACCESS,FALSE,"EVENT");

			WaitForSingleObject(hEvent, INFINITE);

			ReadFile(Pipe, Buff, sizeof(Buff), &Result, NULL);
			spread = *(reinterpret_cast<double*>(Buff));

			CloseHandle(Pipe);
			std::cout << "reciveData \"" << spread << '\"' << std::endl;
			sprintf(debugString, "reciveData=%lf\n", *(reinterpret_cast<double*>(Buff)));
			OutputDebugString(debugString);
			ResetEvent(hEvent);
			ResetEvent(hOnReadyEvent);
		}
		else{
			std::cout << "Error CreateFile" << std::endl;
			OutputDebugString("Error CreateFile\n");
			Sleep(1);
		}

		//Sleep(1000);
	}

	CloseHandle(hOnReadyEvent);
	CloseHandle(hEvent);
	/*
	BYTE Buff[256];
	DWORD Result;
	HANDLE Pipe = NULL;

	while( !EndTransmission ){
		Pipe = CreateFile((const char*)lpszPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		
		if( Pipe != INVALID_HANDLE_VALUE ){
			char debugString[256];
			double spread = 0.0;

			ReadFile(Pipe, Buff, sizeof(Buff), &Result, NULL);
			spread = *(reinterpret_cast<double*>(Buff));

			CloseHandle(Pipe);
			std::cout << "reciveData \"" << spread << '\"' << std::endl;
			sprintf(debugString, "reciveData=%lf\n", *(reinterpret_cast<double*>(Buff)));
			OutputDebugString(debugString);
		}
		else{
			std::cout << "Error CreateFile" << std::endl;
			OutputDebugString("Error CreateFile\n");
			Sleep(1);
			continue;
		}
	
		Sleep(1000);
	}
	*/

	/*
	char Buff[256];
	DWORD Result;

	while( !EndTransmission ){
		auto Pipe = CreateFile((const char*)lpszPath, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		
		if( Pipe != INVALID_HANDLE_VALUE ){
			char debugString[256];

			ReadFile(Pipe, Buff, sizeof(Buff), &Result, NULL);

			CloseHandle(Pipe);
			std::cout << "reciveData \"" << Buff << '\"' << std::endl;
			sprintf(debugString, "reciveData=%s\n", Buff);
			OutputDebugString(debugString);
		}
		else{
			std::cout << "Error CreateFile" << std::endl;
			OutputDebugString("Error CreateFile\n");
			Sleep(1);
			continue;
		}
	
		Sleep(1000);
	}
	*/
}

void Transmission::endTransmission()
{
	EndTransmission = true;
}
