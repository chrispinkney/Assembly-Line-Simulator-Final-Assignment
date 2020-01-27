#include "Item.h"
#include "Utilities.h"

size_t Item::m_widthField { 1 };

Item::Item() {
	m_name = { "" };
	m_description = { "" };
	m_serialNumber = { 0 };
	m_quantity = { 0 };
}

Item::Item(const std::string& record) {
	bool more;
	size_t pos { 0 };

	try {
		setName(m_utilities.extractToken(record, pos, more));
		setSerialNumber(std::stoul(m_utilities.extractToken(record, ++pos, more)));
		setQuantity(std::stoul(m_utilities.extractToken(record, ++pos, more)));
		setDescription(m_utilities.extractToken(record, ++pos, more));
		if (m_utilities.getFieldWidth() > getWidthField()) {
			setWidthField(m_utilities.getFieldWidth()); //Note: All Item objects share the same m_widthField
		}
	}
	catch (const char* msg) {
		std::cerr << "Error: " << msg << std::endl;
	}
}

const std::string& Item::getName() const { return m_name; }
void Item::setName(std::string name) { m_name = { name }; }

const std::string& Item::getDescription() const { return m_description; }
void Item::setDescription(std::string description) { m_description = { description }; }

const unsigned int Item::getSerialNumber() { return m_serialNumber++; }
const unsigned int Item::getSerialNumber() const { return m_serialNumber; }
void Item::setSerialNumber(unsigned int serialNumber) { m_serialNumber = { serialNumber }; }

const unsigned int Item::getQuantity() { return m_quantity; }
const unsigned int Item::getQuantity() const { return m_quantity; }
void Item::setQuantity(unsigned int quantity) { m_quantity = { quantity }; }

void Item::updateQuantity() {
	if (getQuantity() > 0)
		m_quantity--;
}

void Item::setWidthField(size_t widthField) { m_widthField = { widthField }; }
const size_t Item::getWidthField() const { return m_widthField; }

void Item::display(std::ostream& os, bool full) const {
	
	if (!full) {
		os << std::left << std::setw(m_utilities.getFieldWidth()) << getName()
		   << " [" << std::right << std::setw(6) << std::setfill('0') << getSerialNumber() << std::setfill(' ') << "]"
		   << std::setfill(' ') << std::endl;
	}
	else {
		os << std::left << std::setw(m_utilities.getFieldWidth()) << getName()
		   << " [" << std::right << std::setw(6) << std::setfill('0') << getSerialNumber() << std::setfill(' ') << "] "
		   << "Quantity: " << std::left << std::setw(m_utilities.getFieldWidth()) << getQuantity()
		   << "Description: " << getDescription()
		   << std::endl;
	}
}