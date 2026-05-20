#ifndef _PLAIN_BOX
#define _PLAIN_BOX

template<class Itemtype>

class PlainBox
{
private:
    Itemtype item;

public:
    PlainBox();
    PlainBox(const Itemtype& theItem);
    void setItem(const Itemtype& theItem);
    Itemtype getItem() const;
};

#include "PlainBox.h"
#endif