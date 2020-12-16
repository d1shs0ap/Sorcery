#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <string>
#include <vector>
#include <stdexcept>

class Board;
class Deck;
class Graveyard;
class Hand;
class Game;
class Ritual;
class Minion;

class Player
{
    std::string name;
    int life;
    int magic;
    int number;

    // A player’s board is a collection of cards that they have played and which have not been moved to another zone.
    std::shared_ptr<Board> board;
    // A players’ deck is a collection of cards that they may draw from.
    std::shared_ptr<Deck> deck;
    // A player’s graveyard is a collection of minions that have died.
    std::shared_ptr<Graveyard> graveyard;
    // A players’ hand is a collection of cards (to a maximum of 5) that they may play.
    std::shared_ptr<Hand> hand;

public:
    Player(std::string name, int number, std::shared_ptr<Board> board, std::shared_ptr<Deck> deck, std::shared_ptr<Graveyard> graveyard, std::shared_ptr<Hand> hand);

    std::string getName() const;

    int getLife() const;
    void setLife(int life);

    int getMagic() const;
    void setMagic(int magic);
    bool hasEnoughMagic(int cost);

    int getNumber() const;

    std::shared_ptr<Board> getBoard();
    std::shared_ptr<Deck> getDeck();
    std::shared_ptr<Graveyard> getGraveyard();
    std::shared_ptr<Hand> getHand();

    // To draw, a player takes a card from their deck and puts it into their hand. A player may only draw if their
    // hand is not full and their deck is not empty.
    void draw();

    // discard
    void discard(int card);

    // Plays the ith card in hand from the left
    void play(int card, std::shared_ptr<Game> game, bool testing);
    void play(int card, int player, int target, std::shared_ptr<Game> game, bool testing);
    void play(int card, int player, std::shared_ptr<Game> game, bool testing); // for ritual target

    void use(std::shared_ptr<Game> game, int minion, bool testing);
    void use(std::shared_ptr<Game> game, int minion, int player, int target, bool testing);
    void use(std::shared_ptr<Game> game, int minion, int player, bool testing); // for ritual target
};

#endif
