//============================================================================
// TwsApi Test
//============================================================================
//#include "TwsApi\TwsApiL0.h"
//#include "TwsApi\TwsApiDefs.h"
#include "TwsApi\wrappers\historicalWrapper.hpp"

#ifndef historical_request
#define historical_request

#include <sqlite\sqlite3.h>

int historicalRequest();

#endif