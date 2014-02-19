//============================================================================
// TwsApi Test
//============================================================================
#include "TwsApi\TwsApiL0.h"
#include "TwsApi\TwsApiDefs.h"

#include "testFunctions/historicalRequest.hpp"
#include "testFunctions/staticDataRequest.hpp"
#include "testFunctions/clientRequest.hpp"

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

	int i, res;

	std::cout << "welcome to the twsApi test environment"
		<< std::endl
		<< "please pick a test amongst the following:"
		<< std::endl
		<< "1 - historical request"
		<< std::endl
		<< "2 - static data request"
		<< std::endl
		<< "3 - client request"
		<< std::endl
		<< "-----------------------"
		<< std::endl;

	std::cin >> i;

	switch (i)
	{
	case 1:
		return historicalRequest();
		break;
	case 2:
		return staticDataRequest();
		break;
	case 3:
		return clientRequest();
	default:
		std::cout << "unknown test, aborting program...";
		return 0;
	};

}
