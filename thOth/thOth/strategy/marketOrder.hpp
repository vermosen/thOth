#pragma once

#include "thOth/strategy.h"

namespace thOth {

	// Hit the market and get executed 
	// at the current market level
	class marketOrder : public strategy {

	public:

		marketOrder();									// default constructor
		marketOrder(const marketOrder &);				// copy constructor
		marketOrder(const dateTime & dt);				// value constructor
		~marketOrder();									// destructor
		marketOrder & operator=(const marketOrder &);	// assignement operator

		virtual dateTime date() const;					// returns the implementation date

	protected:

	};

}
