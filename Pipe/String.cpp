#include "stdafx.h"
#include "String.h"


void String::split( 
	aht::vecString& tokens, 
	LPCTSTR lpszSep 
	) const
{
    int s = -1;
	int e = static_cast<int>(find_first_of(lpszSep));
    
	while( e != aht::tstring::npos ){
        if( 0 < e )
			tokens.push_back( substr(s+1, e-(s+1)) );
        
		s = e;	
        e = static_cast<int>(find_first_of(lpszSep, e+1));
    }
    
	if( s < size()-1 )
        tokens.push_back(substr(s+1));
}

//	フォーマット
aht::result String::format( LPCTSTR lpszFmt, ...)
{
	aht::result result = aht::rOk;
	va_list	ap;
	TCHAR* lpszBuff = nullptr;

	va_start(ap, lpszFmt);

	try{
		size_t nLen = _vsctprintf( lpszFmt, ap ) + 1;
		
		lpszBuff = new TCHAR[nLen];
#ifdef _UNICODE
		_vstprintf( lpszBuff, nLen, lpszFmt, ap );
#else
		_vstprintf( lpszBuff, lpszFmt, ap );
#endif
		*this = lpszBuff;
		va_end(ap);
		delete [] lpszBuff;
	}
	catch( std::bad_alloc ){
		result = aht::rOutOfMemory;
	}
	catch(...){
		delete [] lpszBuff;
		result = aht::rFail;
	}

	return result;
}

//	大文字変換
String& String::toUpper()
{
	std::transform( begin(), end(), begin(), [](String::value_type v){ return toupper(v); } );
	return *this;
}

//	小文字変換
String& String::toLower()
{
	std::transform( begin(), end(), begin(), [](String::value_type v){ return tolower(v); } );
	return *this;
}

//	左側文字
String String::left(int nCount) const
{
	return substr(0, nCount);
}

//	右側文字
String String::right(int nCount) const
{
	return substr(size() - nCount, nCount);
}

