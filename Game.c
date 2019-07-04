//Assignment 2
//The final Card-Down

//Group members
//Yingzhi Zhou (z5125679)
//Bozhi Yang (z5142096)
//Zhengyu Sun (z5157726)
//Ahnaf Aaqif (z5125723)
//Final Version
//2017-10-29

//Tutor's name
//Stephen Leung (F09B)

#include <stdio.h>
#include <stdlib.h>

#include <err.h>
#include "Game.h"
#include <assert.h>

#define nonexistCard -1

typedef struct _node *Node;
typedef struct _playerHand *PlayerHand;
typedef struct _list *List;
typedef struct _moveNode *MoveNode;
typedef struct _moveList *MoveList;
typedef struct _turnNode *TurnNode;
typedef struct _turnList *TurnList;

typedef struct _node {
    Card card;
    Node next;
} node;

typedef struct _playerHand {
    //the number of card in given card list
    int num;
    List cardList;
} playerHand;

typedef struct _list {
    Node head;
} list;

typedef struct _moveNode {
    playerMove move;
    MoveNode next;
} moveNode;

typedef struct _moveList {
    MoveNode head;
} moveList;

typedef struct _turnNode {
    TurnNode next;
    MoveList moves;
} turnNode;

typedef struct _turnList {
    TurnNode head;
} turnList;

typedef struct _game {
    int deckSize;
    int currentPlayer;
    int nextPlayer;
    int currentTurn;
    Card *card;
    PlayerHand *player;
    direction currentDirection;
    List deckPile;
    List discardPile;
    TurnList turns;
} game;


//helper function
static Node newNode(Card card);
static List newList (void);
static void deleteHeadOfList (List l);
static void insertHeadOfList (List l, Card insert);
static void listDeleteNth (List l, int n);
static void listDeleteCard (List l, Card card);
static direction changeDirection (direction nowDirection);
static int turnLength(TurnList turns);
static int moveLength(TurnNode turn);
static int matchDeclareColor (playerMove lastMove, playerMove move);
static int matchCard (Card a, Card b);
static int canDrawCard (Game game);
static int canPlayCard (Game game);
static int gameIsOver(Game game);
static MoveNode newMoveNode (playerMove move);
static void insertHeadOfMoveList (TurnList list, playerMove move);
static void insertHeadOfTurnList(TurnList list);
static int lengthOfCardList (List l);


// Create a new game engine.
//
// This creates a game with a deck of the given size
// and the value, color, and suit of each card to be taken from
// each of the arrays in order.
//
// Your game will always have 4 players. Each player starts with a hand
// of 7 cards. The first card from the deck is given to player 0, the
// second to player 1, the third to player 2, the fourth to player 3,
// the fifth to player 0, and so on until each player has 7 cards.
Game newGame(int deckSize, value values[], color colors[], suit suits[]) {
    //create a new game
    Game game = calloc(1, sizeof(struct _game));

    int i = 0;
    //one in the *card is '\0' <- use one space
    while (i < deckSize) {
        game->card[i] = newCard(values[i], colors[i], suits[i]);
        i++;
    }

/************************set these card as a link list***********************/
    Node first = newNode(game->card[0]);
    Node curr = first;
    i = 1;
    while (i < deckSize) {
        Card newCard = game->card[i];
        /*calloc here */
        /*pay attention here, we need to free this in destroy game*/
        curr->next = newNode(newCard);
        curr = curr->next;
        i++;
    }
    //create a link list to store the card
    game->deckPile = calloc(1, sizeof(struct _list));
    game->deckPile->head = first;
    //now, we store the card in deck pile as a card list

/*************create 4 player, each player hold a card list********************/
    game->player = calloc(NUM_PLAYERS, sizeof(struct _playerHand));

    //deliver card
    i = 0;
    while (i < 4) {
        Node curr = newNode(game->card[i]);
        game->player[i]->cardList = newList();
        game->player[i]->cardList->head = curr;
        curr->next == NULL;
        game->player[i]->num += 1;
        //now we deliver one card to player 0
        //so we need to delete the head of the deckPile
        deleteHeadOfList (game->deckPile);
        int j = 1;
        while (j < 7) {
            int cardIndex = 4 * j + i;
            Card new = game->card[cardIndex];

            //we need to insert this to the head of the card list of current player's hand
            insertHeadOfList (game->player[i]->cardList, new);
            //the number of cards in current player's hand will also +1
            game->player[i]->num += 1;

            //at the same time, we have to delete this card in deckPile list
            listDeleteNth (game->deckPile, cardIndex);
            j++;
        }
        i++;
    }

    //create a card list for discard pile to store cards
    game->discardPile = calloc(1, sizeof(struct _list));

    //after deliver each player 7 cards
    //we put the top card in the deck pile to the discard pile
    game->discardPile->head = game->deckPile->head;
    deleteHeadOfList (game->deckPile);

    game->deckSize = deckSize;
    game->currentPlayer = 0;
    game->nextPlayer = 1;
    game->currentTurn = 0;
    game->currentDirection = CLOCKWISE;
    game->turns = calloc(1, sizeof(struct _turnList));
    game->turns->head = NULL;
    return game;
}


// Destroy an existing game.
//
// This should free all existing memory used in the game including
// allocations for players and cards.
void destroyGame(Game game) {
    free(game->turns);
    free(game->discardPile);
    int i = 0;
    while (i < NUM_PLAYERS) {
        free(game->player[i].cardList);
        i++;
    }
    free(game->player);
    free(game->deckPile);
    i = 0;
    while (i < game->deckSize) {
        free(game->card[i]);
        i++;
    }
    free(game->card);
    free(game);
}


// The following functions can be used by players to discover
// information about the state of the game.
// Get the number of cards that were in the initial deck.
int numCards(Game game) {
    if (game == NULL) {
        err (EXIT_FAILURE, "No such game exists.");
    }
    return game->deckSize;
}


// Get the number of cards in the initial deck of a particular
// suit.
int numOfSuit(Game game, suit suit) {
    if (game == NULL) {
        err (EXIT_FAILURE, "No such game exists.");
    }
    int i = 0;
    int num = 0;
    while (i < game->deckSize) {
        if (cardSuit(game->card[i]) == suit) {
            num++;
        }
        i++;
    }
    //get the number of card of a specified suit
    return num;
}


// Get the number of cards in the initial deck of a particular color.
int numOfColor(Game game, color color) {
    if (game == NULL) {
        err (EXIT_FAILURE, "No such game exists.");
    }
    int i = 0;
    int num = 0;
    while (i < game->deckSize) {
        if (cardColor(game->card[i]) == color) {
            num++;
        }
        i++;
    }
    //get the number of card of a specified color
    return num;
}


// Get the number of cards in the initial deck of a particular value.
int numOfValue(Game game, value value) {
    if (game == NULL) {
        err (EXIT_FAILURE, "No such game exists.");
    }
    int i = 0;
    int num = 0;
    while (i < game->deckSize) {
        if (cardValue(game->card[i]) == value) {
            num++;
        }
        i++;
    }
    //get the number of card of a specified value
    return num;
}


// Get the number of the player whose turn it is.
int currentPlayer(Game game) {
    if (game == NULL) {
        err (EXIT_FAILURE, "No such game exists.");
    }
    return game->currentPlayer;
}


// Get the current turn number.
// The turn number increases after a player ends their turn.
// The turn number should start at 0 once the game has started.
int currentTurn(Game game) {
    if (game == NULL) {
        err (EXIT_FAILURE, "No such game exists.");
    }
    return game->currentTurn;
}

// Get the number of points for a given player.
// Player should be between 0 and 3.
// This should _not_ be called by a player.
int playerPoints(Game game, int player) {
    if (game == NULL) {
        err (EXIT_FAILURE, "No such game exists.");
    }
    int sum = 0;
    Node curr = game->player[player]->cardList->head;
    while (curr != NULL) {
        sum = sum + cardValue(curr->card);
        curr = curr->next;
    }
    return sum;
}


// Get the current direction of play.
direction playDirection(Game game) {
    if (game == NULL) {
        err (EXIT_FAILURE, "No such game exists.");
    }
    return game->currentDirection;
}

// This function returns the number of turns that have occurred in the
// game so far including the current turn.
// When using either the turnMoves or pastMove function,
// the turn number should be less than the number of moves that this
// function returns.
// (i.e. on turn 0 of the game, this should return 1, as there has been
// 1 turn so far including the current turn; if you called pastMove you
// would need to call it on turn 0, as this is the only possible value
// less than 1.)
int numTurns(Game game) {
    return game->currentTurn + 1;
}


// Get the number of moves that happened on a turn.
//
// A turn may consist of multiple moves such as drawing cards,
// playing cards, and ending the turn.
int turnMoves(Game game, int turn) {
    int lengthOfTurn = turnLength(game->turns);
    TurnNode curr = game->turns->head;
    int i = 0;
    while (i < lengthOfTurn - turn) {
        curr = curr->next;
        i++;
    }
    int lengthOfMove = moveLength(curr);
    return lengthOfMove;
}


// Look at a previous move from a specified turn.
playerMove pastMove(Game game, int turn, int move) {
    int lengthOfTurn = turnLength(game->turns);
    TurnNode currTurn = game->turns->head;
    int i = 0;
    while (i < lengthOfTurn - turn) {
        currTurn = currTurn->next;
        i++;
    }

    int lengthOfMove = moveLength(currTurn);
    MoveNode currMove = currTurn->moves->head;
    i = 0;
    while (i < moveLength - move) {
        currMove = currMove->next;
        i++;
    }
    return currMove->move;
}


// Get the number of cards in a given player's hand.
int playerCardCount(Game game, int player) {
    if (game == NULL) {
        err (EXIT_FAILURE, "No such game exists.");
    }
    //because of we store cards in player's hand by using link list
    //so to calculate the num of card, we use the similar way as
    //calculate the length of a list
    Node curr = game->player[player]->cardList->head;
    int num = 0;
    while (curr != NULL) {
        num++;
        curr = curr->next;
    }
    return num;
}


// Get the number of cards in the current player's hand.
int handCardCount(Game game) {
    int num;
    num = playerCardCount(game, currentPlayer(game));
    return num;
}


// View a card from the current player's own hand.
// The player should not need to free() this card,
// so you should not allocate or clone an existing card
// but give a reference to an existing card.
Card handCard(Game game, int card) {
    int playerIndex = currentPlayer(game);
    Node curr = game->player[playerIndex]->cardList->head;
    Card returnedCard;

    int i = 0;
    //if the curr node is not NULL, then continue find this card
    while (curr != NULL) {
        if (i == card) {
            returnedCard = curr->card;
        }
        curr = curr->next;
        i++;
    }
    return returnedCard;
}


// Check if a given move is valid.
//
// If the last player played a 2 (DRAW_TWO),
// the next player must either play a 2
// or draw 2 cards.
// Otherwise, the player must play a card that is either a ZERO
// or that has the same color, value, or suit as the card on the top
// of the discard pile.
//
// If the player plays an ADVANCE, the next player's turn is skipped.
// If the player plays a BACKWARDS, the direction of play is reversed.
// If the player plays a CONTINUE, they may play another card.
// If the player plays a DECLARE, they must also state which color
// the next player's discarded card should be.
//
// A player can only play cards from their hand.
// A player may choose to draw a card instead of discarding a card.
// A player must draw a card if they are unable to discard a card.
//
// This check should verify that:
// * The card being played is in the player's hand
// * The player has played at least one card before finishing their turn,
//   unless a draw-two was played, in which case the player may not
//   play a card, and instead must draw the appropriate number of cards.
int isValidMove(Game game, playerMove move) {
    int isValid = FALSE;
    if (game->currentTurn == 1 && moveLength(game->turns->head) == 0) {
        if (move.action == PLAY_CARD) {
            isValid = TRUE;
        }
    }
    //CLAIM && CALLOUT
    if (move.action == SAY_TRIO) {
        // current player left 3 cards in his hand, he need to claim his card
        if (handCardCount(game) == 3) {
            isValid = TRUE;
            // the last player forget to claim his card
            // current player call out, force the last player draw one card
        }
    }

    if (move.action == SAY_DUO) {
        // current player left 2 cards in his hand, he need to claim his card
        if (handCardCount(game) == 2) {
            isValid = TRUE;

            // the last player forget to claim his card
            // current player call out, force the last player draw one card
        }
    }

    if (move.action == SAY_UNO) {
        // current player left 2 cards in his hand, he need to claim his card
        if (handCardCount(game) == 1) {
            isValid = TRUE;
            // the last player forget to claim his card
            // current player call out, force the last player draw one card
        }
    }

    //when the action is PLAY_CARD
    if (move.action == PLAY_CARD) {
        //play card action can not do after draw card
        if (canPlayCard(game)) {
            //the card which played match the color/value/suit as the
            //card in the top of discard pile
            if (matchCard (topDiscard(game), move.card)) {
                isValid = TRUE;
            //if the value last player played DECLARE
            } else if (cardValue(topDiscard(game)) == DECLARE) {
                int moveIndex = 0;
                int i = 0;
                int lastTurn = currentTurn(game) - 1;
                //find the index of move move which play DECLARE card
                while (i < turnMoves(game, lastTurn)) {
                    if (pastMove(game, lastTurn, moveIndex).action == PLAY_CARD) {
                        moveIndex = i;
                    }
                    i++;
                }

                playerMove declareColor = pastMove(game, lastTurn, moveIndex);
                //if the card color of this move is the same as the declared color
                //this move is valid move
                if (matchDeclareColor (declareColor, move)) {
                    isValid = TRUE;
                }
            }
        }
    }

    //when the action is DRAW_CARD
    if (move.action == DRAW_CARD) {
        if (canDrawCard (game)) {
            isValid = TRUE;
        }
    }
    return isValid;
}


// Play the given action for the current player
//
// If the player makes the END_TURN move, their turn ends,
// and it becomes the turn of the next player.
//
// This should _not_ be called by the player AI.
void playMove(Game game, playerMove move) {
    if(!gameIsOver(game)) {
        if (isValidMove(game, move)) {
            insertHeadOfMoveList(game->turns, move);

            if (move.action == PLAY_CARD) {

                // Direction
                if (cardValue(move.card) == BACKWARDS) {
                    changeDirection(game->currentDirection);
                    if (game->currentDirection == CLOCKWISE) {
                        game->nextPlayer = (game->currentPlayer + 1) % 4;
                    } else {
                        game->nextPlayer = (game->currentPlayer - 1) % 4;
                    }
                } else if (cardValue(move.card) == ADVANCE) {
                    if (game->currentDirection == CLOCKWISE) {
                        game->nextPlayer = (game->currentPlayer + 2) % 4;
                    } else {
                        game->nextPlayer = (game->currentPlayer - 2) % 4;
                    }
                }

                // Discard card (handCard + discard pile)
                listDeleteCard (game->player[game->currentPlayer]->cardList, move.card);
                insertHeadOfList (game->discardPile, move.card);
            }

            if (move.action == DRAW_CARD) {
                //drar from deckPile
                if (lengthOfCardList (game->deckPile) > 0) {
                    insertHeadOfList (game->player[game->currentPlayer]->cardList, game->deckPile->head->card);
                    deleteHeadOfList (game->deckPile);
                } else {
                    insertHeadOfList (game->player[game->currentPlayer]->cardList, game->discardPile->head->card);
                    deleteHeadOfList (game->discardPile);
                }
            }

            if (move.action == END_TURN) {
                game->currentTurn++;
                insertHeadOfTurnList(game->turns);
                game->currentPlayer = game->nextPlayer;
                if (game->currentDirection == CLOCKWISE) {
                    game->nextPlayer = (game->currentPlayer + 1) % 4;
                } else {
                    game->nextPlayer = (game->currentPlayer - 1) % 4;
                }
                //points?????
            }
        }
    }
}


// Check the game winner.
//
// Returns NOT_FINISHED if the game has not yet finished,
// 0-3, representing which player has won the game, or
// NO_WINNER if the game has ended but there was no winner.
int gameWinner(Game game) {
    int playerIndex = 0;
    int winner = NO_WINNER;
    while (playerIndex < NUM_PLAYERS) {
        if(playerPoints(game, playerIndex) == 0) {
            winner = playerIndex;
        }
        playerIndex++;
    }
    return winner;
}


Card topDiscard(Game game) {
    return game->discardPile->head->card;
}

/**************************************************************
Helper function
**************************************************************/
//create a new node
static Node newNode(Card card) {
    assert(card != NULL);
    Node new = calloc(1, sizeof(struct _node));
    new->card = card; // what guarantee do you have new is not null?
    // what is the logic that guarantees that card argument is what we want?
    return new;
}


//create a new List
static List newList (void) {
    List list = calloc (1, sizeof(struct _list));
    return list;
}


//if a player draw a card
//delete the head of the disPile/deckPile List
static void deleteHeadOfList (List l) {
    Node headNode = l->head;
    if (headNode == NULL) {
        l->head == NULL
    } else {
        Node newheadNode = headNode->next;
        free(headNode);
        l->head = newheadNode;
    }
}


//when player discard a card
//insert card to the head of the disPile/deckPile List
static void insertHeadOfList (List l, Card insert) {
    Node head = l->head;
    Node newHead = newNode(insert);
    if (l->head == NULL) {
        l->head = newHead;
        newHead->next = NULL;
    } else {
        newHead->next = l->head;
        l->head = newHead;
    }
}


//delete the nth term of a list
static void listDeleteNth (List l, int n) {
    Node curr = l->head;
    //if the list is empty
    if (curr == NULL) {
        l->head = NULL;
    }
    if (curr->next == NULL) {
        free(curr);
        l->head = NULL;
    } else {
        //delete the first element in the list
        //the same as delete the head
        if (n == 0) {
            Node newHead = curr->next;
            free(curr);
            l->head = newHead;
        } else {
            int i = 0;
            while (i < n -1) {
                curr = curr->next;
                i++;
            }
            Node newNext = curr->next->next;
            free(curr->next);
            curr->next = newNext;
        }
    }
}


static void listDeleteCard (List l, Card card) {
    Node curr = l->head;
    if (curr->card == card) {
        Node newHead = curr->next;
        free(curr);
        l->head = newHead;
    } else {
        while (curr->next != NULL) {
            if (curr->next->card == card) {
                Node newNext = curr->next->next;
                free(curr->next);
                curr->next = newNext;
                break;
            } else {
                curr = curr->next;
            }
        }
    }
}


//help to reverse the direction
static direction changeDirection (direction nowDirection) {
    if (nowDirection == CLOCKWISE) {
        nowDirection = ANTICLOCKWISE;
    } else if (nowDirection == ANTICLOCKWISE) {
        nowDirection = CLOCKWISE;
    }
    return nowDirection;
}


static int turnLength(TurnList turns) {
    TurnNode curr = turns->head;
    int length = 0;
    while (curr != NULL) {
        length++;
        curr = curr->next;
    }
    return length;
}


static int moveLength(TurnNode turn) {
    MoveNode curr = turn->moves->head;
    int length;
    while (curr != NULL) {
        length++;
        curr = curr->next;
    }
    return length;
}


//find if the color of card which is played match the color declared before
static int matchDeclareColor (playerMove lastMove, playerMove move) {
    int isMatch = FALSE;
    if (lastMove.nextColor == cardColor(move.card)) {
        isMatch = TRUE;
    }
    return isMatch;
}


static int matchCard (Card a, Card b) {
    int isMatch = FALSE;
    if (cardValue(a) == cardValue(b)){
        isMatch = TRUE;
    } else if (cardColor(a) == cardColor(b)) {
        isMatch = TRUE;
    } else if (cardSuit(a) == cardSuit(b)) {
        isMatch = TRUE;
    }
    return isMatch;
}


//in general, player can draw card as he/she want
//but, player cannot DRAW_CARD after PLAY_CARD or END_TURN
static int canDrawCard (Game game) {
    int moveIndex = 0;
    int currTurn = currentTurn (game);
    int canDraw = TRUE;
    while (moveIndex < turnMoves(game, currTurn)) {
        if (pastMove(game, currTurn, moveIndex).action == PLAY_CARD ||
            pastMove(game, currTurn, moveIndex).action == END_TURN) {
            canDraw = FALSE;
        }
        moveIndex++;
    }
    return canDraw;
}


//if a player alrealy have move involves action DRAW_CARD and END_TURN
//a player cannot have PLAY_CARD action twice unless CONTINUE is played ???
//then he can not have action PLAY_CARD anymore
static int canPlayCard (Game game) {
    int moveIndex = 0;
    int currTurn = currentTurn (game);
    int canPlay = TRUE;
    while (moveIndex < turnMoves(game, currTurn)) {
        if (pastMove(game, currTurn, moveIndex).action == DRAW_CARD ||
            pastMove(game, currTurn, moveIndex).action == END_TURN) {
            canPlay = FALSE;
            // can not play card twice in one turn unless continue is played
        } else if (pastMove(game, currTurn, moveIndex).action == PLAY_CARD &&
            cardValue(topDiscard(game)) != CONTINUE) {
            canPlay = FALSE;
        }
        moveIndex++;
    }
    return canPlay;
}


static int gameIsOver(Game game) {
    int i = 0;
    int isOver = FALSE;
    while (i < NUM_PLAYERS) {
        if(playerCardCount(game, i) == 0) {
            isOver = TRUE;
        }
        i++;
    }
    return isOver;
}


static MoveNode newMoveNode (playerMove move) {
    MoveNode new = calloc(1, sizeof(struct _moveNode));
    new->move = move;
    return new;
}


static void insertHeadOfMoveList (TurnList list, playerMove move) {
    MoveNode head = list->head->moves->head;
    MoveNode newHead = newMoveNode(move);
    if (head == NULL) {
        list->head->moves->head = newHead;
        newHead->next = NULL;
    } else {
        newHead->next = list->head->moves->head;
        list->head->moves->head = newHead;
    }
}


static void insertHeadOfTurnList(TurnList list) {
    TurnNode newHead = calloc(1, sizeof(struct _turnNode));
    MoveList newMoveList = calloc(1, sizeof(struct _moveList));
    newMoveList->head = NULL;
    newHead->next = list->head;
    newHead->moves = newMoveList;
    list->head = newHead;
}

static int lengthOfCardList (List l) {
    Node curr = l->head;
    int length;
    while (curr != NULL) {
        length++;
        curr = curr->next;
    }
    return length;
}
