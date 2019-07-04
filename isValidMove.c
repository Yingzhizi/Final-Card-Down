int isValidMove(Game game, playerMove move) {
    //if move is valid if player played a ADVANCE value
    if(game->currentTurn == 0) {
        if(move.action = PLAY_CARD || move.action = END_TURN) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    if (game->currentTurn - 1 >= 0) {
        playerMove lastMove = pastMoveRec(game, currentTurn - 1, moveInTurn(game->currentTurn) - 1);
    }

}
