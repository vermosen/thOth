#pragma once

#include <set>
#include <boost/shared_ptr.hpp>

#include "thOth/types.h"

namespace thOth {

	class observable;

	//! Object that gets notified when a given observable changes
	/*! \ingroup patterns */
	class observer {

	public:

		observer() {}													// constructor
		observer(const observer&);										// copy constructor
		observer& operator=(const observer&);							// assignement operator
		virtual ~observer();											// destructor

		// interface
		std::pair<std::set<boost::shared_ptr<observable> >::iterator, bool>
			registerWith(const boost::shared_ptr<observable>&);
		Size unregisterWith(const boost::shared_ptr<observable>&);

		/*! This method must be implemented in derived classes. An
		instance of %Observer does not call this method directly:
		instead, it will be called by the observables the instance
		registered with when they need to notify any changes.
		*/
		void unregisterWithAll();
		virtual void update() = 0;
	private:

		std::set<boost::shared_ptr<observable> > observables_;
		typedef std::set<boost::shared_ptr<observable> >::iterator iterator;
	};

}