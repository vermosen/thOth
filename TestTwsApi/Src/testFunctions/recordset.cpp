#include "recordset.hpp"

recordset::recordset()
{
}

recordset::recordset(const recordset & o)
{
	data_ = o.data_;							// copy data
}

recordset::~recordset()
{
}

int recordset::callback(void *NotUsed, 
					    int argc, 
						char **argv, 
						char **azColName)
{
	for (int i = 0; i<argc; i++)
		data_.push_back("");
	
	return 0;
}