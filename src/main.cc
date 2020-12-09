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
    Game game;
    TextDisplay textDisplay;
    shared_ptr<TextController> textController;

    bool supplied1 = false;
    bool supplied2 = false;

    // for storing the commands
    string cmd;
    try { // Is the try catch correct?
        while (getline(cin, cmd)) {
            if (cmd == "help") {
                textController->help();
            }
            else if (cmd == "end") {
                textController->end();
            }
            else if (cmd == "quit") {
                textController->quit();
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
                            try {
                                cardInHand = stoi(arg);
                            } catch (const std::invalid_argument& ia) {}
                            
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
            } else if (cmd == "attack") { // takes in 1 or 2 arguments
                stringstream sscmd {cmd};
                string arg;
                int argCount = 0;
                int minion, enemyMinion;
                while(getline(sscmd, arg)){
                    if(argCount==0){
                        ++argCount; // get rid of first arg which is "attack" to read the actual args
                        continue;
                    } else if(argCount==1){ // may be EOF, may not be since may take in 2 args
                        try {
                            minion = stoi(arg);
                        } catch (const std::invalid_argument& ia) {}
                        
                        ++argCount;

                        if(sscmd.eof()) { // if only 1 arg
                            textController->attack(minion);
                            break;
                        }
                    } else if (argCount==2){
                        try {
                            enemyMinion = stoi(arg);
                        } catch (const std::invalid_argument& ia) {}

                        if(sscmd.eof()) { // if only 2 args
                            textController->attack(minion, enemyMinion);
                            break;
                        } else {
                            // throw "too many arguments" error here
                            break;
                        }
                    }
                }
            } else if (cmd == "play") { // takes in 1 or 3 arguments
                stringstream sscmd {cmd};
                string arg;
                int argCount = 0;
                int cardInHand, targetPlayer, targetMinion;
                while(getline(sscmd, arg)){
                    if(argCount==0){
                        ++argCount; // get rid of first arg which is "attack" to read the actual args
                        continue;
                    } else if (argCount==1) {
                        try {
                            cardInHand = stoi(arg);
                        } catch (const std::invalid_argument& ia) {}

                        ++argCount;

                        if(sscmd.eof()) { // if only 1 arg
                            textController->play(cardInHand);
                            break;
                        }
                        continue;
                    } else if(argCount==2){ // may be EOF, may not be since may take in 2 args
                        try {
                            targetPlayer = stoi(arg);
                        } catch (const std::invalid_argument& ia) {}
                        
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
                            try {
                                targetMinion = stoi(arg);
                            } catch (const std::invalid_argument& ia) {}

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
            } else if (cmd == "use") { // takes in 1 or 3 arguments
                stringstream sscmd {cmd};
                string arg;
                int argCount = 0;
                int minion, targetPlayer, targetMinion;
                while(getline(sscmd, arg)){
                    if(argCount==0){
                        ++argCount; // get rid of first arg which is "attack" to read the actual args
                        continue;
                    } else if (argCount==1) {
                        try {
                            minion = stoi(arg);
                        } catch (const std::invalid_argument& ia) {}

                        ++argCount;

                        if(sscmd.eof()) { // if only 1 arg
                            textController->use(minion);
                            break;
                        }
                        continue;
                    } else if(argCount==2){ // may be EOF, may not be since may take in 2 args
                        try {
                            targetPlayer = stoi(arg);
                        } catch (const std::invalid_argument& ia) {}
                        
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
                            try {
                                targetMinion = stoi(arg);
                            } catch (const std::invalid_argument& ia) {}

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
            } else if (cmd == "inspect") { // takes in one argument
                stringstream sscmd {cmd};
                string arg;
                int argCount = 0;
                int minion;
                while(getline(sscmd, arg)){
                    if(argCount==0){
                        ++argCount; // get rid of first arg which is "inspect" to read the actual args
                        continue;
                    } else if (argCount==1){
                        try {
                            minion = stoi(arg);
                        } catch (const std::invalid_argument& ia) {}
                        
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
            }
        }
    } catch (ios::failure &) {}
}
