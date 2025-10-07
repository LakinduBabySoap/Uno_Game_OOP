#include <iostream>
#include "cctype"
#include "WildCard.h"
#include "WildDraw4.h"
#include "Bot.h"
// adding the missing header since WildCard needs to derive from parent Player class too
#include "Player.h"
using namespace std;

WildCard::WildCard() : ActionCard(Color::Wild, Action::ChgColor)
{
    setValue(Value::W);
}

bool WildCard::match(Card * /* top */)
{
    // TODO:
    // Add one statement here to complete the color matching logic
    // for this card type
    return true; // Wild cards can be played on any card
}

void WildCard::play(GameState &uno)
{
    // TODO:
    // Check if the "this" pointer is aiming at a WildDraw4 object.
    // If not, call the superclass Card's play() function.
    WildDraw4 *wildDraw4 = dynamic_cast<WildDraw4 *>(this);
    if (wildDraw4 == nullptr)
    {
        // This is not a WildDraw4 object, so call Card::play()
        Card::play(uno);
    }
    // (This check is to skip redundant superclass Card's play() call
    //  for WildDraw4 since it's been called in Draw2's play().)
    // Hint: use dynamic_cast<>().

    // TODO:
    // Change color from Wild to the color selected by the player.
    // First, get the pointer to the current player via GameState struct.
    Player *currentPlayer = uno.players[*(uno.turn)];
    // Check if it points to a Bot object. Hint: use dynamic_cast<>().
    Bot *bot = dynamic_cast<Bot *>(currentPlayer);
    Color selectedColor;

    if (bot != nullptr)
    {
        // For Bot, use mostFrequentColor() to select a color
        selectedColor = currentPlayer->mostFrequentColor();
    }
    else
    {
        // For Man, prompt for color input
        string input;
        bool validInput = false;

        while (!validInput)
        {
            cout << "Choose a color [R, Y, G, B]: ";
            cin >> input;

            if (input.length() == 1)
            {
                char colorChar = toupper(input[0]);

                switch (colorChar)
                {
                case 'R':
                    selectedColor = Color::Red;
                    validInput = true;
                    break;
                case 'Y':
                    selectedColor = Color::Yellow;
                    validInput = true;
                    break;
                case 'G':
                    selectedColor = Color::Green;
                    validInput = true;
                    break;
                case 'B':
                    selectedColor = Color::Blue;
                    validInput = true;
                    break;
                default:
                    cout << "Invalid option!" << endl;
                    break;
                }
            }
            else
            {
                cout << "Invalid option!" << endl;
            }
        }
    }

    // Set color of this card to the selected color
    setColor(selectedColor);
    // If so, use the mostFrequentColor() function of the Player class
    // to select a color to change.
    // Otherwise (i.e., for a Man object), prompt the user to enter a
    // single character, valid choice in [R, Y, G, B], to select a color
    // to change. Show error message "Invalid option!" if the user input
    // is not one of the 4 letters.
    // Set color of this card to the selected color.

    cout << "Color changed to " << COLORS[int(getColor())] << "!" << endl;
}

string WildCard::toString()
{
    // TODO:
    // Return a string representation of this card with color code shown as 'W'
    return "[WC]";
}