#include "Task.h"

Task::Task(const std::string& file) : Item(file) {
	m_pNextTask = { nullptr };
}

//runs a single cycle of the assembly line for the current task.
//If there are CustomerOrders in the queue, it will verify the fill status of the last CustomerOrder and fill it if the order contains the Item specified by the current Task.
void Task::runProcess(std::ostream& os) {
	if (!m_orders.empty()) 
		if (!m_orders.back().getOrderFillState())
			m_orders.back().fillItem(*this, os);
}

//moves the last CustomerOrder in the queue to the next task on the assembly line if the orders fill state for the current Item is true.Otherwise, the CustomerOrder should remain in the queue for the next processing cycle.If the queue is empty, return false.
bool Task::moveTask() {
	bool moved{};

	if (m_orders.empty())
		moved = false;
	else if (m_orders.back().getItemFillState(getName()))
		if (m_pNextTask) {
			(*m_pNextTask) += std::move(m_orders.back());
			m_orders.pop_back();
			moved = true;
		}

	return moved;
}

//stores the provided Task object's reference into the m_pNextTask pointer.
void Task::setNextTask(Task& task) {
	m_pNextTask = &task;
}

//Removes the last CustomerOrder from the queue, places it in the parameterand returns true.If the CustomerOrder queue is empty, return false.
bool Task::getCompleted(CustomerOrder& customerOrders) {
	bool completed{};

	if (m_orders.empty())
		completed = false;
	else {
		customerOrders = std::move(m_orders.back());
		m_orders.pop_back();
		completed = true;
	}

	return completed;
}

//writes the name of the Item this Task is responsible for into the parameter : ITEM_NAME-- > NEXT_ITEM_NAME
//if m_pNextTask does not exist it writes : ITEM_NAME-- > END OF LINE.
//the messages are terminated with an endline
void Task::validate(std::ostream& os) {
	os << getName() << " --> " << (m_pNextTask ? m_pNextTask->getName() : "END OF LINE") << std::endl;
}

//Moves the parameter onto the front of the CustomerOrder queue.
Task& Task::operator+=(CustomerOrder&& src) {
	m_orders.push_front(std::move(src));
	return *this;
}