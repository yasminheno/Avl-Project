#ifndef DATA_STRUCTURE1_AVLTREENODE_H
#define DATA_STRUCTURE1_AVLTREENODE_H
#include <iostream>
#include <memory>
using std::shared_ptr;

template<class Key, class Value>
class TreeNode{
private:
    Key key;
    Value data;
    TreeNode<Key,Value>* left;
    TreeNode<Key,Value>* right;
    TreeNode<Key,Value>* father;
    int height;

public:
    TreeNode(const Key& key = Key(),const Value& data = Value(),
             TreeNode<Key, Value>* left = nullptr,
             TreeNode<Key, Value>* right = nullptr,
             TreeNode<Key, Value>* father = nullptr,
             int height = 0);
    TreeNode (const TreeNode<Key,Value>& tree_node) = default;
    ~TreeNode() = default;

    TreeNode<Key,Value>* getLeft();
    TreeNode<Key,Value>* getRight();
    TreeNode<Key,Value>* getFather();
    Value getData();
    Key getKey();
    int getHeight();

    void setData(const Value& new_data);
    void setLeft(TreeNode<Key,Value>* new_left);
    void setRight(TreeNode<Key,Value>* new_right);
    void setFather(TreeNode<Key,Value>* new_father);
    void setHeight(int new_height);
    void setKey(int new_key);
    int balanceFactor();
    int max(int height_a, int height_b);

    void updateHeight();
    bool operator <(TreeNode<Key,Value>* otherNode);
    bool operator >(TreeNode<Key,Value>* otherNode);
    void clearNode();

    template<class K,class V>
    friend bool operator==(const TreeNode<Key, Value>& first_tree, const TreeNode<Key, Value>& second_tree);
};

template<class Key, class Value>
TreeNode<Key, Value>::TreeNode(const Key &key, const Value &data, TreeNode<Key, Value>* left,
                               TreeNode<Key, Value>* right, TreeNode<Key, Value>* father, int height) :
        key(key),data(data),left(left),right(right),father(father),height(height){}

template<class Key, class Value>
Value TreeNode<Key, Value>::getData() {
    return this->data;
}

template <class Key, class Value>
bool operator==(const TreeNode<Key, Value>& first_tree, const TreeNode<Key, Value>& second_tree) {
    if (!first_tree.data || !second_tree.data) {
        return false;
    }
    return first_tree.key == second_tree.key;
}



template<class Key, class Value>
TreeNode<Key,Value>* TreeNode<Key,Value>::getLeft() {
    return left;
}

template<class Key, class Value>
TreeNode<Key,Value>* TreeNode<Key,Value>::getRight() {
    return right;
}

template<class Key, class Value>
TreeNode<Key,Value>* TreeNode<Key,Value>::getFather() {
    return father;
}

template<class Key, class Value>
Key TreeNode<Key, Value>::getKey(){
    return key;
}

template<class Key, class Value>
int TreeNode<Key,Value>::getHeight() {
    return height;
}


template<class Key, class Value>
void TreeNode<Key,Value>::setLeft(TreeNode<Key,Value>* new_left){
    this->left = new_left;
}

template<class Key, class Value>
void TreeNode<Key,Value>::setRight(TreeNode<Key,Value>* new_right){
    this->right = new_right;
}


template<class Key, class Value>
void TreeNode<Key,Value>::setData(const Value& new_data){
    this->data = new_data;
}



template<class Key, class Value>
void TreeNode<Key,Value>::setFather(TreeNode<Key, Value>* new_father) {
    this->father = new_father;
}

template<class Key, class Value>
void TreeNode<Key,Value>::setHeight(int new_height) {
    this->height = new_height;
}

template<class Key, class Value>
void TreeNode<Key,Value>::setKey(int new_key){
    this->key = new_key;
}

template<class Key, class Value>
int TreeNode<Key,Value>::max(int height_a, int height_b){
    if(height_a > height_b){
        return height_a;
    }
    return height_b;
}

template<class Key, class Value>
void TreeNode<Key, Value>::updateHeight() {
    int left_height = (this->left) ? this->left->getHeight() : -1;
    int right_height = (this->right) ? this->right->getHeight() : -1;
    this->height = 1 + std::max(left_height, right_height);
}


template<class Key, class Value>
bool TreeNode<Key,Value>::operator<(TreeNode<Key,Value>* otherNode) {
    if (!otherNode) {
        throw std::invalid_argument("Cannot compare with a null TreeNode.");
    }
    return data < otherNode->getData();
}

template<class Key, class Value>
bool TreeNode<Key,Value>::operator>(TreeNode<Key,Value>* otherNode) {
    if (!otherNode) {
        throw std::invalid_argument("Cannot compare with a null TreeNode.");
    }
    return this->data > otherNode->getData();
}

template<class Key, class Value>
int TreeNode<Key,Value>::balanceFactor() {
    int left_height = (this->left) ? this->getLeft()->height : -1;
    int right_height = (this->right) ? this->getRight()->height : -1;
    return left_height - right_height;
}

template<class Key, class Value>
void TreeNode<Key, Value>::clearNode(){
    this->father = nullptr;
    this->right = nullptr;
    this->left = nullptr;
}

#endif //DATA_STRUCTURE1_AVLTREENODE_H