#include <thOth/time/dateTime.hpp>

//#define BOOST_DATE_TIME_HAS_NANOSECONDS

namespace thOth {

	dateTime::dateTime() : ptime() {}													// default ctors

	dateTime::dateTime(const dateTime & dt) : ptime(dt) {}								// copy ctor

	dateTime::dateTime(																	// ctor
		Years y, Months m, Days d, 
		boost::posix_time::time_duration td)		
		: ptime(boost::gregorian::date(y, m, d), td) {}

	dateTime::dateTime(
		const boost::posix_time::ptime & pt) : ptime(pt) {}

	dateTime::dateTime(
		Years y, Months m, Days d,														// detailed Constructor
		Hours H, Minutes M, Seconds S,
		MilliSeconds MS,

#ifndef BOOST_DATE_TIME_HAS_NANOSECONDS

		MicroSeconds MU)

		: ptime(boost::gregorian::date(y, m, d), H + M + S + MS + MU) {};

#else

		MicroSeconds MU, NanoSeconds N)

		: ptime(boost::gregorian::date(y, m, d), H + M + S + MS + MU + N) {};

#endif

	dateTime::~dateTime(){}

	dateTime & dateTime::operator = (const dateTime &dt){

		if (&dt != this) {																// prevent self replication

			// copy elements 

		}

		return *this;

	}

	dateTime::Years dateTime::year() const {											// interfaces
	
		return ptime::date().year();
	
	}

	dateTime::Months dateTime::month() const {
	
		return ptime::date().month();

	}

	dateTime::Days dateTime::day() const {
	
		return ptime::date().day();

	}

	dateTime::Hours dateTime::hour() const {
	
		return dateTime::Hours(ptime::time_of_day().hours());
	
	}

	dateTime::Minutes dateTime::minute() const {
	
		return dateTime::Minutes(ptime::time_of_day().minutes());
	
	}

	dateTime::Seconds dateTime::second() const {
	
		return dateTime::Seconds(ptime::time_of_day().seconds());
	
	}

	dateTime::MilliSeconds dateTime::millisecond() const {
	
		return dateTime::MilliSeconds(ptime::time_of_day().ticks());
	
	}

	dateTime::MicroSeconds dateTime::microsecond() const {

		return dateTime::MicroSeconds(ptime::time_of_day().ticks());

	}

	void dateTime::year(const dateTime::Years& yr) {										// TODO set methods
	
		// set year
	
	}

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
	dateTime::MicroSeconds dateTime::nanoseconds() const {

		return dateTime::NanoSeconds(ptime::time_of_day().ticks());

	}
#endif

	dateTime dateTime::currentTime() {
	
		return dateTime(boost::posix_time::microsec_clock::local_time());
	
	}

}