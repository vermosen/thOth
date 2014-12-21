#ifndef thoth_visitor_hpp
#define thoth_visitor_hpp

namespace thOth {

	template <class T> 
	class visitor {				// visitor class

		public:

			virtual ~visitor() = default;
			virtual bool accept(T *) = 0;

	};
}

#endif