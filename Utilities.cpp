#include "Utilities.h"

size_t Utilities::m_widthField { 1 };
char Utilities::m_delimiter {' '};

void Utilities::setFieldWidth(size_t widthfield) { m_widthField = { widthfield }; }
size_t Utilities::getFieldWidth() const { return m_widthField; }

const std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
	if (next_pos)
		next_pos = str.find(getDelimiter(), next_pos) + 1;

	std::string tempToken = str.substr(next_pos);
	size_t startPos = tempToken.find(getDelimiter());

	if (startPos != std::string::npos) {
		tempToken = tempToken.substr(0, startPos);
		more = true;
		if (getFieldWidth() < tempToken.size())
			setFieldWidth(tempToken.size());
	}
	else if (str[next_pos + 1] == getDelimiter())
		throw("EXCEPTION: There are two delimiters with no token between them.");
		// more = false;
	else
		more = false;

	return tempToken;
}

void Utilities::setDelimiter(const char delimiter) { m_delimiter = { delimiter }; }
const char Utilities::getDelimiter() const { return m_delimiter; }