#include "tkd-pc.h"
#include "tkd-timekeeper.h"

TIMEKEEPER::TIMEKEEPER() { 
	
	initialize();

}

TIMEKEEPER::TIMEKEEPER(NOTIFIER & notifier) {

	myNotifier = &notifier;
	initialize();

}

TIMEKEEPER::~TIMEKEEPER() { 

	destroy = true;

	WaitForSingleObject(timer, 500);
	WaitForSingleObject(logger, 500);

}

void TIMEKEEPER::setNotifier(NOTIFIER & notifier) { 
	
	myNotifier = &notifier;

}

void TIMEKEEPER::setTimerConfig() {

}

void TIMEKEEPER::initialize() { 

	destroy = false;

	GetSystemTime(&currentTime);

	notifyTime = currentTime;
	notifyTime.wMinute += 1;

	timer = CreateThread(NULL,
						 0,
						 timerLaunch,
						 this,
						 0,
						 &timerThreadID);

	logger = CreateThread(NULL,
						  0,
						  loggerLaunch,
						  this,
						  0,
						  &loggerThreadID);

}

DWORD TIMEKEEPER::timerLaunch(LPVOID pThis) {

	TIMEKEEPER * instance = (TIMEKEEPER *) pThis;

	instance->timerThread();

	return 0;

}

DWORD TIMEKEEPER::loggerLaunch(LPVOID pThis) {

	TIMEKEEPER * instance = (TIMEKEEPER *) pThis;

	instance->loggerThread();

	return 0;

}

int TIMEKEEPER::timerThread() {

	while( !destroy ) {

		Sleep(100);

		GetSystemTime(&currentTime);

		if( myNotifier && checkTime() ) {
			if( myNotifier->visible )
				myNotifier->hide();
			else
				myNotifier->show();
			notifyTime = currentTime;
			notifyTime.wMinute += 1;
		}

	}

	return 0;

}

int TIMEKEEPER::loggerThread() {

	while( !destroy ) {

		Sleep(100);

	}

	return 0;

}

bool TIMEKEEPER::checkTime() {

	bool day = (currentTime.wDay == notifyTime.wDay);
	bool hour = (currentTime.wHour == notifyTime.wHour);
	bool minute = (currentTime.wMinute == notifyTime.wMinute);

	return day && hour && minute;

}

int TIMEKEEPER::logData() {

	return 0;

}
