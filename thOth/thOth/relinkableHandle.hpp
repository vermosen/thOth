#ifndef thoth_relinkable_handle_hpp
#define thoth_relinkable_handle_hpp

#include <thOth/handle.hpp>

namespace thOth {

	// extend handle class
	template <class T>
	class relinkableHandle : public handle<T> {
	
	public:
	
		explicit relinkableHandle(
			const boost::shared_ptr<T>& p = boost::shared_ptr<T>(),
			bool registerAsObserver = true);
		
		explicit relinkableHandle(
			T* p,
			bool registerAsObserver = true);
		
		void linkTo(const boost::shared_ptr<T>&,
			bool registerAsObserver = true);
	
	};

	template <class T>
	inline relinkableHandle<T>::relinkableHandle(const boost::shared_ptr<T>& p,
		bool registerAsObserver)
		: handle<T>(p, registerAsObserver) {}

	template <class T>
	inline relinkableHandle<T>::relinkableHandle(T* p,
		bool registerAsObserver)
		: handle<T>(p, registerAsObserver) {}

	template <class T>
	inline void relinkableHandle<T>::linkTo(const boost::shared_ptr<T>& h,
		bool registerAsObserver) {
		this->link_->linkTo(h, registerAsObserver);
	}

}

#endif