#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <random>
#include <chrono>
#include <algorithm>

#include "game/game.h"
#include "view/textDisplay.h"
#include "controller/textController.h"
#include "cardCollections/deck.h"
#include "cardCollections/board.h"
#include "cardCollections/hand.h"
#include "cardCollections/graveyard.h"
#include "game/player.h"
#include "game/game.h"
#include "argException.h"


using namespace std;

int main(int argc, char *argv[])
{
    try {
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
                if (i+1 <= argc - 1){
                    deck1FileName = argv[i+1]; 
                    ++i;
                } else {
                    throw ArgException{"-deck1 requires an argument."};
                }

            // loads a given deck
            } else if (arg == "-deck2") {
                if (i+1 <= argc - 1){
                    deck2FileName = argv[i+1];
                    ++i;
                } else {
                    throw ArgException{"-deck2 requires an argument."};
                }
            
            // loads given actions
            } else if (arg == "-init") {
                if (i+1 <= argc - 1){
                    initFileName = argv[i+1];
                    ++i;
                } else {
                    throw ArgException{"-init requires an argument."};
                }
            }
        }

        
        // -------------------- create and load decks --------------------

        // random seed
        unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
        unsigned seed2 = chrono::system_clock::now().time_since_epoch().count();

        default_random_engine rng1{seed1};
        default_random_engine rng2{seed2};
        
        auto deck1 = make_shared<Deck>(rng1, 0);
        auto deck2 = make_shared<Deck>(rng2, 1);

        // default deck
        ifstream defaultDeck1File{"../decks/default.deck"};
        ifstream defaultDeck2File{"../decks/default.deck"};
        // Load deck 1 and 2
        ifstream deck1File{deck1FileName};
        ifstream deck2File{deck2FileName};
        if (deck1File) { // if deck1 file can be loaded
            deck1->loadDeck(deck1File);
        } else {
            deck1->loadDeck(defaultDeck1File);
        }
        if (deck2File) { // if deck1 file can be loaded
            deck2->loadDeck(deck2File);
        } else {
            deck2->loadDeck(defaultDeck2File);
        }

        // Decks are shuffled if not in testing
        if (TESTING==false) {
            deck1->shuffleDeck();

            deck2->shuffleDeck();
            deck2->shuffleDeck();
        }


        // -------------------- Reading in names --------------------
        ifstream initFile(initFileName);

        // read in name1 and name2
        string name1, name2;
        if (initFile) { // if initFile loads
            if (!(getline(initFile, name1))){
                cout << "Enter Player1's name:" << endl;
                getline(cin, name1);
            }
        } else {
            cout << "Enter Player1's name:" << endl;
            getline(cin, name1);
        }
        
        if (initFile) { // if initFile loads
            if (!(getline(initFile, name2))){
                cout << "Enter Player2's name:" << endl;
                getline(cin, name2);
            }
        } else {
            cout << "Enter Player2's name:" << endl;
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

        // game seed generator
        unsigned gameSeed = chrono::system_clock::now().time_since_epoch().count();
        mt19937_64 generator{gameSeed};

        // game, text display, text controller
        auto game = make_shared<Game>(player1, player2, generator);
        auto textDisplay = make_shared<TextDisplay>(game);
        auto textController = make_unique<TextController>(game, textDisplay);

        // deck sizes before drawing any cards
        int deck1Size = deck1->getSize();
        int deck2Size = deck2->getSize();

        // Both players draw 5 cards
        for (int i = 0; i < min(5, deck1Size); ++i){
            player1->draw();
        }

        for (int i = 0; i < min(5, deck2Size); ++i){
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
                } else {
                    getline(cin, cmd);
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
                        cout << "Command draw is only avalaible in testing mode." << endl;
                    else {
                        textController->draw();
                    }
                    // note: recall that a player can only do this when the number of
                    //       cards in hand is less than 5. This is checked within the
                    //       function Player::draw.
                } else if (cmd.substr(0, 8) == "discard ") { // takes in 1 argument
                    if (TESTING == false)
                        cout << "Command discard is only avalaible in testing mode." << endl;
                    else {
                        stringstream sscmd {cmd};
                        string arg;
                        int argCount = 0;
                        int cardInHand;
                        while(sscmd >> arg) {
                            if(argCount==0){
                                ++argCount; // get rid of first arg which is "discard" to read the actual args
                                continue;
                            } else if (argCount==1){    
                                cardInHand = stoi(arg); // if input received cannot be converted, entire cmd fails
                                ++argCount;

                                if(sscmd.eof()){ // must be EOF since discard only takes in one argument
                                    textController->discard(cardInHand);
                                    break;
                                } else {
                                    // throw "too many arguments" error here
                                    throw ArgException{"discard requires 1 argument."};
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
                    while(sscmd >> arg){
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
                                throw ArgException{"attack requires 1 or 2 arguments."};
                                break;
                            }
                        }
                    }
                } else if (cmd.substr(0, 5) == "play ") { // takes in 1 or 3 arguments
                    stringstream sscmd {cmd};
                    string arg;
                    int argCount = 0;
                    int cardInHand, targetPlayer, targetMinion;
                    while(sscmd >> arg){
                        if(argCount==0){
                            ++argCount; // get rid of first arg which is "attack" to read the actual args
                            continue;
                        } else if (argCount==1) {
                            cardInHand = stoi(arg); // if input received cannot be converted, entire cmd fails
                            ++argCount;

                            if(sscmd.eof()) { // if only 1 arg
                                textController->play(cardInHand, TESTING);
                                break;
                            }
                            continue;
                        } else if(argCount==2){ // may be EOF, may not be since may take in 2 args
                            targetPlayer = stoi(arg); // if input received cannot be converted, entire cmd fails
                            ++argCount;

                            if(sscmd.eof()) { // if only 2 args
                                // throw "too few arguments"
                                throw ArgException{"play requires 1 or 3 arguments."};
                                break;
                            }
                        } else if (argCount==3){
                            if (arg=="r"){ // if ritual
                                if(sscmd.eof()) { // if only 3 args
                                    textController->play(cardInHand, targetPlayer, TESTING);
                                    break;
                                }

                            } else {
                                targetMinion = stoi(arg); // if input received cannot be converted, entire cmd fails

                                if(sscmd.eof()) { // if only 3 args
                                    textController->play(cardInHand, targetPlayer, targetMinion, TESTING);
                                    break;
                                } else {
                                    // throw "too many arguments" error here
                                    throw ArgException{"play requires 1 or 3 arguments."};
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
                    while(sscmd >> arg){
                        if(argCount==0){
                            ++argCount; // get rid of first arg which is "attack" to read the actual args
                            continue;
                        } else if (argCount==1) {
                            minion = stoi(arg); // if input received cannot be converted, entire cmd fails
                            ++argCount;

                            if(sscmd.eof()) { // if only 1 arg
                                textController->use(minion, TESTING);
                                break;
                            }
                            continue;
                        } else if(argCount==2){ // may be EOF, may not be since may take in 2 args
                            targetPlayer = stoi(arg); // if input received cannot be converted, entire cmd fails
                            ++argCount;

                            if(sscmd.eof()) { // if only 2 args
                                // throw "too few arguments"
                                throw ArgException{"use requires 1 or 3 arguments."};
                                break;
                            }
                        } else if (argCount==3){
                            if (arg=="r"){ // if ritual
                                if(sscmd.eof()) { // if only 3 args
                                    textController->use(minion, targetPlayer, TESTING);
                                    break;
                                }

                            } else {
                                targetMinion = stoi(arg); // if input received cannot be converted, entire cmd fails

                                if(sscmd.eof()) { // if only 3 args
                                    textController->use(minion, targetPlayer, targetMinion, TESTING);
                                    break;
                                } else {
                                    // throw "too many arguments" error here
                                    throw ArgException{"use requires 1 or 3 arguments."};
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
                    while(sscmd >> arg){
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
                                throw ArgException{"inspect requires 1 argument."};
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
                    throw ArgException{"Command not recognized."};
                }
                game->clean();
            } catch (const ios::failure& e) {
                cout << e.what() << endl;
            } catch (const invalid_argument& e) { // this is for stoi
                cout << "Please input a valid integer. " << endl;
            } catch (const ArgException& e) {
                cout << e.message << endl;
            }

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
    } catch (ArgException& e) {
        cout << e.message << endl;
    }
}
