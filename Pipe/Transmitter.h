#pragma once
class Transmitter
{
public:
	Transmitter(void);
	virtual ~Transmitter(void);

	void sendData(LPCTSTR lpszPath, BYTE* lpData, size_t size);
	
	void beginReciveData(LPCTSTR lpszPath);

	/////////////////////////////////////////////////////
	//
	//	Get/Set

	void setPath(LPCTSTR value){
		m_path = value;
	}

	LPCTSTR path() const {
		return m_path;
	}

	void setDoesReciveData(bool value){
		m_doesReciveData = value;
	}

	bool doesReciveData() const {
		return m_doesReciveData;
	}

public:
	static const CString ON_READY;
	
	static const CString ON_DATA;

protected:

	virtual void setReciveData(BYTE* data, DWORD size) = 0;

private:
	static void reciveData(void* transmitter);

private:
	

private:
	bool m_doesReciveData;

	CString m_path;
};
