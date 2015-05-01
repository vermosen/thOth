#include <thOth/time/dateTime.hpp>

namespace thOth {

	dateTime::dateTime() : ptime() {}												// default ctors	

	dateTime::dateTime(																// ctor
		years y, months m, days d, 
		boost::posix_time::time_duration td)		
		: ptime(boost::gregorian::date(y, m, d), td) {}

	dateTime::dateTime(
		years y, months m, days d,													// detailed Constructor
		hours H, minutes M, seconds S,
		milliSeconds MS,

#ifndef BOOST_DATE_TIME_HAS_NANOSECONDS

		microSeconds MU)

		: ptime(boost::gregorian::date(y, m, d), H + M + S + MS + MU) {};

#else

		microSeconds MU, nanoSeconds N)

		: ptime(boost::gregorian::date(y, m, d), H + M + S + MS + MU + N) {};

#endif

	dateTime & dateTime::operator = (const dateTime & o) {
	
		if (&o != this) {
		
			// base class assignement operator
			ptime::operator=(o);
		
		}

		return *this;
	
	}

	dateTime::~dateTime(){}

	inline dateTime::years dateTime::year() const {									// interfaces
	
		return ptime::date().year();
	
	}

	dateTime::months dateTime::month() const {
	
		return ptime::date().month();

	}

	dateTime::days dateTime::day() const {
	
		return ptime::date().day();

	}

	dateTime::hours dateTime::hour() const {
	
		return dateTime::hours(ptime::time_of_day().hours());
	
	}

	dateTime::minutes dateTime::minute() const {
	
		return dateTime::minutes(ptime::time_of_day().minutes());
	
	}

	dateTime::seconds dateTime::second() const {
	
		return dateTime::seconds(ptime::time_of_day().seconds());
	
	}

	dateTime::milliSeconds dateTime::millisecond() const {
	
		return dateTime::milliSeconds((int)(ptime::time_of_day().ticks() / 1000));
	
	}

	dateTime::microSeconds dateTime::microsecond() const {

		return dateTime::microSeconds(ptime::time_of_day().ticks());

	}

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
	dateTime::nanoseconds dateTime::nanoseconds() const {

		return dateTime::nanoSeconds(ptime::time_of_day().ticks());

	}
#endif

	dateTime dateTime::currentTime() {
	
		return dateTime(boost::posix_time::microsec_clock::local_time());
	
	}

	// TODO: move into calendar class to manage calendar rules
	dateTime dateTime::advance(const thOth::dateTime & d, const thOth::period & p) {
	
		timeUnit u = p.unit();
		dateTime ret;

		switch (u){

		case timeUnit::year:
			ret = d + boost::gregorian::years(p.amount());
			break;

		case timeUnit::month:
			ret = d + boost::gregorian::months(p.amount());
			break;

		case timeUnit::week:
			ret = d + boost::gregorian::weeks(p.amount());
			break;

		case timeUnit::day:
			ret = d + boost::gregorian::days(p.amount());
			break;

		case timeUnit::hour:
			ret = d + time_duration(boost::posix_time::hours(p.amount()));
			break;

		case timeUnit::minute:
			ret = d + time_duration(boost::posix_time::minutes(p.amount()));
			break;

		case timeUnit::second:
			ret = d + time_duration(boost::posix_time::seconds(p.amount()));
			break;

		case timeUnit::milliSecond:
			ret = d + time_duration(boost::posix_time::milliseconds(p.amount()));
			break;

		case timeUnit::microSecond:
			ret = d + time_duration(boost::posix_time::milliseconds(p.amount()));
			break;

#ifdef BOOST_DATE_TIME_HAS_NANOSECONDS
		case timeUnit::nanoSecond:
			ret = d + time_duration(boost::posix_time::nanoseconds(p.amount()));
			break;
#endif

		case timeUnit::nanoSecond:
			ret = d + time_duration(boost::posix_time::milliseconds(p.amount()));
			break;
		
		}

		return ret;

	}

	dateTime dateTime::strToDate(													// convert string into date
		const std::string & fixStr,
		std::stringstream & ss) {

		dateTime ret;
		
		ss.clear();
		ss.str(fixStr); ss >> ret;
		ss.clear();

		return ret;

	}

	thOth::dateTime dateTime::convertSqlDateTime(const std::string & dtStr) {

		return thOth::dateTime(
			thOth::dateTime::years(boost::lexical_cast<int>(dtStr.substr(0, 4))),
			thOth::dateTime::months(boost::lexical_cast<int>(dtStr.substr(5, 2))),
			thOth::dateTime::days(boost::lexical_cast<int>(dtStr.substr(8, 2))),
			thOth::dateTime::hours(boost::lexical_cast<int>(dtStr.substr(11, 2))),
			thOth::dateTime::minutes(boost::lexical_cast<int>(dtStr.substr(14, 2))),
			thOth::dateTime::seconds(boost::lexical_cast<int>(dtStr.substr(17, 2))),
			thOth::dateTime::milliSeconds(boost::lexical_cast<int>(dtStr.substr(20, 3))),
			thOth::dateTime::microSeconds(boost::lexical_cast<int>(dtStr.substr(23, 3))));
		// TODO: add microsec management

	}

	// sql string conversion
	std::string dateTime::convertSqlDateTime(bool microsec) const {

		std::string temp = boost::posix_time::to_iso_string(*this);

		std::string sql(""); sql
			.append(temp.substr(0, 8))
			.append(temp.substr(9, 
				(microsec ? 13 : 6)));

		return sql;

	}

	// adjust to the closest mulitple increment
	dateTime dateTime::adjust100ms(const thOth::dateTime & d) {
	
#ifdef _WIN32
		__int64 tt = d.time_of_day().ticks();
#else
		int64_t tt = d.time_of_day().ticks();
#endif
		return thOth::dateTime(d.year(), d.month(), d.day(), boost::posix_time::milliseconds((tt - tt % 100000) / 1000));

	};

}
