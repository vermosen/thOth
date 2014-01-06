#pragma once

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

namespace thOth {

	class dateTime : public boost::posix_time::ptime {

	public:

		typedef boost::gregorian::gregorian_calendar::year_type Years;
		typedef boost::gregorian::gregorian_calendar::month_type Months;
		typedef boost::gregorian::gregorian_calendar::day_type Days;

		typedef boost::posix_time::hours Hours;
		typedef boost::posix_time::minutes Minutes;
		typedef boost::posix_time::seconds Seconds;
		typedef boost::posix_time::milliseconds MilliSeconds;
		typedef boost::posix_time::microseconds MicroSeconds;

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
		typedef boost::posix_time::nanoseconds NanoSeconds;
#endif

		typedef boost::posix_time::time_duration t_duration;

		dateTime();																	// base class features
		dateTime(const dateTime &);
		dateTime(const boost::posix_time::ptime &);

		dateTime(Years, Months, Days,												// additional ctor
			boost::posix_time::time_duration

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
			= NanoSeconds(0));
#else
			= MicroSeconds(0));
#endif

		virtual ~dateTime();														// destructor

		dateTime & operator = (const dateTime &);									// = operator

		Years year() const;															// interfaces
		Months month() const;
		Days day() const;
		Hours hour() const;
		Minutes minute() const;
		Seconds second() const;
		MilliSeconds millisecond() const;
		MicroSeconds microsecond() const;

		void year(const Years&);

		static dateTime currentTime();												// get current time

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
		NanoSeconds nanoseconds() const;
#endif

	};

}

