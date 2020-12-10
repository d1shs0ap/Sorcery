#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "game/game.h"
#include "view/textDisplay.h"
#include "controller/textController.h"

bool TESTING = false;

using namespace std;

int main(int argc, char *argv[])
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();

    auto player1 = make_shared<Player>(string name, int number, unique_ptr<Board> board, unique_ptr<Deck> deck, unique_ptr<Graveyard> graveyard, unique_ptr<Hand> hand);
    auto player2 = make_shared<Player>();
    auto game = make_shared<Game>(player1, player2, seed);
    shared_ptr<TextDisplay> textDisplay;
    shared_ptr<TextController> textController;

    bool supplied1 = false;
    bool supplied2 = false;

    // for storing the commands
    string cmd;
    try {
        while (getline(cin, cmd)) {
            try {
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
            } catch (const ios::failure& e) {
            } catch (const std::invalid_argument& ia) {}
        }
    } catch (const ios::failure& e) {
        std::cout << "Caught an ios_base::failure." << endl
                  << "Explanatory string: " << e.what() << endl
                  << "Error code: " << e.code() << endl;
    }
}
