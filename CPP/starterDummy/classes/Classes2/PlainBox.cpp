#include "PlainBox.h"

template<class Itemtype>
PlainBox<Itemtype>::PlainBox() {
}

template<class Itemtype>
PlainBox<Itemtype>::PlainBox(const Itemtype& theItem) {
    item = theItem;
}

template<class Itemtype>
void PlainBox<Itemtype>::setItem(const Itemtype& theItem) {
    item = theItem;
}

template<class Itemtype>
Itemtype PlainBox<Itemtype>::getItem() const {
    return item;
}