#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <vector>
#include <iostream>

#include "observer.h"

class TextDisplay : public Observer {
    std::vector<std::vector<char>> display;
    public:
        virtual void update(Subject & game) override;
        void printHelp();
        void printCard(); // called by "inspect i"
        void printHand(); // called by "hand"
        void printBoard(); // called by "board"
};

#endif
