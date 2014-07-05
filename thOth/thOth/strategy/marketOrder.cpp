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

	void marketOrder::performCalculations() {
	
		// iterates on the TS starting at implementation date
		// TODO : check for bounds
		for (thOth::timeSeries<thOth::quote>::const_iterator It = ts_->cbegin();
			It != ts_->cend(); ++It) {
		
			// after implementation date
			if (It->first > this->implDate_) {
			
				int i = 0;
			
			}
		
		}

	}

}