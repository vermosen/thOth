#include "staticDataWrapper.hpp"

staticDataWrapper::staticDataWrapper(bool CalledFromThread)
: EWrapperL0(CalledFromThread),
errorForRequest_(false) {}

staticDataWrapper::staticDataWrapper(const staticDataWrapper & o)
: EWrapperL0(o)
{

	errorForRequest_ = o.errorForRequest_;

}

staticDataWrapper & staticDataWrapper::operator = (const staticDataWrapper & hw)
{

	if (&hw != this) {

		this->EWrapperL0::operator =(hw);											// calls base class assignement operator
		errorForRequest_ = hw.errorForRequest_;

	}

	return *this;

}

void staticDataWrapper::winError(const IBString& str, int lastError)
{

	fprintf(stderr, "WinError: %d = %s\n", lastError, (const char*)str);
	errorForRequest_ = true;

}

void staticDataWrapper::error(const int id, const int errorCode, const IBString errorString)
{
	fprintf(stderr, "Error for id=%d: %d = %s\n", id, errorCode, (const char*)errorString);
	errorForRequest_ = (id > 0);
	// id == -1 are 'system' messages, not for user requests
	// as a test, set year to 2010 in the reqHistoricalData
	// should raise an std::exception -> need an exception class ???
}