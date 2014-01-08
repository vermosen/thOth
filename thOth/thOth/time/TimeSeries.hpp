#pragma once

#include <thOth/time/dateTime.hpp>

#include <boost/optional.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/reverse_iterator.hpp>
#include <boost/function.hpp>
#include <boost/utility.hpp>
#include <map>
//#include <vector>

namespace thOth {

	template <typename T>
	class TimeSeries : public std::map<dateTime, T> {

	public:

		typedef dateTime key_type;												// key type

		TimeSeries<T>();														// default ctor
		TimeSeries<T>(const TimeSeries<T> &);									// copy ctor
		~TimeSeries<T>() {};													// destructor
		TimeSeries<T> & operator =(const TimeSeries<T> &);						// assignement operator

		template <class DateIterator, class ValueIterator>						// ctor using iterators
		TimeSeries<T>(DateIterator dBegin, DateIterator dEnd,
			ValueIterator vBegin) {

			while (dBegin != dEnd)
				this->insert(std::pair<dateTime, T>(*(dBegin++), *(vBegin++)));
		
		}

	};	

	template <typename T>
	TimeSeries<T>::TimeSeries() : std::map<key_type, T>() {};					// default ctor

	template <typename T>
	TimeSeries<T>::TimeSeries(const TimeSeries<T> & o)							// copy ctor
		: std::map<key_type, T>(o) {};

	template <typename T>
	TimeSeries<T> & TimeSeries<T>::operator = (const TimeSeries<T> & ts) {		// assignement operator

		if (&ts != this) {


		}

		return *this;

	}

}