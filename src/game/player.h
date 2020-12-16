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
    // Constructor
    Player(std::string name, int number, std::shared_ptr<Board> board, std::shared_ptr<Deck> deck, std::shared_ptr<Graveyard> graveyard, std::shared_ptr<Hand> hand);
    // Getter of name
    std::string getName() const;
    // Getter and Setter of life
    int getLife() const;
    void setLife(int life);
    // Getter and Setter of magic
    int getMagic() const;
    void setMagic(int magic);
    // Check if magic >= cost, called by Player::play, use
    bool hasEnoughMagic(int cost);
    // Getter of number
    int getNumber() const;
    // Getters
    std::shared_ptr<Board> getBoard();
    std::shared_ptr<Deck> getDeck();
    std::shared_ptr<Graveyard> getGraveyard();
    std::shared_ptr<Hand> getHand();

    // To draw, a player takes a card from their deck and puts it into their hand. A player may only draw if their
    // hand is not full and their deck is not empty.
    void draw();

    // discard
    void discard(int card);

    // Plays the ith card in hand from the left, called by textController::play
    void play(int card, std::shared_ptr<Game> game, bool testing); // for Minion, Ritual, Spell with no target
    void play(int card, int player, int target, std::shared_ptr<Game> game, bool testing); // for Enchantment, Spell with minion target
    void play(int card, int player, std::shared_ptr<Game> game, bool testing); // for Spell with ritual target
    
    // Use the activated abilityy of the ith minion in board from the left , called by textController::play
    void use(std::shared_ptr<Game> game, int minion, bool testing); // for activated ability with no target
    void use(std::shared_ptr<Game> game, int minion, int player, int target, bool testing); // for activated ability with target
};

#endif
