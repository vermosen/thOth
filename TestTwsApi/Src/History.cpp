//============================================================================
// TwsApi Test
//============================================================================
#include "TwsApiL0.h"
#include "TwsApiDefs.h"
using namespace TwsApi;

bool EndOfHistoricalData	= false;
bool ErrorForRequest		= false;

//----------------------------------------------------------------------------
// MyEWrapper
//----------------------------------------------------------------------------
class MyEWrapper: public EWrapperL0
{
	public:

	MyEWrapper( bool CalledFromThread = true ) : EWrapperL0( CalledFromThread ) {}

	virtual void winError( const IBString& str, int lastError )
	{
		fprintf( stderr, "WinError: %d = %s\n", lastError, (const char*)str );
		ErrorForRequest = true;
	}

	virtual void error( const int id, const int errorCode, const IBString errorString )
	{
		fprintf( stderr, "Error for id=%d: %d = %s\n", id, errorCode, (const char*)errorString );
		ErrorForRequest = (id > 0);
		// id == -1 are 'system' messages, not for user requests
		// as a test, set year to 2010 in the reqHistoricalData
	}

	virtual void historicalData( TickerId reqId, const IBString& date, double open, double high, double low, double close, int volume, int barCount, double WAP, int hasGaps )
	{
		if( IsEndOfHistoricalData(date) )
		{
			EndOfHistoricalData = true;
			return;
		}

		fprintf( stdout, "%10s, %5.3f, %5.3f, %5.3f, %5.3f, %7d\n", (const char*)date, open, high, low, close, volume );
	}

};


//----------------------------------------------------------------------------
// DUMP_DEFS
// Dumps the list of valid values for type T1##T2
// T1 and T2 because the way preprocessor operator ## is defined
//----------------------------------------------------------------------------
// The iterator has a similar interface as the of the std::map
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
int main( int argc, const char* argv[] )
{
	Contract			C;
	C.symbol			= "EUR";
	C.secType			= "CASH";		//"CASH"
	C.currency			= "USD";
	C.exchange			= *Exchange::IDEALPRO;	//"SMART";
	C.primaryExchange	= "";


	IBString EDT		= EndDateTime(2014, 01, 20, 0, 0, 0);	// Attention: for IB, this means last day will be 2013,02,19 
	IBString DS			= DurationStr(5, *DurationHorizon::Days);
	IBString BSS		= *BarSizeSetting::_5_mins;
	IBString WTS		= *WhatToShow::BID;

	if( argc > 1 )
	{
		if( argc < 8 )
		{
			printf	( "args are: symbol  end-date  duration  barsize  what-to-show.\n"
					  "     i.e. EUR    20140120  1 M       1 day    TRADES\n"
					);
			return 1;
		}
		
		C.symbol	= argv[1];
		EDT			= argv[2];

		CHECK_VAR( Duration, Horizon, argv[4] ) // DurationHorizon
			DS		= DurationStr(atoi(argv[3]), argv[4] );

		IBString bss = argv[5]; bss = bss + " " + argv[6];
		CHECK_VAR( BarSize, Setting, (const char*)bss )	// BarSizeSetting
			BSS		= bss;

		CHECK_VAR( WhatTo, Show, argv[7] )	// WhatToShow
			WTS		= argv[7];
	}


	MyEWrapper	MW( false );
	EClientL0*	EC = EClientL0::New( &MW );

	if( EC->eConnect( "", 7496, 100 ) )
	{
		EC->reqHistoricalData
			( 20
			, C
			, EndDateTime(2014,01,20, 0, 0, 0)	// Attention: for IB, this means last day will be 2013,02,19 
			, DS	// DurationStr(1, *DurationHorizon::Days)
			, BSS	// *BarSizeSetting::_10_mins
			, WTS	// *WhatToShow::TRADES
			, UseRTH::AllTradingData
			, FormatDate::AsDate
			);

		while( !EndOfHistoricalData && !ErrorForRequest )
			EC->checkMessages();
	}

	EC->eDisconnect();
	delete EC;

	system("pause");

	return ErrorForRequest;
}
