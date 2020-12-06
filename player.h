#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <string>
#include <vector>

#include "board.h"
class Card;
class Minion;
#include "tas.h"

const int cap = 5;

class Player
{
private:
    std::string name;
    int life;
    // A player’s magic is their main resource used to play cards and use
    // special abilities.
    unsigned int magic;
    // A players’ hand is a collection of cards (to a maximum of 5) that they
    // may play.
    std::vector<std::shared_ptr<Card>> hand;
    // A player’s board is a collection of cards that they have played and
    // which have not been moved to another zone.
    Board board;
    // A player’s graveyard is a collection of minions that have died.
    std::vector<std::shared_ptr<Minion>> graveyard;
    // A players’ deck is a collection of cards that they may draw from.
    std::vector<std::shared_ptr<Card>> deck;

    EndTas endTurnTa;
    StartTas startTurnTa;
    EnterTas enterTa;

public:
    // constructor.
    Player();
    // To draw, a player takes a card from their deck and puts it into their
    // hand. A player may only draw if their hand is not full.
    void draw(std::vector<std::shared_ptr<Card>>);
    void place(int);
    void shuffle(Player p);
    void minionsResort();
};

#endif
