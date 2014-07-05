#ifndef thoth_strategy_hpp
#define thoth_strategy_hpp

#include <thOth/pattern/lazyObject.hpp>
#include <thOth/trade.hpp>

namespace thOth {

	// the strategy class is abstract

	// it takes the initial implementation date/time
	// as an argument

	// strategies generates trade list

	// strategies are lazyObjects
	class strategy : public lazyObject {

		public:

			strategy(const dateTime &);				// value constructor
			strategy(const strategy &);				// copy constructor
			virtual ~strategy();					// virtual destructor
			strategy & operator=(const strategy &);	// assignement operator

			virtual dateTime date() const = 0;		// returns the implementation date

			std::vector<std::shared_ptr<trade> > trades() const;
													// returns the list of trades
			
			void calculate();						// lazyObject implementation

			// this method must be overriden 
			// to perform the right calculation
			virtual void performCalculations() = 0;

		protected:

			strategy();								// default constructor is private
			
			dateTime implDate_;
			std::vector<std::shared_ptr<trade> > trades_;

	};

}

#endif