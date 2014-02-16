//============================================================================
// TwsApi Test
//============================================================================
#include "TwsApiL0.h"
#include "TwsApiDefs.h"

#include "historicalWrapper.hpp"

//----------------------------------------------------------------------------
// DUMP_DEFS
// Dumps the list of valid values for type T1##T2
// T1 and T2 because the way preprocessor operator ## is defined
//----------------------------------------------------------------------------
// The iterator has a similar interface as the std::map
#define DUMP_DEFS( T1, T2 ) \
	for( T1##T2::iterator i = T1##T2::begin(); i != T1##T2::end(); ++i ) { \
	printf( "\'%s\'\n", i->second ); }

//----------------------------------------------------------------------------
// ARGV
// Checks whether V is valid value for type T1##T2, and if not, prints the
// valid values via DUMP_DEFS
// T1 and T2 because the way preprocessor operator ## is defined
//----------------------------------------------------------------------------
#define CHECK_VAR( T1, T2, V ) {\
	T1##T2::ENUMS e; \
	if( !(e *= V) ) { \
	printf("Argument %s unrecognised for %s, following are valid value\n", V, #T1#T2); \
	DUMP_DEFS( T1, T2 ) \
	return 0; \
	} }


//----------------------------------------------------------------------------
// main
//----------------------------------------------------------------------------
int main()
{

	Contract			C;											// contract over a currency pair
	C.symbol = "EUR";												// EUR
	C.secType = "CASH";												//"CASH"
	C.currency = "USD";												// USD
	C.exchange = *TwsApi::Exchange::IDEALPRO;						//"IDEALPRO";
	C.primaryExchange = "";


	IBString EDT = TwsApi::EndDateTime(2014, 01, 21, 11, 0, 0);		// warning: for IB, this means last day will be 2014, 01, 20 
	IBString DS = TwsApi::DurationStr(2000,							// 200 seconds requested
		*TwsApi::DurationHorizon::Seconds);
	IBString BSS = *TwsApi::BarSizeSetting::_1_sec;					// bar size : 1 sec
	IBString WTS = *TwsApi::WhatToShow::BID;						// request : bid

	// creates  wrapper and client
	historicalWrapper HW(false);
	EClient* EC = EClientL0::New(&HW);

	if (EC->eConnect("", 7496, 100))
	{

		EC->reqHistoricalData										// request
			(20, C, EDT, DS
			, BSS, WTS
			, TwsApi::UseRTH::AllTradingData
			, TwsApi::FormatDate::AsDate);

		while (!HW.endOfHistoricalData() && !HW.errorForRequest())
			EC->checkMessages();

	}

	EC->eDisconnect();

	thOth::TimeSeries<TwsApi::quoteDetails> ts = HW.timeSeries();	// get the timeSeries

	// simple data manipulation
	for (thOth::TimeSeries<TwsApi::quoteDetails>::const_iterator It = ts.cbegin(); It != ts.cend(); It++)
	{

		std::cout << "quote date is: " 
				  << It->first 
				  << ", medium value is: " 
				  << ((It->second.high_ + It->second.low_) / 2) << std::endl;

	}

	delete EC;						

	system("pause");

	return HW.errorForRequest();
}
