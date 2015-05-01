/*
 *
 * thOth
 * Copyright (C) 2015 Jean-Mathieu Vermosen
 *
 */

#ifndef observable2_hpp
#define observable2_hpp

#include <boost/signals2.hpp>

#include <thOth/pattern/observer2.hpp>

namespace thOth {

	// template without any return type
	template <typename T>
	class observable2 : public boost::signals2::signal < void(T) > {

	public:

	void operator ()(T i) {													// overload operator ()

			#ifdef DEBUG
			std::cout << "sending signal from thread " << boost::this_thread::get_id() << std::endl;
			#endif

			this->boost::signals2::signal< void(T) >::operator()(i);

		}

		void registerWith(observer2<T> & rc) {

			this->connect(boost::signals2::signal<void(T)>::slot_type(		// handshake
				&observer2<T>::slot, &rc, _1));

		}
	};


}

#endif
