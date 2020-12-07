#ifndef BOARD_H
#define BOARD_H
#include <memory>
#include <vector>

class Card;
class Ritual;

class Board
{
private:
    std::vector<std::shared_ptr<Ritual>> ritual;
    std::shared_ptr<Card> minions; // note: should it be a vector?
};

#endif
