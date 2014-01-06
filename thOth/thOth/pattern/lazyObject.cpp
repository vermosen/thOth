
#include "thOth/pattern/lazyObject.h"

namespace thOth {

	lazyObject::lazyObject()
		: calculated_(false), frozen_(false) {}

	lazyObject::lazyObject(const lazyObject & o)
		: calculated_(o.calculated_), frozen_(o.frozen_) {}

	lazyObject::~lazyObject() {}

	lazyObject & lazyObject::operator = (const lazyObject & o) {
	
		if (&o != this) {
		
			calculated_ = o.calculated_;
			frozen_ = o.frozen_;
		
		}

		return *this;
	
	}

	void lazyObject::update() {

		// forwards notifications only the first time
		if (calculated_) {
			// set to false early
			// 1) to prevent infinite recursion
			// 2) otherways non-lazy observers would be served obsolete
			//    data because of calculated_ being still true
			calculated_ = false;
			// observers don't expect notifications from frozen objects
			if (!frozen_)
				notifyObservers();
			// exiting notifyObservers() calculated_ could be
			// already true because of non-lazy observers
		}
	}

	void lazyObject::recalculate() {

		bool wasFrozen = frozen_;
		calculated_ = frozen_ = false;
	
		try {
		
			calculate();
		}

		catch (...) {
		
			frozen_ = wasFrozen;
			notifyObservers();
			throw;
		
		}
		
		frozen_ = wasFrozen;
		notifyObservers();
	
	}

	void lazyObject::freeze() {
	
		frozen_ = true;
	
	}

	void lazyObject::unfreeze() {
		// send notifications, just in case we lost any,
		// but only once, i.e. if it was frozen
		if (frozen_) {
			frozen_ = false;
			notifyObservers();
		}
	}

	void lazyObject::calculate() const {
		if (!calculated_ && !frozen_) {
			calculated_ = true;   // prevent infinite recursion in
			// case of bootstrapping
			try {
				performCalculations();
			}
			catch (...) {
				calculated_ = false;
				throw;
			}
		}
	}

}