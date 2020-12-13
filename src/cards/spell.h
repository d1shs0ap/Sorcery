#ifndef SPELL_H
#define SPELL_H

#include <memory>
class Game;
#include "card.h"

// Spell card
class Spell : public Card {
    public:
        
        void effect(std::shared_ptr<Game> game);
        void effectWithTarget(int player, int target);
        void effectWithTarget(int player, char ritual);

        virtual ~Spell();
};

#endif
