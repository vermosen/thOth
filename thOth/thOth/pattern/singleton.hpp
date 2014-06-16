#ifndef thoth_singleton_hpp
#define thoth_singleton_hpp

#include <memory>
#include <map>
#include <boost/noncopyable.hpp>

namespace thOth {

	//! Basic support for the singleton pattern.
	/*! The typical use of this class is:
	\code
	class Foo : public singleton<Foo> {
	friend class singleton<Foo>;
	private:
	Foo() {}
	public:
	...
	};
	\endcode
	which, albeit sub-optimal, frees one from the concerns of
	creating and managing the unique instance and can serve later
	as a single implemementation point should synchronization
	features be added.

	\ingroup patterns
	*/
	template <class T>
	class singleton : private boost::noncopyable {

	public:
		//! access to the unique instance
		static T& instance();
	protected:
		singleton() {}
	};

	// template definitions

	template <class T>
	T& singleton<T>::instance() {

		static  std::shared_ptr<T> instances_;

		std::shared_ptr<T>& instance = instances_[0];

		if (!instance)
			instance = std::shared_ptr<T>(new T);
		
		return *instance;

	}

}

#endif