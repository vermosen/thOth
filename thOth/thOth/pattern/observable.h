#pragma once

#include <set>

#include "thOth/types.h"

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

	private:

		typedef std::set<observer*>::iterator iterator;
		std::pair<iterator, bool> registerObserver(observer*);
		Size unregisterObserver(observer*);
		std::set<observer*> observers_;									// observers
	
	};

}