/*
 *
 * kalman filter estimation
 * Jean-Mathieu Vermosen
 * copyright, 2013
 *
 */

#include <ql/utilities/csvBuilder.hpp>

namespace QuantLib {

	namespace detail {

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

		};																				/* copy ctor */

		csvBuilder::~csvBuilder() {

			createFile();

			/* it has been allocated */
			if (rMax_ * cMax_ > 0) {

				for (long i = 0; i < rMax_; i++)
					delete[] data_[i];

				delete[] data_;

			}

		};

		csvBuilder & csvBuilder::operator = (const csvBuilder & builder) {

			if (&builder != this) return *this;

			/* delete old data */
			for (long i = 0; i < rMax_; i++)
				delete[] data_[i];

			delete[] data_;

			rMax_ = builder.rMax_;
			cMax_ = builder.cMax_;

			/* copy new data */
			data_ = new std::string *[rMax_];

			for (long i = 0; i < rMax_; i++)
				data_[i] = new std::string[cMax_];

			for (long i = 0; i < rMax_; i++) {

				for (long j = 0; j < cMax_; j++)
					data_[i][j] = builder.data_[i][j];

			}

			return *this;

		};

		void csvBuilder::add(const std::string & str, long r1, long c1) {

			/* resize */
			if (r1 > rMax_ || c1 > cMax_) resize(r1, c1);

			/* copy data */
			data_[r1 - 1][c1 - 1] = str;

		};

		void csvBuilder::add(double num, long r1, long c1) {

			this->add(boost::lexical_cast<std::string>(num), r1, c1);

		};




		void csvBuilder::add(const QuantLib::Array & arr, long r1, long c1) {

			/* resize */
			if (r1 + arr.size() > rMax_ || c1 > cMax_) resize(r1 + arr.size(), c1);

			/* copy data */
			for (QuantLib::Size i = 0; i < arr.size(); i++)
				data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(arr[i]);

		};

		void csvBuilder::add(const QuantLib::Matrix & mat, long r1, long c1) {

			/* resize */
			if (r1 + mat.rows() > rMax_ || c1 + mat.columns() > cMax_)
				resize(r1 + mat.rows(), c1 + mat.columns());

			/* copy data */
			for (QuantLib::Size i = 0; i < mat.rows(); i++) {

				for (QuantLib::Size j = 0; j < mat.columns(); j++)
					data_[r1 + i - 1][c1 + j - 1] = boost::lexical_cast<std::string>(mat[i][j]);

			}

		};

		void csvBuilder::add(const QuantLib::TimeSeries<double> & ts, long r1, long c1, bool displayDates) {

			/* resize */
			if (r1 + ts.size() > rMax_ || c1 + displayDates > cMax_) resize(r1 + ts.size(), c1 + displayDates);

			/* copy data */
			QuantLib::Size i = 0;

			if (displayDates) {

				for (QuantLib::TimeSeries<double>::const_iterator It = ts.begin(); It != ts.end(); It++, i++) {

					data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(It->first.serialNumber());
					data_[r1 + i - 1][c1] = boost::lexical_cast<std::string>(It->second);

				}

			}
			else {

				for (QuantLib::TimeSeries<double>::const_iterator It = ts.begin(); It != ts.end(); It++, i++) {

					data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(It->second);

				}

			}

		};

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
			std::string ** newData_ = new std::string *[std::max(r1, rMax_)];

			for (long i = 0; i < std::max(r1, rMax_); i++)
				newData_[i] = new std::string[std::max(c1, cMax_)];

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

			rMax_ = std::max(r1, rMax_);
			cMax_ = std::max(c1, cMax_);

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

