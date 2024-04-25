#include <iostream>
#include <fstream>

using namespace std;

enum class TileColor { WHITE, BLACK };
enum class TileStatus { HIDDEN, REVEALED };

struct Tile {
    int number;
    TileColor color;
    TileStatus status;
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

    void displayTiles(ofstream& ofs) {

        /* DO NOT MODIFY the output format! */

        sortTiles();
        for (size_t i = 0; i < numTiles; i++) {
            ofs << tiles[i].number;
            ofs << (tiles[i].color == TileColor::WHITE ? "w" : "b") << "(";
            ofs << (tiles[i].status == TileStatus::HIDDEN ? "H" : "R") << ")";
            if (i != numTiles - 1) ofs << ", ";
        }
    }

    bool isTileRevealed(int index) {
        if (index < numTiles) return tiles[index].status == TileStatus::REVEALED;
        else {
            cerr << "Out of tile index!" << endl;
            exit(1);
        }
    }

    void sortTiles() {

        /* TODO */
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
                else if (tiles[j].number == tiles[j + 1].number)
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
    bool allTilesRevealed() {

        /* TODO: return true if one's tiles are all revealed */
        // player (0 to tilenum), if there is Hidden, return false, else return true;
    }
};

class DaVinciCodeGame {
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

    void initialize() {

        /* If you need, initialize any variables. */

    }

    Tile popCenter() {
        if (numCenter < 0) {
            cerr << "Out of center tile index!" << endl;
            exit(1);
        }
        Tile temp;
        temp = centerTiles[24 - numCenter];
        numCenter--;
        return temp;
        /* TODO: draw one tile from center tiles */

    }

    void initializeTiles() {

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
        for (int i = 0; i < numPlayers; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                players[i].addTile(centerTiles[24 - numCenter]);
                numCenter--;
            }
            players[i].sortTiles();
        }
    }

    void displayPlayersTiles(ofstream& ofs) {

        /* DO NOT MODIFY the output format! */

        for (int i = 0; i < numPlayers; ++i) {
            ofs << "Player " << i + 1 << "'s Tile : [ ";
            players[i].displayTiles(ofs);
            ofs << " ]";
            ofs << endl;
        }
    }

    bool makeGuess( /* TODO */) {

        /* TODO: check and return if the guess was correct */
        /* if the guess was correct, target tile should be revealed */

    }

    void play() {
        ofstream ofs;
        TileColor clue_color;
        int clue_number;
        bool turnContinue = false;

        ofs.open("output.txt");
        if (!ofs.is_open()) {
            cerr << "Outout File error!" << endl;
            exit(1);
        }

        /* DO NOT MODIFY the output format! */
        ofs << "Game Start!" << endl;

        while (true) {
            displayPlayersTiles(ofs);

            // Do not modify the output format
            ofs << "--------------------------------------------------------------------------------------------------" << endl;
            ofs << "Player " << currentPlayerIndex + 1 << "'s Turn: " << endl;
            Player& currentPlayer = players[currentPlayerIndex];

            if (!currentPlayer.allTilesRevealed() && !turnContinue) {

                /* TODO: make currentPlayer recieve one clue tile */
                // centerpop -> sort -> reveal
                /* DO NOT MODIFY the output format! */

                ofs << "Clue tile received: " << clue_number << (clue_color == TileColor::WHITE ? "w" : "b") << endl;
            }

            int targetPlayerIndex, targetTileIndex, guessedNumber = 0;
            targetPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
            Player& targetPlayer = players[targetPlayerIndex];

            /* TODO: guess number of target tile */

            /* DO NOT MODIFY the output format! */

            ofs << endl << "Target index is: " << targetTileIndex + 1 << ", Guessed number is: " << guessedNumber << endl;

            if (makeGuess( /* TODO */)) {

                // Do not modify the output format
                if (targetPlayer.allTilesRevealed()) {
                    ofs << "\nCorrect guess!\n";
                    ofs << "Player " << targetPlayerIndex + 1 << " has lost!" << endl;
                    ofs << "Player " << currentPlayerIndex + 1 << " is the winner!" << endl;
                    return;
                }
                ofs << "Correct guess! Player " << currentPlayerIndex + 1 << " gets another turn. \n" << endl;
                turnContinue = true;
            }
            else {

                /* DO NOT MODIFY the output format! */

                ofs << "Incorrect guess! Player " << currentPlayerIndex + 1 << " reveals a clue tile. \n" << endl;
                if (!currentPlayer.allTilesRevealed()) {

                    /* TODO: reveal one tile of currentPlayer */

                }
                turnContinue = false;
            }

            if (targetPlayer.allTilesRevealed()) {

                /* DO NOT MODIFY the output format! */

                ofs << "Player " << targetPlayerIndex + 1 << " has lost!" << endl;
                ofs << "Player " << currentPlayerIndex + 1 << " is the winner!" << endl;
                return;
            }

            if (!turnContinue) {
                currentPlayerIndex = (currentPlayerIndex + 1) % numPlayers;
            }
        }
        ofs.close();
    }
};

int main() {
    DaVinciCodeGame game(2);
    game.play();
    return 0;
}