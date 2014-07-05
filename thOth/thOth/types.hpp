#ifndef thoth_types
#define thoth_types

#include <cstddef>

namespace thOth {

	typedef std::size_t size;					// size

	typedef double real;						// real number

	typedef long volume;						// volume (int 64 ?)

	enum marketSide : bool {

		bid = true,
		ask = false

	};

	enum quoteType : short {

		Undefined = 0,
		Trade     = 1,
		Bid       = 2,
		Ask       = 3

	};

	//struct quoteDetails {						// deprecated -> quote class

	//	quoteType type_  ;
	//	real      value_ ;
	//	volume    amount_;

	//};

}

#endif