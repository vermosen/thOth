#include "stdafx.h"
#include "conversions/DateTime/DateTime.h"

namespace thOth{

	dateTime dateTimeConversion(const TIMESTAMP_STRUCT& dt) {
	
		dateTime temp(
			dt.year,
			dt.month,
			dt.day,
			dateTime::Hours(dt.hour)
			+ dateTime::Minutes(dt.minute)
			+ dateTime::Seconds(dt.second)

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
			+ boost::posix_time::nanosec(dt.fraction));
#else
			+ boost::posix_time::microsec(dt.fraction / 1000));
#endif
	
		return temp;

	}

	dateTime dateTimeConversion(const LPSYSTEMTIME & dt) {
	
		dateTime temp(
			dt->wYear,
			dt->wMonth,
			dt->wDay,
			dateTime::Hours(dt->wHour)
			+ dateTime::Minutes(dt->wMinute)
			+ dateTime::Seconds(dt->wSecond)
			+ dateTime::MilliSeconds(dt->wMilliseconds));

		return temp;
	
	}

}
