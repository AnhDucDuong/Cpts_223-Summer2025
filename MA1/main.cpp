#include <iostream>
#include "BST.h"

/*

Part A 
1. A move constructor transfers data from one object to another without copying.
2. A move assignment operator transfers data from one existing object to another, freeing old data.


Part B 
BST::empty()             Checks if root is null, constant time                 O(1)
BST::add()               In worst case, traverses a skewed tree of size n      O(n)
BST::makeEmpty()         Recursively visits and deletes each node              O(n)
BST::printLevelOrder()   Visits every node once via queue traversal            O(n)
BST::cloneTree()         Recursively copies each node in the tree              O(n)
*/

using namespace std;

int main() {
	// Test 0: Setup base tree
	BST<string> bstTest;
	bstTest.add("C");
	bstTest.add("p");
	bstTest.add("t");
	bstTest.add("s");
	bstTest.add("2");
	bstTest.add("3");
	bstTest.add("B");
	bstTest.add("S");
	bstTest.add("T");

	// Test 1: Print orders
	cout << "=== Test 1: Print Orders ===" << endl;
	cout << "In-order: ";
	bstTest.printInOrder();
	cout << endl;

	cout << "Level-order: ";
	bstTest.printLevelOrder();
	cout << endl;

	cout << "Post-order: ";
	bstTest.printPostOrder();
	cout << endl;

	cout << "Pre-order: ";
	bstTest.printPreOrder();
	cout << endl << endl;

	// Test 2: Copy constructor test
	BST<string> bstCopy1 = bstTest;
	if (bstCopy1.size() == bstTest.size()
		&& bstCopy1.contains("B") && bstCopy1.contains("S") && bstCopy1.contains("T")) {
		cout << "Copy constructor test-1 passed!" << endl;
	}
	else {
		cout << "Copy constructor test-1 failed!" << endl;
		cout << "bstTest: ";
		bstTest.printLevelOrder();
		cout << endl;
		cout << "bstCopy1: ";
		bstCopy1.printLevelOrder();
		cout << endl;
	}

	// Test 3: Copy constructor deep copy check
	bstCopy1.getNode("B")->setValue("A");
	if (bstTest.contains("B") && !bstTest.contains("A")) {
		cout << "Copy constructor test-2 passed!" << endl;
	}
	else {
		cout << "Copy constructor test-2 failed!" << endl;
		cout << "bstTest: ";
		bstTest.printLevelOrder();
		cout << endl;
	}

	// Test 4: Copy assignment operator
	BST<string> bstCopy2;
	bstCopy2 = bstTest;
	if (bstCopy2.size() == bstTest.size()
		&& bstCopy2.contains("B") && bstCopy2.contains("S") && bstCopy2.contains("T")) {
		cout << "Copy assignment operator test passed!" << endl;
	}
	else {
		cout << "Copy assignment operator test failed!" << endl;
		cout << "bstTest: ";
		bstTest.printLevelOrder();
		cout << endl;
		cout << "bstCopy2: ";
		bstCopy2.printLevelOrder();
		cout << endl;
	}

	// Test 5: Move constructor
	BST<string> bstMove = std::move(bstTest);
	if (bstMove.size() == 9 && bstMove.contains("B") &&
		bstMove.contains("S") && bstMove.contains("T") &&
		bstTest.empty()) {
		cout << "Move constructor test passed!" << endl;
	}
	else {
		cout << "Move constructor test failed!" << endl;
		cout << "bstMove: ";
		bstMove.printLevelOrder();
		cout << endl;
	}

	// Test 6: Move assignment operator
	BST<string> bstMove2;
	bstMove2 = BST<string>({ "B", "S", "T" });

	if (bstMove2.size() == 3 && bstMove2.contains("B")
		&& bstMove2.contains("S") && bstMove2.contains("T")) {
		cout << "Move assignment operator test passed!" << endl;
	}
	else {
		cout << "Move assignment operator test failed!" << endl;
		cout << "bstMove2: ";
		bstMove2.printLevelOrder();
		cout << endl;
	}

	return 0;
}
