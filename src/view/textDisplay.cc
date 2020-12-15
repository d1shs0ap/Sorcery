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
#include "../cardCollections/graveyard.h"
#include "../game/game.h"


using namespace std;

TextDisplay::TextDisplay(shared_ptr<Game> game)
    : game{game} {}

void TextDisplay::addSpace(string &s, int n)
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
    int length = description.size();
    while (counter*NORMAL_LENGTH < length) {
        if ((counter+1)*NORMAL_LENGTH > length) {
            addSpace(description, (counter+1)*NORMAL_LENGTH - description.size());
            card[line + counter].replace(WORD_START, NORMAL_LENGTH, description.substr(counter*NORMAL_LENGTH, NORMAL_LENGTH));
        } else {
            card[line + counter].replace(WORD_START, NORMAL_LENGTH, description.substr(counter*NORMAL_LENGTH, NORMAL_LENGTH));
        }
        ++counter;
    }
}


// add bottom left box
void TextDisplay::printLeftBox(vector<string> &card, string boxContent) {
    card[CARD_HEIGHT - 3].replace(WORD_START - 1, NUMBER_BORDER_LINE.size(), NUMBER_BORDER_LINE);   // |------
    card[CARD_HEIGHT - 2].replace(WORD_START, boxContent.size(), boxContent);                       // | 2
    card[CARD_HEIGHT - 2].replace(NUMBER_BORDER_LINE.size(), 1, "|");                                       // | 2   |
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
    int length = description.size();
    while (counter*SHORTENED_LENGTH < length) {
        if ((counter+1)*SHORTENED_LENGTH > length) {
            addSpace(description, (counter+1)*SHORTENED_LENGTH - description.size());
            card[5 + counter].replace(WORD_START+NUMBER_BORDER_LINE.size(), SHORTENED_LENGTH, description.substr(counter*SHORTENED_LENGTH, SHORTENED_LENGTH));
        } else {
            card[5 + counter].replace(WORD_START+NUMBER_BORDER_LINE.size(), SHORTENED_LENGTH, description.substr(counter*SHORTENED_LENGTH, SHORTENED_LENGTH));
        }
        ++counter;
    }
}








// -------------------- PRINT EMPTY CARDS --------------------

// empty space
vector<string> TextDisplay::emptySpace() {
    vector<string> emptySpace;
    for (int i = 0; i < CARD_HEIGHT; ++i) {
        emptySpace.push_back(EMPTY_SPACE);
    }
    return emptySpace;
}
// empty card
vector<string> TextDisplay::emptyCard() {
    vector<string> emptyCard;
    emptyCard.push_back(HORIZONTAL_LINE);

    for (int i = 0; i < CARD_HEIGHT - 2; ++i) {
        emptyCard.push_back(EMPTY_LINE);
    }

    emptyCard.push_back(HORIZONTAL_LINE);

    return emptyCard;
}








// -------------------- PRINT CARD FUNCTIONS --------------------

// print minion
vector<string> TextDisplay::printMinion(shared_ptr<Minion> minion) {
    vector<string> card = printCardTemplate(minion);

    // add attack and defence
    printLeftBox(card, to_string(minion->computeDef()));
    printRightBox(card, to_string(minion->computeDef()));

    // add activated ability from minion
    if(minion->hasActAbility()) {
        printTopLeftBoxAndDescription(card, minion->computeActAbility()->getDescription(), to_string(minion->computeActAbility()->getCost()));
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
    printLeftBox(card, to_string(enchantment->computeDef()));
    printLeftBox(card, to_string(enchantment->computeAtk()));

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

// print a single card
void TextDisplay::printCard(vector<string> card) {
    for (int i = 0; i < CARD_HEIGHT; ++i) {
        cout << card[i];
    }
}
vector<vector<string>> TextDisplay::getRowString(vector<shared_ptr<Card>> cards, int printLocation) {
    vector<vector<string>> cardsStr;

    // add each card print string to the hand
    for (int i = 0; i < cards.size(); ++i) {
        string type = cards[i]->getType();
        if(type=="Spell") {
            cardsStr.push_back(printSpell(dynamic_pointer_cast<Spell>(cards[i])));
        
        } else if (type=="Ritual") {
            cardsStr.push_back(printRitual(dynamic_pointer_cast<Ritual>(cards[i])));
        
        } else if (type=="Minion") {
            cardsStr.push_back(printMinion(dynamic_pointer_cast<Minion>(cards[i])));
        
        } else if (type=="Enchantment") {
            auto enchantment = dynamic_pointer_cast<Enchantment>(cards[i]);

            // if we are printing from inspect, then it will be a minion followed by list of enchantment cards
            // if we are printing from hand, then it will be the enchantment card in hand
            if(printLocation==INSPECT || printLocation==HAND) {
                cardsStr.push_back(printEnchantment(enchantment));
            
            // if we are printing from board, then we are printing the enchanted minion
            } else if (printLocation==BOARD) {
                cardsStr.push_back(printEnchantedMinion(enchantment));
            }
        } else {
            // error
        }
    }
    return cardsStr;
}

// prints row of vectors (continues row if vector has length > 5)
void TextDisplay::printRow(vector<vector<string>> cardsStr, int printLocation) {
    // print cards from 0 to cards.size() to cards.size() - (card.size() mod 5)
    // each turn we print index 0 to BOARD_WIDTH - 1
    int cardRowCounter = 0;

    while ((cardRowCounter)*BOARD_WIDTH < cardsStr.size()) {

        // iterate through each character row
        for  (int i = 0; i < CARD_HEIGHT; ++i) {

            // if we are printing a board, add the board outline (left)
            if(printLocation==BOARD) {
                cout << '|';
            }

            // iterate through all cards for each character row
            for (int j = cardRowCounter*BOARD_WIDTH; j < (cardRowCounter+1)*BOARD_WIDTH; j++) {
                // card j, row i, card j+1, row i, ...
                if(j >= cardsStr.size()) {
                    break;
                }
                cout << cardsStr[j][i];
            }

            // if we are printing a board, add the board outline (right)
            if(printLocation==BOARD) {
                cout << '|';
            }
            cout << endl;
        }
        ++cardRowCounter;
    }

}


void TextDisplay::printLogo() {
    cout 
    << "|---------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl
    << "|                                                                 _____                                                                                               |" << endl
    << "|                                                                / ____|                                                                                              |" << endl
    << "|                                                               | (___   ___  _ __ ___ ___ _ __ _   _                                                                 |" << endl
    << "|                                                                \\___ \\ / _ \\| '__/ __/ _ \\ '__| | | |                                                                |" << endl
    << "|                                                                ____) | (_) | | | (_|  __/ |  | |_| |                                                                |" << endl
    << "|                                                               |_____/ \\___/|_|  \\___\\___|_|   \\__, |                                                                |" << endl
    << "|                                                                                                __/ |                                                                |" << endl
    << "|                                                                                               |___/                                                                 |" << endl
    << "|---------------------------------------------------------------------------------------------------------------------------------------------------------------------|" << endl;
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

void TextDisplay::printInspect(int minion) {
    auto card = game->getActivePlayer()->getBoard()->getMinion(minion);
    string type = card->getType();

    // print the minion, if it is of type minion
    if (type == "Minion"){
        vector<string> minionStr = printMinion(card);
        printCard(minionStr);
        cout << endl;
    }
    // if type enchantment, first get the minion under enchantment the n print enchantments
    if (type == "Enchantment"){

        // enchantment at the top
        auto topEnchantment = dynamic_pointer_cast<Enchantment>(card);
        // print minion under enchantment
        auto bottomMinion = topEnchantment->getAttachedMinion();
        vector<string> minionStr = printMinion(bottomMinion);
        printCard(minionStr);
        cout << endl;

        // print all enchantments
        vector<shared_ptr<Enchantment>> enchantments = topEnchantment->getEnchantmentList();
        vector<shared_ptr<Card>> cards (enchantments.begin(), enchantments.end());
        vector<vector<string>> cardsStr = getRowString(cards, INSPECT);
        printRow(cardsStr, INSPECT);
    }
}




// -------------------- PRINT HAND --------------------

void TextDisplay::printHand() {
    auto cards = game->getActivePlayer()->getHand()->getCards();
    vector<vector<string>> cardsStr = getRowString(cards, HAND);
    printRow(cardsStr, HAND);
}





// -------------------- PRINT BOARD --------------------

// print player and enemy player
vector<string> TextDisplay::printPlayer(shared_ptr<Player> player) {
    vector<string> card = emptyCard();
    // add name to card
    string name = player->getName();
    card[CARD_HEIGHT/2-2].replace(CARD_WIDTH/2-name.size()/2, name.size(), name);

    // add life and magic to card
    printLeftBox(card, to_string(player->getLife()));
    printRightBox(card, to_string(player->getMagic()));

    // if we are printing the active player
    if(game->getActivePlayer()->getNumber()==player->getNumber()) {
        reverse(card.begin(), card.end());
    }

    return card;
}



// get row of board including ritual
vector<vector<string>> TextDisplay::getRitualRow(shared_ptr<Player> player) {
    auto graveyard = player->getGraveyard();
    auto board = player->getBoard();
    
    vector<vector<string>> row;

    // check if ritual is empty
    auto ritual = board->getRitual();
    if (ritual==nullptr) {
        row.push_back(emptyCard());
    } else {
        row.push_back(printRitual(ritual));
    }
    
    row.push_back(emptySpace());
    
    // PRINT PLAYER
    row.push_back(printPlayer(player));

    row.push_back(emptySpace());
    
    // check if graveyard is empty
    if (graveyard->isEmpty()) {
        row.push_back(emptyCard());
    } else {
        auto topMinion = graveyard->getMinionTop();
        row.push_back(printMinion(topMinion));
    }
    return row;
}
// get row of board including minion
vector<vector<string>> TextDisplay::getMinionRow(shared_ptr<Player> player) {
    auto board = player->getBoard();
    vector<shared_ptr<Minion>> minions = board->getMinions();
    vector<shared_ptr<Card>> cards (minions.begin(), minions.end());
    vector<vector<string>> row = getRowString(cards, BOARD);

    for(int i = row.size(); i < 5; ++i){
        row.push_back(emptyCard());
    }
    return row;
}




void TextDisplay::printBoard()
{
    cout << BOARD_TOP << endl;

    // ENEMY
    auto enemy = game->getInactivePlayer();
    vector<vector<string>> ritualRow = getRitualRow(enemy);
    vector<vector<string>> minionRow = getMinionRow(enemy);
    reverse(ritualRow.begin(), ritualRow.end());
    reverse(minionRow.begin(), minionRow.end());
    printRow(ritualRow, BOARD);
    printRow(minionRow, BOARD);

    // print SORCERY logo
    printLogo();

    // CURRENT PLAYER
    auto player = game->getActivePlayer();
    printRow(getMinionRow(player), BOARD);
    printRow(getRitualRow(player), BOARD);
    

    cout << BOARD_TOP << endl;
  
}
