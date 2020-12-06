#ifndef DECORATOR_H
#define DECORATOR_H
#include <memory>

class Card;

class Decorator
{
private:
    std::shared_ptr<Card> card; // changed variable name to make it more meaningful. this is different from the UML.
};

#endif
