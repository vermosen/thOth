/*
 *
 * Simple recodset class
 *
 */

#include <vector>
#include <string>

#ifndef test_recordset
#define test_recordset

class recordset {

public:

	recordset();
	recordset(const recordset &);
	~recordset();
	
	recordset & operator =(const recordset &);

protected:

	// callback function
	int callback(void *NotUsed, int argc, char **argv, char **azColName);

	std::vector<std::string> data_;

};

#endif