// Name: Chris Pinkney
// Seneca Student ID: 044477149
// Seneca email: cpinkney@myseneca.ca
// Date of completion: 16-Nov-19
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <string>
#include <iomanip>

class Utilities {
private:
	static size_t m_widthField;
	static char m_delimiter;
public:
	void setFieldWidth(size_t);
	size_t getFieldWidth() const;
	
	//size_t getMaxFieldWidth() const;
	//void setMaxFieldWidth(size_t);
	
	const std::string extractToken(const std::string&, size_t&, bool&);
	
	static void setDelimiter(const char);
	const char getDelimiter() const;
};

#endif