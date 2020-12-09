#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <vector>

#include "board.h"
#include "../cardCollections/board.h"
#include "../cardCollections/deck.h"
#include "../cardCollections/graveyard.h"
#include "../cardCollections/hand.h"

const int HAND_CAP = 5;
const int BOARD_CAP = 5;

class Player
{
    std::string name;
    int life;
    int magic;

    // A player’s board is a collection of cards that they have played and which have not been moved to another zone.
    Board board;
    // A players’ deck is a collection of cards that they may draw from.
    Deck deck;
    // A player’s graveyard is a collection of minions that have died.
    Graveyard graveyard;
    // A players’ hand is a collection of cards (to a maximum of 5) that they may play.
    Hand hand;

public:
    Player();
    int getLife() const;
    void setLife(int new_life);

    // To draw, a player takes a card from their deck and puts it into their hand. A player may only draw if their
    // hand is not full and their deck is not empty.
    void draw();
    // Plays the ith card in hand from the left
    void play(int i);
    // Calls all restoreActions() on player's minions
    void restoreActionAll();
};

#endif
