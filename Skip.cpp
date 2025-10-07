#include <iostream>
#include "Skip.h"

using namespace std;
// initializing skip and action card together
Skip::Skip(Color c) : ActionCard(c, Action::Skip)
{
}

void Skip::play(GameState &uno)
{
    Card::play(uno);
    *(uno.turnSkipped) = true;
}