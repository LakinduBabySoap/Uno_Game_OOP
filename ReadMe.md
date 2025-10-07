Collecting workspace information# UNO Card Game Implementation

## Table of Contents
- Introduction
- Game Rules
- Programming Concepts
- Code Architecture
- Building and Running
- Implementation Details
- Gameplay Examples

## Introduction

This project is a C++ implementation of the popular UNO card game that runs in the console. It features both human and computer (bot) players, supports all official UNO card types, and follows standard UNO game rules. The implementation allows 2-5 players in any combination of humans and bots.

## Game Rules

### Cards
UNO is played with a special deck consisting of:
- **Number Cards (0-9)** in four colors: Red, Yellow, Green, and Blue
- **Action Cards**:
  - **Skip**: When played, the next player's turn is skipped
  - **Reverse**: Reverses the direction of play
  - **Draw Two**: Forces the next player to draw 2 cards and skip their turn
- **Wild Cards**:
  - **Wild**: Allows the player to change the current color
  - **Wild Draw Four**: Forces the next player to draw 4 cards, skip their turn, and allows the player to change the color

### Card Values
- Number cards: Face value (0-9)
- Skip, Reverse, Draw Two: 20 points
- Wild and Wild Draw Four: 50 points

### Setup
1. Each player is dealt 7 cards
2. The remaining deck becomes the draw pile
3. One card is turned face up to start the discard pile
4. If the first card is a Wild Draw Four, it is returned to the deck and another card is drawn

### Gameplay
1. Players must match either the color, number, or action of the previous card
2. If unable to play, the player must draw a card from the draw pile
3. If the drawn card can be played, the player may play it immediately
4. If not, the player's turn ends
5. When a player has only one card left, they must call "UNO"
6. The first player to get rid of all their cards wins the round
7. Points are scored based on cards remaining in opponents' hands

### Winning
- The first player to get rid of all cards wins
- If the maximum number of turns is reached, the player with the least points wins
- If all players pass consecutively, the game ends and the player with the least points wins

## Programming Concepts

### Object-Oriented Programming
- **Inheritance**: Complex class hierarchy for different card types
- **Polymorphism**: Virtual functions for card behaviors
- **Encapsulation**: Private member variables with accessor methods
- **Abstract Classes**: Base Player class with pure virtual functions

### Memory Management
- **Dynamic Memory Allocation**: Player objects and cards
- **Smart Resource Management**: Proper cleanup to prevent memory leaks
- **Ownership Transfer**: Cards move between different containers (hands, piles)

### C++ Language Features
- **Virtual Functions**: For polymorphic behavior
- **Function Overriding**: Customizing behavior in derived classes
- **Templates**: Used in standard library containers
- **Lambda Functions**: For custom random shuffle function
- **Cross-Platform Conditional Compilation**: `#ifdef` directives

### Data Structures
- **Vectors**: For storing cards in hands, draw pile, and discard pile
- **Pointers**: For polymorphic card behavior and ownership management

### Game Design Patterns
- **State Pattern**: Game state tracking with the `GameState` struct
- **Strategy Pattern**: Different player strategies (human vs bot)
- **Command Pattern**: Each card type performs specific actions when played

## Code Architecture

### Class Hierarchy
```
Card
├── ActionCard
│   ├── Skip
│   │   └── Draw2
│   ├── Reverse
│   └── WildCard
│       └── WildDraw4
└── NumberCard (implicit in Card)

Player
├── Man (human player)
└── Bot (computer player)

Deck
├── DrawPile
└── DiscardPile
```

### Key Components
- **Card**: Base class for all cards
- **ActionCard**: Base class for cards with special actions
- **Player**: Abstract base class for all players
- **Man**: Human player implementation
- **Bot**: Computer player implementation
- **Deck**: Base class for card collections
- **DrawPile**: The pile players draw from
- **DiscardPile**: The pile players play cards onto
- **GameState**: Struct containing all game state variables

## Building and Running

### Prerequisites
- C++11 compatible compiler
- Standard C++ libraries

### Compiling
```bash
# For all platforms
g++ -std=c++11 *.cpp -o unogame

# Run the executable
./unogame  # On Unix/Mac
unogame.exe  # On Windows
```

### Game Setup
1. Enter a seed for the random number generator (optional)
2. Choose whether to play in debug mode (Y/N)
3. Set maximum number of turns (optional, default is 100)
4. Enter the number of human and bot players (total between 2-5)

## Implementation Details

### Card System
Cards implement a polymorphic design where each card type knows how to:
- Represent itself as a string with `toString()`
- Determine if it matches another card with `match()`
- Perform its action when played with `play()`

### Player Interaction
- **Human Players**: Display hand with playable cards highlighted and prompt for input
- **Bot Players**: Automatically select the first playable card or draw if none is available

### Game Flow Control
The main game loop:
1. Displays the current state (discard pile top card, current color, draw pile size)
2. Gets the current player and handles any pending effects (card draws, skips)
3. Lets the player pick a card to play or draw
4. Processes the played card's effects
5. Checks for game over conditions
6. Updates the game state for the next turn

### Random Number Generation
- Seeded random number generator for reproducible games
- Cross-platform implementation to ensure consistent behavior

## Gameplay Examples

### Sample Turn Display
```
=========================================================
Turn 6: 
Discard Pile: [WC]  Current Color: Red     Draw Pile: 40 
--------------------------------------------------------- 
Player 2 (Man):  
 [x][G8]  [x][Y9]  [2][R2]  [3][WD]  [x][B5]  [x][YS]  [x][G5]  [x][YR]  [8][WC]  
[D]raw 
Enter option: 8
Discarded [WC] 
Choose a color [R, Y, G, B]: Y
Color changed to Yellow!
```

### Key Features
- Clearly shows current game state
- Displays playable cards with their indices ([2][R2])
- Shows unplayable cards with [x] marker
- Allows drawing with the [D]raw option
- Handles special card effects like color selection for wild cards

---

This UNO implementation demonstrates advanced programming concepts while providing an engaging, interactive gaming experience. The code is structured to be maintainable and extensible, allowing for potential future enhancements such as additional card types, game modes, or AI improvements.