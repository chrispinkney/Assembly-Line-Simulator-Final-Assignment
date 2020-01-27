#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Item.h"
#include "Item.h"
#include "Task.h"
#include "Task.h"
#include "CustomerOrder.h"
#include "CustomerOrder.h"
#include "Utilities.h"
#include "Utilities.h"
#include "LineManager.h"
#include "LineManager.h"

using namespace std;

template<typename T>
static void loadFromFile(const char*, vector<T>&);
template<typename T>
static void loadFromFile(const char*, vector<T*>&);


int main(int argc, char** argv)
{
	cout << "Command Line: " << argv[0];
	for (int i = 1; i < argc; i++)
		cout << " " << argv[i];
	cout << endl << endl;

	vector<Task*> theTasks;
	vector<CustomerOrder> theOrders;

	Utilities::setDelimiter(',');
	loadFromFile(argv[1], theTasks);
	Utilities::setDelimiter('|');
	loadFromFile(argv[2], theTasks);

	cout << "=======================" << endl;
	cout << "=   Tasks (summary)   =" << endl;
	cout << "=======================" << endl;
	for (const Task* theItem : theTasks)
		theItem->display(cout, false);
	cout << endl;

	cout << "=======================" << endl;
	cout << "=    Tasks (full)     =" << endl;
	cout << "=======================" << endl;
	for (const Task* theTask : theTasks)
		theTask->display(cout, true);
	cout << endl;

	//Select an object and verify all the functionality it working
	cout << "=======================" << endl;
	cout << "=  Manual Validation  =" << endl;
	cout << "=======================" << endl;
	cout << "getName(): " << theTasks[0]->getName() << endl;
	cout << "getSerialNumber(): " << theTasks[0]->getSerialNumber() << endl;
	cout << "getSerialNumber(): " << theTasks[0]->getSerialNumber() << endl;
	cout << "getQuantity(): " << theTasks[0]->getQuantity() << endl;
	theTasks[0]->updateQuantity();
	cout << "getQuantity(): " << theTasks[0]->getQuantity() << endl;
	cout << endl;




	loadFromFile<CustomerOrder>(argv[3], theOrders);

	cout << "=======================" << endl;
	cout << "=        Orders       =" << endl;
	cout << "=======================" << endl;
	for (CustomerOrder& order : theOrders)
		order.display(std::cout);
	cout << endl;

	LineManager lm(argv[4], theTasks, theOrders);
	cout << "=======================" << endl;
	cout << "=   Validate Tasks    =" << endl;
	cout << "=======================" << endl;
	lm.validateTasks();
	cout << endl;

	cout << "=======================" << endl;
	cout << "=   Filling Orders    =" << endl;
	cout << "=======================" << endl;

	while (!lm.run(cout));		//loop running the assembly line until complete
	cout << endl;

	cout << "=======================" << endl;
	cout << "=   Completed Orders  =" << endl;
	cout << "=======================" << endl;
	lm.displayCompleted(cout);
	cout << endl;

	cout << "=======================" << endl;
	cout << "=  Inventory (full)   =" << endl;
	cout << "=======================" << endl;
	for (const Item* theItem : theTasks)
		theItem->display(cout, true);
	cout << endl;

	// cleanup
	for (const Task* task : theTasks)
		delete task;

	return 0;
}

template<typename T>
static void loadFromFile(const char* filename, vector<T>& theCollection)
{
	ifstream file(filename);
	if (!file)
		throw string("Unable to open [") + filename + "] file.";

	string record;
	while (!file.eof())
	{
		std::getline(file, record);
		T elem(record);
		theCollection.push_back(std::move(elem));
	}

	file.close();
}

template<typename T>
static void loadFromFile(const char* filename, vector<T*>& theCollection)
{
	ifstream file(filename);
	if (!file)
		throw string("Unable to open [") + filename + "] file.";

	string record;
	while (!file.eof())
	{
		std::getline(file, record);
		theCollection.push_back(new T(record));
	}

	file.close();
}