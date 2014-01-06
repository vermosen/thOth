
#include "thOth/strategy.h"

namespace thOth {

	strategy::strategy() {}
	strategy::strategy(const strategy & tr) {
	
		implDate_ = tr.implDate_;
	
	}
	strategy::strategy(const dateTime & implDate)
		: implDate_(implDate) {}
	strategy::~strategy() {}

	dateTime strategy::date() const {
	
		return implDate_;
	
	}

	strategy & strategy::operator = (const strategy & tr) {
	
		if (&tr != this) {
		
			implDate_ = tr.implDate_;

		}
	
		return * this;
	}

}
