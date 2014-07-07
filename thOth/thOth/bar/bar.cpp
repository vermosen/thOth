#include <thOth/bar/bar.hpp>

namespace thOth {

	bar::bar(const std::shared_ptr<timeSeries<quote> > & ts) {

		registerWith(ts);

	}

	bar::bar(const bar & o){
	
		for (std::set<std::shared_ptr<observable> >::const_iterator It =		// register with the observables
			o.observables_.cbegin(); It != o.observables_.cend(); It++)

			this->registerWith(*It);

	}
	
	bar::~bar() {
	
		unregisterWithAll();
	
	}

	bar & bar::operator =(const bar & o) {
	
		if (&o != this) {
		
			// todo: insure the = operator is called from observer class
			barStart_ = o.barStart_;
			barEnd_   = o.barEnd_  ;

			open_  = o.open_ ;
			close_ = o.close_;
			high_  = o.high_ ;
			low_   = o.low_  ;

		}

		return *this;
	
	};

}
