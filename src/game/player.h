#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

#include "../cardCollections/board.h"
#include "../cardCollections/deck.h"
#include "../cardCollections/graveyard.h"
#include "../cardCollections/hand.h"
#include "../cards/spell.h"
#include "../cards/ritual.h"
#include "../cards/minion/minion.h"
#include "../cards/minion/enchantment.h"

const int HAND_CAP = 5;
const int BOARD_CAP = 5;

class Player
{
    std::string name;
    int life;
    int magic;
    int number;

    // A player’s board is a collection of cards that they have played and which have not been moved to another zone.
    std::unique_ptr<Board> board;
    // A players’ deck is a collection of cards that they may draw from.
    std::unique_ptr<Deck> deck;
    // A player’s graveyard is a collection of minions that have died.
    std::unique_ptr<Graveyard> graveyard;
    // A players’ hand is a collection of cards (to a maximum of 5) that they may play.
    std::unique_ptr<Hand> hand;

public:
    Player();

    std::string getName() const;

    int getLife() const;
    void setLife(int life);

    int getMagic() const;
    void setMagic(int magic);

    int getNumber() const;

    Board *getBoard();

    // To draw, a player takes a card from their deck and puts it into their hand. A player may only draw if their
    // hand is not full and their deck is not empty.
    void draw();

    // Plays the ith card in hand from the left
    void play(int card);
    void play(int card, int player, int target);

    void use(int minion);
    void use(int minion, int player, int target);
};

#endif
