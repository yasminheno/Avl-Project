#ifndef AVLTREE_DATASTRUCTRE1_H
#define AVLTREE_DATASTRUCTRE1_H

#include "TreeNode.h"
#include <functional>
#include <cmath>
#include <memory>

using std::shared_ptr;
using std::endl;
using std::cout;
using std::iostream;

template<class Key, class Value>
class Tree{
private:
    TreeNode<Key,Value>* root;
    int size;
public:
    Tree();
    Tree(TreeNode<Key,Value>* root);
    Tree(const Tree<Key,Value>& Tree) = default;
    ~Tree();

    void rrRotate (TreeNode<Key,Value>* unbalanced_node);//done
    void llRotate (TreeNode<Key,Value>* unbalanced_node); //done
    void lrRotate (TreeNode<Key,Value>* unbalanced_node);//done
    void rlRotate (TreeNode<Key,Value>* unbalanced_node);// done
    void insert(Value value,const Key& key);
    void remove(Key key);
    int getSize() const;
    TreeNode<Key,Value>* getRoot() const;
    TreeNode<Key,Value>* find(const Key& key);//done
    bool apply_rotation(TreeNode<Key,Value>* node);//done
    TreeNode<Key,Value>* findMinimalNode(TreeNode<Key,Value>* root_node);//done
    TreeNode<Key,Value>* findMaximalNode(TreeNode<Key,Value>* root_node);
    void printInOrder(TreeNode<Key, Value>* node) const;
    void printPostOrder(TreeNode<Key, Value>* node) const;
    void printPreOrder(TreeNode<Key, Value>* node) const;
    void inorderToArray(TreeNode<Key, Value>* root_node, TreeNode<Key, Value>** array, int& index);
    void clear();
    bool isEmpty() const;




};

template<class Key, class Value>
Tree<Key,Value>::~Tree(){
    clear();
}

template<class Key, class Value>
Tree<Key, Value>::Tree(TreeNode<Key, Value>* root):size(0), root(root) {
    if(root != nullptr){
        size = 1;
    }
}


template<class Key, class Value>
bool Tree<Key, Value>::isEmpty() const {
    return this->root == nullptr; // Tree is empty if root is null
}


template <class Key, class Value>
void Tree<Key, Value>::inorderToArray(TreeNode<Key, Value>* root_node,
                                      TreeNode<Key, Value>** array,
                                      int &index) {  // Pass index by reference
    if (!root_node) return;
    // Recurse on the left subtree
    inorderToArray(root_node->getLeft(), array, index);
    // Store the pointer to the current node in the array
    array[index++] = root_node;
    // Recurse on the right subtree
    inorderToArray(root_node->getRight(), array, index);
}


template<class Key, class Value>
Tree<Key,Value>::Tree() : root(nullptr), size(0){}


template<class Key, class Value>
void Tree<Key, Value>::remove(Key key) {
    TreeNode<Key,Value>* node = find(key);
    if (node == nullptr) return;
    if (root == nullptr) return;

    TreeNode<Key, Value>* parent = node->getFather();

    //removing a leaf
    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        if (parent == nullptr)
            root = nullptr;
        else if (parent->getLeft() == node)
            parent->setFather(nullptr);
        else
            parent->setRight(nullptr);

        delete node;
       parent->updateHeight();
        size--;
    }

        //removing a node with only a getLeft child
    else if (node->getRight() == nullptr) {
        if (parent == nullptr) {
            root = node->getLeft();
            root->setFather(nullptr);
        }
        else if (parent->getLeft() == node) {
            parent->setLeft(node->getLeft());
            node->getLeft()->setFather(parent);
        }
        else {
            parent->setFather(node->getLeft());
            node->getLeft()->setFather(parent);
        }
        delete node;
        parent->updateHeight();
        size--;
    }

        //removing a node with only a getRight child
    else if (node->getLeft() == nullptr) {
        if (parent == nullptr) {
            root = node->getRight();
            root->setFather(nullptr);
        }
        else if (parent->getLeft() == node) {
            parent->setLeft(node->getRight());
            node->getRight()->setFather(parent);
        }
        else {
            parent->setRight(node->getRight());
            node->getRight()->setFather(parent);
        }
        delete node;
        parent->updateHeight();
        size--;
    }


    else {
        TreeNode<Key, Value>* temp = node->getRight();
        while (temp->getLeft() != nullptr)
            temp = temp->getLeft();
        node->setKey(temp->getKey());
        remove(temp->getKey());
    }
}


template<class Key, class Value>
void Tree<Key, Value>::llRotate(TreeNode<Key, Value>* unbalanced_node) {
    if (!unbalanced_node || !unbalanced_node->getLeft()) return;

    TreeNode<Key, Value>* left_child = unbalanced_node->getLeft();
    unbalanced_node->setLeft(left_child->getRight());
    if (left_child->getRight()) {
        left_child->getRight()->setFather(unbalanced_node);
    }

    left_child->setFather(unbalanced_node->getFather());
    if (!unbalanced_node->getFather()) {
        this->root = left_child;
    } else if (unbalanced_node->getFather()->getLeft() == unbalanced_node) {
        unbalanced_node->getFather()->setLeft(left_child);
    } else {
        unbalanced_node->getFather()->setRight(left_child);
    }

    left_child->setRight(unbalanced_node);
    unbalanced_node->setFather(left_child);

    // Update heights
    unbalanced_node->updateHeight();
    left_child->updateHeight();
    //unbalanced_node->getRight()->updateHeight();
}


template<class Key, class Value>
void Tree<Key, Value>::rrRotate(TreeNode<Key, Value>* unbalanced_node) {
    if (!unbalanced_node || !unbalanced_node->getRight()){
        return;
    }

    TreeNode<Key, Value>* right_child = unbalanced_node->getRight();
    unbalanced_node->setRight(right_child->getLeft());
    if (right_child->getLeft()) {
        right_child->getLeft()->setFather(unbalanced_node);
    }

    right_child->setFather(unbalanced_node->getFather());
    if (!unbalanced_node->getFather()) {
        this->root = right_child;
    } else if (unbalanced_node->getFather()->getLeft() == unbalanced_node) {
        unbalanced_node->getFather()->setLeft(right_child);
    } else {
        unbalanced_node->getFather()->setRight(right_child);
    }

    right_child->setLeft(unbalanced_node);
    unbalanced_node->setFather(right_child);

    unbalanced_node->updateHeight();
    right_child->updateHeight();
    //unbalanced_node->getLeft()->updateHeight();
}

template<class Key, class Value>
void Tree<Key,Value>::lrRotate(TreeNode<Key,Value>* unbalanced_node) {
    if (!unbalanced_node || !unbalanced_node->getLeft()) return;

    rrRotate(unbalanced_node->getLeft());
    llRotate(unbalanced_node);
}

template<class Key, class Value>
void Tree<Key,Value>::rlRotate(TreeNode<Key,Value>* unbalanced_node) {
    if (!unbalanced_node || !unbalanced_node->getRight()) return;
    llRotate(unbalanced_node->getRight());
    rrRotate(unbalanced_node);
}


template<class Key, class Value>
int Tree<Key,Value>::getSize() const{
    return this->size;
}

template<class Key, class Value>
TreeNode<Key,Value>* Tree<Key,Value>::getRoot() const {
    return this->root;
}

template<class Key, class Value>
void Tree<Key, Value>::insert(Value value, const Key& key) {
    if (find(key) != nullptr) return; // Key already exists

   TreeNode<Key, Value>* new_node = new TreeNode<Key,Value>(key,value);
    TreeNode<Key, Value>* temp = this->root;
    TreeNode<Key, Value>* temp_father = nullptr;

    while (temp != nullptr) {
        temp_father = temp;
        if (key < temp->getKey()) {
            temp = temp->getLeft();
        } else {
            temp = temp->getRight();
        }
    }

    new_node->setFather(temp_father);
    if (temp_father == nullptr) {
        this->root = new_node; // Tree was empty
    } else if (key < temp_father->getKey()) {
        temp_father->setLeft(new_node);
    } else {
        temp_father->setRight(new_node);
    }

    size++;

    // Update heights and balance the tree
    TreeNode<Key, Value>* current = temp_father;
    while (current != nullptr) {
        current->updateHeight();       // Update the height
        apply_rotation(current);       // Check and apply rotations
        current = current->getFather(); // Move up to the parent
    }
}



template<class Key, class Value>
TreeNode<Key,Value>* Tree<Key,Value>::find(const Key& key) {
    TreeNode<Key,Value>* temp = this->root;
    while (temp != nullptr) {
        if (temp->getKey() == key) {
            return temp;
        } else if (temp->getKey()> key) {
            temp = temp->getLeft();
        } else {
            temp = temp->getRight(); // Move to the right subtree
        }
    }
    return nullptr; // Node with the specified ID not found
}



template<class Key, class Value>
bool Tree<Key,Value>::apply_rotation(TreeNode<Key,Value>* node){
    int balance_factor = node->balanceFactor();
    if (balance_factor == 2)
    {
        if(node->getLeft()->balanceFactor() == -1){
            lrRotate(node);

            return true;
        }
        else if(node->getLeft()->balanceFactor() >= 0){
            llRotate(node);
            return true;
        }
    }
    else if (balance_factor == -2)
    {
        if(node->getRight()->balanceFactor() <= 0)  {
            rrRotate(node);
            return true;
        }
        else if (node->getRight()->balanceFactor() == 1) {
            rlRotate(node);
            return true;
        }
    }
    return false;
}

template<class Key, class Value>
TreeNode<Key,Value>* Tree<Key,Value>::findMaximalNode(TreeNode<Key, Value>* root_node){
    if(root_node == nullptr)
        return nullptr;
    while (root_node->getRight() != nullptr)
        root_node = root_node->getRight();
    return root_node;
}

template<class Key, class Value>
TreeNode<Key,Value>* Tree<Key,Value>::findMinimalNode(TreeNode<Key,Value>* root_node){
    if(root_node == nullptr)
        return nullptr;
    while (root_node->getLeft() != nullptr)
        root_node = root_node->getLeft();
    return root_node;
}




template<class Key, class Value>
void Tree<Key, Value>::printInOrder(TreeNode<Key, Value>* node) const {
    if (node == nullptr) {
        return;
    }
    printInOrder(node->getLeft());
    cout << node->getKey() << ' ';
    printInOrder(node->getRight());
}

template<class Key, class Value>
void Tree<Key, Value>::printPostOrder(TreeNode<Key, Value>* node) const {
    if (node == nullptr) return;
    printPostOrder(node->getLeft());
    printPostOrder(node->getRight());
    cout << node->getKey() << ' ';

}

template<class Key, class Value>
void Tree<Key, Value>::printPreOrder(TreeNode<Key, Value>* node) const {
    if (node == nullptr) return;
    cout << node->getKey() << ' ';
    printPreOrder(node->getLeft());
    printPreOrder(node->getRight());
}




template<class Key, class Value>
void inorderTraversal(TreeNode<Key, Value>* root, void (&visit)(TreeNode<Key, Value>&)) {
    if (root == nullptr) return;

    // Visit left subtree
    inorderTraversal(root->getLeft(), visit);

    // Visit current node
    visit(*root);

    // Visit right subtree
    inorderTraversal(root->getRight(), visit);
}

template<class Key, class Value>
void Tree<Key, Value>::clear() {
    while (root != nullptr)
        remove(root->getKey());
}


#endif