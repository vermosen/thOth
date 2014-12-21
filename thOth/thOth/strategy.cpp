#include <thOth/strategy.hpp>

namespace thOth {

	strategy::strategy() {}
	strategy::strategy(const strategy & tr) {
	
		implDate_ = tr.implDate_;
	
	}
	strategy::strategy(const dateTime & implDate)
		: implDate_(implDate) {}
	strategy::~strategy() {}

	dateTime strategy::date() const {
	
		return implDate_;
	
	}

	strategy & strategy::operator = (const strategy & tr) {
	
		if (&tr != this) {
		
			implDate_ = tr.implDate_;

		}
	
		return * this;
	}

	std::vector<boost::shared_ptr<trade> > strategy::trades() const {
		
		return trades_; 
	
	}

	void strategy::calculate() {

		// could need to do other stuff here...
		lazyObject::calculate();

	}



}
