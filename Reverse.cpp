// TODO:
// Implement the Reverse class
#include <iostream>
#include "Reverse.h"

using namespace std;

Reverse::Reverse(Color c) : ActionCard(c, Action::Reverse)
{
    // Initialize Reverse card with the specified color and Reverse action
}

void Reverse::play(GameState &uno)
{
    Card::play(uno);
    // Reverse the direction by negating the delta value
    *(uno.delta) = -1 * *(uno.delta);
}
