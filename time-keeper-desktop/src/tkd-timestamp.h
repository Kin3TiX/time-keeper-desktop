/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* timestamp interface ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
#pragma once

/* timestamp class definition */
class TIMESTAMP {

	/* public members */
public:

	/* mode enumeration */
	enum mode {
		SEC, MIN, HOUR, DAY
	};

	/* constructor, destructor */
	TIMESTAMP();
	~TIMESTAMP();

	/* operator overloads */
	void operator=(const TIMESTAMP & other);
	bool operator==(const TIMESTAMP & other);

	/* increment time of timestamp */
	void incrementTime(mode, unsigned int);
	void setCurrentTime();

	/* private members */
private:

	/* internal timestamp */
	SYSTEMTIME myTime;

	/* functions to increment timestamp */
	void incrementSeconds(unsigned int);
	void incrementMinutes(unsigned int);
	void incrementHours(unsigned int);
	void incrementDays(unsigned int);
	void setDay(unsigned int);
	void setHour(unsigned int);
	void setMinute(unsigned int);
	void setSecond(unsigned int);

	/* get time info */
	void getTime(WORD &, WORD &, WORD &) const;

};

