#ifndef thoth_observable_hpp
#define thoth_observable_hpp

#include <set>

#include <thOth/types.hpp>

namespace thOth {

	class observer;

	//! Object that notifies its changes to a set of observers
	/*! \ingroup patterns */
	class observable {

		friend class observer;
	
	public:

		observable() {}													// base constructor
		observable(const observable&);									// copy constructor
		observable& operator=(const observable&);						// assignement operator
		virtual ~observable() {}										// destructor

		/*! This method should be called at the end of non-const methods
		or when the programmer desires to notify any changes.
		*/
		void notifyObservers();

	protected:

		std::pair<std::set<observer*>::iterator, bool> registerObserver(observer*);
		size unregisterObserver(observer*);
		std::set<observer*> observers_;									// observers
	
	};

}

#endif
