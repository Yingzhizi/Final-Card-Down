//Yingzhi Zhou (z5125679)
//Version 1(1/10/2017)
//Version 2 (3/10/2017)
//confused about how to initialize the new game use 'Game'


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"

void basicTestForInitialDeck (void);
void testCurrentPlayerAndTurn(void);
void basicTestForPlayerPoints(void);

int main (int argc, char *argv[]) {
    basicTestForInitialDeck ();
    testCurrentPlayerAndTurn();
    basicTestForPlayerPoints();

    printf("All test passed! Congratulation! :)\n");
    return EXIT_SUCCESS;
}

//In this function, we will test
//1, the number of cards in the initial deck
//2, the number of cards in the initial deck of a particular suit
//3, the number of card in the initial deck of a particular color
//4, the number of card in the initial deck of a particular value
//by creating a very simple deck contains 50 cards which are all RED, HEART, 1
void basicTestForInitialDeck (void) {
    //create a simple deck
    value values[50];
    suit suites[50];
    color colors[50];
    int i = 0;
    while (i < 50) {
        values[i] = 1;
        suits[i] = HEARTS;
        colors[i] = RED;
        i++;
    }
    Game g = newGame(50, values, colors, suits);
    //test the number of cards in the initial deck
    assert(numCards(g) == 50);

    //test the number of cards in the initial deck of a particular suit
    assert(numOfSuit(g, HEARTS) == 50);
    assert(numOfSuit(g, DIAMONDS) == 0);
    assert(numOfSuit(g, CLUBS) == 0);
    assert(numOfSuit(g, SPADES) == 0);
    assert(numOfSuit(g, QUESTIONS) == 0);

    //test the number of card in the initial deck of a particular color
    assert (numOfColor(new, RED) == 50);
    assert (numOfColor(new, BLUE) == 0);
    assert (numOfColor(new, GREEN) == 0);
    assert (numOfColor(new, YELLOW) == 0);
    assert (numOfColor(new, PURPLE) == 0);

    //test the number of cards in the intial deck of a particular value
    assert (numOfValue(g, 1) == 50);
    assert (numOfValue(g, DRAW_TWO) == 0);
    assert (numOfValue(g, 3) == 0);
    assert (numOfValue(g, 4) == 0);
    assert (numOfValue(g, 5) == 0);
    assert (numOfValue(g, 6) == 0);
    assert (numOfValue(g, 7) == 0);
    assert (numOfValue(g, 8) == 0);
    assert (numOfValue(g, 9) == 0);
    assert (numOfValue(g, ADVANCE) == 0);
    assert (numOfValue(g, BACKWARDS) == 0);
    assert (numOfValue(g, CONTINUE) == 0);
    assert (numOfValue(g, DECLARE) == 0);
    assert (numOfValue(g, E) == 0);
    assert (numOfValue(g, F) == 0);
    assert (numOfValue(g, 0) == 0);
}

//test currentPlayer, by making moves as each player
//check if the current player is correctly updated
void testCurrentPlayerAndTurn(void) {
    //all has the same type of suit
    //easiest way
    printf ("A very basic test for currentPlayer:\n");
    printf ("This test has a deck of 50 cards, all are RED 1 HEARTS\n");
    value values[50];
    suit suites[50];
    color colors[50];
    int i = 0;
    while (i < 50) {
        values[i] = 1;
        suits[i] = HEARTS;
        colors[i] = RED;
        i++;
    }
    Game g = newGame(50, values, colors, suits);
    int turn = 0;
    while (turn < 10) {
        //at this point, we're at the start of a new game,
        //so the current player is 0
        //direction are 0->1->2->3->0->1->2->3->... because no "BACKWARDS" is played
        //turn 0, player 0; turn 1, player 1...
        //but in turn 4, player becomes 0 again, so no.of player is turn % 4
        printf ("Testing that the current player.\n");
        assert(currentPlayer(g) == turn % 4);

        //test currentTurn and numTurn by constructing game
        //making moves as each player, and checking that
        //curren turn and number of turn are correctly update
        printf ("Testing that the current turn\n");
        assert(currentTurn(g) == turn);

        printf ("Testing that the number of turn\n");
        assert(numTurns(g) == turn + 1);

        //1st card in each player is always RED,1,HEARTS
        //make move as the first player(player 0)
        //need to get a card to play
        Card toPlay = handCard(g, 0);

        //we then want to play that card as a move
        //first make a move struct that says what move we want to do
        //1st move
        playerMove move;
        move.action = PLAY_CARD;
        move.card = toPlay;

        //then play the move
        playMove(g, move);

        //now, we need to end the turn, so we generate another move
        playerMove finalMove;
        finalMove.action = END_TURN;
        playMove (g, finalMove);

        //now we end the 0 turn, so current turn becomes 1
        //and current player should be the next player
        //which means: player becomes (turn+1) player
        //which will be tested in the beginning of the while loop
        turn++;
    }
}

//test the player point and game winner at the end of each round
//by constracting game, continuously making move until
//the player put the final card down and this player is game winner
//checking that each player's point is correctly updated
void basicTestForPlayerPoints(void) {
    //all has the same type of suit
    //easiest way
    printf ("A very basic test for currentPlayer:\n");
    printf ("This test has a deck of 50 cards, all are RED 1 HEARTS\n");
    value values[50];
    suit suites[50];
    color colors[50];
    int i = 0;
    while (i < 50) {
        values[i] = 1;
        suits[i] = HEARTS;
        colors[i] = RED;
        i++;
    }
    Game g = newGame(50, values, colors, suits);
    assert(playerPoints(g, 0) == 7);
    assert(playerPoints(g, 1) == 7);
    assert(playerPoints(g, 2) == 7);
    assert(playerPoints(g, 3) == 7);

    //play that card as a move
    //first make a move struct that says what move we want to do
    //1st move
    ​playerMove move;
    ​move.action = PLAY_CARDS;
    move.card = toPlay;

    //then play the move
    playMove(g, move);

    //now, we need to end this turn, so we generate another move
    playerMove finalMove;
    finalMove.action = END_TURN;
    playMove (g, finalMove);
    assert(playerPoints(g, 0) == 6);
    assert(playerPoints(g, 1) == 7);
    assert(playerPoints(g, 2) == 7);
    assert(playerPoints(g, 3) == 7);

    playMove(g, move);
    playMove (g, finalMove);
    assert(playerPoints(g, 0) == 6);
    assert(playerPoints(g, 1) == 6);
    assert(playerPoints(g, 2) == 7);
    assert(playerPoints(g, 3) == 7);

    playMove(g, move);
    playMove (g, finalMove);
    assert(playerPoints(g, 0) == 6);
    assert(playerPoints(g, 1) == 6);
    assert(playerPoints(g, 2) == 6);
    assert(playerPoints(g, 3) == 7);

}
