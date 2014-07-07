#ifndef thoth_bar_hpp
#define thoth_bar_hpp

#include <thOth/pattern/observable.hpp>
#include <thOth/pattern/observer.hpp>
#include <thOth/time/TimeSeries.hpp>
#include <thOth/quote/quote.hpp>

namespace thOth {

	// a bar class, comes together with a bar factory
	// comes up with open/close/high/low values
	class bar : public observable, observer	{					// observes the quotes, observable ?

		public:

			bar(const std::shared_ptr<timeSeries<quote> > &);	// constructor
			bar(const bar &);									// copy ctor
			virtual ~bar();										// destructor

			bar & operator =(const bar &);						// assignement operator
		
			bar & operator +(const bar &);						// merging operator

			dateTime barStart() const { return barStart_; };	// accessors
			dateTime barEnd  () const { return barEnd_  ; };
			real open  () const { return open_  ; };
			real close () const { return close_ ; };
			real high  () const { return high_  ; };
			real low   () const { return low_   ; };
			real volume() const { return volume_; };

			void update() {};									// observer interface
	
		private:
			
			bar() {};											// no empty bar

			dateTime barStart_;
			dateTime barEnd_  ;

			real open_  ;
			real close_ ;
			real  high_ ;
			real low_   ;
			real volume_;



	};

}

#endif