#pragma once
class Transmitter
{
public:
	Transmitter(void);
	virtual ~Transmitter(void);

	void sendData(LPCTSTR lpszPath, const BYTE* lpData, size_t size);
	
	void beginReciveData(LPCTSTR lpszPath);

	void beginSendData(LPCTSTR lpszPath);

	void beginTestSendData(LPCTSTR lpszTestPath);

	/////////////////////////////////////////////////////
	//
	//	Get/Set

	void setPath(LPCTSTR value){
		m_path = value;
	}

	LPCTSTR path() const {
		return m_path;
	}

	void setSendPath(LPCTSTR value){
		m_sendPath = value;
	}

	LPCTSTR sendPath() const {
		return m_sendPath;
	}

	void setTestPath(LPCTSTR value){
		m_testPath = value;
	}

	LPCTSTR testPath() const {
		return m_testPath;
	}

	void setDoesReciveData(bool value){
		m_doesReciveData = value;
	}

	bool doesSendData() const {
		return m_doesSendData;
	}

	void setDoesSendData(bool value){
		m_doesSendData = value;
	}

	bool doesReciveData() const {
		return m_doesReciveData;
	}

	/////////////////////////////////////////////////////
	//
	//	EventName

	virtual const CString& onReadyReciveEventName() const = 0;
	
	virtual const CString& onReciveEventName() const = 0;

	virtual const CString& onReadySendEventName() const = 0;
	
	virtual const CString& onSendEventName() const = 0;

protected:
	static const CString ON_READY_SPREAD;
	
	static const CString ON_DATA_SPREAD;

	static const CString ON_READY_TRADE;
	
	static const CString ON_DATA_TRADE;

protected:

	virtual void setReciveData(BYTE* data, DWORD size) = 0;

private:
	static void reciveDataProc(void* transmitter);

	static void sendDataProc(void* transmitter);

	static void testSendData(void* transmitter);	

private:
	bool m_doesReciveData;

	bool m_doesSendData;

	CString m_path;

	CString m_sendPath;

	CString m_testPath;
};
