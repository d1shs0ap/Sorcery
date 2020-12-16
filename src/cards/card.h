#ifndef CARD_H
#define CARD_H

#include <string>
#include <memory>
#include <vector>

// Class for all cards
class Card
{
    std::string name;
    std::string type;
    int owner;
    int cost;

public:
    // Default Constructor
    Card();
    // Constructor
    Card(std::string name, std::string type, int owner, int cost);

    // Getters and Setters
    std::string getName() const;
    std::string getType() const;
    int getOwner() const;
    void setOwner(int newOwner);
    int getCost() const;
    void setCost(int newCost);

    // Destructor
    virtual ~Card();
};

#endif
