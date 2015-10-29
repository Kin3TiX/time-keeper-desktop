/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* timestamp interface ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#pragma once
#include "tkd-pc.h"

/* timestamp class definition */
class TIMESTAMP {

	/* public members */
public:

	/* mode enumeration */
	enum mode {
		MIN, HOUR, DAY
	};

	/* constructor, destructor */
	TIMESTAMP(SYSTEMTIME);
	~TIMESTAMP();

	/* operator overloads */
	void operator=(const TIMESTAMP & other);
	bool operator==(const TIMESTAMP & other);

	/* increment time of timestamp */
	void incrementTime(mode, unsigned int);

	/* private members */
private:

	/* internal timestamp */
	SYSTEMTIME myTime;

	/* functions to increment timestamp */
	void incrementMinutes(unsigned int);
	void incrementHours(unsigned int);
	void incrementDays(unsigned int);

	/* get time info */
	void getTime(WORD &, WORD &, WORD &) const;

};

