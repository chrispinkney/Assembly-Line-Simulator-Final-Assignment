// Name: Chris Pinkney
// Seneca Student ID: 044477149
// Seneca email: cpinkney@myseneca.ca
// Date of completion: 17-Nov-19
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Utilities.h"

class Item {
private:
	std::string m_name;
	std::string m_description;
	unsigned int m_serialNumber;
	unsigned int m_quantity;
	static size_t m_widthField;
	Utilities m_utilities;
public:
	Item();
	Item(const std::string&);

	const std::string& getName() const;
	void setName(std::string);

	const std::string& getDescription() const;
	void setDescription(std::string);

	const unsigned int getSerialNumber();
	const unsigned int getSerialNumber() const;
	void setSerialNumber(unsigned int);

	const unsigned int getQuantity();
	const unsigned int getQuantity() const;
	void setQuantity(unsigned int);

	void updateQuantity();

	void setWidthField(size_t);
	const size_t getWidthField() const;

	void display(std::ostream&, bool) const;
};

#endif