#include "testFunctions/historicalRequest.hpp"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	//int i;
	//for (i = 0; i<argc; i++){
	//	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	//}
	//printf("\n");
	return 0;
}

int historicalRequest()
{

	Contract			C;											// contract over a currency pair
	C.symbol = "EUR";												// EUR
	C.secType = "CASH";												//"CASH"
	C.currency = "USD";												// USD
	C.exchange = *TwsApi::Exchange::IDEALPRO;						//"IDEALPRO";
	C.primaryExchange = "";


	IBString EDT = TwsApi::EndDateTime(2014, 01, 21, 11, 0, 0);		// warning: for IB, this means last day will be 2014, 01, 20 
	IBString DS = TwsApi::DurationStr(200,							// 200 bars requested
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

	thOth::TimeSeries<TwsApi::historicalQuoteDetails> ts = HW.timeSeries();	// get the timeSeries

	// connect to a database
	sqlite3 *db;

	if (sqlite3_open("test.db", &db)) {
	
		std::cout << "can't open database : "
				  << sqlite3_errmsg(db)
				  << std::endl;
	
	};

	// Create SQL table
	char * sql = "CREATE TABLE QUOTE_TABLE("  \
		"QUOTE_ID         BIGINT  PRIMARY KEY NOT NULL," \
		"QUOTE_TIME       DATETIME            NOT NULL," \
		"QUOTE_INSTRUMENT INT                 NOT NULL," \
		"QUOTE_TYPE       TINYINT             NOT NULL," \
		"QUOTE_OPEN       REAL                NOT NULL," \
		"QUOTE_HIGH       REAL                        ," \
		"QUOTE_LOW        REAL                        ," \
		"QUOTE_CLOSE      REAL                        ," \
		"VOLUME           BIGINT                       );";

	// error message
	char *zErrMsg = 0;

	// Execute SQL statement

	if (sqlite3_exec(db, sql, callback, 0, &zErrMsg) != SQLITE_OK) {

		std::cout << "table creation error : "
			<< zErrMsg
			<< std::endl;

		sqlite3_free(zErrMsg);

	};

	sqlite3_close(db);

	// simple data manipulation
	for (thOth::TimeSeries<TwsApi::historicalQuoteDetails>::const_iterator It = ts.cbegin(); It != ts.cend(); It++)
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
