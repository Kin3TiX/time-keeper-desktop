/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* time keeper interface ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#pragma once
#include "tkd-notifier.h"

/* time keeper class definition */
class TIMEKEEPER {

	/* public members */
public:

	/* constructors, destructor*/
	TIMEKEEPER();
	TIMEKEEPER(NOTIFIER &);
	~TIMEKEEPER();
	
	/* public time keeper interface */
	void setNotifier(NOTIFIER &);
	void setTimerConfig();

	/* private members */
private:

	/* private data members */
	NOTIFIER * myNotifier;
	HANDLE timer;
	DWORD timerThreadID;
	HANDLE logger;
	DWORD loggerThreadID;
	bool configured;
	bool destroy;
	ULONGLONG currentTime;
	ULONGLONG notifyTime;
	
	/* private internal functions */
	void initialize();
	static DWORD WINAPI timerLaunch(LPVOID);
	static DWORD WINAPI loggerLaunch(LPVOID);
	int timerThread();
	int loggerThread();
	bool checkTime();
	int logData();
	void getNextNotification();

};

