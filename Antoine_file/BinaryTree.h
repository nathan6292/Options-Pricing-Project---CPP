#pragma once
#include <vector>
#include <iostream>

template <typename T>
class BinaryTree {
private:
    int _depth;                             // La profondeur de l'arbre binaire (N)
    std::vector<std::vector<T>> _tree;      // Vecteur de vecteurs pour stocker les n�uds

public:
    BinaryTree();                     // Constructeur
    void setDepth(int);               // Setter pour _depth
    void setNode(int , int , T );     // Setter pour un n�ud sp�cifique
    T getNode(int, int ) ;            // Getter pour un n�ud sp�cifique
    void display()  ;                 // M�thode pour afficher les valeurs
                                      // Getter pour _depth
};

// Constructeur par d�faut
template <typename T>
BinaryTree<T>::BinaryTree() : _depth(0) {}

// Setter pour _depth
template <typename T>
void BinaryTree<T>::setDepth(int depth) {
    _depth = depth;
    _tree.resize(_depth + 1);  // Resize the tree to accommodate depth levels
    for (int i = 0; i <= _depth; ++i) {
        _tree[i].resize(i + 1);  // Each level i has i + 1 nodes
    }
}

// Setter pour un n�ud sp�cifique
template <typename T>
void BinaryTree<T>::setNode(int level, int index, T value) {
    if (level >= 0 && level <= _depth && index >= 0 && index <= level) {
        _tree[level][index] = value;
    }
    else {
        std::cout << "Invalid indices avec set : level " << level << ", index " << index << std::endl;
    }
}

// Getter pour un n�ud sp�cifique
template <typename T>
T BinaryTree<T>::getNode(int level, int index) {
    if (level >= 0 && level <= _depth && index >= 0 && index <= level) {
      
        return _tree[level][index];
    }
    else {
        std::cout << "Invalid indices avec get: level " << level << ", index " << index << std::endl;
        return T();  // Return default value of T
    }
}

// M�thode pour afficher les valeurs
template <typename T>
void BinaryTree<T>::display() {
    for (int i = 0; i <= _depth; ++i) {
        for (int j = 0; j <= i; ++j) {
            std::cout << _tree[i][j] << " ";
        }
        std::cout << std::endl;  // Newline after each level
    }
}

