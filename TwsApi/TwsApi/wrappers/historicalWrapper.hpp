/*

	HistoricalWrapper class is in charge of 
	providing historical data for the user

*/

#ifndef historical_wrapper
#define historical_wrapper

#include "TwsApi\TwsApiL0.h"
#include "TwsApi\TwsApiDefs.h"

#include "thOth/time/timeseries.hpp"

namespace TwsApi {

	struct historicalQuoteDetails {

		TickerId id_;
		double open_;
		double high_;
		double low_;
		double close_;
		int volume_;
		int barCount_;
		double WAP_;
		int hasGaps_;

	};

}

class historicalWrapper : public EWrapperL0
{

public:

	historicalWrapper(bool CalledFromThread = true);								// ctor
	historicalWrapper(const historicalWrapper &);									// copy ctor
	~historicalWrapper(){};															

	historicalWrapper & operator =(const historicalWrapper &);						// assignement operator

	// EWrapperL0 implementation
	virtual void winError(const IBString& str,										// posix implementation never calls win error
						  int lastError);

	virtual void error(const int id, 
					   const int errorCode, 
					   const IBString errorString);

	virtual void historicalData(TickerId reqId, const IBString& date,
								double open, double high, double low,
								double close, int volume, int barCount,
								double WAP, int hasGaps);

	// accessors
	bool endOfHistoricalData() const { return endOfHistoricalData_; };				// end of data (public ?)
	bool errorForRequest() const { return errorForRequest_; };						// error
	thOth::TimeSeries<TwsApi::historicalQuoteDetails> timeSeries() const{			// the time series
		return ts_; };		

protected:

	// parse a date string into some dateTime
	thOth::dateTime convertDateTime(const IBString &) const;

protected:

	bool endOfHistoricalData_;
	bool errorForRequest_;
	
	thOth::TimeSeries<TwsApi::historicalQuoteDetails> ts_;							// timeseries object

};

#endif
