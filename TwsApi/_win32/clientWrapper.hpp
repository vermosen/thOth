/*

	clientWrapper class provides
	real-time quotes

*/

#ifndef client_wrapper
#define client_wrapper

#include "TwsApi\TwsApiL0.h"
#include "TwsApi\TwsApiDefs.h"

namespace TwsApi {

	struct realTimeQuoteDetails {

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

class clientWrapper : public EWrapperL0
{

public:

	clientWrapper(bool CalledFromThread = true);									// ctor
	clientWrapper(const clientWrapper &);											// copy ctor
	~clientWrapper(){};

	clientWrapper & operator =(const clientWrapper &);								// assignement operator

	// EWrapperL0 implementation
	virtual void winError(const IBString& str,										// posix implementation never calls win error
		int lastError);

	virtual void error(const int id,
		const int errorCode,
		const IBString errorString);

	virtual void tickPrice(TickerId tickerId,
		TickType field,
		double price,
		int canAutoExecute);

	virtual void marketDataType(TickerId reqId, int marketDataType);

	// accessors
	bool errorForRequest() const { return errorForRequest_; };						// error

protected:

	bool errorForRequest_;
	int marketDataType_;

};

#endif
