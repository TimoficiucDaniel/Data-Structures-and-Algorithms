#include <assert.h>

#include "SortedMultiMap.h"
#include "SMMIterator.h"
#include <exception>
#include <vector>
#include "iostream"

using namespace std;


bool relation1(TKey cheie1, TKey cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}

void testJump(){
    cout<<"Test functionality\n";
    SortedMultiMap smm = SortedMultiMap(relation1);
    smm.add(1,2);
    smm.add(1,3);
    smm.add(2,2);
    smm.add(2,3);
    smm.add(3,2);
    smm.add(3,3);
    SMMIterator it = smm.iterator();
    it.jumpForward(2);
    assert(it.getCurrent().first==2);
    assert(it.getCurrent().second==2);
    it.jumpForward(2);
    assert(it.getCurrent().first==3);
    assert(it.getCurrent().second==2);
    try{
        it.jumpForward(-2);
        assert(false);
    }catch(exception &e){
        assert(true);
    }
    try{
        it.jumpForward(0);
        assert(false);
    }catch(exception &e){
        assert(true);
    }
    try{
        it.jumpForward(2);
        assert(false);
    }catch(exception &e){
        assert(true);
    }

}

void testAll(){
	SortedMultiMap smm = SortedMultiMap(relation1);
	assert(smm.size() == 0);
	assert(smm.isEmpty());
    smm.add(1,2);
    smm.add(1,3);
    assert(smm.size() == 2);
    assert(!smm.isEmpty());
    vector<TValue> v= smm.search(1);
    assert(v.size()==2);
    v= smm.search(3);
    assert(v.size()==0);
    SMMIterator it = smm.iterator();
    it.first();
    while (it.valid()){
    	TElem e = it.getCurrent();
    	it.next();
    }
    assert(smm.remove(1, 2) == true);
    assert(smm.remove(1, 3) == true);
    assert(smm.remove(2, 1) == false);
    assert(smm.isEmpty());
}

