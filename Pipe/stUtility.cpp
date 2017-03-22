#include "StdAfx.h"
#include "stUtility.h"


//	���O�o��
bool stUtility::writeLog( 
	LPCTSTR lpszFilePath,	//(i)�t�@�C���p�X
	LPCTSTR lpszLog,		//(i)�o�͓��e
	...						//(i)�t�H�[�}�b�g����
	)
{
	bool bResult = true;
	FILE* fp = _tfopen( lpszFilePath, _T("a") );	

	if( fp == NULL )
		return false;
	
	va_list	ap;
	TCHAR* lpszBuff = NULL;
	int nLen = 0;

	va_start(ap, lpszLog);
	nLen = _vsctprintf( lpszLog, ap ) + 1;

	try{
		lpszBuff = new TCHAR[nLen];

#ifdef _UNICODE
		_vstprintf( lpszBuff, nLen, lpszLog, ap );
#else
		_vstprintf( lpszBuff, lpszLog, ap );
#endif
		_ftprintf( fp, lpszBuff );
		va_end(ap);
		delete [] lpszBuff;
		lpszBuff = NULL;
	}
	catch( ... ){
		bResult = false;
	}

	fclose(fp);

	return bResult;
}
