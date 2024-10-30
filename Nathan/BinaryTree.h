#pragma once
#include <vector>
#include <iostream>
#include "Option.h"

template <typename T>
class BinaryTree
{
private:
	int _depth;
	std::vector<std::vector<T>> _tree;

public: 
	BinaryTree(int depth) {
		_depth = depth;
		_tree.resize(depth);
		for (int i = 0; i < depth; i++) {
			_tree[i].resize(i + 1);
		}
	}
	void setDepth(int);
	void setNode(int, int, T);
	T getNode(int, int);
	void display();
};

