
#include "thOth/pattern/observable.h"
#include "thOth/pattern/observer.h"

namespace thOth {

	observable::observable(const observable&) {
		// the observer set is not copied; no observer asked to
		// register with this object
	}

	/*! \warning notification is sent before the copy constructor has
	a chance of actually change the data
	members. Therefore, observers whose update() method
	tries to use their observables will not see the
	updated values. It is suggested that the update()
	method just raise a flag in order to trigger
	a later recalculation.
	*/
	observable& observable::operator=(const observable& o) {

		// as above, the observer set is not copied. Moreover,
		// observers of this object must be notified of the change
		if (&o != this)	notifyObservers();

		return *this;

	}

	std::pair<std::set<observer*>::iterator, bool>
	observable::registerObserver(observer* o) {

		return observers_.insert(o);
	
	}

	Size observable::unregisterObserver(observer* o) {
	
		return observers_.erase(o);
	
	}

	void observable::notifyObservers() {
		bool successful = true;
		std::string errMsg;
		for (iterator i = observers_.begin(); i != observers_.end(); ++i) {
			try {
				(*i)->update();
			}
			catch (std::exception& e) {

				// quite a dilemma. If we don't catch the exception,
				// other observers will not receive the notification
				// and might be left in an incorrect state. If we do
				// catch it and continue the loop (as we do here) we
				// lose the exception. The least evil might be to try
				// and notify all observers, while raising an
				// exception if something bad happened.
				successful = false;
				errMsg = e.what();
			}
			catch (...) {
				successful = false;
			}
		}
	}

}
