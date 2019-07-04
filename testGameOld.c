//Yingzhi Zhou (z5125679)
//Version 1(1/10/2017)
//Version 2 (3/10/2017)
//confused about how to initialize the new game use 'Game'


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
//with this define, can assert something like exper
#define assert(exp) ((void) 0)

//helper function
void testNumCards(void);
void testNumOfSuit(void);
void testNumOfColor(void);
void testNumOfValue(void);
void testCurrentPlayer(void);
void testTurn(void);
void basicPlayerPointsAndgameWinner(void);
void testPlayDirection(void);
void basicTurnMovesAndPastMove (void);
void testPlayerCardCount(void);
void testhandCardCount(void);
void testHandCard(void);
void testValidMove(void);
void testNoWinner (void);
/******************************
 * helper function
 ******************************/
//deck 1
//make a deck of 40 cards
//first 21 cards have value 1
//the 4th player hold BACKWARDS card
Game deck1(void) {
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
Game sameCards(void) {
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

//helper function "playCard "
//generate a move: PLAY_CARD
playerMove playCard(Game game, int n) {
    Card toPlay = handCard(game, n);
    playerMove move;
    move.action = PLAY_CARD;
    move.card = toPlay;
    return move;
}

//generate a move to drawing a card
//say uno/duo/trio
//or end turn
playerMove makeMove(action act) {
    playerMove move;
    move.action = act;
    return move;
}


/******************************
 * helper function
 ******************************/

int main (int argc, char *argv[]) {
    testNumCards(void);
    testNumOfSuit(void);
    testNumOfColor(void);
    testNumOfValue(void);
    testCurrentPlayer(void);
    testTurn(void);
    basicPlayerPointsAndgameWinner(void);
    testPlayDirection(void);
    basicTurnMovesAndPastMove (void);
    testPlayerCardCount(void);
    testhandCardCount(void);
    testHandCard(void);
    testValidMove(void);
    testNoWinner (void);

    printf("All test passed! Congratulation! :)\n");
    return EXIT_SUCCESS;
}

//test the number of cards in the initial deck, should be 800
void testNumCards (void) {
    //test deck1
    Game g = deck1(void);
    assert(numCards(g) == 40);

    destroyGame(g);
    Game g = sameCards(void);
    assert(numCards(g) == 50);
}

//test the number of cards in the initial deck of a particular color
void testNumOfSuit (void) {
    //HEARTS = 0
    //DIAMONDS = 1
    //CLUBS = 2
    //SPADES = 3
    //QUESTIONS = 4
    suit newSuit1 = HEARTS;
    suit newSuit2 = DIAMONDS;
    suit newSuit3 = CLUBS;
    suit newSuit4 = SPADES;
    suit newSuit5 = QUESTIONS;
    //test deck1
    Game g = deck1(void);
    assert(numOfSuit(g, newSuit1) == 0);
    assert(numOfSuit(g, newSuit2) == 0);
    assert(numOfSuit(g, newSuit3) == 40);
    assert(numOfSuit(g, newSuit4) == 0);
    assert(numOfSuit(g, newSuit5) == 0);

    //tesk deck2
    destroyGame(g);
    g = sameCards(void);
    assert(numOfSuit(g, newSuit1) == 50);
    assert(numOfSuit(g, newSuit2) == 0);
    assert(numOfSuit(g, newSuit3) == 0);
    assert(numOfSuit(g, newSuit4) == 0);
    assert(numOfSuit(g, newSuit5) == 0);

}

//test the number of card in the initial deck of a particular color
void testNumOfColor(void) {
    color newColors1 = RED;
    color newColors2 = BLUE;
    color newColors3 = GREEN;
    color newColors4 = YELLOW;
    color newColors5 = PURPLE;
    //test deck1 set
    Game g = deck1(void);
    assert (numOfColor(new, newColors1) == 0);
    assert (numOfColor(new, newColors2) == 0);
    assert (numOfColor(new, newColors3) == 0);
    assert (numOfColor(new, newColors4) == 40);
    assert (numOfColor(new, newColors5) == 0);

    //test deck2 set
    destroyGame(g);
    g = sameCards(void);
    assert (numOfColor(new, newColors1) == 50);
    assert (numOfColor(new, newColors2) == 0);
    assert (numOfColor(new, newColors3) == 0);
    assert (numOfColor(new, newColors4) == 0);
    assert (numOfColor(new, newColors5) == 0);
}

//test the number of cards in the intial deck of a particular value
void testNumOfValue(void) {
    value newValue1 = 1;
    value newValue2 = DRAW_TWO;
    value newValue3 = 3;
    value newValue4 = 4;
    value newValue5 = 5;
    value newValue6 = 6;
    value newValue7 = 7;
    value newValue8 = 8;
    value newValue9 = 9;
    value newValueA = ADVANCE;
    value newValueB = BACKWARDS;
    value newValueC = CONTINUE;
    value newValueD = DECLARE;
    value newValueE = E;
    value newValueF = F;
    value newValue0 = 0;

    //test deck1
    Game g = deck1(void);
    assert (numOfValue(g, newValue1) == 33);
    assert (numOfValue(g, newValue2) == 0);
    assert (numOfValue(g, newValue3) == 0);
    assert (numOfValue(g, newValue4) == 0);
    assert (numOfValue(g, newValue5) == 0);
    assert (numOfValue(g, newValue6) == 0);
    assert (numOfValue(g, newValue7) == 0);
    assert (numOfValue(g, newValue8) == 0);
    assert (numOfValue(g, newValue9) == 0);
    assert (numOfValue(g, newValueA) == 0);
    assert (numOfValue(g, newValueB) == 7);
    assert (numOfValue(g, newValueC) == 0);
    assert (numOfValue(g, newValueD) == 0);
    assert (numOfValue(g, newValueE) == 0);
    assert (numOfValue(g, newValueF) == 0);
    assert (numOfValue(g, newValue0) == 0);

    //test deck 2
    destroyGame(g);
    g = sameCards(void);
    assert (numOfValue(g, newValue1) == 50);
    assert (numOfValue(g, newValue2) == 0);
    assert (numOfValue(g, newValue3) == 0);
    assert (numOfValue(g, newValue4) == 0);
    assert (numOfValue(g, newValue5) == 0);
    assert (numOfValue(g, newValue6) == 0);
    assert (numOfValue(g, newValue7) == 0);
    assert (numOfValue(g, newValue8) == 0);
    assert (numOfValue(g, newValue9) == 0);
    assert (numOfValue(g, newValueA) == 0);
    assert (numOfValue(g, newValueB) == 0);
    assert (numOfValue(g, newValueC) == 0);
    assert (numOfValue(g, newValueD) == 0);
    assert (numOfValue(g, newValueE) == 0);
    assert (numOfValue(g, newValueF) == 0);
    assert (numOfValue(g, newValue0) == 0);
}



    //BACKWARDS??
    //deck 1
    //1st turn
    //player 0
    destroyGame(g);
    printf ("A basic test for currentPlayer:\n");
    printf ("This test has a deck of 40 cards, 33 cards are YELLOW 1 CLUBS,
    7 cards are YELLOW BACKWARDS CLUBS\n");
    g = deck1(void);
    assert(currentPlayer(g) == 0);
    //player 0 play 1st card in his hand.
    playerMove move = playCard(g, 0);
    playMove(g, move);
    //end 1st turn
    playerMove finalMove = mekeMove(END_TURN);
    playMove(g, finalMove);
    //player 1
    printf ("Testing that the current player is 1\n");
    assert(currentPlayer(g) == 1);

    //2ed turn
    move = playCard(g, 0);
    playMove(g, move);
    playMove(g, finalMove);
    //end 2ed turn
    //player 2
    printf ("Testing that the current player is 2\n");
    assert(currentPlayer(g) == 2);

    //3rd turn
    //player 2 played the 6th card in his hand
    //which is BACKWARDS
    move = playCard(g, 5);
    playMove(g, move);
    playMove(g, finalMove);
    //end 3rd turn
    //player 1, because of player 2 discard "BACKWARDS"
    //direction reversed
    printf ("Testing that the current player is 1\n");
    assert(currentPlayer(g) == 1);

    //4th turn
    move = playCard(g, 0);
    playMove(g, move);
    playMove(g, finalMove);
    //end 4th turn
    //player 0;
    printf ("Testing that the current player is 0\n");
    assert(currentPlayer(g) == 0);

    //5th turn
    //play "BACKWARDS" card again
    move = playCard(g, 6);
    playMove(g, move);
    playMove(g, finalMove);
    //end 5th turn
    //direction reversed again
    //player 1;
    printf ("Testing that the current player is 1\n");
    assert(currentPlayer(g) == 1);
}


//test the player point and game winner at the end of each round
//by constracting game, continuously making move until
//the player put the final card down and this player is game winner
//checking that each player's point is correctly updated
void basicPlayerPointsAndgameWinner(void) {
    printf ("A very basic test for currentPlayer:\n");
    printf ("This test has a deck of 50 cards, all are RED 1 HEARTS\n");
    Game g = sameCards(void);
    //each player play one card in turn
    //until one player put the final card down
    //at the end of this round, the number of turn is 25
    int turn = 0;
    while (turns < 25) {
        //get a card to play
        Card toPlay = handCard(g, 0);

        //play that card as a move
        //first make a move struct that says what move we want to do
        //1st move
    ​    playerMove move;
    ​    move.action = PLAY_CARDS;
        move.card = toPlay;

        //then play the move
        playMove(g, move);

        //now, we need to end this turn, so we generate another move
        playerMove finalMove;
        finalMove.action = END_TURN;
        playMove (g, finalMove);
        i++;
    }
    //now, turns = 25
    //at turns 25, player 0 put the final card down
    //player 0 is winner!!! got 0 socre
    //other player all got 1 score
    printf("Testing the final point of player 0 is 0\n");
    assert(playerPoints(g,0) == 0);
    //testing the game winner is player 0
    printf("Testing the game winner is player 0!!!\n");
    assert(gameWinner(g) == 0);

    printf("Testing the final point of player 1 is 1\n");
    assert(playerPoints(g,1) == 1);
    printf("Testing the final point of player 2 is 1\n");
    assert(playerPoints(g,2) == 1);
    printf("Testing the final point of player 3 is 1\n");
    assert(playerPoints(g,3) == 1);

}

//by constracting a very simple game, making moves as each player
//test the number of moves that happened on a turn,
//checking the move in each turn is correctly updated
void basicTurnMovesAndPastMove (void) {
    //the equation of aseert is wrong
    //the type of struct in the LHS is not equal to the RHS
    //LHS is struct_playerMove, but the RHS is action.
    //waiting fixed
//**************************************************
    //for deck made up of same cards
    printf ("A very basic test for currentPlayer:\n");
    printf ("This test has a deck of 50 cards, all are RED 1 HEARTS\n");
    Game game = sameCards();

    //at the beginning of the game, no move happen
    assert(turnMoves(g, 0) == 0);

    //all the cards in this deck are the sameCards
    //the move between 1th to 12th turns are PLAY_CARD and END_TURN
    //so there will have 2 moves in a turn
    int turn = 1;
    while (turn < 13) {
        playerMove move = playCard(game, 0);
        playMove(game, move);
        playerMove finalMove = makeMove(END_TURN);
        playMove(game, finalMove);
        printf("Testing the move in a turn are 2 from 1th to 12th turn\n");
        assert(turnMoves(game, turn) == 2);

        //testing 1st move between 1th to 12th turn is PLAY_CARD;
        printf("Testing the action int 1st move in %dth turn is PLAY_CARD\n", turn);
        playerMove testFirstMove = pastMove(game, turn, 0);
        assert(testFirstMove == move);
        //tesdting 2ed move between 1th to 12th turn is END_TURN;
        printf("Testing the action int 2ed move in %dth turn is END_TURN\n", turn);
        playerMove testSecondMove = pastMove(game, turn, 1);
        assert(testSecondMove == finalMove);
        turn++;
    }
    //the move between 13th to 24th turns consisted of PLAY_CARD and
    //SAY_TRIO/SAY_DUO/SAY_UNO
    //and END_TURN, so in total they have 3 moves in each turn
    while (turn < 25) {
        playerMove move = playCard(game, 0);
        playMove(game, move);
        action act;
        if (turn < 17) {
            act = SAY_TRIO;
        } else if (turn < 21) {
            act = SAY_DUO;
        } else {
            act = SAY_UNO;
        }
        playerMove midMove = makeMove(act);
        playerMove finalMove = makeMove(END_TURN);
        playMove(g, finalMove);
        printf("Testing the move in a turn are 3 from 13th to 24th turn\n");
        assert(turnMoves(game, i) == 3);

        //testing 1st move between 13th to 24th turn is PLAY_CARD;
        printf("Testing the action 1st move in %dth turn is PLAY_CARD\n", turn);
        playerMove testFirstMove = pastMove(game, turn, 0);
        assert(testFirstMove == move);
        //testing 2ed move between 13th to 24th turn is
        //SAY_UNO,SAY_DUO or SAY_TRIO
        printf("Testing the action in 2ed move in %dth turn is %c\n", turn, act);
        playerMove testSecondMove = pastMove(game, turn, 1);
        assert(testSecondMove == midMove);
        //tesdting 3rd move between 13th to 24th turn is END_TURN;
        printf("Testing the action in 3rd move in %dth turn is END_TURN\n", turn);
        playerMove testThirdMove = pastMove(game, turn, 2);
        assert(testThirdMove == finaldMove);
        turn++;
    }

    //At 25th turn, player 0 plays the final card and end the turn
    //consist of PLAY_CARD and END_TURN, 2 moves
    //round finished
    playerMove move = playCard(game, 0);
    playMove(game, move);
    playerMove finalMove = makeMove(END_TURN);
    playMove(game, finalMove);
    printf("Testing the move in 25th turn are 2.\n");
    assert(turnMoves(g, 25) == 2);
    //testing 1st move in 25th turn is PLAY_CARD;
    printf("Testing the 1st move in 25th turn is PLAY_CARD\n");
    playerMove testfitstMove = pastMove(game, 25, 0);
    assert(testfirstMove = move);
    //tesdting 2ed move between 1th to 12th turn is END_TURN;
    printf("Testing the 2ed move in 25th turn is END_TURN\n");
    playerMove testSecondMove = pastMove(game, 25, 1);
    assert(testSecondMove = finalMove);
}



void testDrawTwo(void) {
    //isValidMove(Game game, playerMove move);
    value values[50];
    suit suits[50];
    color colors[50];
    values[0] = 1;
    values[1] = DRAW_TWO;
    values[2] = DRAW_TWO;
    values[3] = 1;
    int i = 4;
    while (i < 50) {
        values[i] = 1;
        i++;
    }

    i = 0;
    while (i < 50) {
        suits[i] = HEARTS;
        colors[i] = RED;
        i++;
    }

    Game game = newGame(50, values, colors, suits);
    //player 0
    //1st move
    playerMove move = playCard(game, 0);
    //then play the move
    playMove(game, move);
    //now, we need to end the turn, so we generate another move
    playerMove finalMove;
    finalMove = makeMove(END_TURN);
    playMove(game, finalMove);

    //now, player 1
    //value: DRAW_TWO
    move = playCard(game, 0);
    playMove(game, move);
    playMove(game, finalMove);
    //test this step is valid
    assert(isValidMove(game, move) == TRUE);

    //player 2
    //need to draw 2 cards or play a 2 value;
    //at this time, play 2
    move = playCard(game, 0);
    playMove(game, move);
    playMove(game, finalMove);
    assert(isValidMove(game, move) == TRUE);

    //player 3
    //need to draw 4 cards or play 2;
    move = makeMove(DRAW_CARD);
    playMove(game, move);
    playMove(game, finalMove);
    assert(isValidMove(game, move) == TRUE);
}

void testAdvanced(void) {
    value values[50];
    suit suits[50];
    color colors[50];
    int i = 0;
    while (i < 50) {
        values[i] = ADVANCE;
        suits[i] = HEARTS;
        colors[i] = RED;
    }
    Game game = newGame(50, values, colors, suits);

    int turn = 1;
    playerMove move;
    playerMove finalMove = makeMove(END_TURN);
    while (turn < 14) {
        move = playCard(game, 0);
        playMove(game, move);
        playMove(game, finalMove);
        //player 0 to player 2
        if (turn % 2 == 0) {
            assert(currentPlayer(game) == 0);
        } else {
            assert(currentPlayer(game) == 2);
        }
        assert(isValidMove(game, move) == TRUE);
        turn++;
    }
}

void testContinue (void) {
    //creat a deck, only the first card is CONTINUE;
    value values[50];
    suit suits[50];
    color colors[50];
    values[0] = CONTINUE;
    values[1] = CONTINUE;
    values[2] = CONTINUE;
    values[3] = CONTINUE;
    int i = 0;
    while (i < 50) {
        colors[i] = RED;
        suits[i] = HEARTS;
        i++;
    }
    i = 4;
    while (i < 50) {
        values[i] = 1;
        i++;
    }

    //create a new game use the deck created before
    Game game = newGame(50, values, colors, suits);
    playerMove move = playCard(game, 0);
    playMove(game, move);
    //because CONTINUE was played, so player may played another card
    move = playCard(game, 0);
    playMove(game, move);
    playerMove finalMove = makeMove(END_TURN);
    playMove(game, finalMove);
    assert(isValidMove(game, move) == TRUE);
    //end turn now

    //next player
    //RED, HEARTS, CONTINUE
    move = playCard(game, 0);
    playMove(game, move);
    //Althought CONTINUE was played, player can also choose
    //do not play another card, just play one card, then end turn
    playMove(game, finalMove);
    //for this situation, the move is also valid
    assert(isValidMove(game, move) == TRUE);

    //next player

}

//test a given move is valid or not
//while a value DECLARE is played
//the current player who play DECLARE must state which color
//the next player's discarded should be
void testDeclare(void) {
    //make a simple deck which contain 50 cards
    //all values are DECLARE and all suits are HEARTS
    //But the color is RED, BLUE, GREEN, YELLOW, altinatively.
    //which means array colors are [0,1,2,3,4,0,1,2,3,...]
    value values[50];
    suit suits[50];
    color colors[50];
    int i = 0;
    while (i < 50) {
        values[i] = DECLARE;
        suits[i] = HEARTS;
        if (i % 5 == 0) {
            colors[i] = RED;
        } else if (i % 5 == 1) {
            colors[i] = BLUE;
        } else if (i % 5 == 2) {
            colors[i] = GREEN;
        } else if (i % 5 == 3) {
            colors[i] = YELLOW;
        } else if (i % 5 == 4) {
            colors[i] = PURPLE;
        }
        i++;
    }
    //create a new game use the deck created before
    Game game = newGame(50, values, colors, suits);
    int turn = 0;
    while (turn < 20) {
        playerMove move;
        move.action = PLAY_CARD;
        //declare the next color
        //for example, player 0 declare the next color is (0%5) + 1
        //which is color blue.
        move.nextColor = (turn % 5) + 1;
        //play the 1st card in handCard
        //for player 0, 1st card is RED
        //for the second player, 1st card is BLUE
        //which is the same as the declred color, so the move is valid.
        move.card = handCard(game, 0);
        playMove(game, move);
        assert(isValidMove(game, move) == TRUE);
        playerMove finalMove = makeMove(END_TURN);
        playMove(game, finalMove);
        turn++;
    }
}



//test the winner at the end of each round
//by constracting a complex game, continuously making move
//if there are no winner
void testNoWinner (void) {
}

//to determine wether a card is in the player's handCard
//if it in, return TRUE; else return != TRUE;
int inPlayerHand (Game game, Card card) {
    int i = 0;
    while (i < handCardCount(game)) {
        if (card == handCard(game, i)) {
            //card in player's hand
            return 1;
        }
        i++;
    }
    //card is not in player's hand
    return 0;
}
