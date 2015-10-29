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
void TIMESTAMP::incrementMinutes(unsigned int) { 


}

/* increment hours of timestamp */
void TIMESTAMP::incrementHours(unsigned int) { 


}

/* increment days of timestamp */
void TIMESTAMP::incrementDays(unsigned int) { 


}
