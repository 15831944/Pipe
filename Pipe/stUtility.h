#pragma once

#include <string>

class stUtility
{
public:

	//	���O�o��
	static bool writeLog( LPCTSTR lpszLog, ...);
	
	static void logFilepath(std::string& filePath);
};

