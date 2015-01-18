#ifndef thOth_trade_message_hpp
#define thOth_trade_message_hpp

#include <thOth/message.hpp>
#include <thOth/trade.hpp>

namespace thOth {

	// ideally, we would build a template
	//template <class T>
	//class mess<T> : public message::impl<message> {

	class tradeMessage : public message::impl<message> {

	public:

		tradeMessage(const instrument & symbol, const dateTime & time,
			const trade & tr) : message::impl < message >(),
			symbol_(symbol), time_(time), trade_(tr) {};

		// accessors
		instrument	symbol		() const { return symbol_  ; };
		dateTime	time		() const { return time_    ; };
		trade		messageTrade() const { return trade_   ; };

		void symbol			(const instrument & s) { symbol_   = s; };
		void time			(const dateTime   & s) { time_     = s; };
		void messageTrade	(const trade	  & s) { trade_    = s; };

	protected:

		instrument  symbol_	;				// symbol name (FIX field 107) together with db identifier
		dateTime	time_	;				// quote time
		trade		trade_	;				// thOth trade

	};
}

#endif