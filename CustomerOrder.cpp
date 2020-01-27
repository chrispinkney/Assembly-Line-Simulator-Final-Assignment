#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField = 1;

CustomerOrder::CustomerOrder() :  m_name { "" }, m_product { "" }, m_cntItem { 0 }, m_lstItem { nullptr } {}

CustomerOrder::CustomerOrder(const std::string& record) {
	size_t pos {0};
	bool more {};
	setName(m_utility.extractToken(record, pos, more));
	setProduct(m_utility.extractToken(record, ++pos, more));

	setCount(record);
	m_lstItem = new ItemInfo*[getCount()];

	for (unsigned int i = 0; i < getCount(); i++)
		m_lstItem[i] = new ItemInfo(m_utility.extractToken(record, ++pos, more));
}

CustomerOrder::~CustomerOrder() {
	for (unsigned int i = 0; i < getCount(); i++)
		delete m_lstItem[i];
	delete[] m_lstItem;
	m_lstItem = nullptr;
}

CustomerOrder::CustomerOrder(CustomerOrder&) { throw "ERROR: Cannot make copies."; }

CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept {
	*this = std::move(src);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) {
	if (this != &src) {
		setName(src.getName());
		setProduct(src.getProduct());
		m_cntItem = src.m_cntItem;
		m_lstItem = src.m_lstItem;
		setWidthField(src.m_widthField);

		src.setName({""});
		src.setProduct({""});
		src.m_cntItem = { 0u };
		src.m_lstItem = { nullptr };
		src.setWidthField(1);


		/*m_name = src.m_name;
		m_product = src.m_product;
		m_cntItem = src.m_cntItem;
		m_lstItem = src.m_lstItem;
		m_widthField = src.m_widthField;

		src.m_name = { "" };
		src.m_product = { "" };
		src.m_cntItem = { 0u };
		src.m_lstItem = { nullptr };
		src.m_widthField = 1;*/
	}
	return *this;
}


const std::string& CustomerOrder::getName() const {	return m_name; }
void CustomerOrder::setName(std::string name) {	m_name = name; }

const std::string& CustomerOrder::getProduct() const { return m_product;  }
void CustomerOrder::setProduct(std::string product) { m_product = product; }

const unsigned int CustomerOrder::getCount() const { return m_cntItem; }
void CustomerOrder::setCount(const std::string& record) { 
	m_cntItem = std::count(record.begin(), record.end(), m_utility.getDelimiter()) - 1; 
}

void CustomerOrder::setWidthField(size_t widthField) { m_widthField = { widthField }; }
const size_t CustomerOrder::getWidthField() const { return m_widthField; }

bool CustomerOrder::getItemFillState(std::string item) const {
	bool fillState{ true };
	for (unsigned int i = 0; i < getCount() && fillState; i++)
		if (m_lstItem[i]->m_itemName == item)
			if (!m_lstItem[i]->m_fillState)
				fillState = false;

	return fillState;
}

bool CustomerOrder::getOrderFillState() const {
	bool fillState{ true };
	for (unsigned int i = 0; i < getCount() && fillState; i++)
		if (!m_lstItem[i]->m_fillState)
			fillState = false;

	return fillState;
}

void CustomerOrder::fillItem(Item& item, std::ostream& os) {
	for (unsigned int i = 0; i < getCount(); i++)
		if (m_lstItem[i]->m_itemName == item.getName() && item.getQuantity() > 0) {
			item.updateQuantity();
			m_lstItem[i]->m_serialNumber = item.getSerialNumber();
			m_lstItem[i]->m_fillState = true;
			os << "Filled " << getName() << ", " << getProduct() << "[" << item.getName() << "]" << std::endl;
		}
		else if (m_lstItem[i]->m_itemName == item.getName() && item.getQuantity() <= 0)
				os << "Unable to fill " << getName() << ", " << getProduct() << "[" << item.getName() << "]" << std::endl;
}

void CustomerOrder::display(std::ostream& os) const {
	os << getName() << " - " << getProduct() << std::endl;
	for (unsigned int i = 0; i < getCount(); i++) {
		os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] " << std::left
		   << std::setw(m_utility.getFieldWidth() - 1) << std::setfill(' ') << m_lstItem[i]->m_itemName << " - " << (m_lstItem[i]->m_fillState ? "FILLED" : "MISSING")
		   << std::endl;
	}
}