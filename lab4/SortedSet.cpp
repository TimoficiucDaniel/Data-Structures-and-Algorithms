#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
    this->r = r;
    cap = 13;
    tableSize = 0;
    primeNumber = 11;
    head = -1;
    table = new TElem *[13];
    for (int i = 0; i <= 12; i++){
        table[i]  = new TElem[2];
        table[i][1] = -1;
        table[i][0] = -10000;
    }
}


bool SortedSet::add(TComp elem) {
	if(search(elem))
        return false;
	if(tableSize == cap)
        resize();
    int probe = h1(elem);
    int offset = h2(elem);
    if(head == -1)

}


bool SortedSet::remove(TComp elem) {
	//TODO - Implementation
	return false;
}


bool SortedSet::search(TComp elem) const {
    int probe = h1(elem);
    int offset = h2(elem);
    int initialPos = probe;
    bool firstItr = true;
    while(true){
        if(table[probe][0]==-10000)
            break;
        else if(table[probe][0] == elem)
            return true;
        else if(probe == initialPos && !firstItr)
            return false;
        else
            probe = (probe+offset)%cap;
        firstItr = false;
    }
	return false;
}


int SortedSet::size() const {
	//TODO - Implementation
	return 0;
}



bool SortedSet::isEmpty() const {
	//TODO - Implementation
	return false;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
	//TODO - Implementation
}

int SortedSet::h1(TComp key) const {
    return key%cap;
}

int SortedSet::h2(TComp key) const {
    return primeNumber-(key%primeNumber);
}

void SortedSet::resize() {

}


