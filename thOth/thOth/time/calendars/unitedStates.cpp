#include "thOth/time/calendars/unitedStates.hpp"

namespace thOth {

	unitedStates::unitedStates(unitedStates::market market) {
		// all calendar instances on the same market share the same
		// implementation instance
		static std::shared_ptr<calendar::impl> settlementImpl(
			new unitedStates::settlementImpl);
		static std::shared_ptr<calendar::impl> nyseImpl(
			new unitedStates::nyseImpl);
		static std::shared_ptr<calendar::impl> governmentImpl(
			new unitedStates::governmentBondImpl);
		switch (market) {
		case settlement:
			impl_ = settlementImpl;
			break;
		case nyse:
			impl_ = nyseImpl;
			break;
		case governmentBond:
			impl_ = governmentImpl;
			break;
		default:
			//QL_FAIL("unknown market");
		}
	}


	bool unitedStates::settlementImpl::isBusinessDay(const dateTime& date) const {
		
		//Weekday w = date.weekday();
		dateTime::Days   d = date.day  ();
		dateTime::Months m = date.month();
		
		if (isWeekend(w)
			// New Year's Day (possibly moved to Monday if on Sunday)
			|| ((d == 1 || (d == 2 && w == Monday)) && m == January)
			// (or to Friday if on Saturday)
			|| (d == 31 && w == Friday && m == December)
			// Martin Luther King's birthday (third Monday in January)
			|| ((d >= 15 && d <= 21) && w == Monday && m == January)
			// Washington's birthday (third Monday in February)
			|| ((d >= 15 && d <= 21) && w == Monday && m == February)
			// Memorial Day (last Monday in May)
			|| (d >= 25 && w == Monday && m == May)
			// Independence Day (Monday if Sunday or Friday if Saturday)
			|| ((d == 4 || (d == 5 && w == Monday) ||
			(d == 3 && w == Friday)) && m == July)
			// Labor Day (first Monday in September)
			|| (d <= 7 && w == Monday && m == September)
			// Columbus Day (second Monday in October)
			|| ((d >= 8 && d <= 14) && w == Monday && m == October)
			// Veteran's Day (Monday if Sunday or Friday if Saturday)
			|| ((d == 11 || (d == 12 && w == Monday) ||
			(d == 10 && w == Friday)) && m == November)
			// Thanksgiving Day (fourth Thursday in November)
			|| ((d >= 22 && d <= 28) && w == Thursday && m == November)
			// Christmas (Monday if Sunday or Friday if Saturday)
			|| ((d == 25 || (d == 26 && w == Monday) ||
			(d == 24 && w == Friday)) && m == December))
			return false;
		return true;
	}


	bool unitedStates::nyseImpl::isBusinessDay(const dateTime & date) const {
		Weekday w = date.weekday();
		Day d = date.dayOfMonth(), dd = date.dayOfYear();
		Month m = date.month();
		Year y = date.year();
		Day em = easterMonday(y);
		if (isWeekend(w)
			// New Year's Day (possibly moved to Monday if on Sunday)
			|| ((d == 1 || (d == 2 && w == Monday)) && m == January)
			// Washington's birthday (third Monday in February)
			|| ((d >= 15 && d <= 21) && w == Monday && m == February)
			// Good Friday
			|| (dd == em - 3)
			// Memorial Day (last Monday in May)
			|| (d >= 25 && w == Monday && m == May)
			// Independence Day (Monday if Sunday or Friday if Saturday)
			|| ((d == 4 || (d == 5 && w == Monday) ||
			(d == 3 && w == Friday)) && m == July)
			// Labor Day (first Monday in September)
			|| (d <= 7 && w == Monday && m == September)
			// Thanksgiving Day (fourth Thursday in November)
			|| ((d >= 22 && d <= 28) && w == Thursday && m == November)
			// Christmas (Monday if Sunday or Friday if Saturday)
			|| ((d == 25 || (d == 26 && w == Monday) ||
			(d == 24 && w == Friday)) && m == December)
			) return false;

		if (y >= 1998) {
			if (// Martin Luther King's birthday (third Monday in January)
				((d >= 15 && d <= 21) && w == Monday && m == January)
				// President Reagan's funeral
				|| (y == 2004 && m == June && d == 11)
				// September 11, 2001
				|| (y == 2001 && m == September && (11 <= d && d <= 14))
				// President Ford's funeral
				|| (y == 2007 && m == January && d == 2)
				) return false;
		}
		else if (y <= 1980) {
			if (// Presidential election days
				((y % 4 == 0) && m == November && d <= 7 && w == Tuesday)
				// 1977 Blackout
				|| (y == 1977 && m == July && d == 14)
				// Funeral of former President Lyndon B. Johnson.
				|| (y == 1973 && m == January && d == 25)
				// Funeral of former President Harry S. Truman
				|| (y == 1972 && m == December && d == 28)
				// National Day of Participation for the lunar exploration.
				|| (y == 1969 && m == July && d == 21)
				// Funeral of former President Eisenhower.
				|| (y == 1969 && m == March && d == 31)
				// Closed all day - heavy snow.
				|| (y == 1969 && m == February && d == 10)
				// Day after Independence Day.
				|| (y == 1968 && m == July && d == 5)
				// June 12-Dec. 31, 1968
				// Four day week (closed on Wednesdays) - Paperwork Crisis
				|| (y == 1968 && dd >= 163 && w == Wednesday)
				) return false;
		}
		else {
			if (// Nixon's funeral
				(y == 1994 && m == April && d == 27)
				) return false;
		}


		return true;
	}


	bool unitedStates::governmentBondImpl::isBusinessDay(const dateTime& date)
		const {
		Weekday w = date.weekday();
		Day d = date.dayOfMonth(), dd = date.dayOfYear();
		Month m = date.month();
		Year y = date.year();
		Day em = easterMonday(y);
		if (isWeekend(w)
			// New Year's Day (possibly moved to Monday if on Sunday)
			|| ((d == 1 || (d == 2 && w == Monday)) && m == January)
			// Martin Luther King's birthday (third Monday in January)
			|| ((d >= 15 && d <= 21) && w == Monday && m == January)
			// Washington's birthday (third Monday in February)
			|| ((d >= 15 && d <= 21) && w == Monday && m == February)
			// Good Friday
			|| (dd == em - 3)
			// Memorial Day (last Monday in May)
			|| (d >= 25 && w == Monday && m == May)
			// Independence Day (Monday if Sunday or Friday if Saturday)
			|| ((d == 4 || (d == 5 && w == Monday) ||
			(d == 3 && w == Friday)) && m == July)
			// Labor Day (first Monday in September)
			|| (d <= 7 && w == Monday && m == September)
			// Columbus Day (second Monday in October)
			|| ((d >= 8 && d <= 14) && w == Monday && m == October)
			// Veteran's Day (Monday if Sunday or Friday if Saturday)
			|| ((d == 11 || (d == 12 && w == Monday) ||
			(d == 10 && w == Friday)) && m == November)
			// Thanksgiving Day (fourth Thursday in November)
			|| ((d >= 22 && d <= 28) && w == Thursday && m == November)
			// Christmas (Monday if Sunday or Friday if Saturday)
			|| ((d == 25 || (d == 26 && w == Monday) ||
			(d == 24 && w == Friday)) && m == December))
			return false;
		return true;
	}

}