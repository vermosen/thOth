#ifndef thoth_bar_hpp
#define thoth_bar_hpp

#include <thOth/pattern/observable.hpp>
#include <thOth/pattern/observer.hpp>
#include <thOth/time/TimeSeries.hpp>
#include <thOth/quote/quote.hpp>

namespace thOth {

	// a quote class
	class bar : public observable, observer	{		// observes the quotes, observable

		public:

			 bar(const TimeSeries<quote> &);		// constructor
			 bar(const bar &);						// copy ctor
			~bar();									// destructor

			bar & operator =(const bar &);			// assignement operator
		
		private:
			bar() {};								// private default ctor

	};

}

#endif