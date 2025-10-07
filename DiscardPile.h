#ifndef DISCARDPILE_H
#define DISCARDPILE_H

#include "Deck.h"

class DiscardPile : public Deck
{
public:
    DiscardPile();
    Card *top() const; // function returns Card object (no modifying of the object)
    void stack(Card *card);
};

#endif // DISCARDPILE_H