#include <thOth/trade.hpp>

namespace thOth{

	trade::trade() {}							// ctor
	trade::trade(const trade & o) {				// copy ctor
	
		tradeDate_ = o.tradeDate_;
		quantity_ = o.quantity_;
		price_ = o.price_;

	}

	trade::trade(const dateTime& dt, const volume& qt, const double& px)
		: tradeDate_(dt), quantity_(qt), price_(px) {}
												// additional ctor

	trade::~trade() {}							// destructor



}