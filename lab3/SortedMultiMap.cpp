#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

/**
 * best case = theta(1)
 * worst case(has to resize) =  theta(n)
 * average case = O(n) i think
 * @return
 */
int SortedMultiMap::allocate() {
    if(this->data.firstEmpty == -1)
        this->resize();
    int newFree = this->data.firstEmpty;
    this->data.firstEmpty = this->data.next[this->data.firstEmpty];
    return newFree;
}

/**
 * worst case = best case =  average =  theta(n)
 */
void SortedMultiMap::resize() {
    TElem *newArray;
    newArray = new TElem[this->data.cap*2];
    int *next;
    int *prev;
    next = new int[this->data.cap*2];
    prev = new int[this->data.cap*2];
    for(int i = 1; i <= this->data.cap; i++)
    {
        next[i]=this->data.next[i];
        prev[i]=this->data.prev[i];
        newArray[i]=this->data.elems[i];
    }
    this->data.elems = newArray;
    this->data.next = next;
    this->data.prev = prev;
    for(int i = this->data.cap+1; i <this->data.cap*2;i++)
    {
        this->data.next[i] = i+1;
        this->data.prev[i] = i-1;
    }
    this->data.next[this->data.cap*2] = -1;
    this->data.firstEmpty =  this->data.cap+1;
    this->data.cap = this->data.cap*2;
}


/**
 * bc = wc = average = theta(1)
 * @param r
 */
SortedMultiMap::SortedMultiMap(Relation r) {
    this->data;
    this->relation = r;

}

/**
 * best case = theta(1)
 * wc = theta(n)
 * average case = O(n)
 * @param c
 * @param v
 */
void SortedMultiMap::add(TKey c, TValue v) {
    TElem a;
    a.first = c;
    a.second = v;
    int pos = this->allocate();
    if(this->data.head == -1)
    {
        this->data.elems[this->data.size+1] = a;
        this->data.head = pos;
        this->data.tail = pos;
        this->data.next[pos] = -1;
        this->data.size ++;
        return;
    }
    if(!this->relation(this->data.elems[this->data.head].first,c))
    {
        this->data.elems[this->data.size+1] = a;
        this->data.next[pos] = this->data.head;
        this->data.prev[this->data.head] = pos;
        this->data.prev[pos] = -1;
        this->data.head = pos;
        this->data.size ++;
        return;
    }
    int index= this->data.head;
    while(index != -1){
            if(!this->relation(this->data.elems[index].first,c)) {
                this->data.elems[this->data.size + 1] = a;
                this->data.next[pos] = index;
                this->data.prev[pos] = this->data.prev[index];
                this->data.prev[index] = pos;
                this->data.next[this->data.prev[pos]] = pos;
                this->data.size++;
                return;
            }
        index =  this->data.next[index];
    }
    this->data.elems[this->data.size+1] = a;
    this->data.next[this->data.tail] = pos;
    this->data.next[pos] = -1;
    this->data.prev[pos] = this->data.tail;
    this->data.tail = pos;
    this->data.size++;
}

/**
 * bc = theta(1)
 * wc = theta(n)
 * average =  theta(n)
 * @param c
 * @return
 */
vector<TValue> SortedMultiMap::search(TKey c) const {
	vector<TValue> v;
    for(int i = 1; i<= this->data.size;i++)
        if(this->data.elems[i].first == c)
            v.push_back(this->data.elems[i].second);
	return v;
}

/**
 * bc = theta(1)
 * wc =  theta(n)
 * average = O(n)
 * @param c
 * @param v
 * @return
 */
bool SortedMultiMap::remove(TKey c, TValue v) {
    if(this->data.size == 1)
        if(c == this->data.elems[this->data.head].first)
            if(v == this->data.elems[this->data.head].second)
            {
                this->data.firstEmpty = this->data.head;
                this->data.head = -1;
                this->data.tail = -1;
                this->data.size = 0;
                return true;
            }
    if (c == this->data.elems[this->data.head].first)
        if (v == this->data.elems[this->data.head].second) {
            int aux = this->data.next[this->data.head];
            this->data.next[this->data.head] = this->data.firstEmpty;
            this->data.firstEmpty = this->data.head;
            this->data.head = aux;
            this->data.prev[aux] = -1;
            this->data.size--;
            return true;
        }
    if (c == this->data.elems[this->data.tail].first)
        if (v == this->data.elems[this->data.tail].second)
        {
            int aux = this->data.prev[this->data.tail];
            this->data.next[aux] = this->data.firstEmpty;
            this->data.firstEmpty = this->data.tail;
            this->data.tail = aux;
            this->data.size--;
            return true;
        }
    int index = this->data.head;
        for(int i = 1; i<= this->data.size;i++)
        {
            if (c == this->data.elems[index].first)
                if (v == this->data.elems[index].second)
                {
                    this->data.next[this->data.prev[index]] = this->data.next[index];
                    this->data.prev[this->data.next[index]] = this->data.prev[index];
                    this->data.next[index] = this->data.firstEmpty;
                    this->data.firstEmpty = index;
                    this->data.size--;
                    return true;
                }
            index =  this->data.next[index];
        }
    return false;
}

/**
 * bc = wc = average = theta(1)
 * @return
 */
int SortedMultiMap::size() const {
	return this->data.size;
}

/**
 * bc = wc = average = theta(1)
 * @return
 */
bool SortedMultiMap::isEmpty() const {
	if(this->data.size == 0)
        return true;
    return false;
}

/**
 * bc = wc = average = theta(1)
 * @return
 */
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() = default;

/**
 * bc = wc = average = theta(1)
 * @return
 */
SortedMultiMap::DLLA::DLLA() {
    this->elems = new TElem[10];
    this->cap = 10;
    this->size = 0;
    this->prev = new int[10];
    this->next = new int[10];
    for(int i = 1; i < 10 ; i++)
    {
        this->next[i] = i+1;
        this->prev[i] = i-1;
    }
    this->next[10] = -1;
    this->prev[1] = -1;
    this->tail = -1;
    this->head = -1;
    this->firstEmpty = 1;
}

void SortedMultiMap::shrink(int pos) {
    for(int i = pos ;  i< this->data.size; i++ )
    {
        this->data.elems[pos]= this->data.elems[pos+1];
    }
}

