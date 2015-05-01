#ifndef thoth_bar_hpp
#define thoth_bar_hpp

#include <thOth/pattern/observable.hpp>
#include <thOth/pattern/observer.hpp>
#include <thOth/time/timeSeries.hpp>
#include <thOth/quote/quote.hpp>
#include <thOth/time/period.hpp>

namespace thOth {

	// a bar class, comes together with a bar factory
	// comes up with open/close/high/low/volume values
	class bar {

		public:

			bar() = delete;										// no empty bar allowed
			
			bar(const bar &);									// copy ctor
			
			bar(real open    , 
				real close   ,
				real high    ,
				real low     ,
				period length,
				size volume   );

			~bar();												// destructor

			bar & operator =(const bar &);						// assignement operator

			// accessors
			real open     () const { return open_  ; };
			real close    () const { return close_ ; };
			real high     () const { return high_  ; };
			real low      () const { return low_   ; };
			size volume   () const { return volume_; };
			period length () const { return length_; };

			void open	(const real		& v) { open_	= v; };
			void close	(const real		& v) { close_	= v; };
			void high	(const real		& v) { high_	= v; };
			void low	(const real		& v) { low_		= v; };
			void volume	(const size		& v) { volume_	= v; };
			void length	(const period	& v) { length_	= v; };

		private:

			real	open_   ;
			real	close_  ;
			real	high_   ;
			real	low_    ;
			period	length_	;
			size	volume_	;

	};
}

#endif
