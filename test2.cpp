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

class Player {
private:
    Tile tiles[13];
    int numTiles = 0;
public:
    void addTile(Tile tile) {
        tiles[numTiles] = tile;
        numTiles++;
    }
    Tile& getTile(int index) {
        if (index < numTiles) return tiles[index];
        else {
            cerr << "out of tile index!" << endl;
            exit(1);
        }
    }
    int getNumTiles() {
        return numTiles;
    }

    void sortTiles() {

        /* TODO */
        // num에 따라 정렬
        // num이 같으면 bw순으로 정렬
        Tile temp;
        for (int i = 0; i < numTiles - 1; i++)
        {
            for (int j = 0; j < numTiles - i - 1; j++)
            {
                if (tiles[j].number > tiles[j + 1].number)
                {
                    temp = tiles[j];
                    tiles[j] = tiles[j + 1];
                    tiles[j + 1] = temp;
                }
                else if (tiles[j].number == tiles[j+1].number)
                {
                    if (tiles[j].color == TileColor::WHITE)
                    {
                        temp = tiles[j];
                        tiles[j] = tiles[j + 1];
                        tiles[j + 1] = temp;
                    }
                }
            }
        }
    }
};


class DaVinciCodeGame
{
private:
    Tile centerTiles[24];
    Player players[4];
    int numCenter = 24;
    int numPlayers;
    int currentPlayerIndex;

public:
    DaVinciCodeGame(int num) {
        numPlayers = num;
        currentPlayerIndex = 0;
        initialize();
        initializeTiles();
        initializePlayerTiles();
    }
    void initialize()
    {}
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
        ifs.close();
    }

    void initializePlayerTiles() {

        /* TODO: make each player draw 4 tiles */
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                players[i].addTile(popCenter());
            }
            players[i].sortTiles();
        }
    }

    Tile popCenter() {
        if (numCenter < 0) {
            cerr << "Out of center tile index!" << endl;
            exit(1);
        }
        /* TODO: draw one tile from center tiles */
        Tile temp;
        temp = centerTiles[24 - numCenter]; // 오류 이유 numCenter = 0이면 초과해버림.
        numCenter--;
        return temp;
    }


    void printtile()
    {
        for (int i = 0; i < 24; i++)
        {
            cout << centerTiles[i].number << " " << static_cast<int>(centerTiles[i].color) << endl;
        }
    }
    void printplayertile()
    {
        for (int i = 0; i < 2; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << players[i].getTile(j).number << " " << static_cast<int>(players[i].getTile(j).color) << endl;
            }
            cout << endl;
        }
    }
};

int main()
{
    DaVinciCodeGame game(2);
    //game.printtile();
    game.printplayertile();
    Tile temp;
    temp = game.popCenter();
    cout << temp.number << " " << static_cast<int>(temp.color) << endl;
    return 0;
}