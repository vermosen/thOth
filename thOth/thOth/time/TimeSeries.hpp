#ifndef thoth_time_series
#define thoth_time_series

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
		typename T, 
		typename Key = thOth::dateTime, 
		typename Rel = std::less<Key>,
		typename All = std::allocator<std::pair<const Key, T>>>
	class timeSeries : public observable {

	public:

		timeSeries<T, Key, Rel, All>();											// default ctor
		timeSeries<T, Key, Rel, All>(const timeSeries<T, Key, Rel, All> &);		// copy ctor
		~timeSeries<T, Key, Rel, All>() {};										// destructor
		timeSeries<T, Key, Rel, All> & operator =(								// assignement operator
			const timeSeries<T, Key, Rel, All> &);	

		template <class Iterator>												// ctor using iterators
		timeSeries<T, Key, Rel, All>(Iterator dBegin, Iterator dEnd){			// don't move outside of
																				// the class declaration
			while (dBegin != dEnd) data_.insert(*(dBegin++));

		};

		void insert(const std::pair<Key, T> &);						// insert new data

		size size () const;														// size
		
		void clear ();															// clear the ts

		// iterator definition
		typedef typename std::map<dateTime, T, Rel, All>::iterator iterator                            ;
		typedef typename std::map<dateTime, T, Rel, All>::reverse_iterator reverse_iterator            ;
		typedef typename std::map<dateTime, T, Rel, All>::const_iterator const_iterator                ;
		typedef typename std::map<dateTime, T, Rel, All>::const_reverse_iterator const_reverse_iterator;

		// iterators
		typename iterator               begin   ()      ;
		typename iterator               end     ()      ;
		typename reverse_iterator       rbegin  ()      ;
		typename reverse_iterator       rend    ()      ;
		typename const_iterator         cbegin  () const;
		typename const_iterator         cend    () const;	
		typename const_reverse_iterator crbegin () const;
		typename const_reverse_iterator crend   () const;
		
	private:

		std::map<dateTime, T> data_;											// data

	};	

	template <typename T, typename Key, typename Rel, typename All>
	timeSeries<T, Key, Rel, All>::timeSeries() {};								// default ctor

	template <typename T, typename Key, typename Rel, typename All>				// copy ctor
	timeSeries<T, Key, Rel, All>::timeSeries(const timeSeries<T, Key, Rel, All> & o)	
		: observable(o) {
	
		data_ = o.data_;
	
	}

	template <typename T, typename Key, typename Rel, typename All>				// assignement operator
	timeSeries<T, Key, Rel, All> & timeSeries<T, Key, Rel, All>::operator = (
		const timeSeries<T, Key, Rel, All> & o) {

		if (&o != this) {

			observable::operator =(o);											// will notify observers
			data_ = o.data_;													// copy data

		}

		return *this;

	}

	template <typename T, typename Key, typename Rel, typename All>
	void timeSeries<T, Key, Rel, All>::insert(const std::pair<Key, T> & n) {
	
		data_.insert(n);
		notifyObservers();
	
	}

	template <typename T, typename Key, typename Rel, typename All>
	inline typename timeSeries<T, Key, Rel, All>::iterator
		timeSeries<T, Key, Rel, All>::begin() {

		return data_.begin();

	}

	template <typename T, typename Key, typename Rel, typename All>
	inline typename timeSeries<T, Key, Rel, All>::iterator
		timeSeries<T, Key, Rel, All>::end() {

		return data_.end();

	}

	template <typename T, typename Key, typename Rel, typename All>
	inline typename timeSeries<T, Key, Rel, All>::reverse_iterator
		timeSeries<T, Key, Rel, All>::rbegin() {

		return data_.rbegin();

	}

	template <typename T, typename Key, typename Rel, typename All>
	inline typename timeSeries<T, Key, Rel, All>::reverse_iterator
		timeSeries<T, Key, Rel, All>::rend() {

		return data_.rend();

	}

	template <typename T, typename Key, typename Rel, typename All>
	inline typename timeSeries<T, Key, Rel, All>::const_iterator
		timeSeries<T, Key, Rel, All>::cbegin() const {

		return data_.cbegin();

	}

	template <typename T, typename Key, typename Rel, typename All>
	inline typename timeSeries<T, Key, Rel, All>::const_iterator
		timeSeries<T, Key, Rel, All>::cend() const {
	
			return data_.cend();
	
	}

	template <typename T, typename Key, typename Rel, typename All>
	inline typename timeSeries<T, Key, Rel, All>::const_reverse_iterator
		timeSeries<T, Key, Rel, All>::crbegin() const {

		return data_.crbegin();

	}

	template <typename T, typename Key, typename Rel, typename All>
	inline typename timeSeries<T, Key, Rel, All>::const_reverse_iterator
		timeSeries<T, Key, Rel, All>::crend() const {

		return data_.crend();

	}

	template <typename T, typename Key, typename Rel, typename All>
	inline size timeSeries<T, Key, Rel, All>::size() const {

			return data_.size();

	}

	template <typename T, typename Key, typename Rel, typename All>
	inline void timeSeries<T, Key, Rel, All>::clear() {

		data_.clear();

	}

}

#endif