#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <climits>
// You may add additional headers if needed

#include "ActionCard.h"
#include "Man.h"
#include "Bot.h"
#include "DrawPile.h"
#include "DiscardPile.h"

using namespace std;

int main()
{
	// Get the game start-up parameters
	string input;
	unsigned int seed = 123;
	cout << "Enter seed (or hit Enter): ";
	getline(cin, input);
	if (!input.empty())
	{
		seed = stoi(input);
	}
	cout << "Seed: " << seed << endl;
	srand(seed);

	bool debugMode = false;
	cout << "Play in debug mode (Y/N)? ";
	getline(cin, input);
	if (input == "Y" || input == "y" || input == "")
	{
		debugMode = true;
	}
	cout << "Debug mode: " << boolalpha << debugMode << endl;

	int turnsMax = 100;
	cout << "Max. turns to play: ";
	getline(cin, input);
	if (!input.empty())
	{
		turnsMax = stoi(input);
	}
	cout << "Max. turns: " << turnsMax << endl;

	int M, B, P;
	while (true)
	{
		cout << "Enter # man and bot players: ";
		cin >> M >> B;
		P = M + B;
		if (P >= 2 && P <= 5)
			break;
		cout << "Require 2 to 5 players!" << endl;
	}
	cout << "#Men: " << M << "; #Bots: " << B << endl;

	// Create an array of pointers to Player objects
	Player **players = new Player *[P];
	for (int i = 0; i < P; i++)
	{
		if (i < M)
			players[i] = new Man;
		else
			players[i] = new Bot;
	}
	Player *player = players[0]; // current player

	// Define variables to track the game state
	DrawPile drawPile;
	DiscardPile discardPile;
	bool turnSkipped = false;
	int cardsToDraw = 0;
	int delta = 1;
	int turn = 0;

	GameState uno{players, &drawPile, &discardPile,
				  &turnSkipped, &cardsToDraw, &turn, &delta, P, debugMode};

	// Shuffle the deck and deal cards to each player
	if (debugMode)
	{
		cout << "Cards created:" << endl;
		drawPile.print();
	}
	drawPile.shuffle();
	for (int i = 0; i < P; i++)
	{
		players[i]->drawCard(&drawPile, H);
	}

	// Draw the first card onto discard pile
	vector<Card *> firstCard;
	drawPile.draw(firstCard, 1);
	discardPile.stack(firstCard.at(0));
	if (debugMode)
	{
		cout << "Draw pile after shuffling and dealing:" << endl;
		drawPile.print();
	}

	// Start the game loop

	// TODO:
	// Print the "turn header" which shows discard pile's top card,
	// current color and current size of draw pile.

	// Print the name of the current player.
	// (Hint: you can use the turn integer to index the players array
	//  to get a pointer to the current player.)

	// If cardsToDraw > 0, current player draws the required # cards.
	// If turnSkipped is true, current player skips picking and playing
	// a card in this turn.
	// Otherwise, call the pickCard() method to get the index of a
	// selected card in hand.
	// Then call the playCard() method with the obtained index if it is
	// not PASSED and not DRAWN.

	// Check game over condition. Exit the game loop if either:
	// (1) current player's hand has no cards.
	// (2) all players consecutively passed their turns
	//     (i.e., no one can play a card or draw).

	// Reset cardsToDraw and turnSkipped for clean state for next turn.

	// Update the turn integer to let the next player become current.

	// TODO:
	// Print the game over message.
	// List all players' hands and the sum of points of all cards in hand.
	// Print the name of the winner.
	// Start the game loop
	int turns = 0;
	int passCount = 0; // Track consecutive passes

	while (turns < turnsMax)
	{
		turns++;

		// Print the "turn header"
		cout << "=========================================================" << endl;
		cout << "Turn " << turns << ": " << endl;
		Card *topCard = discardPile.top();
		cout << "Discard Pile: " << topCard->toString() << "  ";
		cout << "Current Color: " << setw(6) << left << COLORS[int(topCard->getColor())] << "  ";
		cout << "Draw Pile: " << drawPile.size() << endl;
		cout << "---------------------------------------------------------" << endl;

		// Get current player
		player = players[turn];

		// Handle card drawing if needed
		if (cardsToDraw > 0)
		{
			player->drawCard(&drawPile, cardsToDraw);
			cardsToDraw = 0;	// Reset cards to draw
			turnSkipped = true; // Skip the turn after drawing
		}

		int cardIndex;
		// Handle turn
		if (turnSkipped)
		{
			cout << "Turn skipped!" << endl;
			passCount = 0; // Reset pass count since a card effect happened
		}
		else
		{
			cardIndex = player->pickCard(uno);

			if (cardIndex == PASSED)
			{
				passCount++;
				cout << player->getName() << " passed." << endl;
			}
			else if (cardIndex != DRAWN)
			{
				player->playCard(cardIndex, uno);
				passCount = 0; // Reset pass count since a card was played
			}
			else
			{
				// Card was drawn but not played (DRAWN)
				passCount = 0; // Reset pass count since a card was drawn
			}
		}
		// Check game over condition
		if (player->handSize() == 0)
		{
			// Player has no cards left - they win!
			break;
		}

		// Check if all players have passed in sequence
		if (passCount == P)
		{
			cout << "All players passed - game over!" << endl;
			break;
		}

		// Reset flags for next turn
		turnSkipped = false;

		// Update turn for next player
		turn = (turn + delta + P) % P; // Ensure turn stays positive with +P
	}
	// Print game over message
	cout << "=========================================================" << endl;
	if (turns >= turnsMax)
	{
		cout << "Game over - maximum number of turns reached!" << endl;
	}
	else if (player->handSize() == 0)
	{
		cout << "Game over - " << player->getName() << " won!" << endl;
	}
	else
	{
		cout << "Game over - all players passed!" << endl;
	}

	// Print final hand information for all players
	cout << "Final hand points:" << endl;
	for (int i = 0; i < P; i++)
	{
		players[i]->printHand(true); // Show all cards
		cout << "Points: " << players[i]->handPoints() << endl;
	}

	// Determine the winner (lowest points if no one has empty hand)
	if (player->handSize() != 0)
	{
		int minPoints = INT_MAX;
		int winnerIndex = -1;

		for (int i = 0; i < P; i++)
		{
			int points = players[i]->handPoints();
			if (points < minPoints)
			{
				minPoints = points;
				winnerIndex = i;
			}
		}

		cout << "Winner is " << players[winnerIndex]->getName()
			 << " with " << minPoints << " points!" << endl;
	}
	// Clean up - delete all player objects
	for (int i = 0; i < P; i++)
	{
		delete players[i];
	}
	delete[] players;

	return 0;
}