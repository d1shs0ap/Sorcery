#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>
#include <vector>

// Abstract class for all cards
class Card
{
    std::string name;
    std::string type;
    int owner;
    int cost;

public:
    Card();
    Card(std::string name, std::string type, int owner, int cost);

    std::string getName() const;
    std::string getType() const;
    int getOwner() const;
    int getCost() const;

    virtual ~Card();
};

#endif
