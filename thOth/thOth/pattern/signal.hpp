#ifndef thoth_signal_hpp
#define thoth_signal_hpp

#include <boost/signals2.hpp>

namespace thOth {

		class signal {

		protected:

			signal() {};					// private ctor


		private:

			static boost::signals2::signal<void> s_;

	};

}

#endif