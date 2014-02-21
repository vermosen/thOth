#include "testFunctions/databasecreation.hpp"

// callback function
static int callback(void *NotUsed, int argc, char **argv, char **azColName){
	int i;
	for (i = 0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int dataBaseCreation()
{

	try
	{

	sqlite3 *db;

	if (sqlite3_open("test.db", &db)) {

		throw std::exception("The database cannot be oppened");

	};

	// get the table list of the database
	char * tableReq = "SELECT name FROM sqlite_master WHERE type='table';";

	RJM_SQLite_Resultset *pRS = NULL;
	printf("Checking if table exists\n");
	pRS = SQL_Execute("SELECT name FROM sqlite_master " +
		"WHERE type='table' and name='simple_table';", l_sql_db);

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
	return 1;


	}
	catch (std::exception & e)
	{

		std::cout << "an error occured : " 
				  << e.what()
				  << std::endl;
		return 0;

	}
	catch (...)
	{
	
		std::cout << "an unknown error occured..."
				  << std::endl;
	
	}

}
