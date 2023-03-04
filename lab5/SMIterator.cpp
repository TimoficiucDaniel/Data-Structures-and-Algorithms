#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m)
///BC=WC=TC: theta(n)
{

    int node = m.bst.root;
    while (node != NULL_TVALUE){
        if(this->stack.capacity-1 == this->stack.index)
            this->stack.resize();
        this->stack.push(node);
        node = m.bst.nodes[node].left;
    }
    if (!this->stack.empty()){
        this->currentNode = stack.top();
    } else {
        this->currentNode = NULL_TVALUE;
    }
}

void SMIterator::first()
///BC=WC=TC: theta(n)
{
    while (!this->stack.empty())
        this->stack.pop();
    int node = map.bst.root;
    while (node != NULL_TVALUE){
        if(this->stack.capacity-1 == this->stack.index)
            this->stack.resize();
        this->stack.push(node);
        node = map.bst.nodes[node].left;
    }
    if (!this->stack.empty()){
        this->currentNode = stack.top();
    } else {
        this->currentNode = NULL_TVALUE;
    }
}

void SMIterator::next()

{
    if (!valid())
        throw exception();
    int node = this->stack.top();
    this->stack.pop();
    if (map.bst.nodes[node].right !=NULL_TVALUE){
        node = map.bst.nodes[node].right;
        while (node != NULL_TVALUE){
            if(this->stack.capacity-1 == this->stack.index)
                this->stack.resize();
            this->stack.push(node);
            node = map.bst.nodes[node].left;
        }
    }
    if (!this->stack.empty()) {
        this->currentNode = this->stack.top();
    }
    else {
        this->currentNode = NULL_TVALUE;
    }
}

bool SMIterator::valid() const{
    if (map.isEmpty())
        return false;
    return this->currentNode != NULL_TVALUE;
}

TElem SMIterator::getCurrent() const{
    if (!this->valid())
        throw std::exception();
    return map.bst.nodes[this->currentNode].info;
}


void SMIterator::Stack::pop() {
    index--;
}

void SMIterator::Stack::push(int node) {
    index++;
    elems[index] = node;
}

bool SMIterator::Stack::empty() {
    if(index == -1)
        return true;
    return false;
}

int SMIterator::Stack::top() {
    return elems[index];
}

SMIterator::Stack::Stack() {
    elems = new int[100];
    capacity = 100;
    index = -1;
}

void SMIterator::Stack::resize() {
    int* newElems = new int[capacity*2];
    for(int i = 0 ;i < capacity; i++ )
        newElems[i] = elems[i];
    std::swap(elems,newElems);
    capacity*=2;
}
