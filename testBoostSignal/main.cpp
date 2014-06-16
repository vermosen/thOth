// console procedure code snippet

#include <stdio.h>
#include <exception>


#include "sender.hpp"
#include "receiver.hpp"

#include <boost/signals2/signal.hpp>
#include <boost/function.hpp>

int main(int argc, char** argv) {

	try {
	
		sender sd;
		receiver rv;

		// register the signal
		boost::signals2::signal<void(bool)> sign;
		sign.connect(thOth::signal::change.connect(boost::function<void(bool)>(&receiver::update, rv), true));

		// change

	}
	catch (std::exception & e) {

		std::cout
			<< "an error occured: "
			<< std::endl
			<< e.what()
			<< std::endl;

	}
	catch (...) {

		std::cout
			<< "an unknown error occured..."
			<< std::endl;

	}

	system("pause");

}

//// console procedure code snippet
//
//#include <stdio.h>
//#include <exception>
//
//int main(int argc, char** argv) {
//
//	try {
//
//
//
//	}
//	catch (std::exception & e) {
//
//		std::cout
//			<< "an error occured: "
//			<< std::endl
//			<< e.what()
//			<< std::endl;
//
//	}
//	catch (...) {
//
//		std::cout
//			<< "an unknown error occured..."
//			<< std::endl;
//
//	}
//
//	system("pause");
//
//}
