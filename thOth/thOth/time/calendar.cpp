#include "thOth/time/calendar.hpp"

namespace thOth {

	dateTime calendar::adjust(const dateTime& d,
		businessDayConvention c) const {
		//QL_REQUIRE(d != Date(), "null date");
		if (c == unadjusted)
			return d;

		dateTime d1 = d;
		if (c == following || c == modifiedFollowing) {
			
			while (!isBusinessDay(d1))
				d1 + boost::gregorian::days(1);

			if (c == modifiedFollowing) {
				if (d1.month() != d.month())
					return adjust(d, preceding);

			}
		} else if (c == preceding || c == modifiedPreceding) {

			while (!isBusinessDay(d1)) 
				d1 - boost::gregorian::days(1);

			if (c == modifiedPreceding && d1.month() != d.month())
				return adjust(d, following);

		} else {
			//QL_FAIL("unknown business-day convention");
		}
		
		return d1;

	}
}