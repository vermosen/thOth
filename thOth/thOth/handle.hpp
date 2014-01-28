#ifndef thoth_handle_hpp
#define thoth_handle_hpp

#include <thOth/pattern/observable.hpp>
#include <thOth/pattern/observer.hpp>

namespace thOth {

	// Shared handle to an observable
	/* All copies of an instance of this class refer to the same
	observable by means of a relinkable smart pointer. When such
	pointer is relinked to another observable, the change will be
	propagated to all the copies.

	\pre Class T must inherit from Observable
	*/
	template <class T>
	class handle {

	protected:

		// link class
		class link : public observable, 
					 public observer {

		public:

			explicit link(const boost::shared_ptr<T>& h,
				bool registerAsObserver);
			void linkTo(const boost::shared_ptr<T>&,
				bool registerAsObserver);
			bool empty() const { return !h_; }
			const boost::shared_ptr<T>& currentLink() const { return h_; }
			void update() { notifyObservers(); }

		private:

			boost::shared_ptr<T> h_;
			bool isObserver_;
		
		};
		
		boost::shared_ptr<link> link_;

	public:

		// name Constructors
		explicit handle(const boost::shared_ptr<T>& p = boost::shared_ptr<T>(),
			bool registerAsObserver = true)
			: link_(new link(p, registerAsObserver)) {}

		const boost::shared_ptr<T>& currentLink() const;
		const boost::shared_ptr<T>& operator->() const;
		const boost::shared_ptr<T>& operator*() const;

		// checks if the contained shared pointer points to anything
		bool empty() const;
		
		// allows registration as observable
		operator boost::shared_ptr<observable>() const;
		
		// equality test
		template <class U>
		bool operator==(const handle<U>& other) { return link_ == other.link_; }
		
		// disequality test
		template <class U>
		bool operator!=(const handle<U>& other) { return link_ != other.link_; }
		
		// strict weak ordering
		template <class U>
		bool operator<(const handle<U>& other) { return link_ < other.link_; }
	};

	// inline definitions
	template <class T>
	inline handle<T>::link::link(const boost::shared_ptr<T>& h,
		bool registerAsObserver)
		: isObserver_(false) {
		linkTo(h, registerAsObserver);
	}

	template <class T>
	inline void handle<T>::link::linkTo(const boost::shared_ptr<T>& h,
		bool registerAsObserver) {
		if ((h != h_) || (isObserver_ != registerAsObserver)) {
			if (h_ && isObserver_)
				unregisterWith(h_);
			h_ = h;
			isObserver_ = registerAsObserver;
			if (h_ && isObserver_)
				registerWith(h_);
			notifyObservers();
		}
	}

	template <class T>
	inline const boost::shared_ptr<T>& handle<T>::currentLink() const {
		
		if (!empty())
		return link_->currentLink();
	
	};

	template <class T>
	inline const boost::shared_ptr<T>& handle<T>::operator->() const {
		
		if (!empty())
		return link_->currentLink();

	};

	template <class T>
	inline const boost::shared_ptr<T>& handle<T>::operator*() const {

		if (!empty())
		return link_->currentLink();

	};

	template <class T>
	inline bool handle<T>::empty() const {
		return link_->empty();
	};

	template <class T>
	inline handle<T>::operator boost::shared_ptr<observable>() const {
		return link_;
	};

}


#endif