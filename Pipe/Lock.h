#pragma once

#include "CriticalSection.h"

class Lock{
public:
	Lock(CriticalSection& cs);
	~Lock();

private:
	CriticalSection& m_cs;

};

inline Lock::Lock(CriticalSection& cs)
	: m_cs(cs)
{
	::EnterCriticalSection( &cs.get() );
}

inline Lock::~Lock()
{
	::LeaveCriticalSection( &m_cs.get() );
}
