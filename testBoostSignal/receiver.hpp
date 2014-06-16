#include <thOth/pattern/signal.hpp>

/* receiver class*/
class receiver {

public:

	receiver() {};

	void update(const bool v) {

		value_ = v;

	};

	bool getValue() const { return value_; };

private:

	bool value_;

};