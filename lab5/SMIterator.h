#pragma once
#include "SortedMap.h"
#include <stack>

//DO NOT CHANGE THIS PART
class SMIterator{
    friend class SortedMap;
private:
    const SortedMap& map;
    int currentNode;
    //std::stack<int> stack;
    struct Stack{
        int *elems;
        int index;
        int capacity;

        Stack();
        void resize();
        void pop();
        void push(int node);
        bool empty();
        int top();
    };
    Stack stack;
    SMIterator(const SortedMap& mapionar);



public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};