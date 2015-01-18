#include <thOth/trade.hpp>

namespace thOth{

	trade::trade() {}							// ctor
	trade::trade(const trade & o)				// copy ctor
		: quantity_(o.quantity_), price_(o.price_) {}
	
	trade::trade(volume qt, real px)			// additional ctor
		: quantity_(qt), price_(px) {}

	trade & trade::operator = (const trade & o) {// assignement operator
	
		if (&o != this) {
		
			quantity_	= o.quantity_	;
			price_		= o.price_		;
		
		}

		return *this;

	}
}