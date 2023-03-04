#pragma once
#include "IndexedList.h"


class ListIterator{
    //DO NOT CHANGE THIS PART
	friend class IndexedList;
private:
    struct SLLNode;
    typedef SLLNode *PNode;
    struct SLLNode {
        TElem info;
        PNode next;

        SLLNode(TElem e, PNode n);
    };
        const IndexedList& list;
    PNode start;
    PNode current;
		
    ListIterator(const IndexedList& list);
public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;

};

