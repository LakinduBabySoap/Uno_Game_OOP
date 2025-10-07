#include <iostream>
#include "ActionCard.h"

using namespace std;

ActionCard::ActionCard(Color c, Action a) : Card(c, Value::A), action(a)
{
}

Action ActionCard::getAction() const
{
    return action;
}

void ActionCard::setAction(Action a)
{
    action = a;
}

bool ActionCard::match(Card *top)
{
    // Check if this color matches top's color.
    if (getColor() == top->getColor())
    {
        return true;
    }
    // Check if top points to an ActionCard object.
    ActionCard *topActionCard = dynamic_cast<ActionCard *>(top);
    if (topActionCard != nullptr)
    {
        if (getAction() == topActionCard->getAction())
        {
            // to check if the action of current card matches action of the top card
            return true;
        }
    }
    return false;
}

string ActionCard::toString()
{
    // TODO:
    // Print this action card in the form like [WC], [RS], [YD], etc.
    string result = "[";
    result += COLORS[int(getColor())][0]; // first letter of color
    switch (getAction())
    {
    case Action::Skip:
        result += 5;
        break;
    case Action::Reverse:
        result += 18;
        break;
    case Action::Draw2:
        result += "D";
        break;
    default:
        // unsupported action card
        break;
    }
    result += "]";
    return result;
}