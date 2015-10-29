/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* timestamp implementation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "tkd-timestamp.h"

/* constructor */
TIMESTAMP::TIMESTAMP(SYSTEMTIME initialTime) : myTime(initialTime) { }

/* destructor */
TIMESTAMP::~TIMESTAMP() { }

/* assign one timestamp to another */
void TIMESTAMP::operator=(const TIMESTAMP & other) {

	WORD day;
	WORD hour;
	WORD minute;

	other.getTime(day, hour, minute);

	myTime.wDay = day;
	myTime.wHour = hour;
	myTime.wMinute = minute;

}

/* compare two timestampes for equality */
 bool TIMESTAMP::operator==(const TIMESTAMP & other) {

	return false;

}

/* increment state of internal timestamp according to mode and value */
void TIMESTAMP::incrementTime(mode incrementMode, unsigned int incrementValue) { 

	/* switch in increment mode */
	switch( incrementMode ) {

		/* increment minutes */
		case MIN:
			incrementMinutes(incrementValue);
			break;

		/* increment hours */
		case HOUR:
			incrementHours(incrementValue);
			break;

		/* increment hours*/
		case DAY:
			incrementDays(incrementValue);
			break;

		default:
			break;

	}

}

/* increment minutes of timestamp */
void TIMESTAMP::incrementMinutes(unsigned int value) { 

	unsigned int days = 0;
	unsigned int hours = 0;
	unsigned int minutes = 0;

	/* minutes greater than 1 hour */
	if( value > 60 ) {
		hours = value % 60;
		minutes = value - (hours * 60);

		/* hours greater than 1 day */
		if( hours > 24 ) {
			days = hours % 24;
			hours = hours - (days * 24);
		}

	/* minutes less than 1 hour */
	} else {
		minutes = value;
	}

}

/* increment hours of timestamp */
void TIMESTAMP::incrementHours(unsigned int value) {


}

/* increment days of timestamp */
void TIMESTAMP::incrementDays(unsigned int value) {


}

/* pass back time parameters */
void TIMESTAMP::getTime(WORD & day, WORD & hour, WORD & min) const { 

	/* set outputs to internal timestamp parameters */
	day = myTime.wDay;
	hour = myTime.wHour;
	min = myTime.wMinute;

}
