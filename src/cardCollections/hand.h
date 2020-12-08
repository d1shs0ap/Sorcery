#ifndef HAND_H
#define HAND_H

#include <memory>
#include <vector>

#include "../cards/card.h"

class Hand {
    std::vector<std::shared_ptr<Card>> cards;
    public:
        bool isFull();
};

#endif
