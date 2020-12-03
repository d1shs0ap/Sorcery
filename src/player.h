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