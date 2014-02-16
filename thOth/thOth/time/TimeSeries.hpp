#pragma once

#include <thOth/time/dateTime.hpp>
#include <thOth/pattern/observable.hpp>

#include <boost/optional.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>
#include <map>
//#include <vector>

namespace thOth {

	template <typename T>
	class TimeSeries : public observable {

	public:

		typedef dateTime key_type;												// key type

		TimeSeries<T>();															// default ctor
		TimeSeries<T>(const TimeSeries<T> &);									// copy ctor
		~TimeSeries<T>() {};														// destructor
		TimeSeries<T> & operator =(const TimeSeries<T> &);						// assignement operator

		template <class DateIterator, class ValueIterator>						// ctor using iterators
		TimeSeries<T>(DateIterator dBegin, DateIterator dEnd,
			ValueIterator vBegin) {

			while (dBegin != dEnd)
				data_.insert(std::pair<dateTime, T>(*(dBegin++), *(vBegin++)));

			this->notifyObservers();												// notify
		
		}

		void insert(const std::pair<thOth::dateTime, T> &);						// insert new data

		size size() const;														// sise

		// definition
		typedef typename std::map<dateTime, T>::const_iterator const_iterator;

		// iterators
		typename const_iterator cbegin() const;
		typename const_iterator cend() const;
		typename const_iterator begin() const { return cbegin(); };
		typename const_iterator end() const { return cend(); };

	private:

		std::map<dateTime, T> data_;												// data

	};	

	template <typename T>
	TimeSeries<T>::TimeSeries() {};												// default ctor

	template <typename T>
	TimeSeries<T>::TimeSeries(const TimeSeries<T> & o)							// copy ctor
		: observable(o) {
	
		data_ = o.data_;
	
	};

	template <typename T>
	TimeSeries<T> & TimeSeries<T>::operator = (const TimeSeries<T> & o) {		// assignement operator

		if (&o != this) {

			data_ = o.data_;													// copy data
			this->notifyObservers();											// notify

		}

		return *this;

	}

	template <typename T>
	void TimeSeries<T>::insert(const std::pair<thOth::dateTime, T> & n) {
	
		data_.insert(n);
		this->notifyObservers();
	
	}

	template <typename T>
	inline typename std::map<dateTime, T>::const_iterator
		TimeSeries<T>::cbegin() const {

			return data_.begin();
	
	}

	template <class T>
	inline typename TimeSeries<T>::const_iterator
		TimeSeries<T>::cend() const {
	
			return data_.end();
	
	}

	template <class T>
	inline size TimeSeries<T>::size() const {

			return data_.size();

	}

}