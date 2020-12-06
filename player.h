#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <string>
#include <vector>

#include "board.h"
class Card;
class Minion;

class Player
{
private:
    std::string name;
    int life;
    int magic;
    std::vector<std::shared_ptr<Card>> hand;
    Board board;
    std::vector<std::shared_ptr<Minion>> graveyard;
};

#endif
