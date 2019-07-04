//Yingzhi Zhou (z5125679)
//Version 1(1/10/2017)
//confused about how to initialize the new game use 'Game'


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"


//helper function
Game deck1();
Gmae sameCards();
/******************************
 * helper function
 ******************************/
//deck 1
//make a deck of 40 cards
//first 21 cards have value 1
//the 4th player hold BACKWARDS card
Game deck1() {
    value values[40] = {
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
        BACKWARDS,BACKWARDS,BACKWARDS,BACKWARDS,BACKWARDS,
        BACKWARDS,BACKWARDS,1,1,1,1,1,1,1,1,1,1,1,1
    };
    suit suits[40];
    color colors[40];
    int i = 0;
    while (i < 40) {
        colors[i] = YELLOW;
        suits[i] = CLUBS;
        i++;
    }
    Game g = newGame(40, values, colors, suits);
    return g;
}
//deck 2
//in this game, deck size is 50, and all cards have the same value, suit and color
//RED 1 HEARTS
Game sameCards() {
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
    return g;
}

/******************************
 * helper function
 ******************************/

int main (int argc, char *argv[]) {
    /all has the same type of suit
    //easiest way
    //deck 2
    Game g = sameCards();

    //at this point, we're at the start of a new game,
    //so the current player is 0
    assert(currentPlayer(g) == 0);
    assert(currentTurn(g) == 0);
    assert(numTurns(g) == 1);

    //make move as the first player(player 0)
    //need to get a card to play
    //assume it is BLUE 1 HEARTS
    Card toPlay = handCard(g, 0);
    //we then want to play that card as a move:
    //first make a move struct that says what move we want to do
    //1st move
    playerMove move1;
    move1.action = PLAY_CARD;
    move1.card = toPlay;
    //then play the move
    playMove(g, move1);
    //we don't need to free the move, because it's on the stack
    //so, now we made a move, it should now be turn 1
    //and current player should be player 1:
    assert(currentPlayer(g) == 1);
    assert(currentTurn(g) == 1);
    assert(numTurns(g) == 2);
    assert(playDirection(g) == CLOCKWISE);

    //2ed move
    //player 1
    toPlay = handCard(g, 1);
    playerMove move2;
    move2.action = PLAY_CARD;
    move2.card = toPlay;
    playMove(g, move2);
    //now we made the secong move, it should now be turn 2
    //and current player should be player 2:
    assert(currentPlayer(g) == 2);
    assert(currentTurn(g) == 2);
    assert(numTurns(g) == 3);
    assert(playDirection(g) == CLOCKWISE);

    //3rd move
    toPlay = handCard(g, 2);
    playerMove move3;
    move3.action = PLAY_CARD;
    move3.card = toPlay;
    playMove(g, move3);
    assert(currentPlayer(g) == 3);
    assert(currentTurn(g) == 3);
    assert(numTurns(g) == 4);
    assert(playDirection(g) == CLOCKWISE);

    //4th move
    //0->1->2->3->0
    toPlay = handCard(g, 3);
    playerMove move4;
    move4.action = PLAY_CARD;
    move4.card = toPlay;
    playMove(g, move4);
    assert(currentPlayer(g) == 0);
    assert(currentTurn(g) == 4);
    assert(numTurns(g) == 5);
    assert(playDirection(g) == CLOCKWISE);

    //BACKWARDS??
    //deck 1
    //1st turn
    //player 0
    destroyGame(g);
    g = deck1();
    assert(currentPlayer(g) == 0);
    toPlay = handCard(g, 0);
    playerMove move;
    move.action = PLAY_CARD;
    move.card = toPlay;
    playMove(g, move);
    //end 1st turn
    //player 1
    assert(currentPlayer(g) == 1);

    //2ed turn
    toPlay = handCard(g, 7);
    move.action = PLAY_CARD;
    move.card = toPlay;
    playMove(g, move);
    //end 2ed turn
    //player 2
    assert(currentPlayer(g) == 2);

    //3rd turn
    toPlay = handCard(g, 21);
    move.action = PLAY_CARD;
    move.card = toPlay;
    playMove(g, move);
    //end 3rd turn
    //player 1, because of player 2 discard "BACKWARDS"
    //direction reversed
    assert(currentPlayer(g) == 1);

    //4th turn
    toPlay = handCard(g, 8);
    move.action = PLAY_CARD;
    move.card = toPlay;
    playMove(g, move);
    //end 4th turn
    //player 0;
    assert(currentPlayer(g) == 0);

    //5th turn
    //play "BACKWARDS" card again
    toPlay = handCard(g, 21);
    move.action = PLAY_CARD;
    move.card = toPlay;
    playMove(g, move);
    //end 5th turn
    //direction reversed again
    //player 1;
    assert(currentPlayer(g) == 1);
    }
    EXIT_SUCCESS;
}
