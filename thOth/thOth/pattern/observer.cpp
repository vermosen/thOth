
#include "thOth/pattern/observable.hpp"
#include "thOth/pattern/observer.hpp"

namespace thOth {

	observer::observer(const observer& o)
		: observables_(o.observables_) {

		// register with all the observers of the object to copy
		for (iterator i = observables_.begin(); i != observables_.end(); ++i)
			(*i)->registerObserver(this);

	}

	observer& observer::operator=(const observer& o) {
		
		iterator i;
		
		// break the link of the current object
		for (i = observables_.begin(); i != observables_.end(); ++i)
			(*i)->unregisterObserver(this);
		observables_ = o.observables_;

		// register with all the observers of the object to copy
		for (i = observables_.begin(); i != observables_.end(); ++i)
			(*i)->registerObserver(this);
		return *this;
	}

	observer::~observer() {

		// unregister with all the observers
		for (iterator i = observables_.begin(); i != observables_.end(); ++i)
			(*i)->unregisterObserver(this);

	}

	std::pair<std::set<boost::shared_ptr<observable> >::iterator, bool>
		observer::registerWith(const boost::shared_ptr<observable>& h) {

			if (h) {
				h->registerObserver(this);
				return observables_.insert(h);
			}

			return std::make_pair(observables_.end(), false);
		
		}

	size observer::unregisterWith(const boost::shared_ptr<observable>& h) {
		
		if (h)
			h->unregisterObserver(this);
		return observables_.erase(h);
	
	}

	void observer::unregisterWithAll() {
	
		for (iterator i = observables_.begin(); i != observables_.end(); ++i)
			(*i)->unregisterObserver(this);
		observables_.clear();
	
	}

}
