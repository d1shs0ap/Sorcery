#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <string>
#include <vector>

#include "board.h"
class Card;
class Minion;
#include "tas.h"

class Player
{
private:
    std::string name;
    int life;
    int magic;
    std::vector<std::shared_ptr<Card>> hand;
    Board board;
    std::vector<std::shared_ptr<Minion>> graveyard;
    std::vector<std::shared_ptr<Card>> deck;
    EndTas endTurnTa;
    StartTas startTurnTa;
    EnterTas enterTa;

public:
    void draw(std::vector<std::shared_ptr<Card>>);
    void place(int);
    void shuffle(Player p);
    void minionsResort();
};

#endif
