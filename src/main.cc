#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "game/game.h"
#include "view/textDisplay.h"
#include "controller/textController.h"


using namespace std;

int main(int argc, char *argv[])
{
    // -------------------- processing argv --------------------
    
    bool TESTING = false;
    string deck1FileName;
    string deck2FileName;
    string initFileName;

    for (int i = 1; i < argc; ++i) { // 0th argument is the program, we skip it
        string arg = argv[i];
        // may use discard, draw, decks are no longer shuffled, spells/activated abilities changed to 0 if not enough magic
        if (arg == "-testing") {
            TESTING = true;
        
        // loads a given deck
        } else if (arg == "-deck1") {
            deck1FileName = argv[i+1]; 
            ++i;

        // loads a given deck
        } else if (arg == "-deck2") {
            deck2FileName = argv[i+1];
            ++i;
        
        // loads given actions
        } else if (arg == "-init") {
            initFileName = argv[i+1];
            ++i;
        }
    }

    
    // -------------------- create and load decks --------------------

    // random seed
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    
    auto deck1 = make_shared<Deck>(seed, 0);
    auto deck2 = make_shared<Deck>(seed, 1);

    // default deck
    ifstream defaultDeckFile{"../decks/default.deck"};
    // Load deck 1 and 2
    ifstream deck1File{deck1FileName};
    ifstream deck2File{deck2FileName};
    if (deck1File) { // if deck1 file can be loaded
        deck1->loadDeck(deck1File);
    } else {
        deck1->loadDeck(defaultDeckFile);
    }
    if (deck2File) { // if deck1 file can be loaded
        deck2->loadDeck(deck2File);
    } else {
        deck2->loadDeck(defaultDeckFile);
    }

    // Decks are shuffled if not in testing
    if (TESTING==false) {
        deck1->shuffleDeck();
        deck2->shuffleDeck();
    }


    // -------------------- Reading in names --------------------
    ifstream initFile(initFileName);

    // read in name1 and name2
    string name1, name2;
    cout << "Enter Player1's name:" << endl;
    if (initFile) { // if initFile loads
        if (!(getline(initFile, name1))){
            getline(cin, name1);
        }
    } else {
        getline(cin, name1);
    }
    
    std::cout << "Enter Player2's name:" << endl;
    if (initFile) { // if initFile loads
        if (!(getline(initFile, name2))){
            getline(cin, name2);
        }
    } else {
        getline(cin, name2);
    }


    // -------------------- Creating other game objects --------------------

    // board begins empty
    auto board1 = make_shared<Board>();
    auto board2 = make_shared<Board>();

    // graveyard begins empty
    auto graveyard1 = make_shared<Graveyard>();
    auto graveyard2 = make_shared<Graveyard>();
    // need to draw 5 cards
    auto hand1 = make_shared<Hand>();
    auto hand2 = make_shared<Hand>();
    // construct the players
    auto player1 = make_shared<Player>(name1, 0, board1, deck1, graveyard1, hand1);
    auto player2 = make_shared<Player>(name2, 1, board2, deck2, graveyard2, hand2);

    auto game = make_shared<Game>(player1, player2, seed);
    auto textDisplay = make_shared<TextDisplay>();
    auto textController = make_unique<TextController>(game, textDisplay);

    // Both players draw 5 cards
    for (int i = 0; i < 5; ++i){
        player1->draw();
        player2->draw();
    }

    // -------------------- Game loop --------------------

    // if there is init file, then do not randomly decide player start turn
    if (initFile) {
        if(game->getActivePlayer()->getNumber()==1){
            game->changeActive();
        }
    } else {
        cout << "Flipping a coin..." << endl
            << game->getActivePlayer()->getName() << " goes first." << endl;
    }

    // for storing the commands
    string cmd;
    while (game->getWinner()==-1) {
        try {
            // read in from init file first
            if (initFile) {
                if (!(getline(initFile,cmd))){
                    getline(cin, cmd);
                }
            }

            if (cmd == "help") {
                textController->help();
            }
            else if (cmd == "end") {
                textController->end();
            }
            else if (cmd == "quit") { // Quits the game immediately with no winner
                cout << "Quitting game..." << endl;
                return 0;
            } else if (cmd == "draw") {
                if (TESTING == false)
                    cout << "Command draw is only avaliable in testing mode." << endl;
                else {
                    textController->draw();
                }
                // note: recall that a player can only do this when the number of
                //       cards in hand is less than 5. This is checked within the
                //       function Player::draw.
            } else if (cmd.substr(0, 8) == "discard ") { // takes in 1 argument
                if (TESTING == false)
                    cout << "Command discard is only avaliable in testing mode." << endl;
                else {
                    stringstream sscmd {cmd};
                    string arg;
                    int argCount = 0;
                    int cardInHand;
                    while(getline(sscmd, arg)){
                        if(argCount==0){
                            ++argCount; // get rid of first arg which is "discord" to read the actual args
                            continue;
                        } else if (argCount==1){    
                            cardInHand = stoi(arg); // if input received cannot be converted, entire cmd fails
                            ++argCount;

                            if(sscmd.eof()){ // must be EOF since discard only takes in one argument
                                textController->discard(cardInHand);
                                break;
                            } else {
                                // throw "too many arguments" error here
                                break;
                            }
                        }
                    }
                }
            } else if (cmd.substr(0, 7) == "attack ") { // takes in 1 or 2 arguments
                stringstream sscmd {cmd};
                string arg;
                int argCount = 0;
                int minion, enemyMinion;
                while(getline(sscmd, arg)){
                    if(argCount==0){
                        ++argCount; // get rid of first arg which is "attack" to read the actual args
                        continue;
                    } else if(argCount==1){ // may be EOF, may not be since may take in 2 args
                        minion = stoi(arg); // if input received cannot be converted, entire cmd fails
                        ++argCount;

                        if(sscmd.eof()) { // if only 1 arg
                            textController->attack(minion);
                            break;
                        }
                    } else if (argCount==2){
                        enemyMinion = stoi(arg); // if input received cannot be converted, entire cmd fails

                        if(sscmd.eof()) { // if only 2 args
                            textController->attack(minion, enemyMinion);
                            break;
                        } else {
                            // throw "too many arguments" error here
                            break;
                        }
                    }
                }
            } else if (cmd.substr(0, 5) == "play ") { // takes in 1 or 3 arguments
                stringstream sscmd {cmd};
                string arg;
                int argCount = 0;
                int cardInHand, targetPlayer, targetMinion;
                while(getline(sscmd, arg)){
                    if(argCount==0){
                        ++argCount; // get rid of first arg which is "attack" to read the actual args
                        continue;
                    } else if (argCount==1) {
                        cardInHand = stoi(arg); // if input received cannot be converted, entire cmd fails
                        ++argCount;

                        if(sscmd.eof()) { // if only 1 arg
                            textController->play(cardInHand);
                            break;
                        }
                        continue;
                    } else if(argCount==2){ // may be EOF, may not be since may take in 2 args
                        targetPlayer = stoi(arg); // if input received cannot be converted, entire cmd fails
                        ++argCount;

                        if(sscmd.eof()) { // if only 2 args
                            // throw "too few arguments"

                            break;
                        }
                    } else if (argCount==3){
                        if (arg=="r"){ // if ritual
                            if(sscmd.eof()) { // if only 3 args
                                textController->play(cardInHand, targetPlayer, 'r');
                                break;
                            }

                        } else {
                            targetMinion = stoi(arg); // if input received cannot be converted, entire cmd fails

                            if(sscmd.eof()) { // if only 3 args
                                textController->play(cardInHand, targetPlayer, targetMinion);
                                break;
                            } else {
                                // throw "too many arguments" error here
                                break;
                            }
                        }
                    }
                }
            } else if (cmd.substr(0, 4) == "use ") { // takes in 1 or 3 arguments
                stringstream sscmd {cmd};
                string arg;
                int argCount = 0;
                int minion, targetPlayer, targetMinion;
                while(getline(sscmd, arg)){
                    if(argCount==0){
                        ++argCount; // get rid of first arg which is "attack" to read the actual args
                        continue;
                    } else if (argCount==1) {
                        minion = stoi(arg); // if input received cannot be converted, entire cmd fails
                        ++argCount;

                        if(sscmd.eof()) { // if only 1 arg
                            textController->use(minion);
                            break;
                        }
                        continue;
                    } else if(argCount==2){ // may be EOF, may not be since may take in 2 args
                        targetPlayer = stoi(arg); // if input received cannot be converted, entire cmd fails
                        ++argCount;

                        if(sscmd.eof()) { // if only 2 args
                            // throw "too few arguments"
                            break;
                        }
                    } else if (argCount==3){
                        if (arg=="r"){ // if ritual
                            if(sscmd.eof()) { // if only 3 args
                                textController->use(minion, targetPlayer, 'r');
                                break;
                            }

                        } else {
                            targetMinion = stoi(arg); // if input received cannot be converted, entire cmd fails

                            if(sscmd.eof()) { // if only 3 args
                                textController->use(minion, targetPlayer, targetMinion);
                                break;
                            } else {
                                // throw "too many arguments" error here
                                break;
                            }
                        }
                    }
                }
            } else if (cmd.substr(0, 8) == "inspect ") { // takes in one argument
                stringstream sscmd {cmd};
                string arg;
                int argCount = 0;
                int minion;
                while(getline(sscmd, arg)){
                    if(argCount==0){
                        ++argCount; // get rid of first arg which is "inspect" to read the actual args
                        continue;
                    } else if (argCount==1){
                        minion = stoi(arg);
                        
                        ++argCount;

                        if(sscmd.eof()){ // must be EOF since discard only takes in one argument
                            textController->inspect(minion);
                            break;
                        } else {
                            // throw "too many arguments" error here
                            break;
                        }
                    }
                }
            } else if (cmd == "hand") {
                textController->hand();
            } else if (cmd == "board") {
                textController->board();
            } else {
                // throw invalid input
            }
            game->clean();
        } catch (const ios::failure& e) {
            std::cout << "Caught an ios_base::failure." << endl
                << "Explanatory string: " << e.what() << endl
                << "Error code: " << e.code() << endl;
        } catch (const std::invalid_argument& ia) {}
    }

    cout << "Game over! ";
    if (game->getWinner() == 0) {
        cout << "Tie game!" << endl;
    } else if (game->getWinner() == 1) {
        cout << game->getPlayer(0)->getName() << " wins!" << endl;
    } else if (game->getWinner() == 2) {
        cout << game->getPlayer(1)->getName() << " wins!" << endl;
    }

    return 0;
}
