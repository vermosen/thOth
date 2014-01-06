#pragma once

#include <vector>

#include "thOth/pattern/observer.h"
#include "thOth/pattern/observable.h"
#include "thOth/strategy.h"
#include "thOth/trade.h"

namespace thOth {

	// portfolio of trades, gather different 
	// trades. Could be turned into Lazyobject ?
	// should portfolio contains trades or strategies ?
	// could observe strategies and contain the trades...
	class portfolio : public observer,
					  public observable {
	
		public:
			portfolio();
			~portfolio();

			void update();											// observable implementation

			void push_back(const boost::shared_ptr<strategy>&);
			std::vector<trade> trades();							// maybe better to get an iterator on trades ??

		protected:

			std::vector<boost::shared_ptr<strategy> > strategies_;
	
	};

}
