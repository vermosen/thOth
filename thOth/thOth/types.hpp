#ifndef thoth_types
#define thoth_types

#include <cstddef>
#include <stdint.h>

namespace thOth {

	typedef unsigned int 	size   	;				// size
	typedef double			real	;				// real number
<<<<<<< HEAD
	typedef long			volume	;				// volume
=======
	typedef long			volume	;				// volume (int 64 ?)
>>>>>>> branch 'master' of https://github.com/vermosen/thOth
	typedef uint64_t		bigInt	;				// record identifier
	
	enum marketSide : bool {

		bid = 1,
		ask = 0

	};

	enum quoteType : short {

		Undefined = 0,
		Trade     = 1,
		Bid       = 2,
		Ask       = 3

	};

	enum weekday {

		Sunday		= 1,
		Monday		= 2,
		Tuesday		= 3,
		Wednesday	= 4,
		Thursday	= 5,
		Friday		= 6,
		Saturday	= 7

	};

	enum businessDayConvention : short {

		following         = 0,          
		modifiedFollowing = 1, 
		preceding         = 2,
		modifiedPreceding = 3,  
		unadjusted        = 4

	};

	enum timeUnit {

		year,
		month,
		week,
		day,
		hour,
		minute,
		second,
		milliSecond,
		microSecond,
		nanoSecond

	};


}

#endif
