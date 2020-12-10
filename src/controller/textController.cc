#include "textController.h"

// Ends current player's turn
void TextController::end() {

}

// Draws card, only allowed in -testing
void draw();
// Discards ith cardInHand, only allowed in -testing
void discard(int cardInHand);

// Attacks enemy hero/minion
void attack(int minion);
void attack(int minion, int enemyMinion);
// Plays cardInHand (on player 1/2's card, which can be a minion or ritual)
void play(int cardInHand);
void play(int cardInHand, int targetPlayer, int targetMinion);
void play(int cardInHand, int targetPlayer, char targetRitual);
// Uses minion's ability (on player 1/2's card, which can be a minion or ritual)
void use(int minion);
void use(int minion, int targetPlayer, int targetMinion);
void use(int minion, int targetPlayer, char targetRitual);

// Displays list of commands and their formats
void TextController::help() {
    textDisplay->printHelp();
}
// Displays minion owned by active player
void inspect(int minion);
// Displays hand
void hand();
// Displays board
void board();