#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <iomanip> 

// BinaryTree class template 
template <typename T>
// Declaration of the class BinaryTree
class BinaryTree {
	// Declaration of the private variables _depth and _tree
private:
	int _depth;                             
	std::vector<std::vector<T>> _tree;     

public:
	// Declaration of the constructor BinaryTree without parameters (depth = 0)
	BinaryTree();

	// Declaration of the constructor BinaryTree with the parameter depth
	BinaryTree(int);

	// Declaration of the function setDepth that sets the depth of the tree
	void setDepth(int);

	// Declaration of the function setNode that sets the value of a node
	void setNode(int, int, T);

	// Declaration of the function getNode that returns the value of a node
	T getNode(int, int);

	// Declaration of the function display that displays the tree
	void display();
};

// Declaration of the constructor BinaryTree without parameters (depth = 0)
template <typename T>
BinaryTree<T>::BinaryTree() : _depth(0) {}

// Declaration of the constructor BinaryTree with the parameter depth
template <typename T>
BinaryTree<T>::BinaryTree(int depth) {
	setDepth(depth);
}

// Setter for the depth of the tree
template <typename T>
void BinaryTree<T>::setDepth(int depth) {
	_depth = depth;

	// Resize the tree
	_tree.resize(_depth + 1);  

	// Resize the vectors in the tree
	for (int i = 0; i <= depth; ++i) {
		_tree[i].resize(i + 1);
	}
}

// Setter for a specific node
template <typename T>
void BinaryTree<T>::setNode(int i, int j, T value) {
	// Check if the indices are valid
	if (j < 0 || i < 0 || j > _depth || i > _depth) {
		throw std::out_of_range("Invalid tree indices");
	}

	// Set the value of the node
	_tree[i][j] = value;
}

// Getter for a specific node
template <typename T>
T BinaryTree<T>::getNode(int i, int j) {
	// Check if the indices are valid
	if (j < 0 || i < 0 || j > _depth || i > _depth) {
		throw std::out_of_range("Invalid tree indices");
	}
	// Return the value of the node
	return _tree[i][j];
}

// Method to count the number of digits in a number used to display the tree
static int countDigits(double num) {
	int intPart = static_cast<int>(std::abs(num));
	int digits = 0;

	while (intPart != 0.00) {
		intPart /= 10;
		digits++;
	}

	if (digits == 0) digits = 1;

	return digits;
}

// Method to display the tree
template <typename T>
void BinaryTree<T>::display() {
	// Display each element of the tree
	for (int i = 0; i <= _depth; i++) {
		for (int j = 0; j < i + 1; j++) {
			std::cout << _tree[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	// Display the tree in a more visual way
	// The tree is displayed as a triangle

	// space_int is the space between two elements in the tree
	int space_int = 5;

	// Check if the tree contains double values
	bool isdouble = typeid(_tree[0][0]) == typeid(double);

	// space_ext is the space before the first element of the tree for each row
	int space_ext = ((space_int)*_depth) / 2;

	// Display the tree
	for (int i = 0; i < _depth; i++) {
		// old_char_size is the number of digits of the previous element
		int old_char_size = countDigits(_tree[i][0]);

		// Display the right number of spaces before the first element depending on the raw
		if (isdouble) {
			std::cout << std::string(space_ext - (old_char_size / 2) - 1, ' ');
		}
		else {
			std::cout << std::string(space_ext - (old_char_size / 2), ' ');
		}

		// Display the elements of the tree
		for (int j = 0; j < i; j++) {
			int char_size = countDigits(_tree[i][j]);
			int char_size_next = countDigits(_tree[i][j + 1]);
			// Display the element
			std::cout << std::fixed << std::setprecision(2) << _tree[i][j];

			// Display the right number of spaces between two elements
			if (isdouble) {
				std::cout << std::string(space_int - 3, ' ');
			}
			else {
				std::cout << std::string(space_int, ' ');
			}

			// Set the old_char_size to the char_size
			old_char_size = char_size;
		}

		// Display the last element of the row
		std::cout << std::fixed << std::setprecision(2) << _tree[i][i];
		std::cout << std::endl;

		// Display the / and \ of the tree
		if (i < _depth - 1) {
			// Display the right number of spaces before the first element depending on the raw
			std::cout << std::string(space_ext - 2 - countDigits(_tree[i][0]), ' ');

			// Display the / and \ of the tree
			for (int j = 0; j < i + 1; j++) {
				std::cout << std::string(1, ' ');
				std::cout << "/";
				std::cout << std::string(3, ' ');
				std::cout << "\\";
				std::cout << std::string(0, ' ');
			}
		}
		std::cout << std::endl;

		// Update the space_ext (space between the full left and the first element of the tree)
		space_ext = space_ext - space_int / 2 - 1;
	}
}

// Type of the trees that will be used
template class BinaryTree<double>;
template class BinaryTree<bool>;
template class BinaryTree<int>;
