#ifndef SPELL_H
#define SPELL_H

#include "card.h"
#include "../game/game.h"
#include "../game/player.h"

class Game;

// Spell card
class Spell : public Card {
    public:
        
        void effect(std::shared_ptr<Game> game);
        void effectWithTarget(int player, int target);
        void effectWithTarget(int player, char ritual);
};

#endif
