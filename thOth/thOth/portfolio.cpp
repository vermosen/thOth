
#include <thOth/portfolio.hpp>

namespace thOth {

	portfolio::portfolio() {}
	portfolio::~portfolio() {}

	void portfolio::update() {									// observable implementation
	
		notifyObservers();

	}

	void portfolio::push_back(const boost::shared_ptr<strategy>& t) {
	
		this->registerWith(t);

		strategies_.push_back(t);
	
	}

	std::vector<trade> portfolio::trades() {
	
		std::vector<trade> trades;

		for (std::vector<boost::shared_ptr<strategy> >::const_iterator It = strategies_.cbegin();
			It != strategies_.cend(); It++) {
		
			//trades.push_back(); // each trade in each strategies
		
		}

		return trades;
	
	}

}
