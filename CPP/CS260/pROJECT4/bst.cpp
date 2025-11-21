/*********************************
 * Kelvin Muturi
 * CS260 Fall25
 * Project4
 *********************************/

#include "bst.h"

// BST constructor
BST::BST() : root(nullptr), nodeCount(0) {}

//BST destructor
BST::~BST() {
	destroyTree(root);
}

// Public insert method
bool BST::insert(const char* program, const char* gNumber, const char* name, int standing) {
	if (!program || !gNumber || !name || standing < 1 || standing > 5) {
		return false;
	}

	root = insertRecursive(root, program, gNumber, name, standing);
	return root != nullptr;
}

// Recursive insert
BSTNode* BST::insertRecursive(BSTNode* node, const char* program, const char* gNumber, const char* name, int standing) {
	if (node == nullptr) {
		BSTNode* newNode = new BSTNode(); // Create new node

		//Allocate and copy data
		newNode->data.program = new char[strlen(program) + 1];
		strcpy(newNode->data.program, program);

		newNode->data.gNumber = new char[strlen(gNumber) + 1];
		strcpy(newNode->data.gNumber, gNumber);

		newNode->data.name = new char[strlen(name) + 1];
		strcpy(newNode->data.name, name);

		newNode->data.standing = standing;

		nodeCount++;
		return newNode;
	}

	int comparison = strcmp(gNumber, node->data.gNumber);

	if (comparison < 0) {
		node->left = insertRecursive(node->left, program, gNumber, name, standing);
	}
	else {
		node->right = insertRecursive(node->right, program, gNumber, name, standing);
	} //GNumber must be unique

	return node;
}

//Public remove by G number
bool BST::removeByGNumber(const char* gNumber) {
	bool success = false;
	root = removeByGNumberRecursive(root, gNumber, success);
	if (success) nodeCount--;
	return success;
}

//Recursive remove by GNumber
BSTNode* BST::removeByGNumberRecursive(BSTNode* node, const char* gNumber, bool& success) {
	if (node == nullptr) {
		return nullptr;
	}

	int comparison = strcmp(gNumber, node->data.gNumber);

	if (comparison < 0) {
		node->left = removeByGNumberRecursive(node->left, gNumber, success);
	}
	else if (comparison > 0) {
		node->right = removeByGNumberRecursive(node->right, gNumber, success);
	}
	else {
		success = true; //Node found(remove)

		// Case 1: No child or one child
		if (node->left == nullptr) {
			BSTNode* temp = node->right;
			delete node;
			return temp;
		}
		else if (node->right == nullptr) {
			BSTNode* temp = node->left;
			delete node;
			return temp;
		}

		// Case 2: Two children
		BSTNode* temp = findMin(node->right);

		// Copy the data from temp to current node
		node->data.clear();
		node->data.copy(temp->data);

		// Remove the successor
		node->right = removeByGNumberRecursive(node->right, temp->data.gNumber, success);
	}

	return node;
}

// Public remove by program
int BST::removeByProgram(const char* program) {
	return removeByProgramRecursive(root, program);
}

// Recursive remove by program
int BST::removeByProgramRecursive(BSTNode*& node, const char* program) {
	if (node == nullptr) {
		return 0;
	}

	int count = 0;

	// First process left and right subtrees
	count += removeByProgramRecursive(node->left, program);
	count += removeByProgramRecursive(node->right, program);

	// Then check current node
	if (strcmp(node->data.program, program) == 0) {
		// Store GNumber before deletion
		char* gNumberToRemove = new char[strlen(node->data.gNumber) + 1];
		strcpy(gNumberToRemove, node->data.gNumber);

		// Remove this node by G number
		bool success = false;
		node = removeByGNumberRecursive(node, gNumberToRemove, success);

		if (success) {
			count++;
			nodeCount--;
		}

		delete[] gNumberToRemove;
	}

	return count;
}

//Public retrieve method
bool BST::retrieve(const char* gNumber, Student& result) const {
	return retrieveRecursive(root, gNumber, result);
}

//Recursive retrieve
bool BST::retrieveRecursive(BSTNode* node, const char* gNumber, Student& result) const {
	if (node == nullptr) {
		return false;
	}

	int comparison = strcmp(gNumber, node->data.gNumber);

	if (comparison < 0) {
		return retrieveRecursive(node->left, gNumber, result);
	}
	else if (comparison > 0) {
		return retrieveRecursive(node->right, gNumber, result);
	}
	else {
		result.copy(node->data); //Found the student
		return true;
	}
}

//Public display all (in-order traversal)
void BST::displayAll() const {
	cout << "\n====== STUDENTS IN PCC (Sorted by G#) =======" << endl;
	displayInOrder(root);
	cout << "\nTotal students: " << nodeCount << endl; 
}

void BST::displayInOrder(BSTNode* node) const {
	if (node == nullptr) {
		return;
	}

	displayInOrder(node->left);

	cout << "\nProgram: " << node->data.program << endl;
	cout << "G#: " << node->data.gNumber << endl;
	cout << "Name: " << node->data.name << endl;
	cout << "Standing: " << standingToString(node->data.standing) << endl;
	cout << "_____________________________________________________" << endl;
	
	displayInOrder(node->right);
}

//Public monitor
void BST::monitor() const {
	cout << "========== BINARY SEARCH TREE PERFORMANCE ============" << endl;
	cout << "Total nodes: " << nodeCount << endl;
	cout << "Tree height: " << getHeight() << endl;

	if (nodeCount > 0) {
		int minHeight = static_cast<int>(log2(nodeCount + 1));
		int maxHeight = nodeCount;
		int actualHeight = getHeight();

		cout << "\nPerformance Analysis:" << endl;
		cout << "Minimum possible height (balanced):" << minHeight << endl;
		cout << "Maximum possible height (degenerate): " << maxHeight << endl;
		cout << "Actual height: " << actualHeight << endl;

		if (actualHeight <= minHeight * 1.5) {
			cout << "Status: Well-balanced tree " << endl;
			cout << "Expected search performance: O(log n)" << endl;
		}
		else if (actualHeight <= nodeCount * 0.3) {
			cout << "Status: Reasonable balanced tree" << endl;
			cout << "Expected search performance: O(log n) to O(n)" << endl;
		}
		else {
			cout << "Status: Unbalanced tree " << endl;
			cout << "Expected search pertformance: Close to O(n)" << endl;
			cout << "Consider rebalancing the tree." << endl;
		}

		cout << "Load factor (height/nodes): " << (float)actualHeight / nodeCount << endl;
	}
}

//Getting height
int BST::getHeight() const {
	return getHeightRecursive(root);
}

//Calculate height recursively
int BST::getHeightRecursive(BSTNode* node) const {
	if (node == nullptr) {
		return 0;
	}

	int leftHeight = getHeightRecursive(node->left);
	int rightHeight = getHeightRecursive(node->right);

	return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

//Get count
int BST::getCount() const {
	return nodeCount;
}

//Check if empty
bool BST::isEmpty() const {
	return root == nullptr;
}

//Find min node in subtree
BSTNode* BST::findMin(BSTNode* node) const {
	while (node && node-> left != nullptr) {
		node = node->left;
	}
	return node;
}

//Destroy tree
void BST::destroyTree(BSTNode* node) {
	if (node == nullptr) {
		return;
	}

	destroyTree(node->left);
	destroyTree(node->right);
	delete node;
}
