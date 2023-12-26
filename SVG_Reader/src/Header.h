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
#include <locale>
#include <codecvt>
#include <cmath>
#include <unordered_map>
#include <limits>
#include <tuple>
//-------------END-OF-DECLARATION------------//
/*



*/
// Transform type <class Figure>
#define SVG_Translate 1
#define SVG_Rotate 2
#define SVG_Scale 3
// type <class Figure>

//-------------END-OF-DECLARATION------------//
/*



*/
// Define shorter code
#define tag(figure) "<" << figure << ">"
#define check_exception(figure, attribute, code) \
	try { code; } \
	catch (const std::invalid_argument& e) { \
		std::cerr << tag(figure) << '\n'; \
		std::cerr << tag(attribute) << " : " << e.what() << '\n'; \
	} \
	catch (const std::out_of_range& e) { \
		std::cerr << tag(figure) << '\n'; \
		std::cerr << tag(attribute) << " : " << e.what() << '\n'; \
	} \
	catch (...) { \
		std::cerr << tag(figure); \
		std::cerr << tag(attribute) << " : An unknown exception occurred.\n"; \
	}
#define COMMA_TO_SPACE(line) \
    do { \
        std::replace(line.begin(), line.end(), ',', ' '); \
    } while(0)
//-------------END-OF-DECLARATION------------//
/*



*/
// namespace
//using namespace std;

#endif // !HEADER_H