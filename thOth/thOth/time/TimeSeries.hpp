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

	template <typename T>
	class timeSeries : public observable {

	public:

		typedef dateTime key_type;												// key type

		timeSeries<T>();														// default ctor
		timeSeries<T>(const timeSeries<T> &);									// copy ctor
		~timeSeries<T>() {};													// destructor
		timeSeries<T> & operator =(const timeSeries<T> &);						// assignement operator

		template <class DateIterator, class ValueIterator>						// ctor using iterators
		timeSeries<T>(DateIterator dBegin, DateIterator dEnd,
			ValueIterator vBegin) {

			while (dBegin != dEnd)
				data_.insert(std::pair<dateTime, T>(*(dBegin++), *(vBegin++)));

			this->notifyObservers();											// notify
		
		}

		void insert(const std::pair<thOth::dateTime, T> &);						// insert new data

		size size() const;														// sise

		// definition
		typedef typename std::map<dateTime, T>::const_iterator const_iterator;

		// iterators
		typename const_iterator cbegin() const;
		typename const_iterator cend  () const;
		typename const_iterator begin () const { return cbegin(); };
		typename const_iterator end   () const { return cend  (); };

	private:

		std::map<dateTime, T> data_;											// data

	};	

	template <typename T>
	timeSeries<T>::timeSeries() {};												// default ctor

	template <typename T>
	timeSeries<T>::timeSeries(const timeSeries<T> & o)							// copy ctor
		: observable(o) {
	
		data_ = o.data_;
	
	};

	template <typename T>
	timeSeries<T> & timeSeries<T>::operator = (const timeSeries<T> & o) {		// assignement operator

		if (&o != this) {

			data_ = o.data_;													// copy data
			this->notifyObservers();											// notify

		}

		return *this;

	}

	template <typename T>
	void timeSeries<T>::insert(const std::pair<thOth::dateTime, T> & n) {
	
		data_.insert(n);
		this->notifyObservers();
	
	}

	template <typename T>
	inline typename std::map<dateTime, T>::const_iterator
		timeSeries<T>::cbegin() const {

			return data_.begin();
	
	}

	template <class T>
	inline typename timeSeries<T>::const_iterator
		timeSeries<T>::cend() const {
	
			return data_.end();
	
	}

	template <class T>
	inline size timeSeries<T>::size() const {

			return data_.size();

	}

}

#endif