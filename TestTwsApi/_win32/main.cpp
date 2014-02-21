//============================================================================
// TwsApi Test
//============================================================================
#include "TwsApi/TwsApiL0.h"
#include "TwsApi/TwsApiDefs.h"

#include "testFunctions/dataBaseCreation.hpp"
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

	int i;
	
	std::cout << "welcome to the twsApi test environment"
			  << std::endl
			  << "trying to open local ressources..."
			  << std::endl;

	if (!dataBaseCreation()) {
	
		// do something
	
	};

	for (;;)
	{

		std::cout << "please pick a test amongst the following:"
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
		std::cin.clear();
		std::cin.ignore(10000, '\n');

		switch (i)
		{

		case 1:
			return historicalRequest();

		case 2:
			return staticDataRequest();

		case 3:
			return clientRequest();

		default:
			std::cout << "unknown test, ";
			i = 0;

		};
	}
}
