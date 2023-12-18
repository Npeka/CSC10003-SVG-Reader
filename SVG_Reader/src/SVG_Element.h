#ifndef SVG_ELEMENT_H
#define SVG_ELEMENT_H

#include "Header.h"

class SVG_Element {
private:
	static std::unordered_map<string, SVG_Element*> id_map;

protected:
	string id;

public:
	SVG_Element();
	virtual ~SVG_Element() = default;
	void setID(const string& id);
	string getID() const;
	SVG_Element* findGlobalElement(const string& id);
	void parseElementAttributes(string& line);
	
	// Virtual method
	virtual void setElementAttributes(const string& attribute, string& value) = 0;
};

#endif // !SVG_ELEMENT_H