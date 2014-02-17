/* stl headers */
#include <fstream>
#include <iostream>
#include <string>

/* boost headers */
#include <boost/lexical_cast.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>

// thOth headers
#include "thOth/time/timeseries.hpp"

namespace thOth {

	namespace utilities {

		class csvBuilder {

		public:

			csvBuilder(const std::string &);

			csvBuilder(const csvBuilder &);

			~csvBuilder();

			csvBuilder & operator = (const csvBuilder &);

			// TODO : templatize using ostream operator, but might be tricky...
			void add(const boost::numeric::ublas::matrix<double> &, long r1, long c1);
			void add(const boost::numeric::ublas::vector<double> &, long r1, long c1);
			void add(const std::string &, long r1, long c1);
			void add(double, long r1, long c1);

			//void add(const thOth::TimeSeries<T> &, long r1, long c1, bool displayDates = false);

		private:

			void createFile();
			void resize(long r1, long c1);

			std::ofstream csvFile_;
			std::string ** data_;
			long rMax_;
			long cMax_;

		};
	}
}