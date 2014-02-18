#ifndef thoth_portfolio_hpp
#define thoth_portfolio_hpp

#include <vector>

#include <thOth/pattern/observer.hpp>
#include <thOth/pattern/observable.hpp>
#include <thOth/strategy.hpp>
#include <thOth/trade.hpp>

namespace thOth {

	// portfolio of trades, gather different 
	// trades. Should be turned into Lazyobject ?
	// should portfolio contains trades or strategies ?
	// could observe strategies and contain the trades...
	class portfolio : public observer,
					  public observable {
	
		public:
			portfolio();
			~portfolio();

			void update();											// observable implementation

			void push_back(const boost::shared_ptr<strategy>&);

			std::vector<boost::shared_ptr<trade> > trades();		// TODO : provide iterator on trades

		protected:

			std::vector<boost::shared_ptr<strategy> > strategies_;
	
	};

}

#endif