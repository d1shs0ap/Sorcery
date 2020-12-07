#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <string>

void displayHelp()
{
    std::cout << "Commands:" << std::endl;
    std::cout << "help -- Display this message." << std::endl;
    std::cout << "end  -- End the current player’s turn." << std::endl;
    std::cout << "quit -- End the game." << std::endl;
    std::cout << "attack minion other-minion -- Orders minion to attack other-minion." << std::endl;
    std::cout << "attack minion -- Orders minion to attack the opponent." << std::endl;
    std::cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << std::endl;
    std::cout << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << std::endl;
    std::cout << "inspect minion -- View a minion’s card and all enchantments on that minion." << std::endl;
    std::cout << "hand -- Describe all cards in your hand." << std::endl;
    std::cout << "board -- Describe all cards on the board." << std::endl;
}

std::string quitMessage{"Game Over."};

#endif
