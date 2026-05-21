#include "MagicBox.h"

template<class Itemtype>
MagicBox<Itemtype>::MagicBox() {
    PlainBox<Itemtype>();
    firstitemStored = false;
}

template<class Itemtype>
MagicBox<Itemtype>::MagicBox(const Itemtype& theItem) {
    firstitemStored = false;
    setItem(theItem);
}

template<class Itemtype>
void MagicBox<Itemtype>::setItem(const Itemtype& theItem) {
    if (!firstitemStored) {
        PlainBox<Itemtype>::setItem(theItem);
        firstitemStored = true;
    }
}