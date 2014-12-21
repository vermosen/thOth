#include <thOth/bar/bar.hpp>

namespace thOth {

	bar::bar(const bar & o)							// copy ctor
		: open_(o.open_), close_(o.close_), high_(o.high_),
		low_(o.low_), length_(o.length_), volume_(o.volume_) {}
	
	bar::bar(										// detailed ctor
		real open    ,
		real close   ,
		real high    ,
		real low     ,
		period length,
		size volume)
		: open_(open), close_(close), high_(high), 
			low_(low), length_(length), volume_(volume) {};

	bar::~bar() {}									// destructor

	bar & bar::operator =(const bar & o) {			// assignement
	
		if (&o != this) {
		
			open_   = o.open_   ;
			close_  = o.close_  ;
			high_   = o.high_   ;
			low_    = o.low_    ;
			volume_ = o.volume_ ;
			length_ = o.length_ ;

		}

		return *this;
	
	}
}
