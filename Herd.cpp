

#include "Herd.h"
#include "Horse.h"
#include "TreeNode.h"




Herd::Herd(int HerdId): HerdId(HerdId), horses(nullptr){
    if(HerdId <=0){
        throw std::invalid_argument("Invalid Input");
    }
}

int Herd::getID() const{
    return this->HerdId;
}

Tree<int,Horse*>* Herd::getHorsesTree(){
    if(!horses)
        return nullptr;
    return horses;
}

bool operator==(const Herd &herd1, const Herd &herd2) {

    return herd1.getID()==herd2.getID();
}

bool Herd::operator<(const Herd& other) const{
    return this->HerdId < other.HerdId;
}
bool Herd::operator>(const Herd& other) const{
    return this->HerdId > other.HerdId;
}

Herd::~Herd() {
    delete horses;

}

