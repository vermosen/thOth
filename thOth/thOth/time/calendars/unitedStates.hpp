#ifndef united_states_hpp
#define united_states_hpp

#include <string>
#include <memory>

#include "thOth/time/dateTime.hpp"
#include "thOth/time/calendar.hpp"

namespace thOth {

	class unitedStates : public calendar {

	public:

		//! US calendars
		enum market : short {

			settlement = 0,
			nyse = 1,
			governmentBond = 2

		};

		unitedStates(market market = settlement);				// ctor

	private:

		class settlementImpl : public calendar::westernImpl {
		public:
			std::string name() const { return "US settlement"; }
			bool isBusinessDay(const dateTime &) const;
		};
		class nyseImpl : public calendar::westernImpl {
		public:
			std::string name() const { return "New York stock exchange"; }
			bool isBusinessDay(const dateTime &) const;
		};
		class governmentBondImpl : public calendar::westernImpl {
		public:
			std::string name() const { return "US government bond market"; }
			bool isBusinessDay(const dateTime &) const;
		};
	};
}

#endif
