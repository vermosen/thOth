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
			csvFile_(
			new std::ofstream(
			path_.c_str(),
			std::ios::app)) {

			rMax_ = 0;
			cMax_ = 0;

			csvFile_->precision(6);

		};

		csvBuilder::csvBuilder(const csvBuilder & builder) {

			rMax_ = builder.rMax_;
			cMax_ = builder.cMax_;
			data_ = new std::string *[rMax_];

			for (Size i = 0; i < rMax_; i++)
				data_[i] = new std::string[cMax_];

			for (Size i = 0; i < rMax_; i++) {

				for (Size j = 0; j < cMax_; j++)
					data_[i][j] = builder.data_[i][j];

			}

		};																				/* copy ctor */

		csvBuilder::~csvBuilder() {

			createFile();

			/* it has been allocated */
			if (rMax_ * cMax_ > 0) {

				for (Size i = 0; i < rMax_; i++)
					delete[] data_[i];

				delete[] data_;

			}

		};

		csvBuilder & csvBuilder::operator = (const csvBuilder & builder) {

			if (&builder != this) return *this;

			/* delete old data */
			for (Size i = 0; i < rMax_; i++)
				delete[] data_[i];

			delete[] data_;

			rMax_ = builder.rMax_;
			cMax_ = builder.cMax_;

			/* copy new data */
			data_ = new std::string *[rMax_];

			for (Size i = 0; i < rMax_; i++)
				data_[i] = new std::string[cMax_];

			for (Size i = 0; i < rMax_; i++) {

				for (Size j = 0; j < cMax_; j++)
					data_[i][j] = builder.data_[i][j];

			}

			return *this;

		};

		void csvBuilder::add(const std::string & str, Size r1, Size c1) {

			/* resize */
			if (r1 > rMax_ || c1 > cMax_) resize(r1, c1);

			/* copy data */
			data_[r1 - 1][c1 - 1] = str;

		};

		void csvBuilder::add(double num, Size r1, Size c1) {

			this->add(boost::lexical_cast<std::string>(num), r1, c1);

		};

		void csvBuilder::add(const cArray & arr, Size r1, Size c1) {

			/* resize */
			if (r1 + arr.size() > rMax_ || c1 > cMax_) resize(r1 + arr.size(), c1);

			/* copy data */
			for (Size i = 0; i < arr.size(); i++)
				data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(arr[i]);

		};

		void csvBuilder::add(const cMatrix & mat, Size r1, Size c1) {

			/* resize */
			if (r1 + mat.size1() > rMax_ || c1 + mat.size2() > cMax_)
				resize(r1 + mat.size1(), c1 + mat.size2());

			/* copy data */
			for (Size i = 0; i < mat.size1(); i++) {

				for (Size j = 0; j < mat.size2(); j++)
					data_[r1 + i - 1][c1 + j - 1] = boost::lexical_cast<std::string>(mat(i, j));

			}

		};

		void csvBuilder::add(const cTimeSeries & ts, Size r1, Size c1, bool displayDates) {

			/* resize */
			if (r1 + ts.size() > rMax_ || c1 + displayDates > cMax_) resize(r1 + ts.size(), c1 + displayDates);

			/* copy data */
			Size i = 0;

			if (displayDates) {

				for (cTimeSeries::const_iterator It = ts.begin(); It != ts.end(); It++, i++) {

					data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(It->first);
					data_[r1 + i - 1][c1] = boost::lexical_cast<std::string>(It->second);

				}

			}
			else {

				for (cTimeSeries::const_iterator It = ts.begin(); It != ts.end(); It++, i++) {

					data_[r1 + i - 1][c1 - 1] = boost::lexical_cast<std::string>(It->second);

				}

			}

		};

		void csvBuilder::createFile() {

			for (Size i = 0; i < rMax_; i++) {

				std::string newLine;

				for (Size j = 0; j < cMax_; j++) {

					newLine.append(data_[i][j]);
					newLine.append(";");

				}

				std::replace(newLine.begin(), newLine.end(), '.', ',');				// TODO: use internationalization for format
				*csvFile_ << newLine << std::endl;

			}

			csvFile_->close();

		};

		void csvBuilder::setPath(std::string & path_) {

			csvFile_.reset();														// reset pointer count

			csvFile_ = std::shared_ptr<std::ofstream>(								// new ofstream
				new std::ofstream(
				path_.c_str(),
				std::ios::app));

		}

		void csvBuilder::resize(Size r1, Size c1) {

			/* create new container */
			std::string ** newData_ = new std::string *[std::max(r1, rMax_)];

			for (Size i = 0; i < std::max(r1, rMax_); i++)
				newData_[i] = new std::string[std::max(c1, cMax_)];

			// copy old data
			for (Size i = 0; i < rMax_; i++) {

				for (Size j = 0; j < cMax_; j++)
					newData_[i][j] = data_[i][j];

			}

			/* if data_ has been allocated */
			if (rMax_ * cMax_ > 0) {

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