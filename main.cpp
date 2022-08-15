#include <bits/stdc++.h>
#include "tree.hpp"
using namespace std;

int main() {

    vector<int> elements = {9, 6, -3, INT_MIN, INT_MIN, -6, 2, INT_MIN, INT_MIN, 2, INT_MIN, -6, -6, -6};
    BinaryTree<int> *tree = new BinaryTree<int> (elements, INT_MIN);
    tree->print();
    cout << "Max Path Sum: " << tree->maxPathSum();
    return 0;
}