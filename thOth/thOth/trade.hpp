#ifndef thoth_trade_hpp
#define thoth_trade_hpp

#include <thOth/types.hpp>
#include <thOth/time/DateTime.h>

namespace thOth {

	class dateTime;

	class trade {							// base class for trade

	public:
		trade();							// constructor
		trade(const trade &);				// copy constructor
		~trade();							// destructor
		trade & operator =(const trade &);	// assignement operator

		dateTime tradeDate_;
		volume   quantity_;
		double   price_;


	};

}

#endif