#include "Horse.h"
#include <iostream>
#include <utility>


Horse::Horse(int HorseId, int speed): horseId(HorseId), visited(false), speed(speed), my_count(0)
, follow_count(0),herdID(0), follow(nullptr){
    if(HorseId <=0 || speed<= 0){
        throw std::invalid_argument("Invalid Input");
    }
}

Horse::Horse(const Horse& other): horseId(other.horseId), my_count(other.my_count),
                                  follow_count(other.follow_count), herdID(other.herdID), visited(false), speed(other.speed),
                                  follow(other.follow){}

Horse& Horse::operator=(const Horse& other){
    if (this == &other) { // Self-assignment check
        return *this;
    }
    this->horseId = other.horseId;
    this->herdID = other.herdID;
    this->visited = other.visited;
    this->speed = other.speed;
    this->follow_count = other.follow_count;
    this->my_count = other.my_count;
    this->follow = other.follow;
    return *this;
}

const int Horse::getSpeed() const {
    return speed;
}

const int Horse::getID() const{
    return horseId;
}

 int Horse::getHerd() const{
    return this->herdID;
}

const int Horse::getVisited () const{
    return visited;

}

void Horse::setVisited(bool visit){
    this->visited = visit;
}

void Horse::setSpeed(int Speed){
    this->speed = Speed;
}


void Horse::setHerd(int other){
    this->herdID = other;
}

bool Horse::operator<(const Horse& other) const{
    return this->horseId < other.horseId;
}
bool Horse::operator>(const Horse& other) const{
    return this->horseId > other.horseId;
}

bool operator==(const Horse &horse1, const Horse &horse2) {
    return horse1.getID() == horse2.getID();
}

Horse::~Horse(){
       delete follow;
}

void Horse::setfollow(Horse* other) {
    this->follow = other;

}

Horse* Horse::getfollow() const {
    if(!follow)
        return nullptr;
    return this->follow;
}

int Horse::getMyCount() const {
    return my_count;
}

int Horse::getFollowCount() const {
    return follow_count;
}

void Horse::set_my_count(int other_count) {
    my_count = other_count;
}

void Horse::set_follow_count(int other_count) {
    follow_count = other_count;
}

int Horse::getIndex() const {
    return this->index;
}

void Horse::setIndex(int other_index) {
    index = other_index;
}





