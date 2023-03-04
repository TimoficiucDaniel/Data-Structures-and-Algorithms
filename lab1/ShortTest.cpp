#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <exception>
#include <assert.h>
#include <iostream>

bool relation1(TComp e1, TComp e2) {
	return e1 <= e2;
}
/**
 * the complexity is theta(n) due to the fact that it parses once through the bag =  number of elements in the bag(n)
 * then removes it and updates some indexes
 */
void test_remove_iterator(){
    std::cout<<"testing new functionality\n";
    SortedBag b(relation1);
    b.add(5);
    b.add(6);
    b.add(0);
    b.add(5);
    b.add(10);
    b.add(8);
    SortedBagIterator it = b.iterator();
    while(it.valid())
    {
        it.remove();
    }
    assert(b.size() == 0);
    try{
        it.remove();
        assert(false);
    }catch(std::exception&){
        assert(true);
    }
}

void testAll() {
	SortedBag sb(relation1);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);

	assert(sb.size() == 6);
	assert(sb.nrOccurrences(5) == 2);

	assert(sb.remove(5) == true);
	assert(sb.size() == 5);

	assert(sb.search(6) == true);
	assert(sb.isEmpty() == false);

	SortedBagIterator it = sb.iterator();
	assert(it.valid() == true);
	while (it.valid()) {
		it.getCurrent();
		it.next();
	}
	assert(it.valid() == false);
	it.first();
	assert(it.valid() == true);

}

