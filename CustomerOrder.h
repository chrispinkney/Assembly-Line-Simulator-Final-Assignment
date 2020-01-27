// Name: Chris Pinkney
// Seneca Student ID: 044477149
// Seneca email: cpinkney@myseneca.ca
// Date of completion: 20-Nov-19
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef CUSTOMERORDER_H
#define CUSTOMERORDER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <utility>
#include "Item.h"
#include "Utilities.h"

struct ItemInfo {
	std::string m_itemName;
	unsigned int m_serialNumber = 0;
	bool m_fillState = false;

	ItemInfo(std::string src) : m_itemName(src) {};
};

class CustomerOrder {
private:
	std::string m_name;
	std::string m_product;
	unsigned int m_cntItem;
	ItemInfo** m_lstItem;
	static size_t m_widthField;
	Utilities m_utility;
public:
	CustomerOrder();
	CustomerOrder(const std::string&);
	~CustomerOrder();
	CustomerOrder(CustomerOrder&);
	CustomerOrder& operator=(const CustomerOrder&) = delete;
	CustomerOrder(CustomerOrder&&) noexcept;
	CustomerOrder& operator=(CustomerOrder&&);
	
	const std::string& getName() const;
	void setName(std::string);

	const std::string& getProduct() const;
	void setProduct(std::string);

	const unsigned int getCount() const;
	void setCount(const std::string&);

	void setWidthField(size_t);
	const size_t getWidthField() const;

	bool getItemFillState(std::string) const;
	bool getOrderFillState() const;

	void fillItem(Item&, std::ostream&);

	void display(std::ostream&) const;
};

#endif // !CUSTOMERORDER_H