#ifndef thoth_market_order_hpp
#define thoth_market_order_hpp

#include <thOth/strategy.hpp>

namespace thOth {

	// Hit the market and get executed 
	// at the current market level
	class marketOrder : public strategy {

	public:

		marketOrder();									// default constructor
		marketOrder(const marketOrder &);				// copy constructor

		marketOrder(const dateTime &,					// value constructor
					const volume &,
					const marketSide &);

		~marketOrder();									// destructor
		marketOrder & operator=(const marketOrder &);	// assignement operator

		virtual dateTime date() const;					// returns the implementation date


		// lazyObject Interface
		void performCalculations();

	protected:

	};

}

#endif