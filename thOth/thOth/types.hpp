# pragma once

#include <cstddef>
#include <Windows.h>

namespace thOth {

	typedef std::size_t size;				// size

	typedef double real;						// real number

	typedef long volume;

	enum marketSide : bool {

		bid = true,
		ask = false

	};

	enum quoteType : BYTE {

		Undefined = 0,
		Trade = 1,
		Bid = 2,
		Ask = 3

	};

	struct quoteDetails {

		BYTE QUOTE_TYPE;
		float QUOTE_VALUE;
		float QUOTE_AMOUNT;

	};

}

