#ifndef thOth_message_hpp
#define thOth_message_hpp

#include <string>
//#include <istream>

#include <thOth/time/DateTime.hpp>
#include <thOth/pattern/visitor.hpp>
#include <thOth/types.hpp>

namespace thOth {

	// TODO: bring more structure on that one
	typedef std::pair<bigInt, std::string> instrument;

	class message {

	public:

		virtual ~message() = default;

		// message visitor
		class visitor : public thOth::visitor < message > {};

		// visitability
		virtual bool accept(visitor &) = 0;
		bool accept(visitor && v) { return std::move(accept(v)); };

		// message implementation class
		template < typename T>
		class impl : public T {

		public:

			class visitor : public thOth::visitor <impl> {};

			virtual bool accept(message::visitor & av) override {

				auto dv = dynamic_cast<impl::visitor*>(std::addressof(av));
				return dv ? dv->accept(this) : av.accept(this);

			}
		};
	};
}

#endif