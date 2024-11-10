#pragma once
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include<iostream>
#include <vector>
#include <stdexcept>
#include<iomanip>

using namespace std;

template <typename T> //visiblement pour classes template pas possible de diviser en cpp et h
class BinaryTree
{
private:
    int _depth;  //represents N
    std::vector<std::vector<T>> _tree;

public:
    BinaryTree() : _depth(0) {}

    void setDepth(int depth) {
        _depth = depth;
        _tree.resize(_depth + 1);
        for (int i = 0; i <= _depth; ++i) {
            _tree[i].resize(i + 1);
        }
    }

    void setNode(int level, int index, T value) {
        if (level >= 0 && level <= _depth && index >= 0 && index <= level) {
            _tree[level][index] = value;
        }
    }

    T getNode(int level, int index) const {
        if (level >= 0 && level <= _depth && index >= 0 && index <= level) {
            return _tree[level][index];
        }
        throw std::out_of_range("index de noeud non valide");
    }

    void display()
    {
        //affichage du haut
        for (int i = 0; i <= _depth; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                cout << _tree[i][j] << " ";
            }
            std::cout << std::endl;
        }
        cout << endl;

        //affichage du bas
        int width = pow(2, _depth) * 2;  // Calculate initial spacing
        for (int i = 0; i <= _depth; i++) {
            // Print nodes
            for (int j = 0; j <= i; j++) {
                cout << setw((width / 2) - i * 2) << "";
                cout << _tree[i][j];
                if (j < i) {
                    cout << setw(width - i * 4) << "";
                }
            }
            cout << endl;

            // Print branches
            if (i < _depth) {
                for (int j = 0; j <= i; j++) {
                    cout << setw((width / 2) - i * 2 - 1) << "";
                    cout << "/ \\";
                    if (j < i) {
                        cout << setw(width - i * 4 - 2) << "";
                    }
                }
                cout << endl;
            }
        }


    }
};
#endif

