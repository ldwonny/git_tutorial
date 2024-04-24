#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum class TileColor { WHITE, BLACK };

struct Tile 
{
    int number;
    TileColor color;
};

class DaVinciCodeGame
{
private:
    Tile centerTiles[24];

public:
    void initializeTiles()
    {

        /* TODO: initialize tiles with input.txt file */
        ifstream ifs;
        char c[4];
        int i = 0;
        ifs.open("input.txt");
        if (!ifs.is_open()) {
            cerr << "Input File error!" << endl;
            exit(1);
        }
        while (ifs >> c)
        {
            if (strlen(c) == 3)
            {
                centerTiles[i].number = (c[0] - '0') * 10 + c[1] - '0';
                if (c[2] == 'b')
                {
                    centerTiles[i].color = TileColor::BLACK;
                }
                else
                {
                    centerTiles[i].color = TileColor::WHITE;
                }
                i++;
            }
            else if (strlen(c) == 2)
            {
                centerTiles[i].number = c[0] - '0';
                if (c[1] == 'b')
                {
                    centerTiles[i].color = TileColor::BLACK;
                }
                else
                {
                    centerTiles[i].color = TileColor::WHITE;
                }
                i++;
            }
        }
    }
    void printtile()
    {
        for (int i = 0; i < 24; i++)
        {
            cout << centerTiles[i].number << " " << static_cast<int>(centerTiles[i].color) << endl;
        }
    }
};

int main()
{
    DaVinciCodeGame game;
    game.initializeTiles();
    game.printtile();

    return 0;
}