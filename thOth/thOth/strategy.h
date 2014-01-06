#pragma once

#include "thOth/time/occurence.h"

namespace thOth {

	// the trade class get a date which represent 
	// the initial moment of the implementation
	// the child classes will be in charge of 
	// implementing the execution pattern
	class strategy : public occurence {

		public:

			strategy(const dateTime &);				// value constructor
			strategy(const strategy &);				// copy constructor
			virtual ~strategy();					// virtual destructor
			strategy & operator=(const strategy &);	// assignement operator

			virtual dateTime date() const = 0;		// returns the implementation date

			//virtual 

		protected:
			strategy();								// default constructor is private
			dateTime implDate_;

	};

}
