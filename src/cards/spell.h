#ifndef SPELL_H
#define SPELL_H

#include "card.h"

// Spell card
class Spell : public Card {
    public:
        void effect();
        void effectWithTarget(int player, int target);
        void effectWithTarget(int player, char ritual);
};

#endif
