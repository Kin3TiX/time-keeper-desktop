#pragma once

#include "tkd-notifier.h"

class TIMEKEEPER {

public:

	TIMEKEEPER();
	TIMEKEEPER(NOTIFIER &);
	~TIMEKEEPER();

	void setNotifier(NOTIFIER &);
	void setTimerConfig();

private:

	NOTIFIER * myNotifier;
	HANDLE timer;
	DWORD timerThreadID;
	HANDLE logger;
	DWORD loggerThreadID;
	bool configured;
	bool destroy;
	SYSTEMTIME currentTime;
	SYSTEMTIME notifyTime;
	
	void initialize();
	static DWORD WINAPI timerLaunch(LPVOID);
	static DWORD WINAPI loggerLaunch(LPVOID);
	int timerThread();
	int loggerThread();
	bool checkTime();
	int logData();

};

