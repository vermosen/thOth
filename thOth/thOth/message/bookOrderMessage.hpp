#ifndef thOth_book_message_hpp
#define thOth_book_message_hpp

#include "thOth/message/tradeMessage.hpp"

namespace thOth {

	class bookOrderMessage : public message::impl<bookOrderMessage> {

	public:

		enum update_action { new_ = 1, change_ = 2, delete_ = 3 };
		enum entry_type    { bid_ = 1, ask_ = 2   , trade_  = 3 };

		// compare sequence numbers
		bool operator < (const bookOrderMessage & msg) const;

		friend std::ostream & operator << (std::ostream &, const bookOrderMessage &);

		// accessors
		update_action   action     ()	const { return action_		; }
		entry_type      type       ()	const { return type_		; }
		unsigned int    order_count()	const { return order_count_	; }
		unsigned int    level      ()	const { return level_		; }
		unsigned long   seq_number ()	const { return seq_number_	; }
		std::string     sender_id  ()	const { return sender_id_	; }

		void action		(update_action s) { action_		= s; }
		void type		(entry_type s	) { type_		= s; }
		void order_count(unsigned int s	) { order_count_= s; }
		void level		(unsigned int s ) { level_		= s; }
		void seq_number	(unsigned long s) { seq_number_	= s; }
		void sender_id	(std::string s  ) { sender_id_	= s; }

	protected:

		update_action   action_			;	// new, change, delete
		entry_type      type_			;	// bid, ask, trade
		unsigned int    order_count_ = 0;	// number of orders at the level
		unsigned int    level_ = 0		;	// book level
		unsigned long   seq_number_ = 0	;	// sequence number (FIX field 34)
		std::string     sender_id_ = ""	;	// firm sending message (FIX field 49), e.g., CME

	};
}

#endif