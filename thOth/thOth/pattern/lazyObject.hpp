#ifndef THOTH_LAZY_OBJECT
#define THOTH_LAZY_OBJECT

#include "thOth/pattern/observable.hpp"
#include "thOth/pattern/observer.hpp"

namespace thOth {

	//! Framework for calculation on demand and result caching.
	/*! \ingroup patterns */
	class lazyObject : public virtual observable,
					   public virtual observer {

	public:
		lazyObject();									// constructor
		lazyObject(const lazyObject &);					// copy constructor
		virtual ~lazyObject();							// destructor
		lazyObject & operator=(const lazyObject &);		// assignement operator

		void update();									// update
		void recalculate();								// trigger recalculation
		void freeze();									// freeze the object
		void unfreeze();								// unfreeze the object
	
	protected:

		// This method performs all needed calculations by calling
		// the <i><b>performCalculations</b></i> method.
		virtual void calculate() const;
		
		// This method must implement any calculations which must be
		// (re)done in order to calculate the desired results.
		virtual void performCalculations() const = 0;

		mutable bool calculated_, frozen_;

	};

}

#endif