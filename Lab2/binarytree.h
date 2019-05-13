#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "treeexception.h"
#include "treenode.h"

#include <queue>
#include <math.h>
#include <iomanip>
#include <random>
#include <set>
#include <algorithm>

typedef void (*FunctionType)(TreeItemType& anItem);

class BinaryTree {
private:
    TreeNode *root;

public:
// constructors and destructor:
    BinaryTree();
    BinaryTree(const TreeItemType& rootItem) noexcept(false);
    BinaryTree(const TreeItemType& rootItem, BinaryTree& leftTree, BinaryTree& rightTree) noexcept(false);
    BinaryTree(const BinaryTree& tree) noexcept(false);
    virtual ~BinaryTree();

// binary tree operations:
    virtual bool isEmpty() const;
    virtual int getHeight() const;
    virtual int getDiameter() const;
    virtual std::vector<KeyedItem> *getDiameterPath(bool diffHeightOnly = true) const;
    virtual int getNumberOfNodes() const;

    virtual bool add(const TreeItemType& newData);
    virtual bool remove(const TreeItemType& data);
    virtual void clear() const;

    virtual TreeItemType getEntry(const TreeItemType& anEntry) noexcept(false);
    virtual bool contatins(const TreeItemType& data);


    virtual TreeItemType getRootData() const noexcept(false);
    virtual void setRootData(const TreeItemType& newItem) noexcept(false);

    virtual void attachLeft(const TreeItemType& newItem) noexcept(false);
    virtual void attachRight(const TreeItemType& newItem) noexcept(false);

    virtual void attachLeftSubtree(BinaryTree& leftTree) noexcept(false);
    virtual void attachRightSubtree(BinaryTree& rightTree) noexcept(false);
    virtual void detachLeftSubtree(BinaryTree& leftTree) noexcept(false);
    virtual void detachRightSubtree(BinaryTree& rightTree) noexcept(false);
    virtual BinaryTree getLeftSubtree() const noexcept(false);
    virtual BinaryTree getRightSubtree() const noexcept(false);

    virtual void preorderTraverse(FunctionType visit);
    virtual void inorderTraverse(FunctionType visit);
    virtual void postorderTraverse(FunctionType visit);
    virtual void breadthFirstTraverse(FunctionType visit);

    virtual std::vector<KeyedItem> *getBreadthFirstVector();
    virtual void generateRandomTree(int nodeTarget, int valMin, int valMax);
    virtual BinaryTree& operator=(const BinaryTree& rhs) noexcept(false);

protected:
    BinaryTree(TreeNode *nodePtr);  // constructor

    void copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const noexcept(false);
    void  destroyTree(TreeNode *treePtr) const;

    TreeNode *rootPtr() const;
    void setRootPtr(TreeNode *newRoot);

    void getChildPtrs(TreeNode *nodePtr, TreeNode *& leftChildPtr, TreeNode *& rightChildPtr) const;
    void setChildPtrs(TreeNode *nodePtr, TreeNode *leftChildPtr, TreeNode *rightChildPtr);

    void preorder(TreeNode *treePtr, FunctionType visit);
    void inorder(TreeNode *treePtr, FunctionType visit);
    void postorder(TreeNode *treePtr, FunctionType visit);
    std::vector<KeyedItem> *breadthFirst(TreeNode *treePtr, FunctionType visit);

    int getMaxDepth(TreeNode *node) const;
    int getFullCount(TreeNode *node) const;

    bool crawl_add(const TreeItemType &item);
    bool crawl_remove(const TreeItemType &item);
    TreeNode *crawl_contatins(const TreeItemType &data);

    static void t(KeyedItem &someItem);
    TreeNode *buildTree(int depth);
    int calculateDepth(int count);
    int getDiameterUtil(TreeNode *rootM, int *height) const;
    std::vector<KeyedItem> *getMaxPath(TreeNode *rootM, std::vector<KeyedItem> *path, bool diffHeightOnly = true) const;
};

#endif // BINARYTREE_H
