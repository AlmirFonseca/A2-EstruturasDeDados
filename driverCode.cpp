#include "tree.cpp"
#include <iostream>

using namespace std;

int main()
{
    struct Node* root = newNode(1);
    root = insertNode(root, 7);
    root = insertNode(root, 5);
    root = insertNode(root, 2);
    root = insertNode(root, 0);
    printTree(root);


    return 0;
}