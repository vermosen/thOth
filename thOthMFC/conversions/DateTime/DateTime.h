#pragma once
#include "stdafx.h"
#include <thOth/time/DateTime.hpp>

// conversion functions for MFC
namespace thOth{

	dateTime dateTimeConversion(const TIMESTAMP_STRUCT&);
	dateTime dateTimeConversion(const LPSYSTEMTIME &);

};
