#ifndef _TOY_BOX
#define _TOY_BOX
#include "PlainBox.h"

enum Color {BLACK, RED, BLUE, GREEN, YELLOW, WHITE};

template<class Itemtype>

class ToyBox : public PlainBox<Itemtype>
{
private:
    Color boxColor;

public:
    ToyBox();
    ToyBox(const Color& theColor);
    ToyBox(const Itemtype& theItem, const Color& theColor);
    Color getColor() const
    
};

#include "ToyBox.cpp"
#endif