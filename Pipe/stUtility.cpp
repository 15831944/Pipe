#include "StdAfx.h"
#include "stUtility.h"
#include "String.h"

//	ログ出力
bool stUtility::writeLog( 
	LPCTSTR lpszLog,		//(i)出力内容
	...						//(i)フォーマット引数
	)
{
	bool bResult = true;
	String filePath;
	stUtility::logFilepath(filePath);
	FILE* fp = _tfopen( filePath, _T("a") );	

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

void stUtility::logFilepath(std::string& filePath)
{
	TCHAR szPath[MAX_PATH];
	TCHAR szDrive[_MAX_DRIVE];
	TCHAR szDir[_MAX_DIR];
	TCHAR szFName[_MAX_FNAME];
	String strFName;
	time_t timer;
	struct tm *t_st;

	/* 現在時刻の取得 */
	time(&timer);

	t_st = localtime(&timer);

	::GetModuleFileName( NULL, szPath, MAX_PATH );
	_tsplitpath( szPath, szDrive, szDir, NULL, NULL );

	strFName.format( _T("%d%d%d"), t_st->tm_year + 1900, t_st->tm_mon + 1, t_st->tm_mday );

	_tcscat( szDir, _T("Log") );

	_tmakepath( szPath, szDrive, szDir, szFName, _T(".log") );

	filePath = szPath;
}
