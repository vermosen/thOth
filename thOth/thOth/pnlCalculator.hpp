#ifndef thoth_pnl_calculator_hpp
#define thoth_pnl_calculator_hpp

#include <vector>
#include <thOth/portfolio.h>
#include <thOth/time/TimeSeries.hpp>

namespace thOth {

	// P&L calculator observes a portfolio and 
	// restitute it's current P&L.
	// Check bottlenecks to see if it should be 
	// turned into lazyobject

	// should also include a daily cash balance 
	class pnlCalculator : public observer {

	public:
		pnlCalculator(const boost::shared_ptr<portfolio> &);	// base constructor
		pnlCalculator(const pnlCalculator &);					// copy constructor
		~pnlCalculator();										// destructor

		pnlCalculator & operator=(const pnlCalculator &);

	protected:

		pnlCalculator();

		// how should we implement ?
		// current MV is fictious,
		// net P&L should include transaction costs, etc...
		// TimeSeries<double>balance_ ??

	};

}

#endif