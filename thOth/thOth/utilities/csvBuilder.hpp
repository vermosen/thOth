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
#include <iostream>
#include <string>
#include <memory>

// boost headers
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

// thOth headers
#include <thOth/time/TimeSeries.hpp>

// prints a set of strings in a .csv
// TODO : 1 - internationalization
//        2 - limit check
namespace thOth {

	namespace utilities {

		class csvBuilder {

		public:

			typedef boost::numeric::ublas::matrix<double> cMatrix;
			typedef boost::numeric::ublas::vector<double> cArray ;
			typedef TimeSeries<double> cTimeSeries;
			typedef size Size;

			csvBuilder(const std::string &);
			csvBuilder(const csvBuilder & );

			~csvBuilder();

			csvBuilder & operator = (const csvBuilder &);

			void add(const cMatrix &, Size r1, Size c1);
			void add(const cArray &, Size r1, Size c1);
			void add(const std::string &, Size r1, Size c1);
			void add(double, Size r1, Size c1);
			void add(const cTimeSeries &, Size r1, Size c1, bool displayDates = false);

			void push_back(const std::string &);						// simple push_back method for log

			template<class T>
			void add(const std::vector<T> & arr, Size r1, Size c1){

				if (r1 + arr.size() > rMax_ || c1 > cMax_)				// resize
					resize(r1 + arr.size(), c1);

				for (Size i = 0; i < arr.size(); i++)					// try to cast data
					data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(arr[i]);

			};

			void csvBuilder::path(const std::string & path_);			// set the current path

		private:

			csvBuilder() {};											// private default ctor

			void createFile()			 ;
			void resize(Size r1, Size c1);
			void path(std::string & path);								// set a new path for the file

			std::shared_ptr<std::ofstream> csvFile_;
			std::string **				   data_   ;
			Size						   rMax_   ;
			Size						   cMax_   ;

		};
	}
}

#endif