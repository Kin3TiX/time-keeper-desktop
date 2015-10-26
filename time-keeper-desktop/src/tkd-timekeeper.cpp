/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* time keeper implementation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "tkd-pc.h"
#include "tkd-timekeeper.h"

/* default constructor */
TIMEKEEPER::TIMEKEEPER() { 
	
	/* init time keeper */
	initialize();

}

/* constructor overload, provided notifier */
TIMEKEEPER::TIMEKEEPER(NOTIFIER & notifier) {

	/* set notifier and init time keeper */
	myNotifier = &notifier;
	initialize();

}

/* destructor */
TIMEKEEPER::~TIMEKEEPER() { 

	/* signal threads to stop */
	destroy = true;

	/* wait for threads to join */
	WaitForSingleObject(timer, 500);
	WaitForSingleObject(logger, 500);

}

/* set linked notifier */
void TIMEKEEPER::setNotifier(NOTIFIER & notifier) { 
	
	/* set my notifier to provided notifier reference */
	myNotifier = &notifier;

}

/* set the configuration of the timer */
void TIMEKEEPER::setTimerConfig() {

}

/* initialize the time keeper */
void TIMEKEEPER::initialize() { 

	/* reset thread stop flag */
	destroy = false;

	/* initialize current time */
	currentTime = GetTickCount();

	getNextNotification();

	/* launch asynchronous timer thread */
	timer = CreateThread(NULL,
						 0,
						 timerLaunch,
						 this,
						 0,
						 &timerThreadID);

	/* launch asynchronous data logging thread */
	logger = CreateThread(NULL,
						  0,
						  loggerLaunch,
						  this,
						  0,
						  &loggerThreadID);

}

/* timer thread entrypoint */
DWORD TIMEKEEPER::timerLaunch(LPVOID pThis) {

	/* get current object via provided pointer */
	TIMEKEEPER * instance = (TIMEKEEPER *) pThis;

	/* call this object's timer thread function */
	instance->timerThread();

	return 0;

}

/* logger thread entrypoint */
DWORD TIMEKEEPER::loggerLaunch(LPVOID pThis) {

	/* get current object via provided pointer */
	TIMEKEEPER * instance = (TIMEKEEPER *) pThis;

	/* call this object's logger thread function */
	instance->loggerThread();

	return 0;

}

/* timer thread main function */
int TIMEKEEPER::timerThread() {

	/* run until stop flag is set */
	while( !destroy ) {

		/* sleep to allow CPU time for other processes */
		Sleep(100);

		/* wake up, get current time */
		currentTime = GetTickCount64();

		/* if there is a valid notifier set, and checktime() is true */
		if( myNotifier && checkTime() ) {

			/* if the notifier popup is visible, hide it */
			if( myNotifier->visible ) {
				myNotifier->hide();
				getNextNotification();
			
			/* if the notifier popup is inivisible, show it */
			} else {
				myNotifier->show();
				getNextNotification();
			}

		}

	}

	/* return OK */
	return 0;

}

/* logger thread main function */
int TIMEKEEPER::loggerThread() {

	/* run until stop flag detected */
	while( !destroy ) {

		/* sleep to allow CPU time for other processes */
		Sleep(100);

	}

	/* return OK */
	return 0;

}

/* check the current time to see if it matches the notifier time */
bool TIMEKEEPER::checkTime() {

	/* return yay or nay */
	return currentTime >= notifyTime;

}

/* log current task data to database */
int TIMEKEEPER::logData() {

	return 0;

}

/* set the next notify time based on user settings */
void TIMEKEEPER::getNextNotification() {

	/* set current time */
	notifyTime = GetTickCount64();

	/* increment time based on operation */
	if( myNotifier->visible ) {

		/* notifier popup is visible, hide it in 45 seconds */
		notifyTime += 4500;

	} else {

		/* show again in 1 hour */
		notifyTime += 3600000;

	}

}
