#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <vector>
#include <iostream>
#include <memory>


class Game;
class Player;
class Card;
class Enchantment;
class Minion;
class Ritual;
class Spell;

class TextDisplay { 
    enum PRINT_LOCATION{INSPECT, HAND, BOARD};

    const std::string HORIZONTAL_LINE        {"|-------------------------------|"};
    const std::string NUMBER_BORDER_LINE     {"------"};
    const std::string NAME_LINE              {"|                         |     |"};
    const std::string EMPTY_LINE             {"|                               |"};

    const int WORD_START = 2; // words start at index 2
    const int CARD_WIDTH = 33; // card width is 33
    const int CARD_HEIGHT = 16; // changing card height to 16 so a minion can display both of its activated and triggered abilities
    const int NORMAL_LENGTH = CARD_WIDTH - 2*WORD_START;
    const int SHORTENED_LENGTH = NORMAL_LENGTH - NUMBER_BORDER_LINE.size();
    const int BOARD_WIDTH = 5;

    std::shared_ptr<Game> game;

    // convert a card to appropriate strings.
    void addSpace(std::string &s, int n);

    // print a card template
    std::vector<std::string> printCardTemplate(std::shared_ptr<Card> card);
    // add the description of a card
    void printDescription(std::vector<std::string> &card, std::string description, int line);
    // add bottom left box
    void printLeftBox(std::vector<std::string> &card, std::string boxContent);
    // add bottom right box
    void printRightBox(std::vector<std::string> &card, std::string boxContent);
    // add the top left box along with the description (formatting changes since there is box added before description)
    void printTopLeftBoxAndDescription(std::vector<std::string> &card, std::string boxContent, std::string description);

    // print enchantment when it is on board, attached to minions
    std::vector<std::string> printEnchantedMinion(std::shared_ptr<Enchantment> enchantment);
    // print enchantment when it is in hand
    std::vector<std::string> printEnchantment(std::shared_ptr<Enchantment> enchantment);
    // print minion
    std::vector<std::string> printMinion(std::shared_ptr<Minion> minion);
    // print spell
    std::vector<std::string> printSpell(std::shared_ptr<Spell> spell);
    // print ritual
    std::vector<std::string> printRitual(std::shared_ptr<Ritual> ritual);

    // prints row of vectors (continues row if vector has length > 5)
    void printRow(std::vector<std::shared_ptr<Card>> cards, int printLocation);

    public:
        // virtual void update(Subject & game) override;
        // displays all help commands
        void printHelp();
        // displays minion as well as all of the enchantments on it of the active player, called by inspect
        void printInspect(std::shared_ptr<Player> activePlayer, int minion);
        // display active player's hand, called by hand
        void printHand(std::shared_ptr<Player> activePlayer);
        // displays board, where the active player's content is displayed on the bottom, called by board
        void printBoard(std::shared_ptr<Player> activePlayer);
};

#endif
