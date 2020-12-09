#include <iostream>
#include <string>
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
        while (cin >> cmd) {
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
            } else if (cmd.substr(0, 7) == "discard") {
                if (TESTING == false)
                    cout << "Command discard is only avaliable in testing mode." << endl;
                else {
                    try {
                        int cardInHand = stoi(cmd.substr(7));
                        textController->discard(cardInHand);
                    } catch (const std::invalid_argument& ia) {}
                }
            } else if (cmd == "attack") {
                int minion;
                cin >> minion;
                

            } else if (cmd == "play") {

            } else if (cmd == "use") {

            } else if (cmd == "inspect") {
                textController->inspect();
            } else if (cmd == "hand") {
                textController->hand();
            } else if (cmd == "board") {
                textController->board();
            }
        }
    } catch (ios::failure &) {}
}
