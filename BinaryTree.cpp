#pragma once
#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <iomanip> 

int countDigits(double num) {
	int intPart = static_cast<int>(std::abs(num));
	int digits = 0;

	while(intPart != 0.00) {
		intPart /= 10;
		digits++;
	}

	if (digits == 0) digits = 1;

	return digits;
}


template <typename T>
void BinaryTree<T>::setDepth(int depth) {
	_depth = depth;
	_tree.resize(depth+1);
	for (int i = 0; i < depth+1; i++){
		_tree[i].resize(i + 1);
	}
}

template <typename T>
void BinaryTree<T>::setNode(int i, int j, T value) {
	_tree[i][j] = value;
}

template <typename T>
T BinaryTree<T>::getNode(int i, int j) {
	return _tree[i][j];
}

template <typename T>
void BinaryTree<T>::display() {
	for (int i = 0; i <= _depth; i++){
		for (int j = 0; j < i + 1; j++) {
			std::cout << _tree[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	int space_int = 5;
	bool isdouble = typeid(_tree[0][0]) == typeid(double);
	int space_ext = ((space_int) * _depth)/2;
	for (int i = 0; i < _depth; i++){
		int old_char_size = countDigits(_tree[i][0]);
		if (isdouble) {
			std::cout << std::string(space_ext - (old_char_size / 2)-1, ' ');
		}
		else {
			std::cout << std::string(space_ext - (old_char_size / 2), ' ');
		}

		for (int j = 0; j < i; j++) {
			int char_size = countDigits(_tree[i][j]);
			int char_size_next = countDigits(_tree[i][j + 1]);
			std::cout << std::fixed << std::setprecision(2) << _tree[i][j];
			if (isdouble) {
				std::cout << std::string(space_int-3, ' ');
			}
			else {
				std::cout << std::string(space_int, ' ');
			}
			old_char_size = char_size;
		}

		std::cout << std::fixed << std::setprecision(2) << _tree[i][i];
		std::cout << std::endl;

		if (i < _depth - 1){
			std::cout << std::string(space_ext-2-countDigits(_tree[i][0]), ' ');
			for (int j = 0; j < i+1; j++) {
				std::cout << std::string(1, ' ');
				std::cout << "/";
				std::cout << std::string(3, ' ');
				std::cout << "\\";
				std::cout << std::string(0, ' ');
			}
		}
			std::cout << std::endl;
			space_ext = space_ext-space_int/2-1;
	}
}

template class BinaryTree<double>;
template class BinaryTree<bool>;
template class BinaryTree<int>;

