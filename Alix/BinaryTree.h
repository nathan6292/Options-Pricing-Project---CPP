#pragma once
#include <vector>
#include <iostream>
#include "Option.h"

template <typename T>
class BinaryTree {
private:
    int _depth;                             // La profondeur de l'arbre binaire (N)
    std::vector<std::vector<T>> _tree;      // Vecteur de vecteurs pour stocker les nœuds

public:
    BinaryTree();                            // Constructeur
    BinaryTree(int depth) {
		_depth = depth;
		_tree.resize(depth);
		for (int i = 0; i < depth; i++) {
			_tree[i].resize(i + 1);
		}
	}
    void setDepth(int);                // Setter pour _depth
    void setNode(int , int , T ); // Setter pour un nœud spécifique
    T getNode(int, int ) ;   // Getter pour un nœud spécifique
    void display()  ;                    // Méthode pour afficher les valeurs
                        // Getter pour _depth
};

// Constructeur par défaut
template <typename T>
BinaryTree<T>::BinaryTree() : _depth(0) {}

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

// Setter pour _depth
template <typename T>
void BinaryTree<T>::setDepth(int depth) {
    _depth = depth;
	_tree.resize(depth);
	for (int i = 0; i < depth; i++) {
		_tree[i].resize(i + 1);
	}
}

// Setter pour un nœud spécifique
template <typename T>
void BinaryTree<T>::setNode(int level, int index, T value) {
    if (level >= 0 && level <= _depth && index >= 0 && index <= level) {
        _tree[level][index] = value;
    }
    else {
        std::cout << "Invalid indices: level " << level << ", index " << index << std::endl;
    }
}

// Getter pour un nœud spécifique
template <typename T>
T BinaryTree<T>::getNode(int level, int index) {
    if (level >= 0 && level <= _depth && index >= 0 && index <= level) {
        return _tree[level][index];
    }
    else {
        std::cout << "Invalid indices: level " << level << ", index " << index << std::endl;
        return T();  // Return default value of T
    }
}

// Méthode pour afficher les valeurs
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

