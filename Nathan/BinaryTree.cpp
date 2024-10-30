#pragma once
#include "BinaryTree.h"
#include <iostream>
#include <string>
#include <iomanip> 

int countDigits(double num) {
	// Utiliser la partie entière
	int intPart = static_cast<int>(std::abs(num));
	int digits = 0;

	// Compter les chiffres de la partie entière
	while (intPart != 0) {
		intPart /= 10;
		digits++;
	}

	// Gérer les cas où le nombre est entre -1 et 1
	if (digits == 0) digits = 1;

	return digits;
}


template <typename T>
void BinaryTree<T>::setDepth(int depth) {
	_depth = depth;
	_tree.resize(depth);
	for (int i = 0; i < depth; i++) {
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
	for (int i = 0; i < _depth; i++) {
		for (int j = 0; j < i + 1; j++) {
			std::cout << _tree[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	int space_int = 5;
	int space_ext = (space_int-2) * _depth-2;
	for (int i = 0; i < _depth; i++) {
		int old_char_size = countDigits(_tree[i][0]);
		std::cout << std::string(space_ext-(old_char_size/2), ' ');

		for (int j = 0; j < i; j++) {
			int char_size = countDigits(_tree[i][j]);
			int char_size_next = countDigits(_tree[i][j + 1]);
			std::cout << _tree[i][j];
			std::cout << std::string(space_int-(char_size_next/2)-char_size/3, ' ');
			old_char_size = char_size;
		}

		std::cout << _tree[i][i];
		std::cout << std::endl;

		if (i < _depth - 1){
			std::cout << std::string(space_ext-2, ' ');
			for (int j = 0; j < i+1; j++) {
				std::cout << "/";
				std::cout << std::string(3, ' ');
				std::cout << "\\";
				std::cout << std::string(1, ' ');
			}
		}
			std::cout << std::endl;
		space_ext = space_ext-space_int/2-1;
	}



}

template class BinaryTree<double>;