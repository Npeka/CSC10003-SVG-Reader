#ifndef HEADER_H
#define HEADER_H

// C++ library
#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>
/*


*/
// Transform type <class Figure>
#define Translate 1
#define Rotate 2
#define Scale 3
/*


*/
// Exception
#define tag(figure) "<" << figure << ">"
#define check_exeption(figure, attribute, code) \
	try { code; } \
	catch (const std::invalid_argument& e) { \
		cerr << tag(figure) << '\n'; \
		cerr << tag(attribute) << " : " << e.what() << '\n'; \
	} \
	catch (const std::out_of_range& e) { \
		cerr << tag(figure) << '\n'; \
		cerr << tag(attribute) << " : " << e.what() << '\n'; \
	} \
	catch (...) { \
		cerr << tag(figure); \
		cerr << tag(attribute) << " : An unknown exception occurred.\n"; \
	}
/*


*/
// namespace
using namespace std;

#endif // !HEADER_H