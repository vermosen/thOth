#ifndef thoth_trade_hpp
#define thoth_trade_hpp

#include <thOth/types.hpp>
#include <thOth/time/dateTime.hpp>

namespace thOth {

	class trade {							// base class for trade

	public:

		trade ()					;		// constructor
		trade (const trade &)		;		// copy constructor
		trade (volume qt, real px)	;		// additional constructor
		~trade() {}					;		// destructor

		trade & operator =(const trade &);	// assignement operator

		// accessors
		volume quantity	() { return quantity_	; };
		real price		() { return price_		; };

		void quantity (volume s) { quantity_ = s; };
		void price    (real	  s) { price_    = s; };

	protected:

		volume	quantity_ = 0	;
		real	price_	  = -1.0	;

	};

}

#endif
