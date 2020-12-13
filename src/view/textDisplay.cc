#include "textDisplay.h"
#include "../cards/card.h"
#include "../cards/ritual.h"
#include "../cards/spell.h"
#include "../cards/minion/minion.h"
#include "../cards/minion/enchantment.h"
#include "../game/player.h"
#include "../cards/minion/triggeredAbility.h"
#include "../cards/minion/activatedAbility.h"
#include "../cardCollections/board.h"
#include "../cardCollections/hand.h"


using namespace std;

void addSpace(string &s, int n)
{
    for (int i = 0; i < n; ++i)
        s += " ";
}

// -------------------- HELPER PRINT FUNCTIONS --------------------

// print template of any card
vector<string> TextDisplay::printCardTemplate(shared_ptr<Card> card) {
    vector<string> result;
    result.push_back(HORIZONTAL_LINE);              // |-------------------------------|
    result.push_back(NAME_LINE);                    // |                         |     |
    result.push_back(HORIZONTAL_LINE);              // |-------------------------------|
    result.push_back(EMPTY_LINE);                   // |                               |
    result.push_back(HORIZONTAL_LINE);              // |-------------------------------|
    for (int i = 0; i < CARD_HEIGHT - 6; ++i) {
        result.push_back(EMPTY_LINE);               // |                               |
    }
    result.push_back(HORIZONTAL_LINE);              // |-------------------------------|
    
    // Change the name and cost(2nd line)
    string name = card->getName();
    result[1].replace(WORD_START, name.size(), name);
    string cost = to_string(card->getCost());
    result[1].replace(CARD_WIDTH-WORD_START-cost.size(), cost.size(), cost);

    // Change type (4th line)
    string type = card->getType();
    result[3].replace(CARD_WIDTH-WORD_START-type.size(), type.size(), type);

    return result;
}


// add the description of a card
void TextDisplay::printDescription(vector<string> &card, string description, int line) {
    int counter = 0;
    // each line is NORMAL_LENGTH, counter*NORMAL_LENGTH is the amount of length we have already printed
    while (counter*NORMAL_LENGTH < description.size()) {
        card[line + counter].replace(WORD_START, NORMAL_LENGTH, description.substr(counter*NORMAL_LENGTH, NORMAL_LENGTH));
        ++counter;
    }
}


// add bottom left box
void TextDisplay::printLeftBox(vector<string> &card, string boxContent) {
    card[CARD_HEIGHT - 3].replace(WORD_START - 1, NUMBER_BORDER_LINE.size(), NUMBER_BORDER_LINE);   // |------
    card[CARD_HEIGHT - 2].replace(WORD_START, boxContent.size(), boxContent);                       // | 2
    card[CARD_HEIGHT - 2].replace(boxContent.size(), 1, "|");                                       // | 2   |
}
// add bottom right box
void TextDisplay::printRightBox(vector<string> &card, string boxContent) {
    card[CARD_HEIGHT - 3].replace(CARD_WIDTH - 1 - NUMBER_BORDER_LINE.size(), NUMBER_BORDER_LINE.size(), NUMBER_BORDER_LINE);   // ------|
    card[CARD_HEIGHT - 2].replace(CARD_WIDTH - WORD_START - boxContent.size(), boxContent.size(), boxContent);                  //   2   |
    card[CARD_HEIGHT - 2].replace(CARD_WIDTH - 1 - NUMBER_BORDER_LINE.size(), 1, "|");                                          // | 2   |                                                          // | 2   |
}


// add the top left box along with the description (formatting changes since there is box added before description)
void TextDisplay::printTopLeftBoxAndDescription(vector<string> &card, string boxContent, string description) {
    // box
    card[5].replace(WORD_START, boxContent.size(), boxContent);                                 // | 2
    card[5].replace(boxContent.size(), 1, "|");                                                 // | 2   |
    card[6].replace(WORD_START - 1, NUMBER_BORDER_LINE.size(), NUMBER_BORDER_LINE);             // |------

    // description
    int counter = 0;
    // each line is NORMAL_LENGTH, counter*NORMAL_LENGTH is the amount of length we have already printed
    while (counter*SHORTENED_LENGTH < description.size()) {
        card[5 + counter].replace(WORD_START+NUMBER_BORDER_LINE.size(), SHORTENED_LENGTH, description.substr(counter*SHORTENED_LENGTH, SHORTENED_LENGTH));
        ++counter;
    }
}







// -------------------- PRINT CARD FUNCTIONS --------------------

// print minion
vector<string> TextDisplay::printMinion(shared_ptr<Minion> minion) {
    vector<string> card = printCardTemplate(minion);

    // add attack and defence
    printLeftBox(card, to_string(minion->getAtk()));
    printRightBox(card, to_string(minion->getDef()));

    // add activated ability from minion
    if(minion->hasActAbility()) {
        printTopLeftBoxAndDescription(card, minion->getActAbility()->getDescription(), to_string(minion->getActAbility()->getCost()));
    }

    // add triggered ability from enchantment, after activated ability
    if(minion->hasActAbility() && minion->hasTrgAbility()) {
        // when CARD_HEIGHT = 16, 4 lines after activation cost
        printDescription(card, minion->getTrgAbility()->getDescription(), 5+(CARD_HEIGHT-8)/2);

    // add triggered ability from enchantment (no activated ability)
    } else if (minion->hasTrgAbility()) {
        printDescription(card, minion->getTrgAbility()->getDescription(),5);
    }
    return card;
}


// print enchantment when it is on board, attached to minions
vector<string> TextDisplay::printEnchantedMinion(shared_ptr<Enchantment> enchantment) {
    auto minion = enchantment->getAttachedMinion();
    vector<string> card = printCardTemplate(minion);

    // add attack and defence from enchantment
    printLeftBox(card, to_string(enchantment->getAtk()));
    printLeftBox(card, to_string(enchantment->getAtk()));

    // add activated ability from enchantment
    if(enchantment->hasActAbility()) {
        printTopLeftBoxAndDescription(card, enchantment->getActAbility()->getDescription(), to_string(enchantment->getActAbility()->getCost()));
    }

    // add triggered ability from enchantment, after activated ability
    if(enchantment->hasActAbility() && enchantment->hasTrgAbility()) {
        // when CARD_HEIGHT = 16, 4 lines after activation cost
        printDescription(card, enchantment->getTrgAbility()->getDescription(), 5+(CARD_HEIGHT-8)/2);
    
    // add triggered ability from enchantment (no activated ability)
    } else if (enchantment->hasTrgAbility()) {
        printDescription(card, enchantment->getTrgAbility()->getDescription(),5);
    }
    return card;
}


// print enchantment when it is in hand
vector<string> TextDisplay::printEnchantment(shared_ptr<Enchantment> enchantment) {
    vector<string> card = printCardTemplate(enchantment);

    // add atk/def changes, if any
    if(enchantment->getAtkChange()!=""){
        printLeftBox(card, enchantment->getAtkChange());
    }
    if(enchantment->getDefChange()!=""){
        printRightBox(card, enchantment->getDefChange());
    }

    // add descriptions
    printDescription(card, enchantment->getDescription(), 5);
    return card;
}


// print spell
vector<string> TextDisplay::printSpell(shared_ptr<Spell> spell) {
    vector<string> card = printCardTemplate(spell);
    // print its description
    printDescription(card, spell->getDescription(), 5);
    return card;
}


// print ritual
vector<string> TextDisplay::printRitual(shared_ptr<Ritual> ritual) {
    vector<string> card = printCardTemplate(ritual);
    // add its activation cost and description
    printTopLeftBoxAndDescription(card, ritual->getTrgAbility()->getDescription(), to_string(ritual->getActivationCost()));
    // add its number of charges
    printRightBox(card, to_string(ritual->getCharges()));
    return card;
}





// -------------------- PRINT HELP --------------------

void TextDisplay::printHelp()
{
    cout << "Commands:" << endl;
    cout << "help -- Display this message." << endl;
    cout << "end  -- End the current player’s turn." << endl;
    cout << "quit -- End the game." << endl;
    cout << "attack minion other-minion -- Orders minion to attack other-minion." << endl;
    cout << "attack minion -- Orders minion to attack the opponent." << endl;
    cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
    cout << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << endl;
    cout << "inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
    cout << "hand -- Describe all cards in your hand." << endl;
    cout << "board -- Describe all cards on the board." << endl;
}





// -------------------- PRINT INSPECT --------------------

void TextDisplay::printInspect(shared_ptr<Player> activePlayer, int minion) {
    auto card = activePlayer->getBoard()->getMinion(minion);
    string type = card->getType();

    // print the minion, if it is of type minion
    if (type == "Minion"){
        vector<string> minionStr = printMinion(card);
        for (int i = 0; i < minionStr.size(); minionStr) {
            cout << minionStr[i];
        }
        cout << endl;
    }
    // if type enchantment, first get the minion under enchantment the n print enchantments
    if (type == "Enchantment"){

        // enchantment at the top
        auto topEnchantment = dynamic_pointer_cast<Enchantment>(card);
        // print minion under enchantment
        auto bottomMinion = topEnchantment->getAttachedMinion();
        vector<string> minionStr = printMinion(bottomMinion);
        for (int i = 0; i < minionStr.size(); minionStr) {
            cout << minionStr[i];
        }
        cout << endl;

        // print all enchantments
        auto enchantments = topEnchantment->getEnchantmentList();
        vector<vector<string>> enchantmentStr;
        for(int i = 0; i < enchantments.size(); ++i) {
            
        }

        
    }
}




// -------------------- PRINT HAND --------------------

void TextDisplay::printHand(shared_ptr<Player> activePlayer) {
    auto cards = activePlayer->getHand()->getCards();
    vector<vector<string>> hand;

    // add each card print string to the hand
    for (int i = 0; i < cards.size(); ++i) {
        string type = cards[i]->getType();
        if(type=="spell") {
            hand[i] = printSpell(dynamic_pointer_cast<Spell>(cards[i]));
        } else if (type=="ritual") {
            hand[i] = printRitual(dynamic_pointer_cast<Ritual>(cards[i]));
        } else if (type=="minion") {
            hand[i] = printMinion(dynamic_pointer_cast<Minion>(cards[i]));
        } else if (type=="enchantment") {
            hand[i] = printEnchantment(dynamic_pointer_cast<Enchantment>(cards[i]));
        } else {
            // error
        }
    }

    // now print line by line
    for (int i = 0; i < CARD_HEIGHT; ++i) {
        for (auto card : hand) {
            cout << card[i];
        }
        cout << endl;
    }
}





// -------------------- PRINT BOARD --------------------

void TextDisplay::printBoard(shared_ptr<Player> activePlayer)
{
    for (int i = 0; i < 56; i++)
    {
        for (int j = 0; j < 167; j++)
        {
            // print borders
            if (i == 0 || i == 55)
            {
                if (j != 167)
                {
                    cout << "-";
                }
                else
                {
                    cout << "-" << endl;
                }
            }
            else if (j == 0)
            {
                cout << "|";
            }
            else if (j == 166)
            {
                cout << "|" << endl;
            }
            else if (i == 23 || i == 32)
            {
                cout << "-";
                // print "_"
            }
            else if ((i == 24 && j > 65 && j < 71) || (i == 25 && j > 66 && j < 72) ||
                     (i == 26 && (j == 67 || j == 68 || j == 69 || j == 73 || j == 74 || j == 75 || j == 78 || j == 80 || j == 81 || j == 83 || j == 84 || j == 85 || j == 87 || j == 88 || j == 89 || j == 91 || j == 93 || j == 94 || j == 96 || j == 100)) ||
                     (i == 27 && (j == 66 || j == 67 || j == 68 || j == 74 || j == 80 || j == 81 || j == 84 || j == 85 || j == 88 || j == 93 || j == 94)) ||
                     (i == 28 && (j == 65 || j == 66 || j == 67 || j == 68 || j == 74 || j == 84 || j == 88 || j == 89 || j == 98)) ||
                     (i == 29 && (j == 65 || j == 66 || j == 67 || j == 68 || j == 69 || j == 73 || j == 74 || j == 75 || j == 78 || j == 83 || j == 84 || j == 85 || j == 87 || j == 88 || j == 89 || j == 91 || j == 97 || j == 98)) ||
                     (i == 30 && (j == 97 || j == 98)) || (i == 31 && j > 96 && j < 100))
            {
                cout << "_";
                // print "|"
            }
            else if ((i == 25 && j == 71) || (i == 26 && j == 64) || (i == 27 && (j == 77 || j == 95 || j == 97 || j == 99 || j == 101)) ||
                     (i == 28 && (j == 71 || j == 77 || j == 79 || j == 81 || j == 85 || j == 92 || j == 95 || j == 97 || j == 99 || j == 101)) ||
                     (i == 29 && (j == 64 || j == 77 || j == 79 || j == 90 || j == 92 || j == 101)) || (i == 30 && j == 101) || (i == 31 && j == 96))
            {
                cout << "|";
                // print "/"
            }
            else if ((i == 25 && j == 65) || (i == 27 && (j == 72 || j == 82 || j == 86)) || (i == 28 || j == 90) || (i == 29 && (j == 70) || (j == 76)) || (i == 30 && j == 99) || (i == 31 && j == 100))
            {
                cout << "/";
                // print "\"
            }
            else if ((i == 27 && (j == 65 || j == 70 || j == 76 || j == 90)) || (i == 29 && (j == 72 || j == 82 || j == 86 || j == 99)))
            {
                cout << "\\";
                // print "("
            }
            else if ((i == 26 && j == 66) || (i == 28 && (j == 73 || j == 83)))
            {
                cout << "(";
                // print ")"
            }
            else if (i == 28 && j == 75)
            {
                cout << ")";
                // print "'"
            }
            else if (i == 27 && (j == 79 || j == 92))
            {
                cout << "'";
                // print ","
            }
            else if (i == 29 && j == 99)
            {
                cout << ",";
                // print space
            }
            else
            {
                cout << " ";
            }
        }
    }
}