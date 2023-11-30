#ifndef HEADER_H
#define HEADER_H

// C++ library
#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
//-------------END-OF-DECLARATION------------//
/*



*/
// Transform type <class Figure>
#define Translate 1
#define Rotate 2
#define Scale 3
//-------------END-OF-DECLARATION------------//
/*



*/
// Define shorter code
#define tag(figure) "<" << figure << ">"
#define check_exception(figure, attribute, code) \
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
#define CONVERT(T, figure) static_cast<T>(figure)
#define ISVALID(T, figure) dynamic_cast<T>(figure)
#define COMMA_TO_SPACE(line) \
    do { \
        std::replace(line.begin(), line.end(), ',', ' '); \
    } while(0)
//-------------END-OF-DECLARATION------------//
/*



*/
// namespace
using namespace std;

#endif // !HEADER_H