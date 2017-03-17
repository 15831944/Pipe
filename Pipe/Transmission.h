#pragma once
class Transmission
{
public:
	Transmission(void);
	virtual ~Transmission(void);

	void execute(const char* lpszPath);

	//void execute(const char* lpszSendPath, const char* lpszRecivePath);

	static void endTransmission();

private:
	static void sendData(void* lpszPath);
	static void reciveData(void* lpszPath);

private:
	static bool EndTransmission;
};

