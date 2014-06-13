// console procedure code snippet

#include <stdio.h>
#include <exception>

#include <boost/signals2.hpp>

int main(int argc, char** argv) {

	try {
	
		boost::signals2::signal<...> sig();

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
