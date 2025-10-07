#include <iostream>
#include <iomanip>
// You may add additional headers if needed
#include <sstream>
#include <string>
#include <cctype>
#include "Man.h"

using namespace std;

Man::Man() : Player()
{
    setName(getName() + " (Man)");
}

int Man::pickCard(GameState &uno)
{
    // TODO:
    // Show the hand of cards with selectable indexes
    // For each card in hand, print the card's string representation
    // with "[i]"" in front of it, where i is the index of the card
    // in the player's hand vector.
    // If the card cannot match the top of the discard pile, show
    // "[x]" which means the card cannot be played.
    // Print at most 10 cards per line if there are many cards in hand.

    // Show the [D]raw option if draw pile still has cards.

    // You may make an early return with PASSED if no matched cards in hand
    // and draw pile is empty.

    // Get user input for the option (selected card index or 'D' for draw).
    // Keep prompting until the option is valid.
    // If the input is 'D' (case-insensitive), draw 1 card from draw pile
    // into this player's hand vector. The drawn card is added to the back
    // of the vector.
    // If the drawn card is playable, return its index. Otherwise, return
    // the constant DRAWN to mean a card has been drawn but not playable.
    // The caller seeing DRAWN returned should skip playing any card.
    // If the input is an integer that can index a playable card in hand,
    // return the integer.
    //
    // Print error message "Invalid option!" for invalid index or incorrect
    // input.
    //
    // Hint: read the user input as a string first. You can convert it to
    // integer later using an input string stream or the stoi() function.
    // The string stream method is preferred as it can detect non-integer input.
    // Show the hand of cards with selectable indexes
    Card *topCard = uno.discardPile->top();
    bool hasPlayableCard = false;

    cout << name << ": " << endl;

    // Count how many cards displayed on current line
    int cardsOnLine = 0;

    // Check each card in hand and show proper index
    for (int i = 0; i < handSize(); i++)
    {
        if (hand[i]->match(topCard))
        {
            // Card is playable - show index
            cout << " [" << i << "]" << hand[i]->toString() << " ";
            hasPlayableCard = true;
        }
        else
        {
            // Card is not playable - show 'x'
            cout << " [x]" << hand[i]->toString() << " ";
        }

        cardsOnLine++;
        // Start new line after 10 cards
        if (cardsOnLine == 10 && i < handSize() - 1)
        {
            cout << endl;
            cardsOnLine = 0;
        }
    }

    // Show [D]raw option if draw pile has cards
    if (uno.drawPile->size() > 0)
    {
        cout << " [D]raw";
    }
    cout << endl;
    // Early return if no playable cards and draw pile is empty
    if (!hasPlayableCard && uno.drawPile->size() == 0)
    {
        return PASSED;
    }

    // Get user input for option
    while (true)
    {
        cout << "Enter option: ";
        string input;
        cin >> input;

        // Check if input is 'D' (draw card)
        if (input.size() == 1 && (input[0] == 'D' || input[0] == 'd'))
        {
            if (uno.drawPile->size() > 0)
            {
                // Draw a card
                int oldHandSize = handSize();
                drawCard(uno.drawPile);

                // Show the drawn card
                cout << "Drawn " << hand.back()->toString() << endl;

                // Check if drawn card is playable
                if (hand.back()->match(topCard))
                {
                    return oldHandSize; // Index of the drawn card
                }
                else
                {
                    return DRAWN; // Card drawn but not playable
                }
            }
            else
            {
                cout << "No more cards on draw pile!" << endl;
                continue;
            }
        }

        // Try to parse input as integer
        int index;
        stringstream ss(input);
        if (ss >> index && ss.eof())
        {
            // Check if index is valid and card is playable
            if (index >= 0 && index < handSize() && hand[index]->match(topCard))
            {
                return index;
            }
        }

        // If we get here, the option was invalid
        cout << "Invalid option!" << endl;
    }
}
