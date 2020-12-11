#include "textController.h"

using namespace std;

TextController::TextController(shared_ptr<Game> game, shared_ptr<TextDisplay> textDisplay)
    : game{game}, textDisplay{textDisplay} {}

// Ends current player's turn
void TextController::end() {
    game->endTurn();
    game->startTurn();
}


// --- Hand interactions ---

// Draws card, only allowed in -testing
void TextController::draw() {
    auto player = game->getPlayer(game->getActivePlayerNumber());
    player->draw();
}
// Discards ith cardInHand, only allowed in -testing
void TextController::discard(int cardInHand) {
    auto player = game->getPlayer(game->getActivePlayerNumber());
    player->discard(cardInHand);
}


// --- Player actions ---

// Attacks enemy hero/minion
void attack(int minion);
void attack(int minion, int enemyMinion);
// Plays cardInHand (on player 1/2's card, which can be a minion or ritual)
void TextController::play(int cardInHand) {
    auto player = game->getPlayer(game->getActivePlayerNumber());
    player->play(cardInHand);
}
void TextController::play(int cardInHand, int targetPlayer, int targetMinion) {
    auto player = game->getPlayer(game->getActivePlayerNumber());
    player->play(cardInHand, targetPlayer, targetMinion);
}
void TextController::play(int cardInHand, int targetPlayer, char targetRitual) {
    auto player = game->getPlayer(game->getActivePlayerNumber());
    player->play(cardInHand, targetPlayer, targetRitual);
}
// Uses minion's ability (on player 1/2's card, which can be a minion or ritual)
void TextController::use(int minion) {
    auto player = game->getPlayer(game->getActivePlayerNumber());
    player->use(minion);
}
void TextController::use(int minion, int targetPlayer, int targetMinion) {
    auto player = game->getPlayer(game->getActivePlayerNumber());
    player->use(minion, targetPlayer, targetMinion);
}
void TextController::use(int minion, int targetPlayer, char targetRitual) {
    auto player = game->getPlayer(game->getActivePlayerNumber());
    player->use(minion, targetPlayer, targetRitual);
}


// --- Display methods ---

// Displays list of commands and their formats
void TextController::help() {
    textDisplay->printHelp();
}
// Displays minion owned by active player
void TextController::inspect(int minion) {
    textDisplay->printMinion(game->getPlayer(game->getActivePlayerNumber()), minion);
}
// Displays hand
void TextController::hand() {
    textDisplay->printHand(game->getPlayer(game->getActivePlayerNumber()));
}
// Displays board
void TextController::board() {
    textDisplay->printBoard(game->getPlayer(game->getActivePlayerNumber()));
}