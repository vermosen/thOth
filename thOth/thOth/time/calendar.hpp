#ifndef calendar_hpp
#define calendar_hpp

#include <set>

#include "thOth/types.hpp"
#include "thOth/time/dateTime.hpp"

namespace thOth {

	// a base calendar class, use bridge pattern
	class calendar {

	protected:

		class impl {

		public:
			virtual ~impl() {}
			virtual std::string name() const = 0;
			virtual bool isBusinessDay(const dateTime &) const = 0;
			virtual bool isWeekend(weekday) const = 0;
			std::set<dateTime> addedHolidays, removedHolidays;

		};

		boost::shared_ptr<impl> impl_;

	public:

		calendar() {};									// return null implementation by default

		bool empty() const;								// indicates wether the calendar is null or not

		std::string name() const;						// retrieve calendar name

		bool isBusinessDay(const dateTime & d) const;	// return true if the given dateTime falls on a business day

		dateTime adjust(const dateTime &,				// date adjustement
			businessDayConvention convention = following) const;

	protected:

		// partial implementation
		class westernImpl : public impl {

		public:

			bool isWeekend(weekday) const;
			static dateTime easterMonday(dateTime::years);

		};
	};

	// inline definitions
	inline bool calendar::empty() const {
		return !impl_;
	}

	inline std::string calendar::name() const {
		return impl_->name();
	}

	inline bool calendar::isBusinessDay(const dateTime & d) const {
		if (impl_->addedHolidays.find(d) != impl_->addedHolidays.end())
			return false;
		if (impl_->removedHolidays.find(d) != impl_->removedHolidays.end())
			return true;
		return impl_->isBusinessDay(d);
	}
}

#endif
