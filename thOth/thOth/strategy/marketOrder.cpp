#include <thOth/strategy/marketOrder.hpp>

namespace thOth {

	marketOrder::marketOrder() : strategy(dateTime::currentTime()) {}
	marketOrder::marketOrder(const dateTime & implDate,
							 const volume & vol,
							 const marketSide & side) : strategy(implDate) {}
	marketOrder::~marketOrder() {}
	marketOrder & marketOrder::operator = (const marketOrder & tr) {
	
		if (&tr != this) {
		
			// copy elements
		
		}

		return *this;
	
	}

	dateTime marketOrder::date() const {
	
		return implDate_;
	
	}

}