#pragma once

#include "thOth/types.h"
#include "thOth/time/DateTime.h"

namespace thOth {

	class dateTime;

	class trade {							// base class for trade

	public:
		trade();							// constructor
		trade(const trade &);				// copy constructor
		~trade();							// destructor
		trade & operator =(const trade &);	// assignement operator

		dateTime tradeDate_;
		Size     quantity_;
		double   price_;


	};

}
