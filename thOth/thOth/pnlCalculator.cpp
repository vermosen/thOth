
#include <thOth/pnlCalculator.hpp>

namespace thOth{

	pnlCalculator::pnlCalculator() {}
	pnlCalculator::pnlCalculator(const std::shared_ptr<portfolio> & port){
	
		this->registerWith(port);
	
	}
	pnlCalculator::pnlCalculator(const pnlCalculator &){}

	pnlCalculator::~pnlCalculator() {
	
		this->unregisterWithAll();
	
	}
	
	pnlCalculator & pnlCalculator::operator = (const pnlCalculator & pnl){

		if (&pnl != this) {
		
			// copy members
		
		}

		return *this;

	}

}
