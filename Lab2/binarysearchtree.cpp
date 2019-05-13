#include "binarysearchtree.h"

using namespace std;

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::BinarySearchTree(const BinarySearchTree& tree) noexcept(false) {
   copyTree(tree.root, root);
}

BinarySearchTree::~BinarySearchTree() {
   destroyTree(root);
}

bool BinarySearchTree::isEmpty() const {
   return (root == nullptr);
}

void BinarySearchTree::searchTreeInsert(const TreeItemType& newItem) noexcept(false) {
   insertItem(root, newItem);
}

void BinarySearchTree::searchTreeDelete(KeyType searchKey) noexcept(false) {
   deleteItem(root, searchKey);
}

void BinarySearchTree::searchTreeRetrieve(KeyType searchKey, TreeItemType& treeItem)
                                                                const noexcept(false) {
   // if retrieveItem throws a TreeException, it is
   // ignored here and passed on to the point in the code
   // where searchTreeRetrieve was called
   retrieveItem(root, searchKey, treeItem);
}

void BinarySearchTree::preorderTraverse(FunctionType visit) {
   preorder(root, visit);
}

void BinarySearchTree::inorderTraverse(FunctionType visit) {
   inorder(root, visit);
}

void BinarySearchTree::postorderTraverse(FunctionType visit) {
   postorder(root, visit);
}

void BinarySearchTree::insertItem(TreeNode *& treePtr, const TreeItemType& newItem) noexcept(false) {
   if (treePtr == nullptr)
   {  // position of insertion found; insert after leaf

      // create a new node
      try
      {
    treePtr = new TreeNode(newItem, nullptr, nullptr);
      }
      catch (bad_alloc e)
      {
    throw TreeException(
    "TreeException: insertItem cannot allocate memory");
      }  // end try
   }
   // else search for the insertion position
   else if (newItem.getKey() < treePtr->item.getKey())
      // search the left subtree
      insertItem(treePtr->leftChildPtr, newItem);

   else  // search the right subtree
      insertItem(treePtr->rightChildPtr, newItem);
}

void BinarySearchTree::deleteItem(TreeNode *& treePtr, KeyType searchKey) noexcept(false) {
   if (treePtr == nullptr)
      throw TreeException("TreeException: delete failed");  // empty tree

   else if (searchKey == treePtr->item.getKey())
      // item is in the root of some subtree
      deleteNodeItem(treePtr);  // delete the item

   // else search for the item
   else if (searchKey < treePtr->item.getKey())
      // search the left subtree
      deleteItem(treePtr->leftChildPtr, searchKey);

   else  // search the right subtree
      deleteItem(treePtr->rightChildPtr, searchKey);
}

void BinarySearchTree::deleteNodeItem(TreeNode *& nodePtr) {
// Algorithm note: There are four cases to consider:
//   1. The root is a leaf.
//   2. The root has no left child.
//   3. The root has no right child.
//   4. The root has two children.
   TreeNode     *delPtr;
   TreeItemType replacementItem;

   // test for a leaf
   if ( (nodePtr->leftChildPtr == nullptr) &&
        (nodePtr->rightChildPtr == nullptr) )
   {  delete nodePtr;
      nodePtr = nullptr;
   }  // end if leaf
   // test for no left child
   else if (nodePtr->leftChildPtr == nullptr)
   {  delPtr = nodePtr;
      nodePtr = nodePtr->rightChildPtr;
      delPtr->rightChildPtr = nullptr;
      delete delPtr;
   }  // end if no left child

   // test for no right child
   else if (nodePtr->rightChildPtr == nullptr)
   {  delPtr = nodePtr;
      nodePtr = nodePtr->leftChildPtr;
      delPtr->leftChildPtr = nullptr;
      delete delPtr;
   }  // end if no right child

   // there are two children:
   // retrieve and delete the inorder successor
   else
   {  processLeftmost(nodePtr->rightChildPtr,
                      replacementItem);
      nodePtr->item = replacementItem;
   }  // end if two children
}

void BinarySearchTree::processLeftmost(TreeNode *& nodePtr, TreeItemType& treeItem) {
   if (nodePtr->leftChildPtr == nullptr)
   {  treeItem = nodePtr->item;
      TreeNode *delPtr = nodePtr;
      nodePtr = nodePtr->rightChildPtr;
      delPtr->rightChildPtr = nullptr;  // defense
      delete delPtr;
   }

   else
      processLeftmost(nodePtr->leftChildPtr, treeItem);
}

void BinarySearchTree::retrieveItem(TreeNode *treePtr, KeyType searchKey,
                                             TreeItemType& treeItem) const noexcept(false) {
   if (treePtr == nullptr)
      throw TreeException("TreeException: searchKey not found");

   else if (searchKey == treePtr->item.getKey())
      // item is in the root of some subtree
      treeItem = treePtr->item;

   else if (searchKey < treePtr->item.getKey())
      // search the left subtree
      retrieveItem(treePtr->leftChildPtr,
                   searchKey, treeItem);

   else  // search the right subtree
      retrieveItem(treePtr->rightChildPtr,
                          searchKey, treeItem);
}


BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& rhs) noexcept(false) {
   if (this != &rhs)
   {  destroyTree(root);  // deallocate left-hand side
      copyTree(rhs.root, root);  // copy right-hand side
   }  // end if
   return *this;
}

void BinarySearchTree::copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const noexcept(false) {
   // preorder traversal
   if (treePtr != nullptr)
   {  // copy node
      try
      {
    newTreePtr = new TreeNode(treePtr->item, nullptr, nullptr);
    copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
    copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
      }
      catch (bad_alloc e)
      {
    throw TreeException(
       "TreeException: copyTree cannot allocate memory");
      }
   }
   else
      newTreePtr = nullptr;  // copy empty tree
}

void BinarySearchTree::destroyTree(TreeNode *treePtr) {
   // postorder traversal
   if (treePtr != nullptr)
   {  destroyTree(treePtr->leftChildPtr);
      destroyTree(treePtr->rightChildPtr);
      delete treePtr;
      treePtr = nullptr;
   }
}

TreeNode *BinarySearchTree::rootPtr() const {
   return root;
}

void BinarySearchTree::setRootPtr(TreeNode *newRoot) {
   root = newRoot;
}

void BinarySearchTree::getChildPtrs(TreeNode *nodePtr, TreeNode *& leftPtr, TreeNode *& rightPtr) const {
   leftPtr = nodePtr->leftChildPtr;
   rightPtr = nodePtr->rightChildPtr;
}

void BinarySearchTree::setChildPtrs(TreeNode *nodePtr, TreeNode *leftPtr, TreeNode *rightPtr) {
   nodePtr->leftChildPtr = leftPtr;
   nodePtr->rightChildPtr = rightPtr;
}

void BinarySearchTree::preorder(TreeNode *treePtr, FunctionType visit) {
   if (treePtr != nullptr)
   {  visit(treePtr->item);
      preorder(treePtr->leftChildPtr, visit);
      preorder(treePtr->rightChildPtr, visit);
   }
}

void BinarySearchTree::inorder(TreeNode *treePtr, FunctionType visit) {
   if (treePtr != nullptr)
   {  inorder(treePtr->leftChildPtr, visit);
      visit(treePtr->item);
      inorder(treePtr->rightChildPtr, visit);
   }
}

void BinarySearchTree::postorder(TreeNode *treePtr, FunctionType visit) {
   if (treePtr != nullptr)
   {  postorder(treePtr->leftChildPtr, visit);
      postorder(treePtr->rightChildPtr, visit);
      visit(treePtr->item);
   }
}
