#include <iostream>
#include <string>
#include <vector>

#include "player.h"
#include "card.h"
#include "game/game.h"
#include "util.h"

bool TESTING = false;

int main(int argc, char *argv[])
{
    Game game;
    bool supplied1 = false;
    bool supplied2 = false;
    std::string cmd;
    while (std::cin >> cmd)
    {
        if (cmd == "help")
        {
            displayHelp();
        }
        else if (cmd == "end")
        {
            game.endTurn();
        }
        else if (cmd == "quit")
        {
            std::cout << quitMessage << std::endl;
            return 0;
        }
        else if (cmd == "draw")
        {
            if (TESTING == false)
                std::cout << "Command draw is only avaliable in testing mode." << std::endl;
            else
            {
                // note: got some problem here.
            }
            // note: recall that a player can only do this when the number of
            //       cards in hand is less than 5. This is checked within the
            //       function Player::draw.
        }
        else if (cmd == "discard")
        {
            if (TESTING == false)
                std::cout << "Command draw is only avaliable in testing mode." << std::endl;
            else
            {
                // note: got some problem here.
            }
        }
    }
}
