#ifndef TREENODE_H
#define TREENODE_H

#include "keyeditem.h"

typedef KeyedItem TreeItemType;

class TreeNode {

public:
    TreeItemType getItem() const {return item;}

private:
    TreeItemType item; 		// a data item in the tree
    TreeNode *leftChildPtr;	// pointers to children
    TreeNode *rightChildPtr;

    TreeNode() { }
    TreeNode(const TreeItemType& nodeItem,TreeNode *left = nullptr, TreeNode *right = nullptr)
                                            : item(nodeItem), leftChildPtr(left), rightChildPtr(right){}

    bool operator==(const TreeNode& other) {
        return (item == other.getItem()) &&
        (leftChildPtr == other.leftChildPtr) && (rightChildPtr == other.rightChildPtr);
    }

    // friend class - can access private parts
    friend class BinarySearchTree;
    friend class BinaryTree;
};


#endif // TREENODE_H


