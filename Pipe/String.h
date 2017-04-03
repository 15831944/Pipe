#pragma once

#include <vector>

class String;

namespace aht{
	typedef std::vector<String> vecString;
};

#include "TypeDef.h"

class String : public aht::tstring
{
public:
	String();
	String(LPCTSTR lpszStr);
	String(const aht::tstring& arg);
	virtual ~String();

	operator LPCTSTR() const{ return c_str(); }

	//	�����񕪉�
	void split( aht::vecString& tokens, LPCTSTR lpszSep ) const;

	//	�t�H�[�}�b�g
	aht::result format( LPCTSTR lpszFmt, ...);

	//	�啶���ϊ�
	String& toUpper();
	
	//	�������ϊ�
	String& toLower();

	//	��������
	String left(int nCount) const;

	//	�E������
	String right(int nCount) const;

	//	��r���Z�q
	virtual bool operator==( LPCTSTR lpszArg) const;
	virtual bool operator!=( LPCTSTR lpszArg) const;
	virtual bool operator<( LPCTSTR lpszArg) const;
	virtual bool operator<=( LPCTSTR lpszArg) const;
	virtual bool operator>( LPCTSTR lpszArg) const;
	virtual bool operator>=( LPCTSTR lpszArg) const;

	virtual bool operator==( const String& arg) const;
	virtual bool operator!=( const String& arg) const;
	virtual bool operator<( const String& arg) const;
	virtual bool operator<=( const String& arg) const;
	virtual bool operator>( const String& arg) const;
	virtual bool operator>=( const String& arg) const;

	//	�n�b�V���l
	struct Hash{
		std::size_t operator()(const String& key) const;
	};
};


/**
 * �n�b�V���֐�
 */
inline std::size_t String::Hash::operator()(const String& key) const {
    return std::hash<aht::tstring>()((LPCTSTR)this);
}

inline String::String()
{
}

inline String::String(LPCTSTR lpszStr)
{
	assign( lpszStr, _tcslen(lpszStr) );
}

inline String::String(const aht::tstring& arg)
{
	*this = arg.c_str(); 
}

inline String::~String()
{
}

inline bool String::operator==( LPCTSTR lpszArg ) const
{
	return !_tcscmp( this->c_str(), lpszArg );
}

inline bool String::operator!=( LPCTSTR lpszArg ) const
{
	return !( *this == lpszArg );
}

inline bool String::operator<( LPCTSTR lpszArg ) const
{
	return _tcscmp( this->c_str(), lpszArg ) < 0;
}

inline bool String::operator<=( LPCTSTR lpszArg ) const
{
	return ( *this < lpszArg || *this == lpszArg );
}

inline bool String::operator>( LPCTSTR lpszArg ) const
{
	return _tcscmp( this->c_str(), lpszArg ) > 0;
}

inline bool String::operator>=( LPCTSTR lpszArg ) const
{
	return ( *this > lpszArg || *this == lpszArg );
}

inline bool String::operator==( const String& arg) const
{
	return *this == arg.c_str();
}

inline bool String::operator!=( const String& arg) const
{
	return !( *this == arg );
}

inline bool String::operator<( const String& arg) const
{
	return *this < arg.c_str();
}

inline bool String::operator<=( const String& arg) const
{
	return *this <= arg.c_str();
}

inline bool String::operator>( const String& arg ) const
{
	return *this > arg.c_str();
}

inline bool String::operator>=( const String& arg ) const
{
	return *this >= arg.c_str();
}