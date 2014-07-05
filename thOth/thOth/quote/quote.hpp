#ifndef thoth_quote_hpp
#define thoth_quote_hpp

#include <thOth\pattern\observable.hpp>

namespace thOth {

	// a quote class, heritable, potentially pure virtual (w. simpleQuote spec)
	class quote : public observable	{

		public:

			quote ();
			virtual ~quote();

			quoteType type_;
			real      value_;
			volume    amount_;
	
	};

}

#endif