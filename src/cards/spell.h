#ifndef SPELL_H
#define SPELL_H

#include "card.h"

// Spell card
class Spell : public Card {
    public:
        void effect();
};

#endif
