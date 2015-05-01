/*
 *
 * thOth
 * Copyright (C) 2015 Jean-Mathieu Vermosen
 *
 */

#ifndef observer2_hpp
#define observer2_hpp

namespace thOth {

	// The observer class
	template<typename T>
	class observer2 {

		virtual ~observer2() {};

	public:

		virtual void slot(T i) {};

	};
}

#endif
