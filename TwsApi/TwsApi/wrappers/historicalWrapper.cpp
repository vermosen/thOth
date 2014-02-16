#include "historicalWrapper.hpp"

historicalWrapper::historicalWrapper(bool CalledFromThread) 
	: EWrapperL0(CalledFromThread), 
	endOfHistoricalData_(false), 
	errorForRequest_(false),
	ts_() {}

historicalWrapper::historicalWrapper(const historicalWrapper & o)
: EWrapperL0(o) 
{

	endOfHistoricalData_ = o.endOfHistoricalData_;
	errorForRequest_ = o.errorForRequest_;
	ts_ = o.ts_;

}

historicalWrapper & historicalWrapper::operator = (const historicalWrapper & hw)
{

	if (&hw != this) {
	
		this->EWrapperL0::operator =(hw);											// calls base class assignement operator
		endOfHistoricalData_ = hw.endOfHistoricalData_;
		errorForRequest_ = hw.errorForRequest_;
		ts_ = hw.ts_;	
	
	}

	return *this;

}

void historicalWrapper::winError(const IBString& str, int lastError)
{

	fprintf(stderr, "WinError: %d = %s\n", lastError, (const char*)str);
	errorForRequest_ = true;

}

void historicalWrapper::error(const int id, const int errorCode, const IBString errorString)
{
	fprintf(stderr, "Error for id=%d: %d = %s\n", id, errorCode, (const char*)errorString);
	errorForRequest_ = (id > 0);
	// id == -1 are 'system' messages, not for user requests
	// as a test, set year to 2010 in the reqHistoricalData
	// should raise an std::exception -> need an exception class ???
}

void historicalWrapper::marketDataType(TickerId reqId, int marketDataType)
{

	marketDataType_ = marketDataType;

}

void historicalWrapper::historicalData(TickerId reqId, 
									   const IBString& date, 
									   double open, double high, 
									   double low, double close, 
									   int volume, int barCount, 
									   double WAP, int hasGaps)
{
	
	if (IsEndOfHistoricalData(date))
	{

		endOfHistoricalData_ = true;
		return;
	
	}

		TwsApi::historicalQuoteDetails tt{
			reqId, open, high,
			low, close, volume,
			barCount, WAP, hasGaps };

		
		ts_.insert(std::pair<thOth::dateTime, TwsApi::historicalQuoteDetails>(		// copy the current date in the container
			this->convertDateTime(date),
			TwsApi::historicalQuoteDetails{ reqId, open, high,
			low, close, volume,
			barCount, WAP, hasGaps }));

}

thOth::dateTime historicalWrapper::convertDateTime(const IBString & dtStr) const
{

	return thOth::dateTime(															// smallest increments is second
		thOth::dateTime::Years(boost::lexical_cast<int>(dtStr.substr(0, 4))),
		thOth::dateTime::Months(boost::lexical_cast<int>(dtStr.substr(4, 2))),
		thOth::dateTime::Days(boost::lexical_cast<int>(dtStr.substr(6, 2))),
		thOth::dateTime::Hours(boost::lexical_cast<int>(dtStr.substr(10, 2))),
		thOth::dateTime::Minutes(boost::lexical_cast<int>(dtStr.substr(13, 2))),
		thOth::dateTime::Seconds(boost::lexical_cast<int>(dtStr.substr(16, 2))));

};