#ifndef HERD_DATASTRUCTRE1_H
#define HERD_DATASTRUCTRE1_H



#include "AVLTree.h" // Ensure this header defines Tree as a template
#include "Horse.h" // Ensure Horse class is defined
#include "TreeNode.h"
#include <memory>


class Horse; //pre declaration
using std::unique_ptr;


class Herd {
private:
    int HerdId;              // ID of the Herd
   Tree<int,Horse*>* horses;      // Tree of Horse objects

public:
    // Constructor
    explicit Herd(int HerdId);
    Herd(const Herd& other) = default;
    ~Herd();
    int getID() const;
    Tree<int,Horse*>* getHorsesTree();
    bool operator<(const Herd& other) const;
    bool operator>(const Herd& other) const;
    friend bool operator==(const Herd& herd1, const Herd& herd2);
};

#endif
