#include "SortedBagIterator.h"
#include <exception>

using namespace std;

/**
 * constructor bc= wc =overall theta(1)
 * @param b
 */
SortedBagIterator::SortedBagIterator(SortedBag& b) : bag(b) {
	this->index = 0;
    this->sideIndex = 0;
}

/**
 * bc = wc = overall theta(1)
 * @return
 */
TComp SortedBagIterator::getCurrent() {
    if(this->valid())
	    return this->bag.array[this->index][0];
    throw exception();
}

/**
 * bc= wc=overall theta(1)
 * @return
 */
bool SortedBagIterator::valid() {
	if(this->index == this->bag.arrsize)
        return false;
	return true;
}
/**
 * wc=bc=overall theta(1)
 */
void SortedBagIterator::next() {
    {
        if(this->valid()){
            if(this->sideIndex < this->bag.array[this->index][1]-1)
                this->sideIndex ++;
            else
            {
                this->index ++;
                this->sideIndex = 0;
            }
        }
        else
            throw exception();
    }
}
/**
 * wc=bc=overall theta(1)
 */
void SortedBagIterator::first() {
	this->index = 0;
    this->sideIndex = 0;
}

TElem SortedBagIterator::remove() {
    TElem e = this->bag.array[this->index][0];
    if(this->bag.array[this->index][1]>0)
        this->sideIndex --;
    bool x = this->bag.remove(this->bag.array[this->index][0]);
    if(this->sideIndex == 0)
        this->sideIndex = this->bag.array[this->index][1];
    if(!x)
        throw std::exception();
    else
    {
        return e;
    }

}

