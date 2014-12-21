#ifndef thoth_data_time_hpp
#define thoth_data_time_hpp

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "thOth/time/period.hpp"

namespace thOth {

	// TODO: overload the >> operator for datetime
	// TODO: create an external period class which 
	// convert properly into time duration and date increments
	class dateTime : public boost::posix_time::ptime {

	public:

		typedef boost::gregorian::gregorian_calendar::year_type  years ;			// elements from gregorian calendar
		typedef boost::gregorian::gregorian_calendar::month_type months;
		typedef boost::gregorian::gregorian_calendar::day_type   days  ;

		typedef boost::posix_time::hours        hours       ;						// elements from posix_time
		typedef boost::posix_time::minutes      minutes     ;
		typedef boost::posix_time::seconds      seconds     ;
		typedef boost::posix_time::milliseconds milliSeconds;
		typedef boost::posix_time::microseconds microSeconds;

		#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
		typedef boost::posix_time::nanoseconds nanoSeconds  ;
		#endif

		typedef boost::posix_time::time_duration time_duration;						// time duration

		dateTime();																	// base class features

		dateTime(const ptime & pt) : ptime(pt) {};									// build from ptime

		dateTime(years, months, days,												// additional Constructor
			time_duration

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
			= nanoSeconds(0));
#else
			= microSeconds(0));
#endif

		dateTime(years, months , days   , 
				 hours, minutes, seconds, 
				 milliSeconds = milliSeconds(0),									// additional Constructor
				 microSeconds = microSeconds(0)
#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
				 , nanoSeconds = naoseconds(0)
#endif
				 );

		dateTime & operator=(const dateTime &);
		
		virtual ~dateTime();														// destructor

		years        year        () const;											// accessors
		months       month       () const;
		days         day         () const;
		hours        hour        () const;
		minutes      minute      () const;
		seconds      second      () const;
		milliSeconds millisecond () const;
		microSeconds microsecond () const;

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
		NanoSeconds nanoseconds() const;
#endif

		// excel format conversion
		inline double ExcelDate() const {
			return (double)time_.time_count() / 86400000000.0 - 2415019.0; 
		};

		// sql string conversion, optional microsec display
		std::string convertSqlDateTime(bool microsec = false) const;

		// static functions
		static dateTime strToDate(const std::string &, std::stringstream &);		// convert fix str to date
		static dateTime advance(const thOth::dateTime &, const thOth::period &);	// advance for a given period
		static dateTime currentTime();												// get current time
		static dateTime convertSqlDateTime(const std::string &);					// convert a SQL string into dateTime
		
		// todo: make somthing clean...
		static dateTime adjust100ms(const thOth::dateTime &);
	};
}

#endif