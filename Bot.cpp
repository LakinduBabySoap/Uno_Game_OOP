// TODO:
// Implement the Bot class

// For the pickCard method, perform the following:
// (1) show the hand in a hidden manner, i.e., print each card as [Uno],
//     if debugMode is false.
// (2) Pick the first card in hand, from left to right, that matches
//     the top card of the discard pile. Return its index in hand.
// (3) If no playable card in hand, draw a card if draw pile still has cards.
// (4) Set the index to return to be the index of the last element in hand.
// (5) If debugMode in client side is true, print "Drawn [XX]" where [XX] is
//     the card drawn.
// (6) If the card drawn matches the discard pile's top, return the drawn
//     card's index (last element in hand).
//     Otherwise, return the constant DRAWN.
#include <iostream>
#include "Bot.h"

using namespace std;

Bot::Bot() : Player()
{
    setName(getName() + " (Bot)");
}

int Bot::pickCard(GameState &uno)
{
    // 1. Show the hand in a hidden manner if not in debug mode
    printHand(!uno.debugMode);

    Card *topCard = uno.discardPile->top();

    // 2. Pick the first card in hand that matches the top card of discard pile
    for (int i = 0; i < handSize(); i++)
    {
        if (hand[i]->match(topCard))
        {
            return i; // Found a matching card, return its index
        }
    }

    // 3. If no playable card, draw a card if draw pile still has cards
    if (uno.drawPile->size() > 0)
    {
        int initialHandSize = handSize();
        drawCard(uno.drawPile);

        // 4. If in debug mode, print the drawn card
        if (uno.debugMode)
        {
            cout << "Drawn " << hand.back()->toString() << endl;
        }

        // 5. Check if the drawn card matches the discard pile's top
        if (hand.back()->match(topCard))
        {
            return initialHandSize; // Return index of the drawn card (last in hand)
        }
        else
        {
            // 6. Return DRAWN if the drawn card doesn't match
            return DRAWN;
        }
    }

    // If draw pile is empty and no playable cards
    return PASSED;
}