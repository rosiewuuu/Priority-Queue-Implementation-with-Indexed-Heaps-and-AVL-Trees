#include <iostream>
#include <sstream>
#include <string>
#include "AvlTree.h"
#include "AvlNode.h"
#include "BinaryHeap.h"
#include "PQ.h"
#include "dsexceptions.h"
#include <vector>
using namespace std;

// Test program
int main() {

	vector<int> prj = { 1110, 2220, 3330, 4440, 5550, 110, 220, 330, 440, 550,
			20, 30, 40, 50 };
	vector<int> priority = { 111, 222, 333, 444, 555, 11, 22, 33, 44, 55, 2, 3,
			4, 5 };
	PQ<int> Q1;
	PQ<int> Q2(prj, priority);

	for (int i = 0; i < prj.size(); i++) {
		Q1.insert(prj[i], priority[i]);
	}
	cout
			<< "Test 1===========================================================================================================================\n";
	cout
			<< "There are 2 PQ object. One is created by default constructor then set the values using insert function."
			<< endl;
	cout
			<< "The 2nd PQ object is initialized by the constructor that takes two vector arguments. \n";
	cout << "Inserting " << prj.size() << " projects:\n";
	cout << "Project id: ";
	for (int x : prj)
		cout << x << " ";
	cout << endl << "With associated priority: ";
	for (int y : priority)
		cout << y << " ";
	cout << endl << endl;

	cout << "Q1 (build using default constructor and insert() ):\n";
	Q1.display();
	cout << "--------------------------------------------------\n";
	cout << "Q2 (initialized by constructor):\n";
	Q2.display();

	cout
			<< "Test 2===========================================================================================================================\n";

	cout << "Testing findMin() and DeleteMin\n";
	cout << "For Q1, findMin() returns project number '" << Q1.findMin()
			<< "' for the top priority project.\n";
	cout << "After deleting it using deleteMin():\n";
	Q1.deleteMin();
	Q1.display();

	cout
			<< "Test 3===========================================================================================================================\n";

	cout
			<< "Using the previous PQ, update project 5550's priority to 500 and project 330 to priority 1.\n ";
	Q1.updatePriority(5550, 500);
	Q1.updatePriority(330, 1);
	Q1.display();
	cout
			<< "Test 4===========================================================================================================================\n";
	cout << "\nTesting size(): \n";
	cout << "Q1 initially have 14 elements, removing one element in test 2.\n";
	cout << "Q1's current size is: " << Q1.size() << endl;
	cout
			<< "\nTest 5===========================================================================================================================\n";
	cout << "Testing makeEmpty() and isEmpty() on Q1: \n";
	cout << "Displaying tree and heap array after emptying it.\n";
	Q1.makeEmpty();
	Q1.display();
	cout
			<< "\n===============================================================================================================================\n";
	cout << "The above tests have tested all functions in PQ class";

	return 0;
}

