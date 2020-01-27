#include "LineManager.h"

LineManager::LineManager(const std::string& nameOfFile, std::vector<Task*>& v_task, std::vector<CustomerOrder>& v_customerOrder) {
	std::ifstream file(nameOfFile);
	std::string record{}, first{}, next{};
	size_t pos{ 0 };
	bool more{};
	bool exit{false};

	while (!file.eof())	{
		std::getline(file, record);
		first = m_utility.extractToken(record, pos, more);
		if (more)
			next = m_utility.extractToken(record, ++pos, more);

		for (size_t i = 0; i < v_task.size() || !exit; i++)
			if (v_task[i]->getName() == first) {
				if (!exit)
					m_firstTask = i;
				if (next.length() == 0)
					m_lastTask = i;
				else
					for (size_t j = 0; j < v_task.size() || !exit; j++)
						if (v_task[j]->getName() == next) {
							v_task[i]->setNextTask(*v_task[j]);
							exit = true;
						}
			}
		pos = 0;
		first = {};
		next = {};
	}

	for (auto& i : v_customerOrder)
		ToBeFilled.push_back(std::move(i));
	AssemblyLine = v_task;
}


bool LineManager::run(std::ostream& os) {
	bool run {true};
	CustomerOrder order;

	if (!ToBeFilled.empty()) {
		*AssemblyLine[m_firstTask] += std::move(ToBeFilled.front());
		ToBeFilled.pop_front();
	}

	for (auto& i : AssemblyLine)
		i->runProcess(os);

	if (AssemblyLine[m_lastTask]->getCompleted(order))
		Completed.push_back(std::move(order));

	for (auto& i : AssemblyLine)
		if (i->moveTask())
			run = false;

	return run;
}
void LineManager::displayCompleted(std::ostream& os) const {
	if (!Completed.empty())
		for (const auto& i : Completed)
			i.display(os);
}

void LineManager::validateTasks() const {
	if (!AssemblyLine.empty())
		for (const auto& i : AssemblyLine)
			i->validate(std::cout);
}