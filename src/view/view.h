#ifndef DISPLAY_H
#define DISPLAY_H
#include <vector>

#include "observer.h"

class View : public Observer
{
private:
    std::vector<std::vector<char>> display;

public:
    void print();
};

#endif
