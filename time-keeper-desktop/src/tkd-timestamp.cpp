/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* timestamp implementation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#include "tkd-pc.h"
#include "tkd-timestamp.h"

/* constructor */
TIMESTAMP::TIMESTAMP() { 

	/* set object time to be current */
	GetSystemTime(&myTime);

}

/* destructor */
TIMESTAMP::~TIMESTAMP() { }

/* assign one timestamp to another */
void TIMESTAMP::operator=(const TIMESTAMP & other) {

	/* holders for the other timestamp's info */
	WORD day;
	WORD hour;
	WORD minute;

	/* populate holders with the other guy's data */
	other.getTime(day, hour, minute);

	/* update my data to match */
	myTime.wDay = day;
	myTime.wHour = hour;
	myTime.wMinute = minute;

}

/* compare two timestampes for equality */
 bool TIMESTAMP::operator==(const TIMESTAMP & other) {

	/* holders for the other timestamp's info */
	WORD day;
	WORD hour;
	WORD minute;

	/* populate holders with the other guy's data */
	other.getTime(day, hour, minute);

	/* return match */
	return (myTime.wDay == day) && (myTime.wHour == hour) && (myTime.wMinute == minute);

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

/* update internal time to current */
void TIMESTAMP::setCurrentTime() {

	/* set to current time */
	GetSystemTime(&myTime);

}

void TIMESTAMP::incrementSeconds(unsigned int value) { 

	/* holders for rollover values*/
	unsigned int days = 0;
	unsigned int hours = 0;
	unsigned int minutes = 0;
	unsigned int seconds = 0;

	/* minutes greater than 1 hour */
	if( minutes > 60 ) {
		hours = minutes % 60;
		minutes = minutes - (hours * 60);

		/* hours greater than 1 day */
		if( hours > 24 ) {
			days = hours % 24;
			hours = hours - (days * 24);
		}

		/* minutes less than 1 hour */
	} else {
		seconds = value;
	}

	/* set the calculated values */
	setDay(days);
	setHour(hours);
	setMinute(minutes);
	setSecond(seconds);

}

/* increment minutes of timestamp */
void TIMESTAMP::incrementMinutes(unsigned int value) { 

	/* holders for rollover values*/
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

	/* set the calculated values */
	setDay(days);
	setHour(hours);
	setMinute(minutes);

}

/* increment hours of timestamp */
void TIMESTAMP::incrementHours(unsigned int value) {

	/* holders for rollover values*/
	unsigned int days = 0;
	unsigned int hours = 0;

	/* hours greater than 1 day */
	if( hours > 24 ) {
		days = hours % 24;
		hours = hours - (days * 24);
	}

	/* set the calculated values */
	setDay(days);
	setHour(hours);

}

/* increment days of timestamp */
void TIMESTAMP::incrementDays(unsigned int value) {

	/* holders for rollover values*/
	unsigned int days = 0;

	/* set the calculated values */
	setDay(days);


}

/* set day */
void TIMESTAMP::setDay(unsigned int increment) {

	/* if increment is zero, do nothing */
	if( increment ) {

		/* check rollover & increment */
		if( (myTime.wDay + increment) <= 31 ) {

			/* add to the current */
			myTime.wDay += increment;

		/* rollover case*/
		}  else {

			/* calc difference and roll it over */
			myTime.wDay = (myTime.wDay + increment) - 31;
		
		}

	}

}

/* set hour */
void TIMESTAMP::setHour(unsigned int increment) {

	/* if increment is zero, do nothing */
	if( increment ) {

		/* check rollover & increment */
		if( (myTime.wHour + increment) <= 23 ) {

			/* add to the current */
			myTime.wHour += increment;

		/* rollover case */
		} else {

			/* calc differnce and rollover */
			myTime.wHour = (myTime.wHour + increment) - 24;
		
		}

	}

}

/* set minute */
void TIMESTAMP::setMinute(unsigned int increment) {

	/* if increment is zero, do nothing */
	if( increment ) {

		/* check rollover & increment */
		if( (myTime.wMinute + increment) <= 59 ) {

			/* add to the current */
			myTime.wMinute += increment;

			/* rollover case */
		} else {

			/* calc differnce and rollover */
			myTime.wMinute = (myTime.wMinute + increment) - 60;

		}

	}

}

void TIMESTAMP::setSecond(unsigned int) { }

/* pass back time parameters */
void TIMESTAMP::getTime(WORD & day, WORD & hour, WORD & min) const { 

	/* set outputs to internal timestamp parameters */
	day = myTime.wDay;
	hour = myTime.wHour;
	min = myTime.wMinute;

}
