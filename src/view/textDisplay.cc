#include "textDisplay.h"

using namespace std;

void TextDisplay::printHelp()
{
    cout << "Commands:" << endl;
    cout << "help -- Display this message." << endl;
    cout << "end  -- End the current player’s turn." << endl;
    cout << "quit -- End the game." << endl;
    cout << "attack minion other-minion -- Orders minion to attack other-minion." << endl;
    cout << "attack minion -- Orders minion to attack the opponent." << endl;
    cout << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << endl;
    cout << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << endl;
    cout << "inspect minion -- View a minion’s card and all enchantments on that minion." << endl;
    cout << "hand -- Describe all cards in your hand." << endl;
    cout << "board -- Describe all cards on the board." << endl;
}

void TextDisplay::printBoard()
{
    for (int i = 0; i < 56; i++)
    {
        for (int j = 0; j < 167; j++)
        {
            // print borders
            if (i == 0 || i == 55)
            {
                if (j != 167)
                {
                    cout << "-";
                }
                else
                {
                    cout << "-" << endl;
                }
            }
            else if (j == 0)
            {
                cout << "|";
            }
            else if (j == 166)
            {
                cout << "|" << endl;
            }
            else if (i == 23 || i == 32)
            {
                cout << "-";
                // print "_"
            }
            else if ((i == 24 && j > 65 && j < 71) || (i == 25 && j > 66 && j < 72) ||
                     (i == 26 && (j == 67 || j == 68 || j == 69 || j == 73 || j == 74 || j == 75 || j == 78 || j == 80 || j == 81 || j == 83 || j == 84 || j == 85 || j == 87 || j == 88 || j == 89 || j == 91 || j == 93 || j == 94 || j == 96 || j == 100)) ||
                     (i == 27 && (j == 66 || j == 67 || j == 68 || j == 74 || j == 80 || j == 81 || j == 84 || j == 85 || j == 88 || j == 93 || j == 94)) ||
                     (i == 28 && (j == 65 || j == 66 || j == 67 || j == 68 || j == 74 || j == 84 || j == 88 || j == 89 || j == 98)) ||
                     (i == 29 && (j == 65 || j == 66 || j == 67 || j == 68 || j == 69 || j == 73 || j == 74 || j == 75 || j == 78 || j == 83 || j == 84 || j == 85 || j == 87 || j == 88 || j == 89 || j == 91 || j == 97 || j == 98)) ||
                     (i == 30 && (j == 97 || j == 98)) || (i == 31 && j > 96 && j < 100))
            {
                cout << "_";
                // print "|"
            }
            else if ((i == 25 && j == 71) || (i == 26 && j == 64) || (i == 27 && (j == 77 || j == 95 || j == 97 || j == 99 || j == 101)) ||
                     (i == 28 && (j == 71 || j == 77 || j == 79 || j == 81 || j == 85 || j == 92 || j == 95 || j == 97 || j == 99 || j == 101)) ||
                     (i == 29 && (j == 64 || j == 77 || j == 79 || j == 90 || j == 92 || j == 101)) || (i == 30 && j == 101) || (i == 31 && j == 96))
            {
                cout << "|";
                // print "/"
            }
            else if ((i == 25 && j == 65) || (i == 27 && (j == 72 || j == 82 || j == 86)) || (i == 28 || j == 90) || (i == 29 && (j == 70) || (j == 76)) || (i == 30 && j == 99) || (i == 31 && j == 100))
            {
                cout << "/";
                // print "\"
            }
            else if ((i == 27 && (j == 65 || j == 70 || j == 76 || j == 90)) || (i == 29 && (j == 72 || j == 82 || j == 86 || j == 99)))
            {
                cout << "\\";
                // print "("
            }
            else if ((i == 26 && j == 66) || (i == 28 && (j == 73 || j == 83)))
            {
                cout << "(";
                // print ")"
            }
            else if (i == 28 && j == 75)
            {
                cout << ")";
                // print "'"
            }
            else if (i == 27 && (j == 79 || j == 92))
            {
                cout << "'";
                // print ","
            }
            else if (i == 29 && j == 99)
            {
                cout << ",";
                // print space
            }
            else
            {
                cout << " ";
            }
        }
    }
}