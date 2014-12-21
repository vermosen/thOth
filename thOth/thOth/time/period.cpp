#include <thOth/time/period.hpp>

namespace thOth {

	period::period(const period & o) {

		// copy data
		unit_ = o.unit_;
		n_    = o.n_   ;
		
	}

	period::period(
		timeUnit u,
		size a)
		: unit_(u), n_(a) {};

	period::~period() {}

	period & period::operator =(const period & o) {

		if (&o != this) {

			unit_ = o.unit_;
			n_    = o.n_   ;

		}

		return *this;

	}
}
