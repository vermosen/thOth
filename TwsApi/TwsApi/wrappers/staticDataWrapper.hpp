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

	struct quoteDetails {

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

class staticDataWrapper : public EWrapperL0
{

public:

	staticDataWrapper(bool CalledFromThread = true);								// ctor
	staticDataWrapper(const staticDataWrapper &);									// copy ctor
	~staticDataWrapper(){};

	staticDataWrapper & operator =(const staticDataWrapper &);						// assignement operator

	// EWrapperL0 implementation
	virtual void winError(const IBString& str,										// posix implementation never calls win error
		int lastError);

	virtual void error(const int id,
		const int errorCode,
		const IBString errorString);

	// accessors
	bool errorForRequest() const { return errorForRequest_; };						// error

protected:

	bool errorForRequest_;

};

#endif
