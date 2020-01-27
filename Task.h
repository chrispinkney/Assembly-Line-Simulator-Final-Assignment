// Name: Chris Pinkney
// Seneca Student ID: 044477149
// Seneca email: cpinkney@myseneca.ca
// Date of completion: 25-Nov-19
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef TASK_H
#define TASK_H

#include <deque>
#include <iostream>
#include <string>
#include "Item.h"
#include "CustomerOrder.h"

class Task : public Item {
private:
	std::deque<CustomerOrder> m_orders;
	Task* m_pNextTask;
public:
	Task(const std::string&);
	Task(Task&) = delete;
	Task& operator=(Task&) = delete;
	Task(Task&&) = delete;
	Task& operator=(Task&&) = delete;
	void runProcess(std::ostream&);
	bool moveTask();
	void setNextTask(Task&);
	bool getCompleted(CustomerOrder&);
	void validate(std::ostream&);
	Task& operator+=(CustomerOrder&&);
};

#endif // !TASK_H
