#ifndef thoth_time_series
#define thoth_time_series

#include <thOth/types.hpp>
#include <thOth/time/dateTime.hpp>
#include <thOth/pattern/observable.hpp>

#include <boost/optional.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>
#include <map>

namespace thOth {

	template <
		typename Key,
		typename T,
		typename Rel = std::less<Key>,
		typename All = std::allocator<std::pair<const Key, T>>>
	class timeSeries : public observable {

	public:

		timeSeries<Key, T,  Rel, All>();										// default ctor
		timeSeries<Key, T,  Rel, All>(const timeSeries<Key, T,  Rel, All> &);	// copy ctor
	   ~timeSeries<Key, T,  Rel, All>() {};										// destructor
		timeSeries<Key, T,  Rel, All> & operator =(								// assignement operator
			const timeSeries<Key, T,  Rel, All> &);	

		template <class Iterator>												// ctor using iterators
		timeSeries<Key, T,  Rel, All>(Iterator dBegin, Iterator dEnd){			// don't move outside of
																				// the class declaration
			while (dBegin != dEnd) data_.insert(*(dBegin++));

		};

		void insert(const std::pair<Key, T> &);									// insert new data

		size nObs() const;														// size
		
		void clear();															// clear the ts

		// iterator definition
		typedef typename std::map<Key, T, Rel, All>::iterator iterator								;
		typedef typename std::map<Key, T, Rel, All>::reverse_iterator reverse_iterator				;
		typedef typename std::map<Key, T, Rel, All>::const_iterator const_iterator					;
		typedef typename std::map<Key, T, Rel, All>::const_reverse_iterator const_reverse_iterator	;

		// iterators
		typename std::map<Key, T, Rel, All>::iterator 				begin	()		;
		typename std::map<Key, T, Rel, All>::iterator 				end  	()		;
		typename std::map<Key, T, Rel, All>::reverse_iterator 		rbegin  ()      ;
		typename std::map<Key, T, Rel, All>::reverse_iterator       rend    ()      ;
		typename std::map<Key, T, Rel, All>::const_iterator         cbegin  () const;
		typename std::map<Key, T, Rel, All>::const_iterator         cend    () const;
		typename std::map<Key, T, Rel, All>::const_reverse_iterator crbegin () const;
		typename std::map<Key, T, Rel, All>::const_reverse_iterator crend   () const;
		
	private:

		std::map<dateTime, T> data_;											// data

	};	

	template <typename Key, typename T, typename Rel, typename All>
	timeSeries<Key, T,  Rel, All>::timeSeries() {};								// default ctor

	template <typename Key, typename T, typename Rel, typename All>				// copy ctor
	timeSeries<Key, T,  Rel, All>::timeSeries(const timeSeries<Key, T,  Rel, All> & o)	
		: observable(o) {
	
		data_ = o.data_;
	
	}

	template <typename Key, typename T, typename Rel, typename All>				// assignement operator
	timeSeries<Key, T,  Rel, All> & timeSeries<Key, T,  Rel, All>::operator = (
		const timeSeries<Key, T,  Rel, All> & o) {

		if (&o != this) {

			observable::operator =(o);											// will notify observers
			data_ = o.data_;													// copy data

		}

		return *this;

	}

	template <typename Key, typename T, typename Rel, typename All>
	void timeSeries<Key, T,  Rel, All>::insert(const std::pair<Key, T> & n) {
	
		data_.insert(n);
		notifyObservers();
	
	}

	template <typename Key, typename T, typename Rel, typename All>
	inline typename timeSeries<Key, T,  Rel, All>::iterator
		timeSeries<Key, T,  Rel, All>::begin() {

		return data_.begin();

	}

	template <typename Key, typename T, typename Rel, typename All>
	inline typename timeSeries<Key, T,  Rel, All>::iterator
		timeSeries<Key, T,  Rel, All>::end() {

		return data_.end();

	}

	template <typename Key, typename T, typename Rel, typename All>
	inline typename timeSeries<Key, T,  Rel, All>::reverse_iterator
		timeSeries<Key, T,  Rel, All>::rbegin() {

		return data_.rbegin();

	}

	template <typename Key, typename T, typename Rel, typename All>
	inline typename timeSeries<Key, T,  Rel, All>::reverse_iterator
		timeSeries<Key, T,  Rel, All>::rend() {

		return data_.rend();

	}

	template <typename Key, typename T, typename Rel, typename All>
	inline typename timeSeries<Key, T,  Rel, All>::const_iterator
		timeSeries<Key, T,  Rel, All>::cbegin() const {

		return data_.cbegin();

	}

	template <typename Key, typename T, typename Rel, typename All>
	inline typename timeSeries<Key, T,  Rel, All>::const_iterator
		timeSeries<Key, T,  Rel, All>::cend() const {
	
			return data_.cend();
	
	}

	template <typename Key, typename T, typename Rel, typename All>
	inline typename timeSeries<Key, T,  Rel, All>::const_reverse_iterator
		timeSeries<Key, T,  Rel, All>::crbegin() const {

		return data_.crbegin();

	}

	template <typename Key, typename T, typename Rel, typename All>
	inline typename timeSeries<Key, T,  Rel, All>::const_reverse_iterator
		timeSeries<Key, T,  Rel, All>::crend() const {

		return data_.crend();

	}

	template <typename Key, typename T, typename Rel, typename All>
	inline size timeSeries<Key, T,  Rel, All>::nObs() const {

			return data_.size();

	}

	template <typename Key, typename T, typename Rel, typename All>
	inline void timeSeries<Key, T,  Rel, All>::clear() {

		data_.clear();

	}

}

#endif
