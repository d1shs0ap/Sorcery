<<<<<<< HEAD
#ifndef GAME_H
#define GAME_H

#include <string>
#include <memory>
#include "game.h"

class Player {
  string name;
  int life;
  int magic;
  vector<shared_ptr<Card>> hand;
  Board board;
  vector<shared_ptr<Minion>> graveyard;
  vec<shared_ptr<Card>> deck;
  public:
    
};
=======
#ifndef PLAYER_H
#define PLAYER_H
#include <memory>
#include <string>
#include <vector>

#include "board.h"
class Card;
class Minion;
#include "tas.h"

const int handCap = 5;
const int boardCap = 5;

class Player
{
private:
    std::string name;
    int life;
    // A player’s magic is their main resource used to play cards and use
    // special abilities.
    int magic;
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
    // hand. A player may only draw if their hand is not full and their deck is
    // not empty.
    void draw(std::vector<std::shared_ptr<Card>>);
    void play(int i);
    void shuffle(Player p);
    void minionsResort();
};

#endif
>>>>>>> 0a85745329a33a869cd736d010639e1f8a9d1e13
