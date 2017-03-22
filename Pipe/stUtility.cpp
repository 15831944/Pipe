#include "StdAfx.h"
#include "stUtility.h"


//	ログ出力
bool stUtility::writeLog( 
	LPCTSTR lpszFilePath,	//(i)ファイルパス
	LPCTSTR lpszLog,		//(i)出力内容
	...						//(i)フォーマット引数
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
