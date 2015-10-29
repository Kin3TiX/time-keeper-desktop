/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* timestamp interface ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#pragma once
#include "tkd-pc.h"

/* timestamp class definition */
class TIMESTAMP {

	/* public members */
public:

	/* public data */
	unsigned char day;
	unsigned char hour;
	unsigned char minute;
	SYSTEMTIME myTime;

	/* mode enumeration */
	enum mode {
		MIN, HOUR, DAY
	};

	/* constructor, destructor */
	TIMESTAMP(SYSTEMTIME);
	~TIMESTAMP();

	/* increment time of timestamp */
	void incrementTime(mode, unsigned int);

	/* private members */
private:

	/* functions to increment timestamp */
	void incrementMinutes(unsigned int);
	void incrementHours(unsigned int);
	void incrementDays(unsigned int);

};

