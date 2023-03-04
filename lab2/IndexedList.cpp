#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

/**
 * constructor bc = wc =overall theta(1)
 */
IndexedList::IndexedList() {
	this->head = nullptr;
}

/**
 * bc = wc = overall theta(n) due to the fact that we parse the list once (n number of elements)
 * @return
 */
int IndexedList::size() const {
    if(this->head == nullptr)
        return 0;
    PNode p;
    p = this->head;
    int nr = 1;
    while(p->next != nullptr)
    {
        nr++;
        p = p->next;
    }
    return nr;
}

/**
 * wc = bc = overall theta(1) simple return
 * @return
 */
bool IndexedList::isEmpty() const {
    if(this->head == nullptr)
        return true;
    return false;
}
/**
 * bc = element is the head -> theta(1)
 * wc =  element is the last -> theta(n)
 * overall = O(n)
 * @param pos
 * @return
 */
TElem IndexedList::getElement(int pos) const {
    if(pos >= this->size() || pos < 0 )
        throw std::exception();
    PNode pn = this->head;
    for(int i = 0; i < this->size();i++)
    {
        if(pos == i)
            return pn->info;
        pn = pn->next;
    }
}

/**
 * bc = element is the first in the list theta(1) or is not in array
 * wc = element is the last in the array theta(n)
 * overall = O(n)
 * @param pos
 * @param e
 * @return
 */
TElem IndexedList::setElement(int pos, TElem e) {
    if(pos >= this->size() || pos < 0 )
        throw std::exception();
    PNode np = this->head;
    TElem copy;
    for(int i =0 ;i < this->size();i++)
    {
        if(pos == i)
        {
            copy = np->info;
            np->info = e;
            return copy;
        }
        np = np->next;
    }
}

/**
 * bc =  list empty -> head is end -> theta(1)
 * wc =  rest of the time -> theta(n)
 * overall =  O(n)
 * @param e
 */
void IndexedList::addToEnd(TElem e) {
    if(this->head == nullptr) {
        PNode np = new SLLNode(e, nullptr);
        this->head = np;
        return;
    }
    PNode n = this->head;
    for(int i = 0; i< this->size()-1; i++)
    {
        n = n->next;
    }
    PNode pn = new SLLNode(e, nullptr);
    n->next = pn;
}
/**
 * bc =  pos is the first in the list theta(pos)
 * wc =  pos is last -> theta(pos)
 * overall = theta(pos)
 * @param pos
 * @param e
 */
void IndexedList::addToPosition(int pos, TElem e) {
    if(pos > this->size() || pos < 0 )
    {
        throw std::exception();
    }
    PNode n = this->head;
    if(pos == 0 )
    {
        PNode pn = new SLLNode(e , nullptr);
        pn->next = this->head;
        this->head =  pn;
        return;
    }
    for(int i = 0; i< this->size()-1; i++)
    {
        if(pos == i+1)
        {
            PNode pn = new SLLNode(e , nullptr);
            pn->next = n->next;
            n->next = pn;
            return;

        }
        n = n->next;
    }
    if(pos == this->size()) {
        PNode pn = new SLLNode(e, nullptr);
        n->next = pn;
        return;
    }
}
/**
 * bc = pos is first in list theta(1)
 * wc =  pos it the last in the list theta(n)
 * overall = O(n)
 * @param pos
 * @return
 */
TElem IndexedList::remove(int pos) {
    if(pos >= this->size() || pos < 0 )
        throw std::exception();
    PNode np = this->head;
    PNode np2 = nullptr;
    TElem copy;
    if(pos == 0)
    {
        np = this->head;
        copy = this->head->info;
        this->head = this->head->next;
        delete np;
        return copy;
    }
    for(int i = 0; i < this->size()-1;i++)
    {

        if(pos == i)
        {
            copy = np->info;
            np2->next = np->next;
            delete np;
            return copy;
        }
        np2 = np;
        np = np->next;
    }
    if(pos == this->size() -1)
    {
        np2->next = nullptr;
        copy = np->info;
        delete np;
        return copy;
    }
}

/**
 * linear search theta(n)
 * @param e
 * @return
 */
int IndexedList::search(TElem e) const{
    PNode n = this->head;
    for(int i = 0 ;i< this->size()-1;i++)
    {
        if(n->info == e)
            return i;
        n= n->next;
    }
    if(n->info == e)
        return this->size()-1;
	return -1;
}

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

/**
 * destructor theta(n) =bc=wc= overall
 */
IndexedList::~IndexedList() {
    while (head != nullptr) {
        PNode p = head;
        head = head->next;
        delete p;
    }
}

/**
 * bc = wc = overall  = theta(n)
 * @param cond
 */
void IndexedList::filter(Condition cond) {
    PNode current = this->head;
    PNode prev = nullptr;
    for(int i = 0 ; i < this->size() - 1 ;i++)
    {
        if(!cond(current->info))
            if(prev == nullptr)
            {
                this->head = this->head->next;
                current = this->head;
                i--;
            }
        else
            {
            prev->next = current->next;
            current = current->next;
            i--;
            }
        else
        {
            prev = current;
            current = current->next;
        }
    }
}

IndexedList::SLLNode::SLLNode(TElem e, IndexedList::PNode n) {
        this->info = e;
        this->next = n;
}
