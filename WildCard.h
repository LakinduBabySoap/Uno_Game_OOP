#ifndef WILDCARD_H
#define WILDCARD_H

#include "ActionCard.h"
// virtual here to prevent diamond problem where 2 classes inherit from ActionCard
class WildCard : public virtual ActionCard
{
public:
    WildCard();
    virtual bool match(Card * /* top */) override;
    virtual void play(GameState &uno) override;
    virtual std::string toString() override;
};

#endif // WILDCARD_H