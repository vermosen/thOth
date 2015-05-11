#ifndef thoth_types
#define thoth_types

#include <cstddef>
#include <stdint.h>

namespace thOth {

	typedef unsigned int 	size   	;				// size
	typedef double			real	;				// real number
	typedef long			volume	;				// volume
	typedef long			volume	;				// volume (int 64 ?)
	typedef uint64_t		bigInt	;				// record identifier
	
	enum marketSide {

		bid	,
		ask

	};

	enum quoteType {

		Undefined ,
		Trade     ,
		Bid       ,
		Ask

	};

	enum weekday {

		Sunday		,
		Monday		,
		Tuesday		,
		Wednesday	,
		Thursday	,
		Friday		,
		Saturday

	};

	enum businessDayConvention {

		following         ,
		modifiedFollowing ,
		preceding         ,
		modifiedPreceding ,
		unadjusted

	};

	enum timeUnit {

		year		,
		month		,
		week		,
		day			,
		hour		,
		minute		,
		second		,
		milliSecond	,
		microSecond	,
		nanoSecond

	};
}

#endif
