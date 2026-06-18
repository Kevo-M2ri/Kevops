#include "ToyBox.h"

template<class Itemtype>
ToyBox<Itemtype>::ToyBox() {
    PlainBox<Itemtype>();
    boxColor = Color::BLACK;
}

template<class Itemtype>
ToyBox<Itemtype>::ToyBox(const Color& theColor) {
    PlainBox<Itemtype>();
    boxColor = theColor;
}

template<class Itemtype>
ToyBox<Itemtype>::ToyBox(const Itemtype& theItem, const Color& theColor) {
    PlainBox<Itemtype>(theItem);
    PlainBox<Itemtype>::setItem(theItem);
    boxColor = theColor;
}

template<class Itemtype>
Color ToyBox<Itemtype>::getColor() const {
    return boxColor;
}