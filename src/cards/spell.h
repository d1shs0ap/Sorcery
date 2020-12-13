#ifndef SPELL_H
#define SPELL_H

#include <memory>
class Game;
#include "card.h"

// Spell card
class Spell : public Card {
    std::string description;

    public:
        
        void effect(std::shared_ptr<Game> game);
        void effectWithTarget(int player, int target);
        void effectWithTarget(int player, char ritual);
        std::string getDescription();

        virtual ~Spell();
};

#endif
