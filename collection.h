#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;
template<typename Item>
class Collection;
template<typename Item>
ostream&operator<<(ostream& out, const Collection<Item>&c);
template<typename Item>

class Collection {
public:
    Collection();
    Collection(int size);
    Collection(Collection<Item>& a);
    virtual int size();
    virtual Item get(int ndx) const;
    virtual void add(Item e);
    virtual void removeEnd();
    virtual Collection <Item>& operator= (Collection<Item>& a);
    virtual Item operator [](int ndx);
    virtual void operator -(int num);
    virtual ~Collection() = default;



    friend ostream& operator<< <>(ostream& out, const Collection& c);


protected:
    int capacity;
    int curSize;
    static const int INITIAL_CAPACITY = 8;
    void expand();
    unique_ptr<Item[]> elements; // stores items in list

};
template<typename Item>
Collection<Item>::Collection(){
    capacity = INITIAL_CAPACITY;
    curSize = 0;
    elements = make_unique<Item[]>(capacity);
}
template<typename Item>
Collection<Item>::Collection(int size){
    capacity = size;
    curSize = 0;
    elements = make_unique<Item[]>(capacity);
}
template<typename Item>
Collection<Item>::Collection(Collection<Item>& a){
    capacity = a.capacity;
    curSize = a.curSize;
    elements = make_unique<Item[]>(capacity);
    for (int i = 0; i < curSize; i++) {
        elements[i] = a.elements[i];
    }
}

template<typename Item>
int Collection<Item>::size() {
    return curSize;
}
template<typename Item>
Item Collection<Item>::get(int ndx) const {
    return elements[ndx];

}


template<typename Item>
Item Collection<Item>::operator [](int ndx) {
    return get(ndx);
}


template<typename Item>
void Collection<Item>::operator -(int num) {
    for (int i = 0; i < num; i++) {
        removeEnd();
    }
}

template<typename Item>
void Collection<Item>::add(Item e) {
    if (curSize == capacity) {
        expand();
    }
    elements[curSize] = e;
    curSize++;
}

template<typename Item>
void Collection<Item>::removeEnd() {

    curSize--;
    if (curSize < 0) {
        throw runtime_error("Collection is empty");
    }
}
template<typename Item>
Collection<Item>& Collection<Item>:: operator=(Collection<Item>&a) {
    auto newElements = make_unique<Item[]>(a.capacity);
    for (int i = 0 ; i < a.curSize; i++) {
        newElements[i] = a.elements[i];
    }
    elements = move(newElements);
    capacity = a.capacity;
    curSize = a.curSize;

    return *this;
}

template<typename Item>
void Collection<Item>::expand() {
    auto newElements = make_unique<Item[]>(capacity * 2);
    for (int i = 0 ; i < capacity; i++) {
        newElements[i] = elements[i];
    }
    elements = move(newElements);
    capacity *=2;


}
template<typename Item>
ostream&operator<<(ostream& out, const Collection<Item>&c) {
    for (int i = 0; i < c.curSize; i++) {
        out << c.elements[i];
        if (i< c.curSize - 1) out << endl;

    }
    return out;
}

template<typename Item>
class SortedCollection: public Collection<Item> {
public:
    SortedCollection() : Collection<Item>() {}

    SortedCollection(int size) : Collection<Item>(size) {}

    SortedCollection(const SortedCollection<Item>& a) : Collection<Item>(a) {}


    // 2. Overloaded add method (O(N) Insertion Algorithm)
    virtual void add(Item e) override;

    // 3. Overloaded += operator to add an Item
    virtual SortedCollection<Item>& operator+=(Item e);
    bool contains(Item e);
};
template<typename Item>
void SortedCollection<Item>::add(Item e) {
    if (this->curSize == this->capacity) {
        this->expand();
    }

    int i = this->curSize - 1;

    while (i >= 0 && this->elements[i] > e) {
        this->elements[i + 1] = this->elements[i];
        i--;
    }

    this->elements[i + 1] = e;
    this->curSize++;
}
template<typename Item>
SortedCollection<Item>& SortedCollection<Item>::operator+= (Item e) {
    this->add(e);

    return *this;
}

template<typename Item>
bool SortedCollection<Item>::contains(Item e) {
    for (int i = 0; i< this->curSize; i++) {
        if (this->elements[i] ==e ) {
            return true;
        }
    }return false;
}
