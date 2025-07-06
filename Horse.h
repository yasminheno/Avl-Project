#ifndef DATA_STRUCTURE1_HORSE_H
#define DATA_STRUCTURE1_HORSE_H

#include <memory>
#include "Herd.h"


class Herd;

class Horse{
private:
    int horseId;
    int herdID;
    bool visited;
    int speed;
    int my_count;
    int follow_count;
    Horse* follow;
    int index;


public:
    Horse(int HorseId, int speed);
    Horse(const Horse& other);
    Horse& operator = (const Horse& other);
    const int getSpeed() const;
    const int getID() const;
    operator int() const;
    //shared_ptr<LinkingNode<Horse>> getLinkPrev();
    //shared_ptr<LinkingNode<Horse>> getLinkNext();
    int getHerd () const;
    const int getVisited () const;
    void setVisited(bool visit);
    void setSpeed(int speed);
    //void setLinkNext(shared_ptr<Horse> other);
    void setHerd(int other);
    void setfollow(Horse* other);
    int getMyCount () const;
    int getFollowCount () const;
    void set_my_count (int other_count);
    void set_follow_count (int other_count);
    Horse* getfollow() const;
    void setIndex(int other_index);
    int getIndex() const;
    //void setNextNull();
    ~Horse();
    bool operator<(const Horse& other) const;
    bool operator>(const Horse& other) const;
    friend bool operator==(const Horse& horse1, const Horse& horse2);




};


#endif //DATA_STRUCTURE1_HORSE_H