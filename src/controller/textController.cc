#include "textController.h"
#include "../game/game.h"
#include "../game/player.h"
#include "../cardCollections/board.h"
#include "../cards/minion/triggeredAbility.h"
#include "../cards/minion/minion.h"
#include "../view/textDisplay.h"
#include "../cardCollections/hand.h"



using namespace std;

// REMEMBER TO ADD EXCEPTIONS (TRY/CATCH) LATER!!!

// Subtract 1 from all card, minion, player values to match array indexing (which starts at 0)

TextController::TextController(shared_ptr<Game> game, shared_ptr<TextDisplay> textDisplay)
    : game{game}, textDisplay{textDisplay} {}

// Ends current player's turn
void TextController::end() {
    game->endTurn();
    game->startTurn();
}


// -------------------- Hand interactions -------------------

// Draws card, only allowed in -testing
void TextController::draw() {
    auto player = game->getActivePlayer();
    player->draw();
}
// Discards ith cardInHand, only allowed in -testing
void TextController::discard(int cardInHand) {
    auto player = game->getActivePlayer();
    player->discard(cardInHand - 1);
}


// --- Player actions ---

// Attacks enemy hero/minion
void TextController::attack(int minion) {
    auto player = game->getActivePlayer();
    auto board = player->getBoard();
    auto concreteMinion = board->getMinion(minion - 1);
    concreteMinion->attack(game->getInactivePlayer());
}
void TextController::attack(int minion, int enemyMinion) {
    auto player = game->getActivePlayer();
    auto board = player->getBoard();
    auto concreteMinion = board->getMinion(minion - 1);

    auto enemyPlayer = game->getInactivePlayer();
    auto enemyBoard = enemyPlayer->getBoard();
    auto concreteEnemyMinion = enemyBoard->getMinion(enemyMinion - 1);

    concreteMinion->attack(concreteEnemyMinion);
}
// Plays cardInHand (on player 1/2's card, which can be a minion or ritual)
void TextController::play(int cardInHand) {
    auto player = game->getActivePlayer();
    auto card = player->getHand()->getCard(cardInHand - 1);

    player->play(cardInHand - 1, game);

    if (card->getType()=="Minion") {
        game->checkTriggered(MINION_ENTER);
    }
}
void TextController::play(int cardInHand, int targetPlayer, int targetMinion) {
    auto player = game->getActivePlayer();
    auto card = player->getHand()->getCard(cardInHand - 1);

    player->play(cardInHand - 1, targetPlayer - 1, targetMinion - 1);

    if (card->getType()=="Minion") {
        game->checkTriggered(MINION_ENTER);
    }
}
void TextController::play(int cardInHand, int targetPlayer, char targetRitual) {
    auto player = game->getActivePlayer();
    auto card = player->getHand()->getCard(cardInHand - 1);

    player->play(cardInHand - 1, targetPlayer - 1, targetRitual);

    if (card->getType()=="Minion") {
        game->checkTriggered(MINION_ENTER);
    }
}

// Uses minion's ability (on player 1/2's card, which can be a minion or ritual)
void TextController::use(int minion) {
    auto player = game->getActivePlayer();
    player->use(game->shared_from_this(), minion - 1);
}
void TextController::use(int minion, int targetPlayer, int targetMinion) {
    auto player = game->getActivePlayer();
    player->use(game->shared_from_this(), minion - 1, targetPlayer - 1, targetMinion - 1);
}
void TextController::use(int minion, int targetPlayer, char targetRitual) {
    auto player = game->getActivePlayer();
    player->use(game->shared_from_this(), minion - 1, targetPlayer - 1, targetRitual);
}


// ------------------- Display methods --------------------

// Displays list of commands and their formats
void TextController::help() {
    textDisplay->printHelp();
}
// Displays minion owned by active player
void TextController::inspect(int minion) {
    textDisplay->printInspect(minion - 1);
}
// Displays hand
void TextController::hand() {
    textDisplay->printHand();
}
// Displays board
void TextController::board() {
    textDisplay->printBoard();
}
