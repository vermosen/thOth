#include <boost/signals2/signal.hpp>

/* sender class*/
class sender {

public:

	sender(bool v = false) : value_(v) {};

	void setValue(const bool v) {

		value_ = v;
		//this->change();
	
	};

private:

	bool value_;

};