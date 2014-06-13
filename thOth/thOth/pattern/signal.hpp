#include <boost/signal.hpp>

class signal {

	private:

		signal() {};					// private ctor
		signal(const signal &); 		// private copy ctor

	public:

		static boost::signal<void(bool value)> changeOccured;


};