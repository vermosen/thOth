/= == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == =
// TwsApi Test
//============================================================================
#include "TwsApi\TwsApiL0.h"
#include "TwsApi\TwsApiDefs.h"
#include "TwsApi\wrappers\historicalWrapper.hpp"

int staticDataRequest()
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