#ifndef thoth_period_hpp
#define thoth_period_hpp

#include <boost/date_time/posix_time/posix_time_duration.hpp>

#include "thoth/types.hpp"

namespace thOth {

	// period class
	class period {

	public:

		period() = delete;							// no default ctor
		period(const period &);						// copy ctor
		period(timeUnit, size);						// ctor
		~period();									// destructor

		period & operator=(const period &);			// assignement operator
	
		timeUnit unit () const { return unit_; };
		size   amount () const { return n_   ; };

	private:

		timeUnit unit_;
		size     n_   ;

	};
}

#endif