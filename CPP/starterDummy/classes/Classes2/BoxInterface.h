#ifndef _BOX_INTERFACE
#define _BOX_INTERFACE

template<class Itemtype>
class BoxInterface
{
public:
    virtual void setItem(const Itemtype& theItem) = 0;
    virtual Itemtype getItem() const = 0;
};

#endif