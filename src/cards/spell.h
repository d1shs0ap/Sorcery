#ifndef SPELL_H
#define SPELL_H

#include "card.h"

// Spell card
class Spell : public Card {
    public:
        void effect(Game game);
        void effectWithTarget(int player, int target, Game game);
        void effectWithTarget(int player, char ritual, Game game);
};

#endif
