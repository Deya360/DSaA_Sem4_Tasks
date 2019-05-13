#include "binarytree.h"

using namespace std;

BinaryTree::BinaryTree() : root(nullptr) {}

BinaryTree::BinaryTree(const TreeItemType& rootItem) {
    try{
        root = new TreeNode(rootItem, nullptr, nullptr);

    } catch (bad_alloc e) {
        delete root;
        throw TreeException("TreeException: constructor cannot allocate memory");
    }
}

BinaryTree::BinaryTree(const TreeItemType& rootItem, BinaryTree& leftTree, BinaryTree& rightTree) {
    try {
        root = new TreeNode(rootItem, nullptr, nullptr);

        attachLeftSubtree(leftTree);
        attachRightSubtree(rightTree);
    } catch (bad_alloc e) {
        delete root;
        throw TreeException("TreeException: constructor cannot allocate memory");
    }
}

BinaryTree::BinaryTree(const BinaryTree& tree) {
    try {
        copyTree(tree.root, root);

    } catch (bad_alloc e) {
        destroyTree(tree.root);
        throw TreeException("TreeException: copy constructor cannot allocate memory");
    }
}

BinaryTree::BinaryTree(TreeNode *nodePtr) : root(nodePtr) {}

BinaryTree::~BinaryTree() {
    destroyTree(root);
}

bool BinaryTree::isEmpty() const {
    return (root == nullptr);
}

int BinaryTree::getHeight() const {
    return getMaxDepth(root);
}
int BinaryTree::getMaxDepth(TreeNode* node) const {
    if (node == nullptr) return 0;
    else {
        int lDepth = getMaxDepth(node->leftChildPtr);
        int rDepth = getMaxDepth(node->rightChildPtr);

        if (lDepth > rDepth) return(lDepth + 1);
        else return(rDepth + 1);
    }
}

int BinaryTree::getNumberOfNodes() const {
    return getFullCount(root);
}
int BinaryTree::getFullCount(TreeNode* root) const {
    if (root == nullptr) return 0;

    int res = 0;
    if  (root->leftChildPtr && root->rightChildPtr)
       res++;

    res += (getFullCount(root->leftChildPtr) +
            getFullCount(root->rightChildPtr));
    return res;
}

bool BinaryTree::add(const TreeItemType &newData) {
    return crawl_add(newData);
}
bool BinaryTree::crawl_add(const TreeItemType &item) {
    if (!root) {
        root = new TreeNode(item);
        return true;
    }

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* temp = q.front();
        q.pop();

        if (!temp->leftChildPtr) {
            temp->leftChildPtr = new TreeNode(item);
            return true;
        }
        else q.push(temp->leftChildPtr);

        if (!temp->rightChildPtr) {
            temp->rightChildPtr = new TreeNode(item);
            return true;
        }
        else q.push(temp->rightChildPtr);
    }
    return false;
}


bool BinaryTree::remove(const TreeItemType &data) {
    return crawl_remove(data);
}
bool BinaryTree::crawl_remove(const TreeItemType &item) {
    if (root) {
        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* temp = q.front();
            q.pop();

            if (temp->leftChildPtr) {
                if (temp->leftChildPtr->leftChildPtr || temp->leftChildPtr->rightChildPtr) {
                    q.push(temp->leftChildPtr);

                } else if (temp->leftChildPtr->getItem() == item) {
                    destroyTree(temp->leftChildPtr);
                    return true;
                }
            }

            if (temp->rightChildPtr) {
                if (temp->rightChildPtr->leftChildPtr || temp->rightChildPtr->rightChildPtr) {
                    q.push(temp->rightChildPtr);

                } else if (temp->rightChildPtr->getItem() == item) {
                    destroyTree(temp->rightChildPtr);
                    return true;
                }
            }
        }

        if (root->getItem()==item) {
            destroyTree(root);
            return true;
        }
    }
    return false;
}


bool BinaryTree::contatins(const TreeItemType &data) {
    return crawl_contatins(data);
}

TreeItemType BinaryTree::getEntry(const TreeItemType &anEntry) {
    TreeNode *tempTN = crawl_contatins(anEntry);
    if(tempTN) return tempTN->getItem();
    throw TreeException("TreeException: Entry dosen't exist in tree");
}

TreeNode *BinaryTree::crawl_contatins(const TreeItemType &data) {
    if (root) {
        if (root->getItem()==data)
            return root;

        std::queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* temp = q.front();
            q.pop();

            if (temp->leftChildPtr) {
                if (temp->leftChildPtr->getItem()==data) return temp->leftChildPtr;
                else q.push(temp->leftChildPtr);
            }

            if (temp->leftChildPtr) {
                if (temp->leftChildPtr->getItem()==data) return temp->leftChildPtr;
                else q.push(temp->leftChildPtr);
            }
        }
    }
    return nullptr;
}

void BinaryTree::clear() const {
    destroyTree(root);
}

TreeItemType BinaryTree::getRootData() const {
    if (isEmpty())
        throw TreeException("TreeException: Empty tree");
    return root->item;
}

void BinaryTree::setRootData(const TreeItemType& newItem) {
    if (!isEmpty()) root->item = newItem;
    else root = new TreeNode(newItem, nullptr, nullptr);
}

void BinaryTree::attachLeft(const TreeItemType& newItem) {
    if (isEmpty())
        throw TreeException("TreeException: Empty tree");

    else if (root->leftChildPtr != nullptr)
        throw TreeException("TreeException: Cannot overwrite left subtree");

    else { // Assertion: nonempty tree; no left child
        try {
            root->leftChildPtr = new TreeNode(newItem, nullptr, nullptr);

        } catch (bad_alloc e) {
            throw TreeException("TreeException: attachLeft cannot allocate memory");
        }
    }
}

void BinaryTree::attachRight(const TreeItemType& newItem) {
    if (isEmpty())
        throw TreeException("TreeException: Empty tree");

    else if (root->rightChildPtr != nullptr)
        throw TreeException("TreeException: Cannot overwrite right subtree");

    else {  // Assertion: nonempty tree; no right child
        try {
            root->rightChildPtr = new TreeNode(newItem, nullptr, nullptr);

        } catch (bad_alloc e) {
            throw TreeException("TreeException: attachRight cannot allocate memory");
        }
    }
}

void BinaryTree::attachLeftSubtree(BinaryTree& leftTree) {
    if (isEmpty())
        throw TreeException("TreeException: Empty tree");

    else if (root->leftChildPtr != nullptr)
        throw TreeException("TreeException: Cannot overwrite left subtree");

    else {
        root->leftChildPtr = leftTree.root;
        leftTree.root = nullptr;
    }
}

void BinaryTree::attachRightSubtree(BinaryTree& rightTree) {
    if (isEmpty())
        throw TreeException("TreeException: Empty tree");

    else if (root->rightChildPtr != nullptr)
        throw TreeException("TreeException: Cannot overwrite right subtree");

    else {
        root->rightChildPtr = rightTree.root;
        rightTree.root = nullptr;
    }
}

void BinaryTree::detachLeftSubtree(BinaryTree& leftTree) {
    if (isEmpty())
        throw TreeException("TreeException: Empty tree");

    else {
        leftTree = BinaryTree(root->leftChildPtr);
        root->leftChildPtr = nullptr;
    }
}

void BinaryTree::detachRightSubtree(BinaryTree& rightTree) {
    if (isEmpty())
        throw TreeException("TreeException: Empty tree");

    else {
        rightTree = BinaryTree(root->rightChildPtr);
        root->rightChildPtr = nullptr;
    }
}

BinaryTree BinaryTree::getLeftSubtree() const {
    TreeNode *subTreePtr;

    if (isEmpty())
    return BinaryTree();
    else {
        copyTree(root->leftChildPtr, subTreePtr);
        return BinaryTree(subTreePtr);
    }
}

BinaryTree BinaryTree::getRightSubtree() const {
    TreeNode *subTreePtr;

    if (isEmpty()) return BinaryTree();
    else {
        copyTree(root->rightChildPtr, subTreePtr);
        return BinaryTree(subTreePtr);
    }
}

void BinaryTree::preorderTraverse(FunctionType visit) {
    preorder(root, visit);
}

void BinaryTree::inorderTraverse(FunctionType visit) {
    inorder(root, visit);
}

void BinaryTree::postorderTraverse(FunctionType visit) {
    postorder(root, visit);
}

void BinaryTree::breadthFirstTraverse(FunctionType visit) {
    breadthFirst(root, visit);
}

std::vector<KeyedItem> *BinaryTree::getBreadthFirstVector() {
    return breadthFirst(root, t);
}
void BinaryTree::t(KeyedItem &someItem) {
    someItem = someItem; //really deya?!
}

int BinaryTree::getDiameter() const {
    int height = 0;
    return getDiameterUtil(root, &height);
}

std::vector<KeyedItem>* BinaryTree::getDiameterPath(bool diffHeightOnly) const {
    std::vector<KeyedItem> *diameterPath = new std::vector<KeyedItem>;
    return getMaxPath(root, diameterPath, diffHeightOnly);
}

BinaryTree& BinaryTree::operator=(const BinaryTree& rhs) {
    if (this != &rhs) {
        destroyTree(root);  // deallocate left-hand side
        copyTree(rhs.root, root);  // copy right-hand side
    }
    return *this;
}

void BinaryTree::copyTree(TreeNode *treePtr, TreeNode *& newTreePtr) const {
    // preorder traversal
    if (treePtr != nullptr) {  // copy node
        try {
            newTreePtr = new TreeNode(treePtr->item, nullptr, nullptr);
            copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
            copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);

        } catch (bad_alloc e) {
            throw TreeException("TreeException: copyTree cannot allocate memory");
        }

    } else newTreePtr = nullptr;  // copy empty tree
}

void BinaryTree::destroyTree(TreeNode *treePtr) const {
    // postorder traversal
    if (treePtr != nullptr) {
        destroyTree(treePtr->leftChildPtr);
        destroyTree(treePtr->rightChildPtr);
        delete treePtr;
        treePtr = nullptr;
    }
}

TreeNode *BinaryTree::rootPtr() const {
    return root;
}

void BinaryTree::setRootPtr(TreeNode *newRoot) {
    root = newRoot;
}

void BinaryTree::getChildPtrs(TreeNode *nodePtr, TreeNode *& leftPtr, TreeNode *& rightPtr) const {
    leftPtr = nodePtr->leftChildPtr;
    rightPtr = nodePtr->rightChildPtr;
}

void BinaryTree::setChildPtrs(TreeNode *nodePtr, TreeNode *leftPtr, TreeNode *rightPtr) {
    nodePtr->leftChildPtr = leftPtr;
    nodePtr->rightChildPtr = rightPtr;
}

void BinaryTree::preorder(TreeNode *treePtr, FunctionType visit) {
    if (treePtr != nullptr) {
        visit(treePtr->item);
        preorder(treePtr->leftChildPtr, visit);
        preorder(treePtr->rightChildPtr, visit);
    }
}

void BinaryTree::inorder(TreeNode *treePtr, FunctionType visit) {
    if (treePtr != nullptr) {
        inorder(treePtr->leftChildPtr, visit);
        visit(treePtr->item);
        inorder(treePtr->rightChildPtr, visit);
    }
}

void BinaryTree::postorder(TreeNode *treePtr, FunctionType visit) {
    if (treePtr != nullptr) {
        postorder(treePtr->leftChildPtr, visit);
        postorder(treePtr->rightChildPtr, visit);
        visit(treePtr->item);
    }
}

std::vector<KeyedItem> *BinaryTree::breadthFirst(TreeNode *treePtr, FunctionType visit) {
    if (treePtr != nullptr) {
        std::vector<KeyedItem> *vec = new std::vector<KeyedItem>;
        vec->push_back(root->getItem());

        std::queue<TreeNode*> q;
        q.push(treePtr);

        int count = 1;
        int treeDepth = getMaxDepth(root);
        while (count < pow(2,treeDepth)) {
            TreeNode *temp = q.front();
            visit(temp->item);
            q.pop();

            if (temp->leftChildPtr != nullptr) {
                q.push(temp->leftChildPtr);
                vec->push_back(temp->leftChildPtr->getItem());
            } else {
                TreeNode *temp2 = buildTree(treeDepth-calculateDepth(count));
                q.push(temp2);
                vec->push_back(temp2->getItem().getKey());
            }
            count++;

            if (temp->rightChildPtr != nullptr) {
                q.push(temp->rightChildPtr);
                vec->push_back(temp->rightChildPtr->getItem());
            } else {
                TreeNode *temp2 = buildTree(treeDepth-calculateDepth(count));
                q.push(temp2);
                vec->push_back(temp2->getItem());
            }
            count++;
        }

        return vec;
    }
    return nullptr;
}
TreeNode* BinaryTree::buildTree(int depth) {
    TreeNode *t = new TreeNode(KeyedItem(""));
    if (depth > 1) {
        t->leftChildPtr = buildTree(depth-1);
        t->rightChildPtr = buildTree(depth-1);
    }
    return t;
}
int BinaryTree::calculateDepth(int count) {
    int c = 0;
    while (count > pow(2,c)) c++;
    if (c<3) return 1;
    return c-2;
}

void BinaryTree::generateRandomTree(int nodeTarget, int valMin, int valMax) {
    std::random_device r;
    std::mt19937 engine{static_cast<long unsigned int>(time(nullptr))};;
    std::uniform_int_distribution<int> nodeR(0, 5); //  a 5/6 chance to create a node
    std::uniform_int_distribution<int> valR(valMin, valMax);

    std::set<int> randSet;
    while (randSet.size() < nodeTarget+1) randSet.insert(valR(engine));

    std::vector<int> vals(randSet.size());
    std::copy(randSet.begin(), randSet.end(), vals.begin());

    std::queue<TreeNode*> q;
    TreeNode *rootM = new TreeNode(KeyedItem(std::to_string(vals.at(0))));
    q.push(rootM);

    int nodeCount = 1;
    TreeNode *curNode;
    while (nodeCount < nodeTarget) {
        if (q.size()!=0) {
            curNode = q.front();
            q.pop();
        }

        if(nodeR(engine)) {
            curNode->leftChildPtr = new TreeNode(KeyedItem(std::to_string(vals.at(nodeCount))));
            q.push(curNode->leftChildPtr);
            nodeCount++;
        }

        if(nodeR(engine)) {
            curNode->rightChildPtr = new TreeNode(KeyedItem(std::to_string(vals.at(nodeCount))));
            q.push(curNode->rightChildPtr);
            nodeCount++;
        }

//        if (nodeCount > nodeTarget/2) nodeR = std::uniform_int_distribution<int>(0, 2); // a 2/3 chance
    }
    root = rootM;
}

int BinaryTree::getDiameterUtil(TreeNode *rootM, int *height) const {
    int lh = 0, rh = 0;
    int ldiameter = 0, rdiameter = 0;
    if(rootM == nullptr) {
        *height = 0;
        return 0;
    }

    ldiameter = getDiameterUtil(rootM->leftChildPtr, &lh);
    rdiameter = getDiameterUtil(rootM->rightChildPtr, &rh);

    *height = max(lh, rh) + 1;

    return max(lh + rh + 1, max(ldiameter, rdiameter));
}


std::vector<KeyedItem>* BinaryTree::getMaxPath(TreeNode *rootM, std::vector<KeyedItem> *path, bool diffHeightOnly) const {
    std::vector<KeyedItem> *ldiameter;
    std::vector<KeyedItem> *rdiameter;

    if(rootM == nullptr || (rootM->leftChildPtr == nullptr && rootM->rightChildPtr == nullptr)) {
        path->clear();
        return new std::vector<KeyedItem>;
    }

    std::vector<KeyedItem> *lpath = new std::vector<KeyedItem>;
    lpath->push_back(rootM->getItem());
    std::vector<KeyedItem> *rpath = new std::vector<KeyedItem>;
    rpath->push_back(rootM->getItem());

    ldiameter = getMaxPath(rootM->leftChildPtr, lpath);
    rdiameter = getMaxPath(rootM->rightChildPtr, rpath);


    if ((lpath->size()==rpath->size()) && (lpath->size()==0)) {
        path->insert(path->end(),rootM->getItem());
    } else if (lpath->size() == rpath->size()) {
        std::random_device r;
        std::mt19937 engine{static_cast<long unsigned int>(time(nullptr))};;
        std::uniform_int_distribution<int> nodeR(0, 1);

        if (nodeR(engine)) {
            path->insert(path->end(),lpath->begin(),lpath->end());
        } else {
            path->insert(path->end(),rpath->begin(),rpath->end());
        }

    } else if (lpath->size() > rpath->size()) {
        path->insert(path->end(),lpath->begin(),lpath->end());
    } else {
        path->insert(path->end(),rpath->begin(),rpath->end());
    }

    std::vector<KeyedItem> *lrpath;
    lrpath = lpath;
    std::reverse(lrpath->begin(),lrpath->end());
    if (rpath->size() > 1) {
        if (lpath->size()==rpath->size() && diffHeightOnly) {
            lrpath->insert(lrpath->end(),rpath->begin()+1,rpath->end()-1);
        } else { //Normal
            lrpath->insert(lrpath->end(),rpath->begin()+1,rpath->end());
        }

    } else {
        lrpath->insert(lrpath->end(),rpath->begin(),rpath->end());
    }

    if (lrpath->size() > max(ldiameter->size(),rdiameter->size())) {
        return lrpath;
    } else {
        if (ldiameter->size() > rdiameter->size()) {
            return ldiameter;
        } else {
            return rdiameter;
        }
    }
}


