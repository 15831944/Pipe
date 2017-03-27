#pragma once

#include <WinBase.h>

class CriticalSection{
public:
	CriticalSection(void);
	~CriticalSection(void);

	CRITICAL_SECTION& get();

private:
	// �r������p�N���e�B�J���Z�b�V����
	CRITICAL_SECTION m_cs;
};

inline CriticalSection::CriticalSection(void)
{
	::InitializeCriticalSection(&m_cs);
}

inline CriticalSection::~CriticalSection(void)
{
	::DeleteCriticalSection(&m_cs);
}

inline CRITICAL_SECTION& CriticalSection::get()
{
	return m_cs;
}
