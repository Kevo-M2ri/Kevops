#ifndef _MAGIC_BOX
#define _MAGIC_BOX
#include "PlainBox.h"

template<class Itemtype>
class MagicBox : public PlainBox<Itemtype>
{

private:
    bool firstitemStored;

public:
    MagicBox();
    MagicBox(const Itemtype& theItem);
    void setItem(const Itemtype& theItem);
}

#include "MagicBox.cpp"
#endif