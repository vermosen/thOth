/*
 *
 * Simple csvBuilder class
 * Jean-Mathieu Vermosen
 * copyright, 2013
 *
 */

#include <thOth/utilities/csvBuilder.hpp>

namespace thOth {

	namespace utilities {

		csvBuilder::csvBuilder(													// main ctor
			const std::string & path_, 
			bool overwrite) {

			if (overwrite)

				csvFile_ =
					new std::ofstream(											// truncation mode
						path_.c_str(),
						std::ios::trunc);

			else

				csvFile_ =
					new std::ofstream(											// append mode
						path_.c_str(),
						std::ios::app);

			rMax_ = 0;
			cMax_ = 0;

			csvFile_->precision(6);

		};																

		csvBuilder::~csvBuilder() {

			createFile();

			if (rMax_ * cMax_ > 0) {											// has been previously allocated

				for (Size i = 0; i < rMax_; i++)
					delete[] data_[i];

				delete[] data_;

			}

		};

		csvBuilder & csvBuilder::operator = (const csvBuilder & builder) {

			if (&builder != this) {

				boost::lock_guard<boost::mutex> dataGuard(dataMutex_);			// lock mutex

				for (Size i = 0; i < rMax_; i++)								// delete old data
					delete[] data_[i];

				delete[] data_;

				rMax_ = builder.rMax_;
				cMax_ = builder.cMax_;

				data_ = new std::string *[rMax_];								// allocate new data

				for (Size i = 0; i < rMax_; i++)
					data_[i] = new std::string[cMax_];

				for (Size i = 0; i < rMax_; i++) {								// data copy

					for (Size j = 0; j < cMax_; j++)
						data_[i][j] = builder.data_[i][j];

				}

			}

			return *this;

		};

		void csvBuilder::add(const std::string & str, Size r1, Size c1) {

			boost::lock_guard<boost::mutex> dataGuard(dataMutex_);				// lock mutex

			if (r1 > rMax_ || c1 > cMax_)										// allocate
				allocate(r1, c1);							

			data_[r1 - 1][c1 - 1] = str;										// update

		};

		void csvBuilder::add(double num, Size r1, Size c1) {

			this->add(boost::lexical_cast<std::string>(num), r1, c1);

		};

		void csvBuilder::add(const cArray & arr, Size r1, Size c1) {
			
			boost::lock_guard<boost::mutex> dataGuard(dataMutex_);				// lock data mutex
			
			if (r1 + arr.size() > rMax_ || c1 > cMax_)							// allocate
				allocate(r1 + arr.size(), c1);

			for (Size i = 0; i < arr.size(); i++)								// copy data
				data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(arr[i]);

		};

		void csvBuilder::add(const cMatrix & mat, Size r1, Size c1) {
			
			boost::lock_guard<boost::mutex> dataGuard(dataMutex_);				// lock data mutex
			
			if (r1 + mat.size1() > rMax_ || c1 + mat.size2() > cMax_)			// allocate
				allocate(r1 + mat.size1(), c1 + mat.size2());

			for (Size i = 0; i < mat.size1(); i++) {							// copy data

				for (Size j = 0; j < mat.size2(); j++)
					data_[r1 + i - 1][c1 + j - 1] = boost::lexical_cast<std::string>(mat(i, j));

			}

		};

		void csvBuilder::add(cTimeSeries & ts, Size r1, Size c1, bool displayDates) {

			Size i = 0;

			boost::lock_guard<boost::mutex> dataGuard(dataMutex_);				// lock data mutex

			if (r1 + ts.nObs() > rMax_ || c1 + displayDates > cMax_)
				allocate(r1 + ts.nObs(), c1 + displayDates);

			if (displayDates) {													// display dates ?

				for (cTimeSeries::iterator It = ts.begin(); It != ts.end(); It++, i++) {

					data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(It->first);
					data_[r1 + i - 1][c1] = boost::lexical_cast<std::string>(It->second);

				}

			}
			else {

				for (cTimeSeries::iterator It = ts.begin(); It != ts.end(); It++, i++)
					data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(It->second);

			}

		};

		void csvBuilder::createFile() {

			boost::lock_guard<boost::mutex> dataGuard(dataMutex_);				// lock data mutex

			for (Size i = 0; i < rMax_; i++) {

				std::string newLine;

				for (Size j = 0; j < cMax_; j++) {

					newLine.append(data_[i][j]);
					newLine.append(";");

				}

				std::replace(newLine.begin(), newLine.end(), '.', ',');			// TODO: use internationalization for format
				*csvFile_ << newLine << std::endl;

			}

			csvFile_->close();

		}

		void csvBuilder::path(const std::string & path_, bool overwrite) {

			delete csvFile_;													// reset pointer count

			if (overwrite)

				csvFile_ =														// truncation mode
					new std::ofstream(											
						path_.c_str(),
						std::ios::trunc);

			else

				csvFile_ =														// append mode
					new std::ofstream(											
						path_.c_str(),
						std::ios::app);

		}

		void csvBuilder::allocate(Size r1, Size c1) {

			std::string ** newData_ = new std::string *[std::max(r1, rMax_)];	// creates a bigger container

			for (Size i = 0; i < std::max(r1, rMax_); i++)
				newData_[i] = new std::string[std::max(c1, cMax_)];

			for (Size i = 0; i < rMax_; i++) {									// copy old data

				for (Size j = 0; j < cMax_; j++)
					newData_[i][j] = data_[i][j];

			}

			if (rMax_ * cMax_ > 0) {											// if prior data has been allocated

				for (Size i = 0; i < rMax_; i++)
					delete[] data_[i];

				delete[] data_;

			}

			data_ = newData_;
			rMax_ = std::max(r1, rMax_);
			cMax_ = std::max(c1, cMax_);

		};
	}
}
