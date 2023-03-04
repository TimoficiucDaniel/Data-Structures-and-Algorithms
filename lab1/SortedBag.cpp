#include "SortedBag.h"
#include "SortedBagIterator.h"

/**
 * wc = bc = overall =  theta(1)
 * @param r
 */
SortedBag::SortedBag(Relation r) {
    this->r = r;
    this->arrsize = 0;
    this->capacity = 100;
    this->array = new TElem*[this->capacity];
    for(int i = 0; i < capacity ; i++)
        this->array[i] =  new TElem[2];
}

/**
 * bc = wc = overall = theta(3*n)=theta(n) where n is the capacity of the vector bcs
 * it parses the vector 3 times:once to create a copy, once to copy the vector, once to delete the original;
 */
void SortedBag::resize(){
    TElem **auxarray = new TElem *[this->capacity*2];
    for(int i = 0; i < this->capacity*2 ; i++)
        auxarray[i] = new TElem[2];
    for(int i = 0; i < this->capacity ; i++)
    {
        auxarray[i][0] = this->array[i][0];
        auxarray[i][1] = this->array[i][1];

    }
    for(int i = 0; i < capacity; i++)
        delete[] this->array[i];
    delete[] this->array;
    this->array = auxarray;
    this->capacity *= 2;
}


/**
 * wc = the element is not in the array and has to be placed at the end and it also has to resize =
 * around theta(n*3 + n*2 ) =  theta(n)
 * bc =  the element to be added is the first element in the array so theta(1)
 * overall = O(n)
 * @param e
 */
void SortedBag::add(TComp e) {
    if(this->arrsize == this->capacity)
        this->resize();
    if(this->arrsize == 0)
    {
        this->array[0][0] = e;
        this->array[0][1] = 1;
        this->arrsize ++;
    }
    else{
        for(int i = 0 ; i <= this->arrsize; i++ )
            if(e == this->array[i][0])
            {
                this->array[i][1]++;
                return;
            }
        for(int i = 0;i <= this->arrsize ; i++)
            if(r(e, this->array[i][0]))
            {
                for(int j = this->arrsize; j > i ; j-- ) {
                    this->array[j][0] = this->array[j - 1][0];
                    this->array[j][1] = this->array[j - 1][1];
                }
                this->array[i][0] = e;
                this->array[i][1] = 1;
                this->arrsize ++;
                return;
            }
        this->array[this->arrsize][0] = e;
        this->array[this->arrsize][1] = 1;
        this->arrsize ++;
    }
}

/**
 * wc =  the element is not in the array -> exception -> theta(n)
 * bc =  the element is the first in the array -> theta(1)
 * overall =  O(n)
 * @param e
 * @return
 */
bool SortedBag::remove(TComp e) {
    for (int i = 0; i < this->arrsize; i++)
        if (e == this->array[i][0])
            if(this->array[i][1] > 1)
            {
                this->array[i][1]--;
                return true;
            }
            else
            {
                for (int j = i; j < this->arrsize - 1; j++) {
                    this->array[j][0] = this->array[j + 1][0];
                    this->array[j][1] = this->array[j + 1][1];
                }
                this->arrsize--;
                return true;
            }
    return false;
}

/**
 * simple linear search->theta(n)
 * @param elem
 * @return
 */
bool SortedBag::search(TComp elem) const {
    for(int i = 0 ; i < this->arrsize; i++)
        if(elem  == this->array[i][0])
            return true;
    return false;
}

/**
 * simple linear search ->theta(n)
 * @param elem
 * @return
 */
int SortedBag::nrOccurrences(TComp elem) const {
    for(int i = 0 ; i < this->arrsize; i++)
        if(elem  == this->array[i][0])
            return this->array[i][1];
    return 0;
}


/**
 * just counts all the elements in the array wc=bc=overall theta(n)
 * @return
 */
int SortedBag::size() const {
    int nr = 0;
    for(int i  = 0 ;i < this->arrsize; i++)
        nr = nr + this->array[i][1];
    return nr;
}

/**
 * bc= wc=overall theta(1_
 * @return
 */
bool SortedBag::isEmpty() const {
    if(this->arrsize == 0)
        return true;
    return false;
}

/**
 * constructor for iterator bc = wc =overall theta(n)
 * @return
 */
SortedBagIterator SortedBag::iterator() {
    return SortedBagIterator(*this);
}


/**
 * destructor for array wc=bc=overall theta(n)
 */
SortedBag::~SortedBag() {
    for(int i = 0; i< this->capacity;i++)
        delete[] this->array[i];
    delete[] this->array;
}
