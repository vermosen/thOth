#ifndef thOth_trade_message_hpp
#define thOth_trade_message_hpp

#include <thOth/message.hpp>

namespace thOth {

	class tradeMessage : public message::impl<message> {

	public:

		tradeMessage(const instrument & symbol, const thOth::dateTime & time,
			double price, int quantity) : message::impl < message >(),
			symbol_(symbol), time_(time), price_(price), quantity_(quantity) {};

		// accessors
		instrument      symbol   () const { return symbol_  ; };
		thOth::dateTime time     () const { return time_    ; };
		double          price    () const { return price_   ; };
		int             quantity () const { return quantity_; };

		void symbol   (const instrument & s){ symbol_   = s; };
		void time     (const dateTime   & s){ time_     = s; };
		void price    (double             s){ price_    = s; };
		void quantity (int                s){ quantity_ = s; };

	protected:

		instrument      symbol_			;	// symbol name (FIX field 107) together with db identifier
		thOth::dateTime time_			;	// quote time
		double          price_    = .0	;	// price
		int             quantity_ =  0	;	// number of units (contracts, shares, etc.)

	};
}

#endif