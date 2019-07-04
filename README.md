# Final-Card-Down
My first year card game

# Introduction
The game Final Card-Down is a card game played with a special printed deck.
Each card has a value between 0x0 and 0xF, a suit of either hearts, diamonds, clubs, spades, or questions, and a color of either red, green, blue, yellow, or purple.
Each player is dealt a hand of 7 cards. The first player to place their final card down in the discard pile wins.

# Rules
<h3>The Cards</h3>
There are 800 cards in the traditional deck for Final Card-Down. Each card has a suit, color, and a value and there are two of each kind of card.

There are 16 values that a card can have, one for each value from 0 to F in hexadecimal; 0 may also be referred to as NULL. There are five suits; hearts, diamonds, clubs, spades, and questions. There are five colors; red, blue, green, yellow, and purple.

<h3>The Start Of Play</h3>
At the start of the game, the deck is shuffled. From the deck, each player is dealt 7 cards. The first card goes to the first player, the second to the second player, the third to the third player, the fourth to the fourth player, the fifth to the first player, and so on, until each player has 7 cards. These 7 cards form the players hand. The top card on the deck is then removed and placed facing up, starting the discard pile. The rest of the deck becomes the draw pile.

<h3>Playing the Game</h3>
Each player takes a turn, starting in a clockwise direction. During a turn a player may make one of the following sets of actions:

* Call the previous player out for having reached 3, 2, or 1 cards left in their hand. This may only be done once for each number of cards. Then,
* Draw a card from the draw pile then end their turn,
* Discard a card with the same value, color, or suit as the card on the top of the discard pile or a card with a value of NULL.

  * If the value of the card is

    * 2, the next player must either draw two cards from the deck into their hand or play another card with a value of 2. If they play a 2, they draw no cards and the player after them must draw 4 cards. Cards with a value of 2 may be stacked on each other increasing the number of cards to be drawn by 2 until a player can not place down a 2 card.
    * A, they next player’s turn is skipped,
    * B, the order of play is reversed,
    * C, the player may discard an additional card,
    * D, the player may declare the color that the next card played must have (instead of the color of the card they played).
  * If there are now
    * three cards left in the players hand, they must say the word “TRIO”,
    * two cards left in the players hand, they must say the word “DUO”,
    * one cards left in the players hand, they must say the word “UNO”.
  * If the player does not say one of the above phrases at the appropriate time, the next player may say it at the start of their turn, forcing the player to draw 2 cards.

  * If there are no cards remaining in the draw pile, then the current discard pile is collected and inverted to become the draw pile. The discard pile does not need to be shuffled when turning it into the draw pile. The first card that was played into the discard pile will become the first card to be drawn from the draw pile.
  
# Get the files
<h3>testGame.c</h3>
which tests an implementation of the functions in Game.h
<h3>Game.c</h3>
which implements the functions described in Game.h
<h3>player.c</h3>
which implements an AI using the function described in player.h
