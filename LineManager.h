// Name: Chris Pinkney
// Seneca Student ID: 044477149
// Seneca email: cpinkney@myseneca.ca
// Date of completion: 25-Nov-19
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include <deque>
#include <fstream>
#include <iostream>
#include "Task.h"
#include "CustomerOrder.h"

class LineManager {
private:
	std::vector<Task*> AssemblyLine;
	size_t m_firstTask;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	size_t m_lastTask;
	unsigned int m_cntCustomerOrder;
	Utilities m_utility;
public:
	LineManager(const std::string&, std::vector<Task*>&, std::vector<CustomerOrder>&);
	bool run(std::ostream&);
	void displayCompleted(std::ostream&) const;
	void validateTasks() const;
};

#endif // !LINEMANAGER_H
