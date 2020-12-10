#ifndef TEXT_CONTROLLER_H
#define TEXT_CONTROLLER_H

#include <memory>
#include <vector>

#include "../game/game.h"
#include "../view/textDisplay.h"

// Receives TEXT input and translate them into model actions
class TextController {
    std::shared_ptr<Game> game;
    std::shared_ptr<TextDisplay> textDisplay;

    public:
        // Ends current player's turn
        void end();

        // Draws card, only allowed in -testing
        void draw();
        // Discards ith cardInHand, only allowed in -testing
        void discard(int cardInHand);
        
        // Attacks enemy hero/minion
        void attack(int minion);
        void attack(int minion, int enemyMinion);
        // Plays cardInHand (on player 1/2's card, which can be a minion or ritual)
        void play(int cardInHand) {
            
            // try {

            // } catch () { // check if cardInHand is in range
                
            // }
        }
        void play(int cardInHand, int targetPlayer, int targetMinion);
        void play(int cardInHand, int targetPlayer, char targetRitual);
        // Uses minion's ability (on player 1/2's card, which can be a minion or ritual)
        void use(int minion);
        void use(int minion, int targetPlayer, int targetMinion);
        void use(int minion, int targetPlayer, char targetRitual);
        
        // Displays list of commands and their formats
        void help();
        // Displays minion owned by active player
        void inspect(int minion);
        // Displays hand
        void hand();
        // Displays board
        void board();
};

#endif
