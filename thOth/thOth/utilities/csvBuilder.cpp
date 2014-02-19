/*
 *
 * kalman filter estimation
 * Jean-Mathieu Vermosen
 * copyright, 2013
 *
 */

#include <thOth/utilities/csvBuilder.hpp>

namespace thOth {

	namespace utilities {

		csvBuilder::csvBuilder(const std::string & path_) :
			csvFile_(path_.c_str(), std::ios::app) {

			rMax_ = 0;
			cMax_ = 0;

			csvFile_.precision(6);

		};

		csvBuilder::csvBuilder(const csvBuilder & builder) {

			rMax_ = builder.rMax_;
			cMax_ = builder.cMax_;
			data_ = new std::string *[rMax_];

			for (long i = 0; i < rMax_; i++)
				data_[i] = new std::string[cMax_];

			for (long i = 0; i < rMax_; i++) {

				for (long j = 0; j < cMax_; j++)
					data_[i][j] = builder.data_[i][j];

			}

		};																				// copy ctor

		csvBuilder::~csvBuilder() {

			createFile();

			if (rMax_ * cMax_ > 0) {													// has been allocated

				for (long i = 0; i < rMax_; i++)
					delete[] data_[i];

				delete[] data_;

			}

		};

		csvBuilder & csvBuilder::operator = (const csvBuilder & builder) {				// assignement operator

			if (&builder != this) return *this;

			for (long i = 0; i < rMax_; i++)											// delete old data
				delete[] data_[i];

			delete[] data_;

			rMax_ = builder.rMax_;
			cMax_ = builder.cMax_;

			data_ = new std::string *[rMax_];											// copy new data

			for (long i = 0; i < rMax_; i++)
				data_[i] = new std::string[cMax_];

			for (long i = 0; i < rMax_; i++) {

				for (long j = 0; j < cMax_; j++)
					data_[i][j] = builder.data_[i][j];

			}

			return *this;

		};

		void csvBuilder::add(const std::string & str, long r1, long c1) {

			if (r1 > rMax_ || c1 > cMax_) resize(r1, c1);								// resize

			data_[r1 - 1][c1 - 1] = str;												// copy data

		};

		void csvBuilder::add(double num, long r1, long c1) {

			this->add(boost::lexical_cast<std::string>(num), r1, c1);

		};




		void csvBuilder::add(const boost::numeric::ublas::vector<double> & arr, long r1, long c1) {
			
			if (r1 + arr.size() > rMax_ || c1 > cMax_)									// resize
				resize(r1 + arr.size(), c1);

			for (thOth::size i = 0; i < arr.size(); i++)								// copy data
				data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(arr[i]);

		};

		void csvBuilder::add(const boost::numeric::ublas::matrix<double> & mat, long r1, long c1) {

			if (r1 + mat.size1() > rMax_ || c1 + mat.size2() > cMax_)					// resize
				resize(r1 + mat.size1(), c1 + mat.size2());

			for (thOth::size i = 0; i < mat.size1(); i++) {							// copy data

				for (thOth::size j = 0; j < mat.size2(); j++)
					data_[r1 + i - 1][c1 + j - 1] = boost::lexical_cast<std::string>(mat(i, j));

			}

		};

		//void csvBuilder::add(const QuantLib::TimeSeries<double> & ts, long r1, long c1, bool displayDates) {

		//	if (r1 + ts.size() > rMax_ || c1 + displayDates > cMax_)					// resize
		//		resize(r1 + ts.size(), c1 + displayDates);

		//	/* copy data */
		//	thOth::size i = 0;

		//	if (displayDates) {

		//		for (thOth::TimeSeries<double>::const_iterator It = ts.begin(); It != ts.end(); It++, i++) {

		//			data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(It->first.serialNumber());
		//			data_[r1 + i - 1][c1] = boost::lexical_cast<std::string>(It->second);

		//		}

		//	}
		//	else {

		//		for (thOth::TimeSeries<double>::const_iterator It = ts.begin(); It != ts.end(); It++, i++) {

		//			data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(It->second);

		//		}

		//	}

		//};

		void csvBuilder::createFile() {

			for (long i = 0; i < rMax_; i++) {

				std::string newLine;

				for (long j = 0; j < cMax_; j++) {

					newLine.append(data_[i][j]);
					newLine.append(";");

				}

				std::replace(newLine.begin(), newLine.end(), '.', ',');					/* translate in US format */
				csvFile_ << newLine << std::endl;

			}

			csvFile_.close();

		};

		void csvBuilder::resize(long r1, long c1) {

			/* create new container */
			std::string ** newData_ = new std::string *[max(r1, rMax_)];

			for (long i = 0; i < max(r1, rMax_); i++)
				newData_[i] = new std::string[max(c1, cMax_)];

			// copy old data
			for (long i = 0; i < rMax_; i++) {

				for (long j = 0; j < cMax_; j++)
					newData_[i][j] = data_[i][j];

			}

			/* if data_ has been allocated */
			if (rMax_ * cMax_ > 0) {

				for (long i = 0; i < rMax_; i++)
					delete[] data_[i];

				delete[] data_;

			}

			data_ = newData_;

			rMax_ = max(r1, rMax_);
			cMax_ = max(c1, cMax_);

		};
	}
}
		
		//
//void to_csv(const QuantLib::Matrix & data, std::string path) {							/* prints the resulted matrix in a .csv */
//
//		std::ofstream myFile(path.c_str(),std::ios::app) ;									/* opens file */
//
//		myFile.precision(6) ;																/* sets precision */
//
//		for (QuantLib::Size i = 0 ; i < data.rows() ; i++) {
//	
//				std::string newLine ;
//
//				for (QuantLib::Size j = 0 ; j < data.columns() ; j++) {
//
//						newLine.append(boost::lexical_cast<std::string>(data[i][j])) ;
//						newLine.append(";") ;
//
//					}
//
//				std::replace(newLine.begin(), newLine.end(), '.', ',') ;					/* translate in US format */
//				myFile << newLine << std::endl ;
//
//			}
//
//		myFile.close() ;
//
//	} ;
//
//void to_csv(const QuantLib::Array & data, std::string path) {								/* prints the resulted array in a .csv */
//
//		std::ofstream myFile(path.c_str(),std::ios::app) ;									/* opens file */
//
//		myFile.precision(6) ;																/* sets precision */
//
//		for (QuantLib::Size i = 0 ; i < data.size() ; i++) {
//	
//				std::string newLine ;
//
//				newLine.append(boost::lexical_cast<std::string>(data[i])) ;
//
//				newLine.append(";") ;
//
//				std::replace(newLine.begin(), newLine.end(), '.', ',') ;					/* translate in US format */
//
//				myFile << newLine << std::endl ;
//
//			}
//
//		myFile.close() ;
//
//	} ;
//
//void to_csv(std::string data, std::string path) {											/* prints the resulted array in a .csv */
//
//		std::ofstream myFile(path.c_str(),std::ios::app) ;									/* opens file */
//
//		myFile.precision(6) ;																/* sets precision */
//
//		data.append(";") ;
//
//		std::replace(data.begin(), data.end(), '.', ',') ;								/* translate in US format */
//
//		myFile << data << std::endl ;
//
//		myFile.close() ;
//
//	} ;
//
//void to_csv(const QuantLib::TimeSeries<double> & data, std::string path) {
//
//		std::ofstream myFile(path.c_str(),std::ios::app) ;									/* opens file */
//
//		myFile.precision(6) ;																/* sets precision */
//
//		for (QuantLib::TimeSeries<double>::const_iterator It = data.cbegin() ; It != data.cend() ; It++) {
//	
//				std::string newLine ;
//
//				newLine.append(boost::lexical_cast<std::string>(It->first.serialNumber())) ;
//
//				newLine.append(";") ;
//
//				newLine.append(boost::lexical_cast<std::string>(It->second)) ;
//
//				newLine.append(";") ;
//
//				std::replace(newLine.begin(), newLine.end(), '.', ',') ;					/* translate in US format */
//
//				myFile << newLine << std::endl ;
//
//			}
//
//		myFile.close() ;
//
//	} ;

