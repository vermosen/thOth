/*
 * This class allows one to issue a csv file
 * by passing various object to the builder.
 * At this stage, there is no safety mecanism
 * implemented and the user has to take care 
 * about the current file size
 */

#ifndef thoth_csv_builder_hpp
#define thoth_csv_builder_hpp

// stl headers
#include <fstream>

// boost headers
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/thread/mutex.hpp>

// thOth headers
#include <thOth/time/timeSeries.hpp>

namespace thOth {

	namespace utilities {

		// prints a set of strings in a .csv
		// TODO : 1 - internationalization for .csv format
		//        2 - limit check for data size
		//		  3 - command to purge existing file
		//        4 - date conversion into excel format
		//        5 - replace with a list
		class csvBuilder {

		public:

			typedef boost::numeric::ublas::matrix<double> cMatrix;
			typedef boost::numeric::ublas::vector<double> cArray ;
			typedef timeSeries<thOth::dateTime, double> cTimeSeries;
			typedef size Size;

			// C++11 enabled ?
			#if __cplusplus > 199711L

			csvBuilder() = delete;										// no default ctor
			csvBuilder(const csvBuilder &) = delete;					// no copy ctor 

			#endif

			csvBuilder(const std::string &,								// specifies the file path
					   bool overwrite = false);							// default to append mode

			virtual ~csvBuilder();										// virtual destructor

			csvBuilder & operator = (const csvBuilder &);				// assignement operator

			void add(const cMatrix &, Size r1, Size c1);
			void add(const cArray &, Size r1, Size c1);
			void add(const std::string &, Size r1, Size c1);
			void add(double, Size r1, Size c1);
			void add(cTimeSeries &, Size r1, Size c1, bool displayDates = false);

			template<class T>
			void add(const std::vector<T> & arr, Size r1, Size c1) {	// generic vector<T>

				for (Size i = 0; i < arr.size(); i++)					// calls the right add() function
					add(arr[i], r1 + i, c1);

			};

			void path(const std::string & path_,						// set another path
					  bool overwrite = false);						

			void allocate(Size r1, Size r2);							// pre-allocate a given range

		protected:

			void createFile()			 ;
			void path(std::string & path);								// set a new path for the file

			std::ofstream * csvFile_;
			std::string **  data_   ;
			Size	        rMax_   ;
			Size		    cMax_   ;

			boost::mutex dataMutex_;									// mutex to lock/unlock for data modification

		};
	}
}

#endif
