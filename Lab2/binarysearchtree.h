#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "TreeException.h"
#include "TreeNode.h"

typedef void (*FunctionType)(TreeItemType& anItem);

class BinarySearchTree {

private:
   TreeNode *root;

public:
// constructors and destructor:
   BinarySearchTree();
   BinarySearchTree(const BinarySearchTree& tree)
      noexcept(false);
   virtual ~BinarySearchTree();

// binary search tree operations:
// Precondition for all methods: No two items in a binary
// search tree have the same search key.

   virtual bool isEmpty() const;

   virtual void searchTreeInsert(const TreeItemType& newItem) noexcept(false);

   virtual void searchTreeDelete(KeyType searchKey) noexcept(false);

   virtual void searchTreeRetrieve(KeyType searchKey,TreeItemType& treeItem) const noexcept(false);

   virtual void preorderTraverse(FunctionType visit);

   virtual void inorderTraverse(FunctionType visit);

   virtual void postorderTraverse(FunctionType visit);


   virtual BinarySearchTree& operator=(const BinarySearchTree& rhs) noexcept(false);

protected:
   void insertItem(TreeNode *& treePtr, const TreeItemType& newItem) noexcept(false);

   void deleteItem(TreeNode *& treePtr, KeyType searchKey) noexcept(false);

   void deleteNodeItem(TreeNode *& nodePtr);

   void processLeftmost(TreeNode *& nodePtr,TreeItemType& treeItem);

   void retrieveItem(TreeNode *treePtr, KeyType searchKey, TreeItemType& treeItem) const noexcept(false);


   void copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const noexcept(false);
   void destroyTree(TreeNode *treePtr);

   void preorder(TreeNode *treePtr, FunctionType visit);
   void inorder(TreeNode *treePtr, FunctionType visit);
   void postorder(TreeNode *treePtr, FunctionType visit);

   TreeNode *rootPtr() const;
   void setRootPtr(TreeNode *newRoot);

   void getChildPtrs(TreeNode *nodePtr, TreeNode *& leftChildPtr, TreeNode *& rightChildPtr) const;
   void setChildPtrs(TreeNode *nodePtr, TreeNode *leftChildPtr, TreeNode *rightChildPtr);

};

#endif // BINARYSEARCHTREE_H
