#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

ListIterator::ListIterator(const IndexedList& list) : list(list){
   this->start = reinterpret_cast<PNode>(this->list.head); // probabil crapa aci din cauza reintepretarii
   this->current = reinterpret_cast<PNode>(this->list.head);
}

void ListIterator::first(){
    this->start = reinterpret_cast<PNode>(this->list.head);
    this->current =  this->start;
}

void ListIterator::next(){
    if(this->valid())
        this->current = this->current->next;
    else
        throw std::exception();
}

bool ListIterator::valid() const{
    if(this->start == nullptr)
        return false;
    if(this->current == nullptr)
        return false;
//    if(this->current->next == nullptr)
//        return false;
	return true;
}

TElem ListIterator::getCurrent() const{
    if(valid())
        return this->current->info;
    else
        throw std::exception();
    }