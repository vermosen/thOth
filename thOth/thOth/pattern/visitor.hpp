#pragma once

namespace thOth {

	template <class T> class visitor {				// visitor class

		public:
			virtual ~visitor() {}
			virtual void visit(T&) = 0;
	
	};

}
