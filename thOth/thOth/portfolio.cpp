
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

	std::vector<boost::shared_ptr<trade> > portfolio::trades() {
	
		std::vector<boost::shared_ptr<trade> > ret;

		for (std::vector<boost::shared_ptr<strategy> >::const_iterator It = strategies_.cbegin();
			It != strategies_.cend(); It++) {
		
			std::vector<boost::shared_ptr<trade> > temp = It->get()->trades();

			for (std::vector<boost::shared_ptr<trade> >::const_iterator Jt = temp.cbegin();
				Jt != temp.cend(); Jt++)

				ret.push_back(*Jt);								// each trade in each strategies
		
		}

		return ret;
	
	}

}
