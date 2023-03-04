#include "SMMIterator.h"
#include "SortedMultiMap.h"

/**
 * bc = wc = average = theta(1)
 * @return
 */
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->head = map.data.head;
    this->current = this->head;
}

/**
 * bc = wc = average = theta(1)
 * @return
 */
void SMMIterator::first(){
	this->current = this->head;
}

/**
 * bc = wc = average = theta(1)
 * @return
 */
void SMMIterator::next(){
    if(this->head==-1) {
        //this->current = -2;
        throw exception();
    }
	this->current = map.data.next[this->current];
}

/**
 * bc = wc = average = theta(n)
 * @return
 */
bool SMMIterator::valid() const{
	int counter = 0 ;
    int index = this->head;
    if(this->current==-1)
        return false;
    while(this->current != index)
    {
        counter++;
        if(counter >= map.data.size)
            return false;
        index = map.data.next[index];
    }
	return true;
//    if(this->current==-1)
//        return false;
//    return true;
}

/**
 * bc = wc = average = theta(1)
 * @return
 */
TElem SMMIterator::getCurrent() const{
    if(this->head==-1)
        throw exception();
	return map.data.elems[this->current];
}

void SMMIterator::jumpForward(int k) {
    if(this->current==-2)
        throw exception();
    if(k<=0)
        throw exception();
    while(k>0)
    {
        if(map.data.next[this->current]==-1)
        {
            this->current = -2;
            break;
        }
        this->current = map.data.next[this->current];
        k--;
    }

}


